/*
********************************************
*
* File    : sysctrl.h
* By      : dianguai14
* Version : v1.0
* Date    : 
* Descript: 
********************************************
*/

#ifndef __SYS_CTRL_H
#define __SYS_CTRL_H

#define SRAM_CTRL_REG0      	(SYSCTRL_BASE+0x000)
#define SRAM_CTRL_REG1      	(SYSCTRL_BASE+0x004)
#define GP_DATA_REG				(SYSCTRL_BASE+0x008)
#define CBIST_CTRL_REG			(SYSCTRL_BASE+0x010)
#define BIST_CTRL_REG      		(SYSCTRL_BASE+0x014)
#define BIST_START_ADDR_REG     (SYSCTRL_BASE+0x018)
#define BIST_END_ADDR_REG      	(SYSCTRL_BASE+0x01C)
#define BIST_DATA_MASK_REG      (SYSCTRL_BASE+0x020)

#define VERSION_REG      		(SYSCTRL_BASE+0x024)
#define CHIP_ID_REG				(SYSCTRL_BASE+0x028)
#define SRAM_CONFIG_REG			(SYSCTRL_BASE+0x02C)


//#define SRAM_TEST_REG     		(SYSCTRL_BASE+0x048)

#define TEST_DBG_REG0      		(SYSCTRL_BASE+0x090)
#define TEST_DBG_REG1      		(SYSCTRL_BASE+0x094)

#define PLL_CTRL_REG0     		(SYSCTRL_BASE+0x0A0)
#define PLL_CTRL_REG1     		(SYSCTRL_BASE+0x0A4)
#define CPU_CTRL_REG			(SYSCTRL_BASE+0x0B4)
#define CLK_OUT_REG     		(SYSCTRL_BASE+0x0F0)

s32 bist_test(u32 startaddr, u32 endaddr, u32 bistmode);
s32 sys_ctrl_test();

#endif
