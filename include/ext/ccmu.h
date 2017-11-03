/*
******************************************
*
* File    : cmmu.h
* By      : dianguai14
* Version : v1.0
* Date    : 2013-06-25
* Descript: define of ccmu module
******************************************
*/
#ifndef __CCMU_H
#define __CCMU_H

/*******************CCM PLL************************/
#define CCM_PLL_CPU_REG  			(CCM_BASE+0x000)
#define CCM_PLL_AUDIO_REG  			(CCM_BASE+0x008)
#define CCM_PLL_VIDEO_REG 			(CCM_BASE+0x010)
#define CCM_PLL_VE_REG    			(CCM_BASE+0x018)
#define CCM_PLL_DDR_REG     		(CCM_BASE+0x020)
#define CCM_PLL_PERH_REG  			(CCM_BASE+0x028)

#define CCM_CPUCLK_CFG_REG			(CCM_BASE+0x050)
#define CCM_AHB_APB_RATIO_REG		(CCM_BASE+0x054)

#define CCM_AHB_CLK_GAT_REG0		(CCM_BASE+0x060)
#define CCM_AHB_CLK_GAT_REG1		(CCM_BASE+0x064)
#define CCM_APB_CLK_GAT_REG			(CCM_BASE+0x068)

#define CCM_SDC0_CLK_REG			(CCM_BASE+0x088)
#define CCM_SDC1_CLK_REG			(CCM_BASE+0x08c)
#define CCM_DAUDIO_CLK_REG			(CCM_BASE+0x0b0)
#define CCM_SPDIF_CLK_REG			(CCM_BASE+0x0b4)
#define CCM_CIR_CLK_REG				(CCM_BASE+0x0b8)

#define CCM_USBPHY_CFG_REG			(CCM_BASE+0x0cc)

#define CCM_DRAMCLK_CFG_REG			(CCM_BASE+0x100)
#define CCM_DEBE_CLK_REG			(CCM_BASE+0x104)
#define CCM_DEFE_CLK_REG			(CCM_BASE+0x10c)
#define CCM_LCD_CLK_REG				(CCM_BASE+0x118)
#define CCM_DEITLA_CLK_REG			(CCM_BASE+0x11c)

#define CCM_CSI_CLK_REG				(CCM_BASE+0x134)

#define CCM_VE_CLK_REG				(CCM_BASE+0x13c)
#define CCM_ADDA_CLK_REG			(CCM_BASE+0x140)

#define CCM_AVS_CLK_REG				(CCM_BASE+0x144)
#define CCM_PLL_LKTM_REG			(CCM_BASE+0x200)
#define CCM_PLLCPU_LKTM_REG			(CCM_BASE+0x204)

#define CCM_PPLCPU_BIAS_REG			(CCM_BASE+0x220)
#define CCM_PPLAUDIO_BIAS_REG		(CCM_BASE+0x224)
#define CCM_PPLVIDEO_BIAS_REG		(CCM_BASE+0x228)
#define CCM_PPLVE_BIAS_REG			(CCM_BASE+0x22c)
#define CCM_PPLDDR_BIAS_REG			(CCM_BASE+0x230)
#define CCM_PPLPERH_BIAS_REG		(CCM_BASE+0x234)

#define CCM_PPLCPU_TUNING_REG		(CCM_BASE+0x250)
#define CCM_PPLDDR_TUNING_REG		(CCM_BASE+0x260)

#define CCM_PPLAUDIO_PATCTRL_REG	(CCM_BASE+0x284)
#define CCM_PPLVIDEO_PATCTRL_REG	(CCM_BASE+0x288)
#define CCM_PPLDDR_PATCTRL_REG		(CCM_BASE+0x290)

#define CCM_AHB_SOFT_RST_REG0		(CCM_BASE+0x2c0)
#define CCM_AHB_SOFT_RST_REG1		(CCM_BASE+0x2c4)
#define CCM_APB_SOFT_RST_REG		(CCM_BASE+0x2d0)

/* cmmu pll ctrl bit field */
#define CCM_PLL_STABLE_FLAG			(1U << 28)

/* Clock ID */
#define AHB_BUS0					(0)
#define AHB_BUS1					(1)
#define APB_BUS						(2)


/* AHB_BUS0 */
#define USB_OTG_CKID				((AHB_BUS0 << 8) | 24)
#define SPI1_CKID					((AHB_BUS0 << 8) | 21)
#define SPI0_CKID					((AHB_BUS0 << 8) | 20)
#define DRAM_CKID					((AHB_BUS0 << 8) | 14)
#define SDC1_CKID					((AHB_BUS0 << 8) | 9 )
#define SDC0_CKID					((AHB_BUS0 << 8) | 8 )
#define DMA_CKID					((AHB_BUS0 << 8) | 6 )

/*AHB_BUS1 */
#define FE_CKID						((AHB_BUS1 << 8) | 14)
#define DE_CKID						((AHB_BUS1 << 8) | 12)
#define TVE_CKID					((AHB_BUS1 << 8) | 10)
#define TVD_CKID					((AHB_BUS1 << 8) | 9 )
#define CSI_CKID					((AHB_BUS1 << 8) | 8 )
#define LCD_CKID					((AHB_BUS1 << 8) | 4 )
#define VE_CKID						((AHB_BUS1 << 8) | 0 )

