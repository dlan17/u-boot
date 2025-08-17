// SPDX-License-Identifier: (GPL-2.0+ OR MIT)

#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <clk/sunxi.h>
#include <linux/bitops.h>

#include <dt-bindings/clock/sun60i-a733-ccu.h>
#include <dt-bindings/reset/sun60i-a733-ccu.h>

static struct ccu_clk_gate a733_gates[] = {
	[CLK_PLL_PERIPH0_200M]	= GATE_DUMMY,
	[CLK_APB1]			= GATE_DUMMY,
	[CLK_MBUS_GMAC0]	= GATE(0x05e4, BIT(11)),
	[CLK_BUS_MMC0]		= GATE(0x0d0c, BIT(0)),
	[CLK_BUS_MMC1]		= GATE(0x0d1c, BIT(0)),
	[CLK_BUS_MMC2]		= GATE(0x0d2c, BIT(0)),
	[CLK_BUS_UART0]		= GATE(0x0e00, BIT(0)),
	[CLK_BUS_UART1]		= GATE(0x0e04, BIT(0)),
	[CLK_BUS_UART2]		= GATE(0x0e08, BIT(0)),
	[CLK_BUS_UART3]		= GATE(0x0e0c, BIT(0)),
	[CLK_BUS_UART4]		= GATE(0x0e10, BIT(0)),
	[CLK_BUS_UART5]		= GATE(0x0e14, BIT(0)),
	[CLK_BUS_I2C0]		= GATE(0x0e80, BIT(0)),
	[CLK_BUS_I2C1]		= GATE(0x0e84, BIT(0)),
	[CLK_BUS_I2C2]		= GATE(0x0e88, BIT(0)),
	[CLK_BUS_I2C3]		= GATE(0x0e8c, BIT(0)),
	[CLK_SPI0]			= GATE(0x0f00, BIT(31)),
	[CLK_SPI1]			= GATE(0x0f08, BIT(31)),
	[CLK_BUS_SPI0]		= GATE(0x0f04, BIT(0)),
	[CLK_BUS_SPI1]		= GATE(0x0f0c, BIT(0)),
	[CLK_GMAC0_PHY]		= GATE(0x1410, BIT(31)),
	[CLK_BUS_GMAC0]		= GATE(0x141c, BIT(0)),
	[CLK_USB_OHCI0]		= GATE(0x1300, BIT(31)),
	[CLK_USB_OHCI1]		= GATE(0x1308, BIT(31)),
	[CLK_BUS_OHCI0]		= GATE(0x1304, BIT(0)),
	[CLK_BUS_OHCI1]		= GATE(0x130c, BIT(0)),
	[CLK_BUS_EHCI0]		= GATE(0x1304, BIT(4)),
	[CLK_BUS_EHCI1]		= GATE(0x130c, BIT(4)),
	[CLK_USB_GATE0]		= GATE(0x1304, BIT(8)),
	[CLK_USB_GATE1]		= GATE(0x130c, BIT(8)),
};

static struct ccu_reset a733_resets[] = {
	[RST_BUS_MMC0]		= RESET(0x0d0c, BIT(16)),
	[RST_BUS_MMC1]		= RESET(0x0d1c, BIT(16)),
	[RST_BUS_MMC2]		= RESET(0x0d2c, BIT(16)),
	[RST_BUS_UART0]		= RESET(0x0e00, BIT(16)),
	[RST_BUS_UART1]		= RESET(0x0e04, BIT(16)),
	[RST_BUS_UART2]		= RESET(0x0e08, BIT(16)),
	[RST_BUS_UART3]		= RESET(0x0e0c, BIT(16)),
	[RST_BUS_UART4]		= RESET(0x0e10, BIT(16)),
	[RST_BUS_UART5]		= RESET(0x0e14, BIT(16)),
	[RST_BUS_I2C0]		= RESET(0x0e80, BIT(16)),
	[RST_BUS_I2C1]		= RESET(0x0e84, BIT(16)),
	[RST_BUS_I2C2]		= RESET(0x0e8c, BIT(16)),
	[RST_BUS_I2C3]		= RESET(0x0e10, BIT(16)),
	[RST_BUS_SPI0]		= RESET(0x0f04, BIT(16)),
	[RST_BUS_SPI1]		= RESET(0x0f0c, BIT(16)),
	[RST_BUS_GMAC0]		= RESET(0x141c, BIT(16) | BIT(17)),
	[RST_USB_PHY0]		= RESET(0x1300, BIT(30)),
	[RST_USB_PHY1]		= RESET(0x1308, BIT(30)),
	[RST_BUS_OHCI0]		= RESET(0x1304, BIT(16)),
	[RST_BUS_OHCI1]		= RESET(0x130c, BIT(16)),
	[RST_BUS_EHCI0]		= RESET(0x1304, BIT(20)),
	[RST_BUS_EHCI1]		= RESET(0x130c, BIT(20)),
};

const struct ccu_desc a733_ccu_desc = {
	.gates	= a733_gates,
	.resets	= a733_resets,
	.num_gates = ARRAY_SIZE(a733_gates),
	.num_resets = ARRAY_SIZE(a733_resets),
};
