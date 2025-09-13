#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>
#include <asm/arch/prcm.h>
#include <linux/delay.h>

#ifndef SUNXI_CPU_PLL_CFG_BASE
#define SUNXI_CPU_PLL_CFG_BASE 0
#endif

#ifdef CONFIG_XPL_BUILD
void clock_init_safe(void)
{
}

void clock_init_uart(void)
{
	void *const ccm = (void *)SUNXI_CCM_BASE;

	/* uart clock source is apb2 */
	writel(APB2_CLK_SRC_OSC24M|
	       APB2_CLK_RATE_N_1|
	       APB2_CLK_RATE_M(1),
	       ccm + CCU_A733_APB1_CFG);

	/* uart clock source */
	writel(APB2_CLK_SRC_OSC24M|
	       APB2_CLK_RATE_N_1|
	       APB2_CLK_RATE_M(1),
	       ccm + CCU_A733_APB_UART_CLK_CFG);

	/* open the clock for uart */
	setbits_le32(ccm + CCU_A733_UART_GATE_RESET,
		     1 << (CONFIG_CONS_INDEX - 1));

	/* deassert uart reset */
	setbits_le32(ccm + CCU_A733_UART_GATE_RESET,
		     1 << (RESET_SHIFT + CONFIG_CONS_INDEX - 1));
}

void clock_set_pll1(unsigned int clk)
{
	/* Do not support clocks < 288MHz as they need factor P */
	if (clk < 288000000)
		clk = 288000000;

	clk /= 24000000;
}

int clock_twi_onoff(int port, int state)
{
	return 0;
}
#endif /* CONFIG_XPL_BUILD */

/* PLL_PERIPH0 clock, used by the MMC driver */
unsigned int clock_get_pll6(void)
{
	void *const ccm = (void *)SUNXI_CCM_BASE;
	uint32_t rval = readl(ccm + CCU_H6_PLL6_CFG);
	int n = ((rval & CCM_PLL6_CTRL_N_MASK) >> CCM_PLL6_CTRL_N_SHIFT) + 1;
	int div1, m;

	if (IS_ENABLED(CONFIG_SUNXI_GEN_NCAT2) || IS_ENABLED(CONFIG_MACH_SUN60I_A733)) {
		div1 = ((rval & CCM_PLL6_CTRL_P0_MASK) >>
			CCM_PLL6_CTRL_P0_SHIFT) + 1;
		m = ((rval >> 1) & 1) + 1;
	} else {
		div1 = ((rval & CCM_PLL6_CTRL_DIV1_MASK) >>
			CCM_PLL6_CTRL_DIV1_SHIFT) + 1;
		if (IS_ENABLED(CONFIG_MACH_SUN50I_H6))
			m = 4;
		else
			m = 2;
	}

	return 24000000U * n / m / div1;
}
