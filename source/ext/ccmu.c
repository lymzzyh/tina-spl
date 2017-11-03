/*
*******************************************
*
* File    : 
* By      : dianguai14
* Version : v1.0
* Date    : 2013-2-17 20:27:22
* Descript: 
*******************************************
*/

#include "include.h"

void  aw_delay(volatile unsigned n)
{
	while(n)
	{
		n--;
		__asm__ __volatile__("nop" ::: "memory", "cc");
	}
}

void ccm_clock_enable(u32 clk_id)
{
	switch(clk_id>>8) {
		case AHB_BUS0:
			set_wbit(CCM_AHB_CLK_GAT_REG0, 0x1U<<(clk_id&0xff));
			break;
		case AHB_BUS1:
			set_wbit(CCM_AHB_CLK_GAT_REG1, 0x1U<<(clk_id&0xff));
			break;
		case APB_BUS:
			set_wbit(CCM_APB_CLK_GAT_REG, 0x1U<<(clk_id&0xff));
			break;
		default: break;
	}
}

void ccm_clock_disable(u32 clk_id)
{
	switch(clk_id>>8) {
		case AHB_BUS0:
			clr_wbit(CCM_AHB_CLK_GAT_REG0, 0x1U<<(clk_id&0xff));
			break;
		case AHB_BUS1:
			clr_wbit(CCM_AHB_CLK_GAT_REG1, 0x1U<<(clk_id&0xff));
			break;
		case APB_BUS:
			clr_wbit(CCM_APB_CLK_GAT_REG, 0x1U<<(clk_id&0xff));
			break;
		default: break;
	}
}

void ccm_module_enable(u32 clk_id)
{
	switch(clk_id>>8) {
		case AHB_BUS0:
			set_wbit(CCM_AHB_SOFT_RST_REG0, 0x1U<<(clk_id&0xff));
			break;
		case AHB_BUS1:
			set_wbit(CCM_AHB_SOFT_RST_REG1, 0x1U<<(clk_id&0xff));
			break;
		case APB_BUS:
			set_wbit(CCM_APB_SOFT_RST_REG, 0x1U<<(clk_id&0xff));
			break;
		default: break;
	}
}

void ccm_module_disable(u32 clk_id)
{
	switch(clk_id>>8) {
		case AHB_BUS0:
			clr_wbit(CCM_AHB_SOFT_RST_REG0, 0x1U<<(clk_id&0xff));
			break;
		case AHB_BUS1:
			clr_wbit(CCM_AHB_SOFT_RST_REG1, 0x1U<<(clk_id&0xff));
			break;
		case APB_BUS:
			clr_wbit(CCM_APB_SOFT_RST_REG, 0x1U<<(clk_id&0xff));
			break;
		default: break;
	}
}

void ccm_module_reset(u32 clk_id)
{
	ccm_module_disable(clk_id);
	ccm_module_enable(clk_id);
}

static void ccm_wait_pll_stable(u32 pll_base)
{
#ifndef FPGA_PLATFORM
	u32 rval = 0;
	u32 time = 0xfff;
	
	do {
		rval = readl(pll_base);
		time --;
	} while (time && !(rval & CCM_PLL_STABLE_FLAG));
#endif
}

/* pll = 24000000 * n * k / (m * p) */
u32 ccm_setup_pll_cpu_clk(u32 pll_clk)
{
	u32 n, k, m, p;
	u32 rval = 0;
	u32 div = 0;

	if (pll_clk > 720000000)
		pll_clk = 720000000;

	if((pll_clk%24000000) == 0){
		div = pll_clk/24000000;
		n = div - 1;
		k = 0;
		m = 0;
		p = 0;
	}
	else if((pll_clk%12000000) == 0){
		m = 1;
		div = pll_clk/12000000;
		if((div%3) == 0)
			k = 2;
		else if((div%4) == 0)
			k = 3;
		else
			k = 1;
		n = (div/(k+1)) - 1;
		p = 0;
	}
	else{
		div = pll_clk/24000000;
		n = div - 1;
		k = 0;
		m = 0;
		p = 0;
	}

	rval = readl(CCM_PLL_CPU_REG);
	rval &= ~((0x3 << 16) | (0x1f << 8) | (0x3 << 4) | (0x3 << 0));
	rval |= (1U << 31) | (p << 16) | (n << 8) | (k << 4) | m;
	writel(rval, CCM_PLL_CPU_REG);
	ccm_wait_pll_stable(CCM_PLL_CPU_REG);
	
	n = n + 1;
	k = k + 1;
	m = m + 1;
	p = 1;

	return 24000000 * n * k / (m * p);
}