/* APB_BUS  */
#define UART2_CKID					((APB_BUS << 8) | 22)
#define UART1_CKID					((APB_BUS << 8) | 21)
#define UART0_CKID					((APB_BUS << 8) | 20)
#define TWI2_CKID					((APB_BUS << 8) | 18)
#define TWI1_CKID					((APB_BUS << 8) | 17)
#define TWI0_CKID					((APB_BUS << 8) | 16)
#define DAUDIO_CKID					((APB_BUS << 8) | 12)
#define RSB_CKID					((APB_BUS << 8) | 3 )
#define CIR_CKID					((APB_BUS << 8) | 2 )
#define SPDIF_CKID					((APB_BUS << 8) | 1 )
#define ADDA_CKID					((APB_BUS << 8) | 0 )

/* APB2_BUS  */


#define CLK_LOSC					(32000)
#define CLK_24M						(24000000)

#define CPU_CLK_SRC_LOSC			(0)
#define CPU_CLK_SRC_24M				(1)
#define CPU_CLK_SRC_PLLCPU			(2)

#define AHB_CLK_SRC_LOSC			(0)
#define AHB_CLK_SRC_24M				(1)
#define AHB_CLK_SRC_CPUCLK			(2)
#define AHB_CLK_SRC_PLLPERH			(3)

void ccm_clock_enable(u32 clk_id);
void ccm_clock_disable(u32 clk_id);
void ccm_module_enable(u32 clk_id);
void ccm_module_disable(u32 clk_id);
void ccm_module_reset(u32 clk_id);
void ccm_clock_disable_all(void);
void ccm_reset_all_module(void);

u32 ccm_setup_pll_cpu_clk(u32 pll_clk);
u32 ccm_get_pll_cpu_clk(void);
u32 ccm_setup_pll_audio_clk(u32 pll_clk);
u32 ccm_get_pll_audio_clk(void);
u32 ccm_setup_pll_video_clk(u32 pll_clk);
u32 ccm_get_pll_video_clk(void);
u32 ccm_setup_pll_ve_clk(u32 pll_clk);
u32 ccm_get_pll_ve_clk(void);
u32 ccm_setup_pll_ddr_clk(u32 pll_clk);
u32 ccm_get_pll_ddr_clk(void);
u32 ccm_setup_pll_periph_clk(u32 pll_clk);
u32 ccm_get_pll_periph_clk(void);

void ccm_set_cpu_clk_src(u32 src);
void ccm_set_ahb_config(u32 src, u32 div, u32 pre_div);
void ccm_set_apb_config(u32 div);
void ccm_set_pll_stable_time(u32 time);
void ccm_set_pll_cpu_stable_time(u32 time);

u32 ccm_get_ahb_clk(void);
u32 ccm_get_apb_clk(void);




/*****************************************************/
/*    PIO control register                          */
/*****************************************************/
#define PIO_BASE		 0x01C20800
#define PIO_A_CFG0		 (PIO_BASE+0x00)
#define PIO_A_CFG1     (PIO_BASE+0x04)
#define PIO_A_CFG2  	 (PIO_BASE+0x08)
#define PIO_A_CFG3  	 (PIO_BASE+0x0C)
#define PIO_A_DATA		 (PIO_BASE+0x010)
#define PIO_A_MULDRV0  (PIO_BASE+0x14)
#define PIO_A_MULDRV1	 (PIO_BASE+0x18)
#define PIO_A_PUP0		 (PIO_BASE+0x1C)
#define PIO_A_PUP1		 (PIO_BASE+0x20)

#define PIO_C_CFG0		 (PIO_BASE+0x48)
#define PIO_C_CFG1     (PIO_BASE+0x4c)
#define PIO_C_CFG2	   (PIO_BASE+0x50)
#define PIO_C_CFG3	   (PIO_BASE+0x54)
#define PIO_C_DATA		 (PIO_BASE+0x58)
#define PIO_C_MULDRV0  (PIO_BASE+0x5c)
#define PIO_C_MULDRV1  (PIO_BASE+0x60)
#define PIO_C_PUP0	   (PIO_BASE+0x64)
#define PIO_C_PUP1	   (PIO_BASE+0x68)

#define PIO_D_CFG0		 (PIO_BASE+0x6c)
#define PIO_D_CFG1     (PIO_BASE+0x70)
#define PIO_D_CFG2	   (PIO_BASE+0x74)
#define PIO_D_CFG3	   (PIO_BASE+0x78)
#define PIO_D_DATA		 (PIO_BASE+0x7c)
#define PIO_D_MULDRV0  (PIO_BASE+0x80)
#define PIO_D_MULDRV1  (PIO_BASE+0x84)
#define PIO_D_PUP0	   (PIO_BASE+0x88)
#define PIO_D_PUP1	   (PIO_BASE+0x8c)



















#endif
