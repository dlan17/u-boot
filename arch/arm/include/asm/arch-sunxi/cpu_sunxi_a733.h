/*
 * SPDX-License-Identifier:	GPL-2.0+
 *
 */

#ifndef _SUNXI_CPU_SUNXI_A733_H
#define _SUNXI_CPU_SUNXI_A733_H

#define SUNXI_CCM_BASE			0x02002000

#define SUNXI_WDT_BASE			0x02050000
#define SUNXI_TIMER_BASE		0x02052000

#define SUNXI_TWI0_BASE			0x02510000
#define SUNXI_TWI1_BASE			0x02511000
#define SUNXI_TWI2_BASE			0x02512000
#define SUNXI_TWI3_BASE			0x02513000

#define SUNXI_SRAMC_BASE		0x03000000
/* SID address space starts at 0x03006000, but e-fuse is at offset 0x200 */
#define SUNXI_SIDC_BASE			0x03006000
#define SUNXI_SID_BASE			0x03006200
#define SUNXI_GIC400_BASE		0x03020000

#define SUNXI_MMC0_BASE			0x04020000
#define SUNXI_MMC1_BASE			0x04021000
#define SUNXI_MMC2_BASE			0x04022000

#define SUNXI_PRCM_BASE			0x07010000
#define SUNXI_R_WDOG_BASE		0x07020400
#define SUNXI_R_CPUCFG_BASE		0x07050000
#define SUNXI_R_TWI_BASE		0x07083000
#define SUNXI_RTC_BASE			0x07090000

#define SUNXI_CPUCFG_BASE		0x08815000 // FIXME
#define SUNXI_CPU_PLL_CFG_BASE		0x08870000

#ifndef __ASSEMBLY__
void sunxi_board_init(void);
void sunxi_reset(void);
int sunxi_get_sid(unsigned int *sid);
#endif

#endif /* _SUNXI_CPU_SUNXI_A733_H */
