// SPDX-License-Identifier: GPL-2.0
//
// Copyright (c) 2023 Andras Szemzo <szemzo.andras@gmail.com>

#include <linux/clk.h>
#include <linux/io.h>
//#include <linux/iommu.h>
#include <linux/mailbox_client.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_reserved_mem.h>
#include <linux/platform_device.h>
#include <linux/remoteproc.h>
#include <linux/reset.h>
#include <linux/soc/sunxi/sunxi_sram.h>
#include "remoteproc_internal.h"


#define SUN8I_RISCV_START_ADDR_REG	0x0204
#define SUN8I_RISCV_CLK_FREQ		600000000

struct sun8i_v853_rproc {
	void __iomem		*cfg_base;
	struct clk		*riscv_clk;
	struct clk		*riscv_clk_cfg;
	struct reset_control	*riscv_dbg;
	struct reset_control	*riscv_soft;
	struct reset_control	*riscv_cfg;
	struct reset_control	*riscv_clk_gate;
	struct mbox_client	client;
//	bool has_iommu;
	struct mbox_chan	*rx_chan;
	struct mbox_chan	*tx_chan;
};

static int sun8i_v853_rproc_start(struct rproc *rproc)
{
	struct sun8i_v853_rproc *riscv = rproc->priv;
	int ret;

	/* turn off clk and asserd cpu */
	ret = reset_control_assert(riscv->riscv_clk_gate);
	if (ret)
		return ret;

	ret = reset_control_deassert(riscv->riscv_dbg);
	if (ret)
		return ret;

	ret = reset_control_deassert(riscv->riscv_soft);
	if (ret)
		return ret;

	ret = clk_prepare_enable(riscv->riscv_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(riscv->riscv_clk_cfg);
	if (ret)
		goto err_riscv_clk_cfg;

	/* Reset e907 msgbox */

	ret = reset_control_deassert(riscv->riscv_cfg);
	if (ret)
		goto err_riscv_clk;

	writel(rproc->bootaddr, riscv->cfg_base + SUN8I_RISCV_START_ADDR_REG);

	/* turn on clk */
	reset_control_deassert(riscv->riscv_clk_gate);

	return 0;

err_riscv_clk:
	clk_disable_unprepare(riscv->riscv_clk_cfg);

err_riscv_clk_cfg:
	clk_disable_unprepare(riscv->riscv_clk);

	reset_control_assert(riscv->riscv_cfg);
	reset_control_assert(riscv->riscv_dbg);
	reset_control_assert(riscv->riscv_soft);
	reset_control_assert(riscv->riscv_clk_gate);

	return ret;
}

static int sun8i_v853_rproc_stop(struct rproc *rproc)
{
	struct sun8i_v853_rproc *riscv = rproc->priv;

	reset_control_assert(riscv->riscv_cfg);
	reset_control_assert(riscv->riscv_dbg);
	reset_control_assert(riscv->riscv_soft);
	reset_control_assert(riscv->riscv_clk_gate);

	clk_disable_unprepare(riscv->riscv_clk);
	clk_disable_unprepare(riscv->riscv_clk_cfg);

	return 0;
}

static void sun8i_v853_rproc_kick(struct rproc *rproc, int vqid)
{
	struct sun8i_v853_rproc *riscv = rproc->priv;
	long msg = vqid;
	int ret;

	dev_info(&rproc->dev, "sun8i_v853_rproc kick\n");

	ret = mbox_send_message(riscv->tx_chan, (void *)msg);
	if (ret)
		dev_warn(&rproc->dev, "Failed to kick: %d\n", ret);
}

static int sun8i_v853_rproc_mem_alloc(struct rproc *rproc,
				 struct rproc_mem_entry *mem)
{
	struct device *dev = &rproc->dev;
	void *va;

	dev_dbg(dev, "map memory: %pa+%zx\n", &mem->dma, mem->len);
	va = ioremap_wc(mem->dma, mem->len);
	if (!va) {
		dev_err(dev, "Unable to map memory region: %pa+%zx\n",
			&mem->dma, mem->len);
		return -ENOMEM;
	}

	/* Update memory entry va */
	mem->va = va;

	return 0;
}

static int sun8i_v853_rproc_mem_release(struct rproc *rproc,
				   struct rproc_mem_entry *mem)
{
	dev_dbg(&rproc->dev, "unmap memory: %pa\n", &mem->dma);
	iounmap(mem->va);

	return 0;
}


static int sun8i_v853_rproc_parse_fw(struct rproc *rproc, const struct firmware *fw)
{
	struct device *dev = rproc->dev.parent;
	struct device_node *np = dev->of_node;
	struct rproc_mem_entry *mem;
	struct reserved_mem *rmem;
	struct of_phandle_iterator it;
	int index = 0;

	of_phandle_iterator_init(&it, np, "memory-region", NULL, 0);
	while (of_phandle_iterator_next(&it) == 0) {
		rmem = of_reserved_mem_lookup(it.node);
		if (!rmem) {
			of_node_put(it.node);
			dev_err(dev, "unable to acquire memory-region\n");
			return -EINVAL;
		}

		/*  No need to map vdev buffer */
		if (strcmp(it.node->name, "vdev0buffer")) {
			/* Register memory region */
			mem = rproc_mem_entry_init(dev, NULL,
						   (dma_addr_t)rmem->base,
						    rmem->size, rmem->base,
						    sun8i_v853_rproc_mem_alloc,
						    sun8i_v853_rproc_mem_release,
						    it.node->name);
		} else {
			/* Register reserved memory for vdev buffer allocation */
			mem = rproc_of_resm_mem_entry_init(dev, index,
							   rmem->size,
							   rmem->base,
							   it.node->name);
		}

		if (!mem) {
			of_node_put(it.node);
			return -ENOMEM;
		}

		rproc_add_carveout(rproc, mem);
		index++;
	}

	return rproc_elf_load_rsc_table(rproc, fw);
//	return 0;
}

static const struct rproc_ops sun8i_v853_rproc_ops = {
	.start			= sun8i_v853_rproc_start,
	.stop			= sun8i_v853_rproc_stop,
	.kick			= sun8i_v853_rproc_kick,
	.load			= rproc_elf_load_segments,
	.parse_fw		= sun8i_v853_rproc_parse_fw,
	.find_loaded_rsc_table	= rproc_elf_find_loaded_rsc_table,
	.sanity_check		= rproc_elf_sanity_check,
	.get_boot_addr		= rproc_elf_get_boot_addr,
};

static void sun8i_v853_rproc_mbox_rx_callback(struct mbox_client *client, void *msg)
{
	struct rproc *rproc = dev_get_drvdata(client->dev);

	rproc_vq_interrupt(rproc, (long)msg);
}

static void sun8i_v853_rproc_mbox_free(void *data)
{
	struct sun8i_v853_rproc *riscv = data;

	if (!IS_ERR_OR_NULL(riscv->tx_chan))
		mbox_free_channel(riscv->tx_chan);
	if (!IS_ERR_OR_NULL(riscv->rx_chan))
		mbox_free_channel(riscv->rx_chan);
}

static int sun8i_v853_rproc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct sun8i_v853_rproc *riscv;
	const char *firmware_name;
	struct rproc *rproc;
	int ret;
	u32 freq;


	firmware_name = NULL;
	of_property_read_string(np, "firmware-name", &firmware_name);
	rproc = devm_rproc_alloc(dev, dev_name(dev), &sun8i_v853_rproc_ops,
				 firmware_name, sizeof(struct sun8i_v853_rproc));
	if (!rproc)
		return -ENOMEM;

	dev_set_drvdata(dev, rproc);
	riscv = rproc->priv;

	/* Manually start the rproc */
	rproc->auto_boot = false;


	riscv->cfg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(riscv->cfg_base))
		return -EINVAL;

	riscv->riscv_clk = devm_clk_get(dev, "riscv");
	if (IS_ERR(riscv->riscv_clk))
		return dev_err_probe(dev, PTR_ERR(riscv->riscv_clk),
				     "Failed to get riscv clock\n");

	riscv->riscv_clk_cfg = devm_clk_get(dev, "cfg");
	if (IS_ERR(riscv->riscv_clk_cfg))
		return dev_err_probe(dev, PTR_ERR(riscv->riscv_clk_cfg),
				     "Failed to get riscv cfg clock\n");

	freq = SUN8I_RISCV_CLK_FREQ;
	of_property_read_u32(np, "clock-frequency", &freq);
	ret = clk_set_rate(riscv->riscv_clk, freq);
	if (ret)
		return dev_err_probe(dev, ret,
				     "Failed to set clock frequency\n");


	riscv->riscv_dbg = devm_reset_control_get_exclusive(dev, "dbg");
	if (IS_ERR(riscv->riscv_dbg))
		return dev_err_probe(dev, PTR_ERR(riscv->riscv_dbg),
				     "Failed to get dbg reset\n");

	riscv->riscv_soft = devm_reset_control_get_exclusive(dev, "soft");
	if (IS_ERR(riscv->riscv_soft))
		return dev_err_probe(dev, PTR_ERR(riscv->riscv_soft),
				     "Failed to get soft reset\n");

	riscv->riscv_cfg = devm_reset_control_get_exclusive(dev, "cfg");
	if (IS_ERR(riscv->riscv_cfg))
		return dev_err_probe(dev, PTR_ERR(riscv->riscv_cfg),
				     "Failed to get cfg reset\n");

	riscv->riscv_clk_gate = devm_reset_control_get_exclusive(dev, "clk_gate");
	if (IS_ERR(riscv->riscv_clk_gate))
		return dev_err_probe(dev, PTR_ERR(riscv->riscv_clk_gate),
				     "Failed to get clk_gate\n");

	riscv->client.dev = dev;
	riscv->client.rx_callback = sun8i_v853_rproc_mbox_rx_callback;

	ret = devm_add_action(dev, sun8i_v853_rproc_mbox_free, riscv);
	if (ret)
		return ret;

	riscv->rx_chan = mbox_request_channel_byname(&riscv->client, "rx");
	if (IS_ERR(riscv->rx_chan))
		return dev_err_probe(dev, PTR_ERR(riscv->rx_chan),
				     "Failed to request RX channel\n");

	riscv->tx_chan = mbox_request_channel_byname(&riscv->client, "tx");
	if (IS_ERR(riscv->tx_chan))
		return dev_err_probe(dev, PTR_ERR(riscv->tx_chan),
				     "Failed to request TX channel\n");

	ret = devm_rproc_add(dev, rproc);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to register rproc\n");

	return 0;
}

static const struct of_device_id sun8i_v853_rproc_of_match[] = {
	{ .compatible = "allwinner,sun8i-v853-rproc" },
	{}
};
MODULE_DEVICE_TABLE(of, sun8i_v853_rproc_of_match);

static struct platform_driver sun8i_v853_rproc_driver = {
	.probe		= sun8i_v853_rproc_probe,
	.driver		= {
		.name		= "sun8i-v853-rproc",
		.of_match_table	= sun8i_v853_rproc_of_match,
	},
};
module_platform_driver(sun8i_v853_rproc_driver);

MODULE_AUTHOR("Andras Szemzo <szemzo.andras@gmail.com>");
MODULE_DESCRIPTION("Allwinner sun8i-v853 remoteproc driver");
MODULE_LICENSE("GPL");