u32 ccm_get_pll_cpu_clk(void)
{
#ifdef FPGA_PLATFORM
	return PLL_CPU_CLK;
#else
	u32 rval = readl(CCM_PLL_CPU_REG);
	u32 m = (0x3 & (rval >> 0));
	u32 k = (0x3 & (rval >> 4));
	u32 n = (0x1f & (rval >> 8));
	u32 p = (0x3 & (rval >> 16));


	n = n + 1;
	k = k + 1;
	m = m + 1;
	if(p == 0)
		p = 1;
	else if(p == 1)
		p = 2;
	else if(p == 2)
		p = 4;

	return 24000000 * n * k / (m * p);
#endif
}

u32 ccm_setup_pll_audio_clk(u32 pll_clk)
{
	return PLL_AUDIO_CLK;
}

u32 ccm_get_pll_audio_clk(void)
{
	return PLL_AUDIO_CLK;
}

u32 ccm_setup_pll_video_clk(u32 pll_clk)
{
	return PLL_VIDEO_CLK;
}

u32 ccm_get_pll_video_clk(void)
{
	return PLL_VIDEO_CLK;
}

u32 ccm_setup_pll_ve_clk(u32 pll_clk)
{
	return PLL_VE_CLK;
}

u32 ccm_get_pll_ve_clk(void)
{
	return PLL_VE_CLK;
}

/* pll = 24*n*k/m */
u32 ccm_setup_pll_ddr_clk(u32 pll_clk)
{
	u32 n,m=0,k=0;
	u32 rval = 0;

	if (pll_clk > 240000000)
		pll_clk = 240000000;

	m = 1;
	k = 0;
	n = pll_clk/12000000 - 1;

	rval = (1U << 31)| (n << 8) | (k << 4)  | (m << 0);
	writel(rval, CCM_PLL_DDR_REG);
	ccm_wait_pll_stable(CCM_PLL_DDR_REG);

	n = n + 1;
	k = k + 1;
	m = m + 1;

	return 24000000 * n * k / m;
}

u32 ccm_get_pll_ddr_clk(void)
{
	u32 n,k,m;
	u32 rval;
	rval = readl(CCM_PLL_DDR_REG);

	n = (0x1f & (rval >> 8));
	k = (0x3 & (rval >> 4));
	m = (0x3 & (rval >> 0));

	n = n + 1;
	k = k + 1;
	m = m + 1;

	return 24000000 * n * k / m;
}

/*
 * PERIPH PLL should be 600M
 */
u32 ccm_setup_pll_periph_clk(u32 pll_clk)
{
	u32 rval = readl(CCM_PLL_PERH_REG) | (1U << 31);
	writel(rval, CCM_PLL_PERH_REG);

	return PLL_PERH_CLK;
}

u32 ccm_get_pll_periph_clk(void)
{
	return PLL_PERH_CLK;
}

/*
 * Setup CPU Clock Source
 */
void ccm_set_cpu_clk_src(u32 src)
{
	u32 rval = readl(CCM_CPUCLK_CFG_REG);
	rval &= ~(0x3 << 16);
	rval |= (src << 16);
	writel(rval, CCM_CPUCLK_CFG_REG);
}

/*
 * AHB Clock Configuration
 * PRE_DIV only valid for PERIPH PLL
 */
void ccm_set_ahb_config(u32 src, u32 div, u32 pre_div)
{
	u32 rval = readl(CCM_AHB_APB_RATIO_REG);
	switch (div){
		case 1:
			div = 0;
			break;
		case 2:
			div = 1;
			break;
		case 4:
			div = 2;
			break;
		case 8:
			div = 3;
			break;
		default: break;
	}

	rval &= ~(0x3 << 4);
	rval |= (div << 4);
	rval |= ((pre_div-1) << 6);

	writel(rval, CCM_AHB_APB_RATIO_REG);
	rval = readl(CCM_AHB_APB_RATIO_REG);
	rval &= ~(3 << 12);
	rval |= (src << 12);
	writel(rval, CCM_AHB_APB_RATIO_REG);
}

/*
 * APB Clock Source is AHB
 */
void ccm_set_apb_config(u32 div)
{
	u32 rval = readl(CCM_AHB_APB_RATIO_REG);
	switch (div){
		case 1:
			div = 0;
			break;
		case 2:
			div = 1;
			break;
		case 4:
			div = 2;
			break;
		case 8:
			div = 3;
			break;
		default: break;
	}
	rval &= ~(0x3 << 8);
	rval |= (div << 8);
	writel(rval, CCM_AHB_APB_RATIO_REG);
}


