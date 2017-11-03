/*
***********************************************
*
* File    : platform.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript: Base address of moduels
***********************************************
*/
#ifndef __PLATFORM_H
#define __PLATFORM_H

#define SYS_SRAM_BASE		(0x00000000)

/* base address of modules */
#define SYSCTRL_BASE		(0x01c00000)
#define DRAMCOM_BASE		(0x01c01000)
#define DMA_BASE			(0x01c02000)
#define SPI0_BASE			(0x01c05000)
#define SPI1_BASE			(0x01c06000)
#define TVE_BASE			(0x01c0a000)
#define TVD_BASE			(0x01c0b000)
#define LCD_BASE			(0x01c0c000)
#define VE_BASE				(0x01c0e000)
#define MMC0_BASE			(0x01c0f000)
#define MMC1_BASE			(0x01c10000)

#define USB_OTG_BASE		(0x01c13000)

#define CCM_BASE			(0x01c20000)
#define INTC_BASE			(0x01c20400)
#define PIO_BASE			(0x01c20800)
#define TIMER_BASE			(0x01c20c00)
#define PWM_BASE			(0x01c21000)
#define SPDIF_BASE			(0x01c21400)
#define RSB_BASE			(0x01c21800)
#define DAUDIO_BASE			(0x01c22000)
#define CIR_BASE			(0x01c22c00)
#define LRADC_BASE			(0x01c23400)
#define ADDA_BASE			(0x01c23c00)
#define TP_BASE				(0x01c24800)

#define UART0_BASE			(0x01c25000)
#define UART1_BASE			(0x01c25400)
#define UART2_BASE			(0x01c25800)
#define TWI0_BASE			(0x01c27000)
#define TWI1_BASE			(0x01c27400)
#define TWI2_BASE			(0x01c27800)

#define CSI_BASE			(0x01cb0000)
#define DEFE_BASE			(0x01e00000)
#define DEBE_BASE			(0x01e60000)
#define DEITLA_BASE			(0x01e70000)

#define BROM_BASE			(0xFFFF0000)

#define OTG_BASE			(0x01c13000)




#endif
