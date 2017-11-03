/*
 * sys-dram.c
 *
 * Copyright(c) 2007-2017 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <xboot.h>

#define REG(x)    					(*(volatile unsigned int *)(x))

#define DRAMC_PHY_BASE      			0x01C01000

#define DRAM_REG_SCONR                  REG(DRAMC_PHY_BASE + 0x00)
#define DRAM_REG_STMG0R                 REG(DRAMC_PHY_BASE + 0x04)
#define DRAM_REG_STMG1R                 REG(DRAMC_PHY_BASE + 0x08)
#define DRAM_REG_SCTLR                  REG(DRAMC_PHY_BASE + 0x0c)
#define DRAM_REG_SREFR                  REG(DRAMC_PHY_BASE + 0x10)
#define DRAM_REG_SEXTMR                 REG(DRAMC_PHY_BASE + 0x14)
#define DRAM_REG_DDLYR                  REG(DRAMC_PHY_BASE + 0x24)
#define DRAM_REG_DADRR                  REG(DRAMC_PHY_BASE + 0x28)
#define DRAM_REG_DVALR                  REG(DRAMC_PHY_BASE + 0x2c)
#define DRAM_REG_DRPTR0                 REG(DRAMC_PHY_BASE + 0x30)
#define DRAM_REG_DRPTR1                 REG(DRAMC_PHY_BASE + 0x34)
#define DRAM_REG_DRPTR2                 REG(DRAMC_PHY_BASE + 0x38)
#define DRAM_REG_DRPTR3                 REG(DRAMC_PHY_BASE + 0x3c)
#define DRAM_REG_SEFR                   REG(DRAMC_PHY_BASE + 0x40)
#define DRAM_REG_MAE	                REG(DRAMC_PHY_BASE + 0x44)
#define DRAM_REG_ASPR                   REG(DRAMC_PHY_BASE + 0x48)
#define DRAM_REG_SDLY0                  REG(DRAMC_PHY_BASE + 0x4C)
#define DRAM_REG_SDLY1                  REG(DRAMC_PHY_BASE + 0x50)
#define DRAM_REG_SDLY2                  REG(DRAMC_PHY_BASE + 0x54)
#define DRAM_REG_MCR0					REG(DRAMC_PHY_BASE + 0x100 + 4*0)
#define DRAM_REG_MCR1					REG(DRAMC_PHY_BASE + 0x100 + 4*1)
#define DRAM_REG_MCR2					REG(DRAMC_PHY_BASE + 0x100 + 4*2)
#define DRAM_REG_MCR3					REG(DRAMC_PHY_BASE + 0x100 + 4*3)
#define DRAM_REG_MCR4					REG(DRAMC_PHY_BASE + 0x100 + 4*4)
#define DRAM_REG_MCR5					REG(DRAMC_PHY_BASE + 0x100 + 4*5)
#define DRAM_REG_MCR6					REG(DRAMC_PHY_BASE + 0x100 + 4*6)
#define DRAM_REG_MCR7					REG(DRAMC_PHY_BASE + 0x100 + 4*7)
#define DRAM_REG_MCR8					REG(DRAMC_PHY_BASE + 0x100 + 4*8)
#define DRAM_REG_MCR9					REG(DRAMC_PHY_BASE + 0x100 + 4*9)
#define DRAM_REG_MCR10					REG(DRAMC_PHY_BASE + 0x100 + 4*10)
#define DRAM_REG_MCR11					REG(DRAMC_PHY_BASE + 0x100 + 4*11)
#define DRAM_REG_BWCR                   REG(DRAMC_PHY_BASE + 0x140)


//PIO register for dram
#define DRAM_PIO_BASE       			0x01c20800
#define DRAM_PIO_MEMSIZE    			0x400
#define SDR_PAD_DRV_REG                 REG(DRAM_PIO_BASE + 0x2C0)
#define SDR_PAD_PUL_REG                 REG(DRAM_PIO_BASE + 0x2C4)
#define SDR_VREF                        REG(DRAM_PIO_BASE + 0x24)

//CCM register for dram
#define DRAM_CCM_BASE       			0x01c20000
#define DRAM_CCM_SDRAM_PLL_REG          REG(DRAM_CCM_BASE + 0x20)
#define DRAM_CCM_AHB1_GATE_REG          REG(DRAM_CCM_BASE + 0x60)
#define DRAM_CCM_DRAM_GATING_REG		REG(DRAM_CCM_BASE + 0x100)
#define DRAM_CCM_SIGMA_REG			    REG(DRAM_CCM_BASE + 0x290)
#define DRAM_CCM_AHB1_RST_REG			REG(DRAM_CCM_BASE + 0x2C0)

#define SDR_T_CAS               		0x2//CL
#define SDR_T_RAS               		0x8//120000ns>=tRAS>=42ns  SDR166
#define SDR_T_RCD               		0x3//tRCD>=15ns   SDR166
#define SDR_T_RP                		0x3//tRP>=15ns   SDR166
#define SDR_T_WR                		0x3//tRP>=12ns   SDR166
#define SDR_T_RFC              		    0xd//tRFC>=60ns   SDR166
#define SDR_T_XSR               		0xf9//tXSRD>=200CK
#define SDR_T_RC                		0xb//tRC>=60ns  SDR166
#define SDR_T_INIT              		0x8//
#define SDR_T_INIT_REF          		0x7
#define SDR_T_WTR               		0x2//tWTR>=2CK   SDR166
#define SDR_T_RRD               		0x2//tRRD>=12ns  SDR166
#define SDR_T_XP                		0x0// one clk is ok

enum dram_type_t
{
    DRAM_TYPE_SDR=0,
    DRAM_TYPE_DDR=1,
    DRAM_TYPE_MDDR=2,
};

struct dram_para_t
{
    u32_t           base;           // dram base address
    u32_t           size;           // dram size, based on     (unit: MByte)
    u32_t           clk;            // dram work clock         (unit: MHz)
    u32_t           access_mode;    // 0: interleave mode 1: sequence mode
    u32_t           cs_num;         // dram chip count  1: one chip  2: two chip
    u32_t           ddr8_remap;     // for 8bits data width DDR 0: normal  1: 8bits
    enum dram_type_t   sdr_ddr;           // ddr/ddr2/sdr/mddr/lpddr/...
    u32_t           bwidth;         // dram bus width
    u32_t           col_width;      // column address width
    u32_t           row_width;      // row address width
    u32_t           bank_size;      // dram bank count
    u32_t           cas;            // dram cas
};


static void aw_delay(volatile unsigned n)
{
	while(n)
	{
		n--;
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
	}
}

static int DRAMC_initial(void)
{
	unsigned int time = 0xffffff;

    //initialization
    DRAM_REG_SCTLR = DRAM_REG_SCTLR | 0x1;
    while( (DRAM_REG_SCTLR & 0x1) && time-- )
    {
        if(time == 0)
        	return 0;
    }

    return 1;
}

static int DRAMC_delay_scan(void)
{
	unsigned int time = 0xffffff;

	//check whether read result is right for the readpipe value
    DRAM_REG_DDLYR|= 0x1;
    while( (DRAM_REG_DDLYR & 0x1) && time-- )
    {
        if(time == 0)
        	return 0;
    }
    return 1;
}

static void CSP_DRAMC_set_autofresh_cycle(u32_t clk) //120MHZ  7.8us,8192rows,936=0x3a8
{
    u32_t reg_val = 0;
	u32_t row = 0;
	u32_t temp = 0;

	row = DRAM_REG_SCONR;
	row &= 0x1E0;
	row >>= 0x5;

    //64 ms/8192 rows = 7.8us per refresh cycle
    if(row == 0xC)
    {
        if(clk >= 1000000)
        {
            //HZ
            temp = clk + (clk >> 3) + (clk >> 4) + (clk >> 5);
            while(temp >= (10000000 >> 6))
            {
          	    temp -= (10000000 >> 6);
          	    reg_val++;
            }
        }
        else
        {
            //MHZ
        	reg_val = (clk*499)>>6;
        }
   	}
   	else if(row == 0xB) //64ms/4096 rows = 15.6us per refresh cycle
   	{
   		if(clk >= 1000000)
   		{
   			temp = clk + (clk >> 3) + (clk >> 4) + (clk >> 5);
   			while(temp >= (10000000 >> 7))
        	{
            	temp -= (10000000 >> 7);
            	reg_val++;
        	}
   		}
   		else
   		{
   			reg_val = (clk*499)>>5;
   		}
   	}
   	DRAM_REG_SREFR = reg_val;
}

static u32_t DRAMC_para_setup(struct dram_para_t *para)
{
    u32_t   reg_val = 0;

    //setup SCONR register
    reg_val = (para->ddr8_remap) 			|
    		  (0x1<<1)           			|
    		  ((para->bank_size>>2)<<3)		|
    		  ((para->cs_num>>1)<<4)        |
    		  ((para->row_width-1)<<5)      |
    		  ((para->col_width-1)<<9)      |
    		  ((para->sdr_ddr ? (para->bwidth>>4) : (para->bwidth>>5))<<13)  |
    		  (para->access_mode<<15)       |
    		  (para->sdr_ddr<<16);
#ifdef DRAM_PAD_MODE0_TEST
    reg_val &= ~0x6;
#endif

#ifdef DRAM_PAD_MODE2_TEST
    reg_val &= ~0x6;
    reg_val |= 0x4;
#endif
    DRAM_REG_SCONR = reg_val;

    //set DRAM control register
    DRAM_REG_SCTLR = DRAM_REG_SCTLR | 0x1<<19;  //enable delay auto refresh mode

	//initialization
    return DRAMC_initial();
}

static u32_t DRAMC_check_delay(u32_t bwidth)
{
    u32_t   dsize;
    u32_t   i,j;
    u32_t   num = 0;
    u32_t   dflag = 0;

    dsize = ((bwidth == 16) ? 4 : 2);     //data width:  16bits  DQS0~1     8bits  DQS0

    for(i=0; i<dsize; i++)
    {
    	if(i == 0)
    		dflag = DRAM_REG_DRPTR0;//DQS0 LOW 32 levels
    	else if(i == 1)
    		dflag = DRAM_REG_DRPTR1;//DQS0 HIGH 32 levels
    	else if(i == 2)
    		dflag = DRAM_REG_DRPTR2;//DQS1 LOW 32 levels
    	else if(i == 3)
    		dflag = DRAM_REG_DRPTR3;//DQS1 LOW 32 levels

        for(j=0; j<32; j++)
        {
            if(dflag & 0x1)            //1 success   0 fail
                num++;
            dflag >>= 1;
        }
    }

    return num;
}

static u32_t sdr_readpipe_scan(void)
{
	u32_t k=0;
	for(k=0;k<32;k++)
    {
		REG(0x80000000+4*k)=k;
	}
    for(k=0;k<32;k++)
	{
		if( REG(0x80000000+4*k)!=k )
		return 0;
	}
    return 1;
}

static u32_t sdr_readpipe_select(void)
{
  u32_t value=0;
  u32_t i=0;
  for(i=0;i<8;i++)
  {
      //set readpipe is i
	  DRAM_REG_SCTLR &=(~(0x7<<6 ));
      DRAM_REG_SCTLR |=(i<<6);
      if(sdr_readpipe_scan())
      {
    	  value=i;
    	  return value;
      }

  }
  return value;

}

static u32_t CSP_DRAMC_check_type(struct dram_para_t *para)
{
    u32_t reg_val = 0;
    u32_t i;
    u32_t times = 0;

    //check 8 readpipe values
    for(i=0; i<8; i++)
    {
        //readpipe value
        reg_val = DRAM_REG_SCTLR;
        reg_val &= ~(0x7<<6);
        reg_val |= (i<<6);
        DRAM_REG_SCTLR = reg_val;

        //check whether read result is right for the readpipe value
        DRAMC_delay_scan();

        //check whether the DQS flag is success
        if(DRAM_REG_DDLYR & 0x30)
        {
            //fail
            times++;
            //break;
        }
    }
    //all the readpipe values fail
    if(times == 8)
    {
        //SDR
        para->sdr_ddr = DRAM_TYPE_SDR;
        return 0;
    }
    else
    {
        //DDR
        para->sdr_ddr = DRAM_TYPE_DDR;
        return 1;
    }
}

static u32_t CSP_DRAMC_scan_readpipe(struct dram_para_t *para)
{
    u32_t   i, rp_best=0,rp_val=0 ;
    u32_t   reg_val = 0;
    u32_t   readpipe[8];

    if(para->sdr_ddr == DRAM_TYPE_DDR)
    {
        //DDR type
        for(i=0; i<8; i++)
        {
            //readpipe value fill
            reg_val = DRAM_REG_SCTLR;
            reg_val &= ~(0x7<<6);
            reg_val |= (i<<6);
            DRAM_REG_SCTLR = reg_val;//write i to read_pipe

			//initialization
//			DRAMC_initial();

            //check whether read result is right for the readpipe value
        	DRAMC_delay_scan();

            readpipe[i] = 0;
            if((((DRAM_REG_DDLYR>>4) & 0x3) == 0x0) && (((DRAM_REG_DDLYR>>4) & 0x1) == 0x0))//Success for an matching delay
            {
            	readpipe[i] = DRAMC_check_delay(para->bwidth);
            }

			//get the best readpipe value
 			if(rp_val < readpipe[i])
 			{
 				rp_val = readpipe[i];
 				rp_best = i;
 			}
        }

         //set the best readpipe and check it
        reg_val = DRAM_REG_SCTLR;
        reg_val &= ~(0x7<<6);
        reg_val |= (rp_best<<6);
        DRAM_REG_SCTLR = reg_val;

        //check whether read result is right for the readpipe value
        DRAMC_delay_scan();

        //tune ddr delay line value
//        DRAMC_delay_tune(para->clk);
    }
    else
    {
        //SDR type
        //set up the sdr parameters
        reg_val = DRAM_REG_SCONR;
        reg_val &= (~(0x1<<16));
        reg_val &= (~(0x3<<13));
        DRAM_REG_SCONR = reg_val;

        //initialization
//		DRAMC_initial();

		rp_best=sdr_readpipe_select();//auto select the best readpipe

        //set the best readpipe and check it
        reg_val = DRAM_REG_SCTLR;
        reg_val &= ~(0x7<<6);
        reg_val |= (rp_best<<6);
        DRAM_REG_SCTLR = reg_val;
    }

    return 0;
}

static u32_t CSP_DRAMC_get_dram_size(struct dram_para_t *para)
{
    u32_t   colflag = 10, rowflag = 13;
    u32_t   i = 0;
    u32_t   val1=0;
    u32_t   count = 0;
    u32_t   addr1, addr2;

    //--------------------column test begin---------------------------------
    para->col_width = colflag;
    para->row_width = rowflag;

    //fill the parameter and initial
    DRAMC_para_setup(para);

     //scan the best readpipe
    CSP_DRAMC_scan_readpipe(para);

    //bank0 10 column or 9 column test
    for(i=0;i<32;i++)
    {
        *( (u32_t *) (0x80000200+i) ) = 0x11111111;
        *( (u32_t *) (0x80000600+i) ) = 0x22222222;
    }
    for(i=0;i<32;i++)
    {
        val1 = *( (u32_t *) (0x80000200+i) );
        if(val1 == 0x22222222)
            count++;
    }

    //not 10 column
    if(count == 32)
    {
    	colflag = 9;
    }
    else
    {
    	colflag = 10;
	}

    //--------------------row test begin-------------------------------
    count = 0;
    para->col_width = colflag;
    para->row_width = rowflag;

    //fill the parameter and initial
    DRAMC_para_setup(para);

    //scan the best readpipe
    //CSP_DRAMC_scan_readpipe();

    if(colflag == 10)
    {
        addr1 = 0x80400000;
        addr2 = 0x80c00000;
    }
    else
    {
        addr1 = 0x80200000;
        addr2 = 0x80600000;
    }
    //bank0 13 row or 12 row test
    for(i=0;i<32;i++)
    {
        *( (u32_t *) (addr1+i) ) = 0x33333333;
        *( (u32_t *) (addr2+i) ) = 0x44444444;
    }
    for(i=0;i<32;i++)
    {
        val1 = *( (u32_t *) (addr1+i) );
        if(val1 == 0x44444444)
        {
            count++;
        }
    }

    if(count == 32)  //not 13 row
    {
        rowflag = 12;
    }
    else
        rowflag = 13;

    para->col_width = colflag;
    para->row_width = rowflag;

	//return size type
	(para->row_width != 13) ? (para->size = 16) : ( (para->col_width == 10) ? (para->size = 64) : (para->size = 32) );
	if(para->row_width != 13)
    {
        para->size = 16;
    }
    else if(para->col_width == 10)
    {
        para->size = 64;
    }
    else
    {
        para->size = 32;
    }

	//set DRAM refresh interval register
    CSP_DRAMC_set_autofresh_cycle(para->clk);

    //fill the parameter and initial
    para->access_mode = 0;
    DRAMC_para_setup(para);

    //scan the best readpipe
    //CSP_DRAMC_scan_readpipe();

    return 0;
}

static s32_t CSP_DRAMC_init(struct dram_para_t *dram_para, s32_t mode)
{
    u32_t reg_val = 0;
    u32_t i;

    SDR_VREF|=(0x7)<<12;
    aw_delay(1000);//must delay

    if( ((dram_para->cas)>>3)&0x1)
    {
    	SDR_PAD_PUL_REG|=((0x1<<23)|(0x20<<17));//use internal VREF
    }

    if((dram_para->clk>=144)&&(dram_para->clk<=180))
    {
    	SDR_PAD_DRV_REG=0xaaa;
    }
    if((dram_para->clk)>=180)//when hight fre should extent pad Driving
    {
    	SDR_PAD_DRV_REG=0xfff;
    }


    //ccmu configure M | K | N
    if((dram_para->clk)<=96)
    {
    	reg_val = (0x1<<0) | (0x0<<4) | (((dram_para->clk*2)/12 - 1)<<8) | (0x1u<<31);//N=PLL/12---PLL=12*N(N<=32)---DDR_CLK=6*N--M=2K
    }
    else
    {
    	reg_val = (0x0<<0) | (0x0<<4) | (((dram_para->clk*2)/24 - 1)<<8) | (0x1u<<31);//N=PLL/24---PLL=24*N(N<=32)---DDR_CLK=12*N--M=K
    }

//------------------------------------------------------------------------------------
//dram_para->cas:bit7:bit4=0001:pll �ڷ�0.4
//dram_para->cas:bit7:bit4=0010:pll �ڷ�0.3
//dram_para->cas:bit7:bit4=0100:pll �ڷ�0.2
//dram_para->cas:bit7:bit4=1000:pll �ڷ�0.1

     if(dram_para->cas & (0x1<<4))
     {
    	 DRAM_CCM_SIGMA_REG= 0xD1303333;
     }
     else if(dram_para->cas & (0x1<<5))//----------------------------------------------------------------------------------------
     {
    	 DRAM_CCM_SIGMA_REG=0xcce06666;
     }
     else if(dram_para->cas & (0x1<<6))//---------------------------------------------------------------------------------------
     {
    	 DRAM_CCM_SIGMA_REG=0xc8909999;
     }
     else if(dram_para->cas & (0x1<<7))//----------------------------------------------------------------------------------------
     {
    	 DRAM_CCM_SIGMA_REG=0xc440cccc;
     }
     if( dram_para->cas & (0xf<<4) )//open frequnce extend
     {
    	 reg_val |= 0x1<<24;
     }
//------------------------------------------------------------------------------------
     DRAM_CCM_SDRAM_PLL_REG = reg_val;
     DRAM_CCM_SDRAM_PLL_REG|=(0x1<<20);//updata
    while((DRAM_CCM_SDRAM_PLL_REG&(1<<28)) == 0);
    aw_delay(1000);

    //dram ahb1 gating
    DRAM_CCM_AHB1_GATE_REG |= 0x1<<14;

    //dram reset
    DRAM_CCM_AHB1_RST_REG &= ~(0x1<<14);
    for(i=0; i<10; i++)
    	continue;
    DRAM_CCM_AHB1_RST_REG |= (0x1<<14);

	 //set SDRAM PAD TYPE
    reg_val = SDR_PAD_PUL_REG;
    (dram_para->sdr_ddr == DRAM_TYPE_DDR) ? (reg_val |= (0x1<<16)) : (reg_val &= ~(0x1<<16));
    SDR_PAD_PUL_REG = reg_val;

    //set MCTL Timing 0 Register
    reg_val = (SDR_T_CAS<<0)|(SDR_T_RAS<<3)|(SDR_T_RCD<<7)|(SDR_T_RP<<10)|(SDR_T_WR<<13)|(SDR_T_RFC<<15)|(SDR_T_XSR<<19)|(SDR_T_RC<<28);
    DRAM_REG_STMG0R = reg_val;

    //set MCTL Timing 1 Register
    reg_val = (SDR_T_INIT<<0)|(SDR_T_INIT_REF<<16)|(SDR_T_WTR<<20)|(SDR_T_RRD<<22)|(SDR_T_XP<<25);
    DRAM_REG_STMG1R = reg_val;

    //set extend mode register
//    reg_val = 0x1<<16;
//    DRAM_REG_SEXTMR = reg_val;

    //parameters setup and update
    DRAMC_para_setup(dram_para);

    //check DRAM TYPE
    CSP_DRAMC_check_type(dram_para);

    //update SDRAM PAD TYPE
    reg_val = SDR_PAD_PUL_REG;
    (dram_para->sdr_ddr == DRAM_TYPE_DDR) ? (reg_val |= (0x1<<16)) : (reg_val &= ~(0x1<<16));
    SDR_PAD_PUL_REG = reg_val;

	//set DRAM refresh interval register
    CSP_DRAMC_set_autofresh_cycle(dram_para->clk);
    //scan the best readpipe
    CSP_DRAMC_scan_readpipe(dram_para);//readpipe---inserted in read data path(not write) for SDRAM in order to correctly latch data

    //check DRAM SIZE
    CSP_DRAMC_get_dram_size(dram_para);



    //basic rw test
    for(i=0; i<128; i++)
    {
    	REG(dram_para->base + 4*i) = dram_para->base + 4*i;
    }

    for(i=0; i<128; i++)
    {
    	if( REG(dram_para->base + 4*i) != (dram_para->base + 4*i) )
    	{
    		return 0;
    	}
    }

    return 1;
}

#define PLL_DDR_CLK				(156000000)
static int mctl_init(void)
{
	struct dram_para_t parameters;
	/*= {
			 	0x80000000,				//base
			 	64,						//size--MBYTE
			 	PLL_DDR_CLK/1000000,	//clk
				1,						//access_mode
				1,						//cs_num
				0,						//ddr8_remap
				DRAM_TYPE_DDR,			//sdr_ddr
				16,						//bwidth
				10,						//col_width
				13,						//row_width
				4,						//bank_size
				0x3						//cas
		};
	parameters.clk = PLL_DDR_CLK/1000000;*/

	/*
	init dram , base        is 0x80000000
init dram , clk         is 144
init dram , access_mode is 1
init dram , cs_num      is 1
init dram , ddr8_remap  is 0
init dram , sdr_ddr     is 1
init dram , bwidth      is 16
init dram , col_width   is 10
init dram , row_width   is 13
init dram , bank_size   is 4
init dram , cas         is 3
init dram , size        is 0
dram init successed,size is 32

	 */
	parameters.base = 0x80000000;
	parameters.size = 64;
	parameters.clk = PLL_DDR_CLK / 1000000;
	parameters.access_mode = 1;
	parameters.cs_num = 1;
	parameters.ddr8_remap = 0;
	parameters.sdr_ddr = DRAM_TYPE_DDR;
	parameters.bwidth = 16;
	parameters.col_width = 10;
	parameters.row_width = 13;
	parameters.bank_size = 4;
	parameters.cas = 0x3;
	return CSP_DRAMC_init(&parameters, 0);
}

void sys_dram_init(void)
{
	u32_t * p;
	int i = 0;
	char fmt[16];
	fmt[0] = 'D';
	fmt[1] = 'D';
	fmt[2] = 'R';
	fmt[3] = '=';
	fmt[4] = '%';
	fmt[5] = 'x';
	fmt[6] = '\r';
	fmt[7] = '\n';
	fmt[8] = 0;

	i = mctl_init();
	printk(fmt, i);

	p = (u32_t *)(0x80000000);
	for(i = 0; i< 128; i++)
		printk(fmt, p[i]);
}