void ccm_set_pll_stable_time(u32 time)
{
	writel(time&0xffff, CCM_PLL_LKTM_REG);
}

void ccm_set_pll_cpu_stable_time(u32 time)
{
	writel(time&0xffff, CCM_PLLCPU_LKTM_REG);
}

u32 ccm_get_ahb_clk(void)
{
	u32 src,sel;
	u32 pre_div;
	u32 rval;
	u32 div;
	rval = readl(CCM_AHB_APB_RATIO_REG);

	div = 0x3 & (rval >> 4);
	switch (div) {
		case 0:
			div = 1;
			break;
		case 1:
			div = 2;
			break;
		case 2:
			div = 4;
			break;
		case 3:
			div = 8;
			break;
		default: break;
	}

	pre_div = 0x3 & (rval >> 6);
	pre_div++;

	sel = 0x3 & (rval >> 12);
	switch (sel) {
		case 0:
			src = CLK_LOSC;
			break;
		case 1:
			src = CLK_24M;
			break;
		case 2:
			src = ccm_get_pll_cpu_clk();
			break;
		case 3:
			src = ccm_get_pll_periph_clk()/pre_div;
			break;
		default: break;
	}

	return src / div;
}

u32 ccm_get_apb_clk(void)
{
	u32 src = ccm_get_ahb_clk();
	u32 div = (readl(CCM_AHB_APB_RATIO_REG) >> 8) & 0x3 ;

	switch (div) {
		case 0:
			div = 1;
			break;
		case 1:
			div = 2;
			break;
		case 2:
			div = 4;
			break;
		case 3:
			div = 8;
			break;
		default: break;
	}

	return src / div;
}

//CPUFRQ function SRC
void CPUFrq(u32 src,u32 pllValue)
{
	u32 rdata,n,k,p;

	//PLL-cpu set the freq 48MHz/step
	if(pllValue>720)
	{
		k = 1;
		p = 0;
		n = pllValue/48-1;
		rdata = get_wvalue(CCM_PLL_CPU_REG) & ~(3<<16) & ~(0x1F<<8) & ~(0x3<<4) | (p<<16) | (n<<8) | (k<<4) | (1<<31);
		put_wvalue(CCM_PLL_CPU_REG,rdata);
#ifndef FPGA_PLATFORM	//wait for pll lock bit
		do{
			rdata = (get_wvalue(CCM_PLL_CPU_REG)>>28) & 1;
		}while(!rdata);
#endif
	}
	else if(pllValue < 240)		// /4
	{
		k = 0;
		p = 2;
		n = pllValue*(p+1)/24-1;
		rdata = get_wvalue(CCM_PLL_CPU_REG) & ~(3<<16) & ~(0x1F<<8) & ~(0x3<<4) | (p<<16) | (n<<8) | (k<<4) | (1<<31);
		put_wvalue(CCM_PLL_CPU_REG,rdata);
#ifndef FPGA_PLATFORM	//wait for pll lock bit
		do{
			rdata = (get_wvalue(CCM_PLL_CPU_REG)>>28) & 1;
		}while(!rdata);
#endif
	}
	else
	{
		k = 0;
		p = 0;
		n = pllValue/24-1;
		rdata = get_wvalue(CCM_PLL_CPU_REG) & ~(3<<16) & ~(0x1F<<8) & ~(0x3<<4) | (p<<16) | (n<<8) | (k<<4) | (1<<31);
		put_wvalue(CCM_PLL_CPU_REG,rdata);
#ifndef FPGA_PLATFORM	//wait for pll lock bit
		do{
			rdata = (get_wvalue(CCM_PLL_CPU_REG)>>28) & 1;
		}while(!rdata);
#endif
	}

	rdata = get_wvalue(CCM_CPUCLK_CFG_REG) & ~(0x3<<16) | (src<<16);
	put_wvalue(CCM_CPUCLK_CFG_REG,rdata);
	aw_delay(100);
	//ahb/abp clk src switch to CPU clk/pll
	//rdata = get_wvalue(CCM_AHB_APB_RATIO_REG) & ~(0x3<<16) & ~(0x3<<12)  & ~(0x3<<8)  & ~(0xF<<4) | (3<<16) | (1<<12) | (0<<8) | (0<<4);	//HCLK_C/AHB1/APB
	rdata = get_wvalue(CCM_AHB_APB_RATIO_REG) & ~(0x3<<16) & ~(0x3<<12)  & ~(0x3<<8)  & ~(0xF<<4) | (3<<16) | (3<<12) | (0<<8) | (0xE<<4);
	put_wvalue(CCM_AHB_APB_RATIO_REG,rdata);
	aw_delay(100);
}

