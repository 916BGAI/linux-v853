// SPDX-License-Identifier: GPL-2.0
/*
 * Allwinner V851s SoC pinctrl driver.
 *
 * Copyright (c) 2016-2021  weidonghui <weidonghui@allwinnertech.com>
 * Copyright (c) 2023 Andras Szemzo <szemzo.andras@gmail.com>
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/io.h>

#include "pinctrl-sunxi.h"

/* Pin banks are: A C D E F G H I */
static const struct sunxi_desc_pin sun8i_v853_pins[] = {

	/* bank A */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_a"),		/* CKOP */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D8 */
		SUNXI_FUNCTION(0x5, "test"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_a"),		/* CKON */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D9 */
		SUNXI_FUNCTION(0x5, "test"),		/* test */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_a"),		/* D1N */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D10 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_a"),		/* D1P */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D11 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_a"),		/* D0P */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D12 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_a"),		/* D0N */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D13 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* D0N/D2N */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D14 */
		SUNXI_FUNCTION(0x4, "i2c1"),		/* SCK */
		SUNXI_FUNCTION(0x5, "pwm0"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* D0P/D2P */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D15 */
		SUNXI_FUNCTION(0x4, "i2c1"),		/* SDA */
		SUNXI_FUNCTION(0x5, "pwm1"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* D1N/D3N */
		SUNXI_FUNCTION(0x3, "i2c4"),		/* SCK */
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x5, "pwm2"),
		SUNXI_FUNCTION(0x6, "uart2"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* D1P/D3P */
		SUNXI_FUNCTION(0x3, "i2c4"),		/* SDA */
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x5, "pwm3"),
		SUNXI_FUNCTION(0x6, "uart2"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_b"),		/* CKON */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* HSYNC */
		SUNXI_FUNCTION(0x4, "csi"),		/* MCLK0 */
		SUNXI_FUNCTION(0x5, "i2c0"),		/* SCK */
		SUNXI_FUNCTION(0x6, "clk"),		/* FANOUT0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi_b"),		/* CKOP */
		SUNXI_FUNCTION(0x3, "ncsi"),		/* VSYNC */
		SUNXI_FUNCTION(0x4, "csi"),		/* MCLK1 */
		SUNXI_FUNCTION(0x5, "i2c0"),		/* SDA */
		SUNXI_FUNCTION(0x6, "clk"),		/* FANOUT1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 11)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 12),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D0 */
		SUNXI_FUNCTION(0x4, "csi"),		/* MCLK0 */
		SUNXI_FUNCTION(0x5, "uart0"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 12)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 13),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D1 */
		SUNXI_FUNCTION(0x4, "csi"),		/* MCLK1 */
		SUNXI_FUNCTION(0x5, "uart0"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 13)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 14),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D2 */
		SUNXI_FUNCTION(0x4, "i2c1"),		/* SCK */
		SUNXI_FUNCTION(0x5, "clk"),		/* FANOUT0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 14)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 15),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D3 */
		SUNXI_FUNCTION(0x4, "i2c1"),		/* SDA */
		SUNXI_FUNCTION(0x5, "clk"),		/* FANOUT1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 15)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 16),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D4 */
		SUNXI_FUNCTION(0x4, "i2c0"),		/* SCK */
		SUNXI_FUNCTION(0x5, "uart3"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 16)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 17),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D5 */
		SUNXI_FUNCTION(0x4, "i2c0"),		/* SDA */
		SUNXI_FUNCTION(0x5, "uart3"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 17)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 18),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D6 */
		SUNXI_FUNCTION(0x4, "wiegand"),		/* D0	*/
		SUNXI_FUNCTION(0x5, "uart3"),		/* RTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 18)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 19),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* D7 */
		SUNXI_FUNCTION(0x4, "wiegand"),		/* D1	*/
		SUNXI_FUNCTION(0x5, "uart3"),		/* CTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 19)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 20),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* MCLK */
		SUNXI_FUNCTION(0x4, "csi"),		/* SM_VS */
		SUNXI_FUNCTION(0x5, "tcon"),		/* TRIG */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 20)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 21),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "ncsi"),		/* PCLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 21)),
	/* bank C */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* CLK */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* CLK */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* CS0 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* CMD */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CS0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* MOSI_IO0 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D2 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MOSI */
		SUNXI_FUNCTION(0x5, "boot_sel0"),	/* SEL0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* MOSI_IO1 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D1 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MISO */
		SUNXI_FUNCTION(0x5, "boot_sel1"),	/* SEL1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* WP_IO2 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D0 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* WP */
		SUNXI_FUNCTION(0x5, "pwm4"),
		SUNXI_FUNCTION(0x6, "i2c1"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* HOLD_IO3 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D3 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* HOLD */
		SUNXI_FUNCTION(0x5, "pwm4"),
		SUNXI_FUNCTION(0x6, "i2c1"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* IO4 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D4 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CSI */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* IO5 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D5 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* IO6 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D6 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* IO7 */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* D7 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "spif"),		/* DQS */
		SUNXI_FUNCTION(0x3, "sdc2"),		/* DS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "sdc2"),		/* RTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 11)),
	/* bank D */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D2 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D3 */
		SUNXI_FUNCTION(0x3, "pwm0"),
		SUNXI_FUNCTION(0x4, "emac"),		/* RXD1 */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D0N */
		SUNXI_FUNCTION(0x6, "spi1"),		/* CS0/CSX */
		SUNXI_FUNCTION(0x7, "emac"),		/* TXD0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D4 */
		SUNXI_FUNCTION(0x3, "pwm1"),
		SUNXI_FUNCTION(0x4, "emac"),		/* RXD0 */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D1P */
		SUNXI_FUNCTION(0x6, "spi1"),		/* CLK/SCLK */
		SUNXI_FUNCTION(0x7, "emac"),		/* TXD1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D5 */
		SUNXI_FUNCTION(0x3, "pwm2"),
		SUNXI_FUNCTION(0x4, "emac"),		/* CRS_DV */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D1N */
		SUNXI_FUNCTION(0x6, "spi1"),		/* MOSI/SDO */
		SUNXI_FUNCTION(0x7, "emac"),		/* RXER */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D6 */
		SUNXI_FUNCTION(0x3, "pwm3"),
		SUNXI_FUNCTION(0x4, "emac"),		/* RXER */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D1P */
		SUNXI_FUNCTION(0x6, "spi1"),		/* MISO/SDI/TE/DCX */
		SUNXI_FUNCTION(0x7, "emac"),		/* CRS_DV */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D7 */
		SUNXI_FUNCTION(0x3, "pwm4"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXD1 */
		SUNXI_FUNCTION(0x5, "dsi"),		/* CKN */
		SUNXI_FUNCTION(0x6, "spi1"),		/* HOLD/DCX/WRX */
		SUNXI_FUNCTION(0x7, "emac"),		/* RXD1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D10 */
		SUNXI_FUNCTION(0x3, "pwm5"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXD0 */
		SUNXI_FUNCTION(0x5, "dsi"),		/* CKP */
		SUNXI_FUNCTION(0x6, "spi1"),		/* WP/TE */
		SUNXI_FUNCTION(0x7, "emac"),		/* RXD */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D11 */
		SUNXI_FUNCTION(0x3, "pwm6"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXCK */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D2N */
		SUNXI_FUNCTION(0x6, "spi1"),		/* CS1 */
		SUNXI_FUNCTION(0x7, "emac"),		/* MDC */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D12 */
		SUNXI_FUNCTION(0x3, "pwm7"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXEN */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D13 */
		SUNXI_FUNCTION(0x3, "pwm8"),
		SUNXI_FUNCTION(0x5, "dsi"),		/* D2P */
		SUNXI_FUNCTION(0x7, "emac"),		/* MDIO */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D14 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* MCLK */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D3N */
		SUNXI_FUNCTION(0x7, "emac"),		/* TXEN */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D15 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* BCLK */
		SUNXI_FUNCTION(0x5, "dsi"),		/* D3P */
		SUNXI_FUNCTION(0x7, "emac"),		/* TXCKk */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 11)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 12),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D18 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* LCLK */
		SUNXI_FUNCTION(0x5, "dmic"),		/* DATA3 */
		SUNXI_FUNCTION(0x7, "pwm11"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 12)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 13),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D19 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* DOUT0 */
		SUNXI_FUNCTION(0x5, "dmic"),		/* DATA2 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 13)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 14),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D20 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* DOUT1 */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* DIN1 */
		SUNXI_FUNCTION(0x5, "dmic"),		/* DATA1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 14)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 15),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D21 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* DOUT2 */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* DIN2 */
		SUNXI_FUNCTION(0x5, "dmic"),		/* DATA0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 15)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 16),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D22 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* DOUT3 */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* DIN3 */
		SUNXI_FUNCTION(0x5, "dmic"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 16)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 17),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* D23 */
		SUNXI_FUNCTION(0x3, "i2s1"),		/* DIN0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 17)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 18),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* CLK */
		SUNXI_FUNCTION(0x4, "emac"),		/* EPHY_25M */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CLK */
		SUNXI_FUNCTION(0x6, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x7, "uart2"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 18)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 19),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* DE */
		SUNXI_FUNCTION(0x3, "pwm9"),
		SUNXI_FUNCTION(0x4, "tcon"),		/* TRIG */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MOSI */
		SUNXI_FUNCTION(0x6, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x7, "uart2"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 19)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 20),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* HSYNC */
		SUNXI_FUNCTION(0x3, "pwm10"),
		SUNXI_FUNCTION(0x4, "emac"),		/* MDC */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MISO */
		SUNXI_FUNCTION(0x6, "i2c2"),		/* SCK */
		SUNXI_FUNCTION(0x7, "uart2"),		/* RTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 20)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 21),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd"),		/* VSYNC */
		SUNXI_FUNCTION(0x4, "emac"),		/* MDIO */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CS0 */
		SUNXI_FUNCTION(0x6, "i2c2"),		/* SDA */
		SUNXI_FUNCTION(0x7, "uart2"),		/* CTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 21)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 22),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm9"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 22)),
	/* bank E */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* PCLK */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXD/RXD1 */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* MCLK */
		SUNXI_FUNCTION(0x5, "pwm0"),
		SUNXI_FUNCTION(0x6, "sdc1"),		/* CLK */
		SUNXI_FUNCTION(0x7, "uart3"),		/* TX */
		SUNXI_FUNCTION(0x8, "i2c3"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* MCLK */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXCK/TXCK */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* BCLK */
		SUNXI_FUNCTION(0x5, "pwm1"),
		SUNXI_FUNCTION(0x6, "sdc1"),		/* CMD */
		SUNXI_FUNCTION(0x7, "uart3"),		/* RX */
		SUNXI_FUNCTION(0x8, "i2c3"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* HSYNC */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXCTL/CRS_DV */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* LCLK */
		SUNXI_FUNCTION(0x5, "pwm2"),
		SUNXI_FUNCTION(0x6, "sdc1"),		/* D0 */
		SUNXI_FUNCTION(0x7, "uart3"),		/* CTS */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* VSYNC */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXD0 */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* DIN0 */
		SUNXI_FUNCTION(0x5, "pwm3"),
		SUNXI_FUNCTION(0x6, "sdc1"),		/* D1 */
		SUNXI_FUNCTION(0x7, "uart3"),		/* RTS */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D0 */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXD0 */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* DOUT0 */
		SUNXI_FUNCTION(0x5, "pwm4"),
		SUNXI_FUNCTION(0x6, "sdc1"),		/* D2 */
		SUNXI_FUNCTION(0x7, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x8, "i2c0"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D1 */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXD1 */
		SUNXI_FUNCTION(0x5, "pwm5"),
		SUNXI_FUNCTION(0x6, "sdc1"),		/* D3 */
		SUNXI_FUNCTION(0x7, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x8, "i2c0"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D2 */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXCTL/TXEN */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D2 */
		SUNXI_FUNCTION(0x5, "pwm6"),
		SUNXI_FUNCTION(0x6, "uart1"),		/* TX */
		SUNXI_FUNCTION(0x8, "i2c4"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D3 */
		SUNXI_FUNCTION(0x3, "emac"),		/* CLKIN/RXER */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D15 */
		SUNXI_FUNCTION(0x5, "pwm7"),
		SUNXI_FUNCTION(0x6, "uart1"),		/* TX */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* DOUT0 */
		SUNXI_FUNCTION(0x8, "i2c4"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D4 */
		SUNXI_FUNCTION(0x3, "emac"),		/* MDC */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D18 */
		SUNXI_FUNCTION(0x5, "pwm8"),
		SUNXI_FUNCTION(0x6, "wiegand"),		/* D0 */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* DIN0 */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D5 */
		SUNXI_FUNCTION(0x3, "emac"),		/* MDIO */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D19 */
		SUNXI_FUNCTION(0x5, "pwm9"),
		SUNXI_FUNCTION(0x6, "wiegand"),		/* D1 */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* LRCK */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D6 */
		SUNXI_FUNCTION(0x3, "emac"),		/* EPHY_25M */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D20 */
		SUNXI_FUNCTION(0x5, "pwm10"),
		SUNXI_FUNCTION(0x6, "uart2"),		/* RTS */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* BCLK */
		SUNXI_FUNCTION(0x8, "wiegand"),		/* D0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D7 */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXD3 */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D21 */
		SUNXI_FUNCTION(0x5, "csi"),		/* SM_VS */
		SUNXI_FUNCTION(0x6, "uart2"),		/* CTS */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* MCLK */
		SUNXI_FUNCTION(0x8, "wiegand"),		/* D1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 11)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 12),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D8 */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXD2 */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D22 */
		SUNXI_FUNCTION(0x5, "csi"),		/* MCLK0 */
		SUNXI_FUNCTION(0x6, "uart2"),		/* TX */
		SUNXI_FUNCTION(0x7, "uart3"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 12)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 13),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D9 */
		SUNXI_FUNCTION(0x3, "emac"),		/* RXCK */
		SUNXI_FUNCTION(0x4, "lcd"),		/* D23 */
		SUNXI_FUNCTION(0x5, "csi"),		/* MCLK1 */
		SUNXI_FUNCTION(0x6, "uart2"),		/* RX */
		SUNXI_FUNCTION(0x7, "uart3"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 13)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 14),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D10 */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXD3 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 14)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 15),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi"),		/* D11 */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXD2 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 15)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 16),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "i2c0"),		/* SCK */
		SUNXI_FUNCTION(0x3, "i2c4"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 16)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 17),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "i2c0"),		/* SDA */
		SUNXI_FUNCTION(0x3, "i2c4"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 17)),
	/* bank F */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc0"),		/* D1 */
		SUNXI_FUNCTION(0x3, "jtag"),		/* MS */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CLK */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CLK */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* MS */
		SUNXI_FUNCTION(0x7, "cpu"),		/* BIST0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc0"),		/* D0 */
		SUNXI_FUNCTION(0x3, "jtag"),		/* DI */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MOSI */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MOSI */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* DI */
		SUNXI_FUNCTION(0x7, "cpu"),		/* BIST1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc0"),		/* CLK */
		SUNXI_FUNCTION(0x3, "uart0"),		/* TX */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MISO */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MISO */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc0"),		/* CMD */
		SUNXI_FUNCTION(0x3, "jtag"),		/* DO */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CSO */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CS0 */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* DO */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc0"),		/* D3 */
		SUNXI_FUNCTION(0x3, "uart0"),		/* RX */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CS1 */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CS1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc0"),		/* D2 */
		SUNXI_FUNCTION(0x3, "jtag"),		/* CK */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* CK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "dbg_clk"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 6)),
	/* bank G */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc1"),		/* CLK */
		SUNXI_FUNCTION(0x3, "lcd"),		/* D0 */
		SUNXI_FUNCTION(0x4, "uart3"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc1"),		/* CMD */
		SUNXI_FUNCTION(0x3, "lcd"),		/* D1 */
		SUNXI_FUNCTION(0x4, "uart3"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc1"),		/* D0 */
		SUNXI_FUNCTION(0x3, "lcd"),		/* D8 */
		SUNXI_FUNCTION(0x4, "uart3"),		/* CTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc1"),		/* D1 */
		SUNXI_FUNCTION(0x3, "lcd"),		/* D9 */
		SUNXI_FUNCTION(0x4, "uart3"),		/* RTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc1"),		/* D2 */
		SUNXI_FUNCTION(0x3, "lcd"),		/* D16 */
		SUNXI_FUNCTION(0x4, "uart1"),		/* RTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "sdc1"),		/* D3 */
		SUNXI_FUNCTION(0x3, "lcd"),		/* D17 */
		SUNXI_FUNCTION(0x4, "uart1"),		/* CTS */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "i2c4"),		/* SCK */
		SUNXI_FUNCTION(0x3, "clk"),		/* FANOUT0 */
		SUNXI_FUNCTION(0x4, "uart1"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(G, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "i2c4"),		/* SDA */
		SUNXI_FUNCTION(0x3, "clk"),		/* FANOUT1 */
		SUNXI_FUNCTION(0x4, "uart1"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 7)),
	/* bank H */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm0"),
		SUNXI_FUNCTION(0x3, "i2s0"),		/* MCLK */
		SUNXI_FUNCTION(0x4, "spi1"),		/* CLK */
		SUNXI_FUNCTION(0x5, "uart3"),		/* TX */
		SUNXI_FUNCTION(0x6, "dmic"),		/* DATA3 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm1"),
		SUNXI_FUNCTION(0x3, "i2s0"),		/* BCLK */
		SUNXI_FUNCTION(0x4, "spi1"),		/* MOSI */
		SUNXI_FUNCTION(0x5, "uart3"),		/* RX */
		SUNXI_FUNCTION(0x6, "dmic"),		/* DATA2 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm2"),
		SUNXI_FUNCTION(0x3, "i2s0"),		/* LRCK */
		SUNXI_FUNCTION(0x4, "spi1"),		/* MISO */
		SUNXI_FUNCTION(0x5, "uart3"),		/* CTS */
		SUNXI_FUNCTION(0x6, "dmic"),		/* DATA1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm3"),
		SUNXI_FUNCTION(0x3, "i2s0"),		/* DOUT0 */
		SUNXI_FUNCTION(0x4, "spi1"),		/* CS0 */
		SUNXI_FUNCTION(0x5, "uart3"),		/* RTS */
		SUNXI_FUNCTION(0x6, "dmic"),		/* DATA0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm4"),
		SUNXI_FUNCTION(0x3, "i2s0"),		/* DIN0 */
		SUNXI_FUNCTION(0x4, "spi1"),		/* CS1 */
		SUNXI_FUNCTION(0x5, "clk"),		/* FANOUT2 */
		SUNXI_FUNCTION(0x6, "dmic"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm5"),
		SUNXI_FUNCTION(0x3, "emac"),		/* RXD1 */
		SUNXI_FUNCTION(0x4, "i2c2"),		/* SCK */
		SUNXI_FUNCTION(0x5, "uart2"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm6"),
		SUNXI_FUNCTION(0x3, "emac"),		/* RXD0 */
		SUNXI_FUNCTION(0x4, "i2c2"),		/* SDA */
		SUNXI_FUNCTION(0x5, "uart2"),		/* RX */
		SUNXI_FUNCTION(0x6, "i2s1"),		/* MCLK */
		SUNXI_FUNCTION(0x7, "dmic"),		/* DATA3 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm7"),
		SUNXI_FUNCTION(0x3, "emac"),		/* CRS_DV */
		SUNXI_FUNCTION(0x4, "uart0"),		/* TX */
		SUNXI_FUNCTION(0x5, "uart2"),		/* RTS */
		SUNXI_FUNCTION(0x6, "i2s1"),		/* BCLK */
		SUNXI_FUNCTION(0x7, "dmic"),		/* DATA2 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm8"),
		SUNXI_FUNCTION(0x3, "emac"),		/* RXER */
		SUNXI_FUNCTION(0x4, "uart0"),		/* RX */
		SUNXI_FUNCTION(0x5, "uart2"),		/* CTS */
		SUNXI_FUNCTION(0x6, "i2s1"),		/* LRCK */
		SUNXI_FUNCTION(0x7, "dmic"),		/* DATA1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm9"),
		SUNXI_FUNCTION(0x3, "emac"),		/* TXD1 */
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x5, "uart0"),		/* TX */
		SUNXI_FUNCTION(0x6, "i2s1"),		/* DIN0 */
		SUNXI_FUNCTION(0x7, "dmic"),		/* DATA0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm10"),
		SUNXI_FUNCTION(0x3, "emac"),		/* TXD0 */
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x5, "uart0"),		/* RX */
		SUNXI_FUNCTION(0x6, "i2s1"),		/* DOUT0 */
		SUNXI_FUNCTION(0x7, "dmic"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* MS */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXCK */
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* MS */
		SUNXI_FUNCTION(0x5, "i2c2"),		/* SCK */
		SUNXI_FUNCTION(0x6, "spi3"),		/* CLK */
		SUNXI_FUNCTION(0x7, "clk"),		/* FANOUT0 */
		SUNXI_FUNCTION(0x8, "pwm4"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 11)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 12),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* CK */
		SUNXI_FUNCTION(0x3, "emac"),		/* TXEN */
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* CK */
		SUNXI_FUNCTION(0x5, "i2c2"),		/* SDA */
		SUNXI_FUNCTION(0x6, "spi3"),		/* MOSI */
		SUNXI_FUNCTION(0x7, "clk"),		/* FANOUT1 */
		SUNXI_FUNCTION(0x8, "pwm5"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 12)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 13),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* DO */
		SUNXI_FUNCTION(0x3, "emac"),		/* MDC */
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* DO */
		SUNXI_FUNCTION(0x5, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x6, "spi3"),		/* MISO */
		SUNXI_FUNCTION(0x7, "wiegand"),		/* D0 */
		SUNXI_FUNCTION(0x8, "pwm6"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 13)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 14),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* DI */
		SUNXI_FUNCTION(0x3, "emac"),		/* MDIO */
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* DI */
		SUNXI_FUNCTION(0x5, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x6, "spi3"),		/* CS0 */
		SUNXI_FUNCTION(0x7, "wiegand"),		/* D1 */
		SUNXI_FUNCTION(0x8, "pwm7"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 14)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 15),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "clk"),		/* FANOUT2 */
		SUNXI_FUNCTION(0x3, "ephy_25m"),	/* EPHY_25M */
		SUNXI_FUNCTION(0x6, "spi3"),		/* CS1 */
		SUNXI_FUNCTION(0x8, "pwm8"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 6, 15)),
	/* bank I */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(I, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* MCLK0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 7, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(I, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* SM_HS */
		SUNXI_FUNCTION(0x4, "spi2"),		/* CLK */
		SUNXI_FUNCTION(0x5, "i2c1"),		/* SCK */
		SUNXI_FUNCTION(0x6, "i2c4"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 7, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(I, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "csi"),		/* SM_VS */
		SUNXI_FUNCTION(0x3, "tcon"),		/* TRIG */
		SUNXI_FUNCTION(0x4, "spi2"),		/* MOSI */
		SUNXI_FUNCTION(0x5, "i2c1"),		/* SDA */
		SUNXI_FUNCTION(0x6, "i2c4"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 7, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(I, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x4, "spi2"),		/* MISO */
		SUNXI_FUNCTION(0x5, "i2c0"),		/* SCA */
		SUNXI_FUNCTION(0x6, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x7, "clk"),		/* FANOUT0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 7, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(I, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x4, "spi2"),		/* CS0 */
		SUNXI_FUNCTION(0x5, "i2c0"),		/* SDA */
		SUNXI_FUNCTION(0x6, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x7, "clk"),		/* FANOUT1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 7, 4)),
};

static const unsigned int sun8i_v853_irq_bank_map[] = { 0, 2, 3, 4, 5, 6, 7, 8 };

static const struct sunxi_pinctrl_desc sun8i_v853_pinctrl_data = {
	.pins = sun8i_v853_pins,
	.npins = ARRAY_SIZE(sun8i_v853_pins),
	.pin_base = 0,
	.irq_banks = ARRAY_SIZE(sun8i_v853_irq_bank_map),
	.irq_bank_map = sun8i_v853_irq_bank_map,
	.io_bias_cfg_variant = BIAS_VOLTAGE_PIO_POW_MODE_CTL,
};

static int sun8i_v853_pinctrl_probe(struct platform_device *pdev)
{
	unsigned long variant = (unsigned long)of_device_get_match_data(&pdev->dev);

	return sunxi_pinctrl_init_with_variant(pdev, &sun8i_v853_pinctrl_data, variant);
}

static const struct of_device_id sun8i_v853_pinctrl_match[] = {
	{
		.compatible = "allwinner,sun8i-v853-pinctrl",
		.data = (void *)PINCTRL_SUN20I_D1
	},
	{}
};

static struct platform_driver sun8i_v853_pinctrl_driver = {
	.probe	= sun8i_v853_pinctrl_probe,
	.driver	= {
		.name		= "sun8i-v853-pinctrl",
		.of_match_table	= sun8i_v853_pinctrl_match,
	},
};
builtin_platform_driver(sun8i_v853_pinctrl_driver);
