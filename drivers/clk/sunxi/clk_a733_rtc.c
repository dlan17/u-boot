// SPDX-License-Identifier: (GPL-2.0+ OR MIT)

#include <clk-uclass.h>
#include <dm.h>
#include <clk/sunxi.h>
#include <dt-bindings/clock/sun60i-a733-rtc.h>
#include <linux/bitops.h>

static struct ccu_clk_gate a733_rtc_gates[] = {
	[CLK_IOSC]				= GATE_DUMMY,
	[CLK_OSC32K]			= GATE_DUMMY,
	[CLK_HOSC]				= GATE_DUMMY,
	[CLK_RTC_32K]			= GATE_DUMMY,
	[CLK_OSC32K_FANOUT]		= GATE_DUMMY,
	[CLK_HOSC_SERDES1]		= GATE(0x16c, BIT(5)),
	[CLK_HOSC_SERDES0]		= GATE(0x16c, BIT(4)),
	[CLK_HOSC_HDMI]			= GATE(0x16c, BIT(1)),
	[CLK_HOSC_UFS]			= GATE(0x16c, BIT(0)),
};

const struct ccu_desc a733_rtc_ccu_desc = {
	.gates = a733_rtc_gates,
	.num_gates = ARRAY_SIZE(a733_rtc_gates),
};
