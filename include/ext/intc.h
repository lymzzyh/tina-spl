/*
***********************************************
*
* File    : irq.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-28
* Descript:
***********************************************
*/
#ifndef __INTC_H
#define __INTC_H

/* INTC registers */
#define INTC_VECTOR_REG		(INTC_BASE + 0x0000)
#define INTC_BASE_ADDR		(INTC_BASE + 0x0004)
#define NMI_IRQ_CTRL		(INTC_BASE + 0x000c)

#define INTC_PEND_REG0		(INTC_BASE + 0x0010)
#define INTC_PEND_REG1		(INTC_BASE + 0x0014)

#define INTC_ENABLE_REG0	(INTC_BASE + 0x0020)
#define INTC_ENABLE_REG1	(INTC_BASE + 0x0024)

#define INTC_MASK_REG0		(INTC_BASE + 0x0030)
#define INTC_MASK_REG1		(INTC_BASE + 0x0034)

#define INTC_RESP_REG0		(INTC_BASE + 0x0040)
#define INTC_RESP_REG1		(INTC_BASE + 0x0044)

#define INTC_FF_REG0		(INTC_BASE + 0x0050)
#define INTC_FF_REG1		(INTC_BASE + 0x0054)

#define INTC_PRIO_REG0		(INTC_BASE + 0x0060)
#define INTC_PRIO_REG1		(INTC_BASE + 0x0064)
#define INTC_PRIO_REG2		(INTC_BASE + 0x0068)
#define INTC_PRIO_REG3		(INTC_BASE + 0x006c)

#define INTC_SRC_IRQ(_n)	(_n)
/* intc source list */

#define INTC_SRC_NMI		INTC_SRC_IRQ(0 )
#define INTC_SRC_UART0		INTC_SRC_IRQ(1 )
#define INTC_SRC_UART1      INTC_SRC_IRQ(2 )
#define INTC_SRC_UART2      INTC_SRC_IRQ(3 )
//#define       			INTC_SRC_IRQ(4 )
#define INTC_SRC_SPDIF      INTC_SRC_IRQ(5 )
#define INTC_SRC_CIR        INTC_SRC_IRQ(6 )
#define INTC_SRC_TWI0       INTC_SRC_IRQ(7 )
#define INTC_SRC_TWI1       INTC_SRC_IRQ(8 )
#define INTC_SRC_TWI2       INTC_SRC_IRQ(9 )
#define INTC_SRC_SPI0       INTC_SRC_IRQ(10)
#define INTC_SRC_SPI1       INTC_SRC_IRQ(11)

//#define        			INTC_SRC_IRQ(12)
#define INTC_SRC_TIMER0	    INTC_SRC_IRQ(13)
#define INTC_SRC_TIMER1		INTC_SRC_IRQ(14)
#define INTC_SRC_TIMER2     INTC_SRC_IRQ(15)
#define INTC_SRC_WDOG       INTC_SRC_IRQ(16)
#define INTC_SRC_RSB        INTC_SRC_IRQ(17)

#define INTC_SRC_DMA        INTC_SRC_IRQ(18)
//#define         			INTC_SRC_IRQ(19)
#define INTC_SRC_TP         INTC_SRC_IRQ(20)
#define INTC_SRC_AUDIO      INTC_SRC_IRQ(21)
#define INTC_SRC_LRADC      INTC_SRC_IRQ(22)
#define INTC_SRC_MMC0       INTC_SRC_IRQ(23)
#define INTC_SRC_MMC1       INTC_SRC_IRQ(24)
//#define    				INTC_SRC_IRQ(25)
#define INTC_SRC_USBOTG  	INTC_SRC_IRQ(26)
#define INTC_SRC_TVD   		INTC_SRC_IRQ(27)
#define INTC_SRC_TVE        INTC_SRC_IRQ(28)
#define INTC_SRC_LCD	    INTC_SRC_IRQ(29)
#define INTC_SRC_DEFE       INTC_SRC_IRQ(30)
#define INTC_SRC_DEBE      	INTC_SRC_IRQ(31)
#define INTC_SRC_CSI        INTC_SRC_IRQ(32)
#define INTC_SRC_DEITLA     INTC_SRC_IRQ(33)
#define INTC_SRC_VE    		INTC_SRC_IRQ(34)
#define INTC_SRC_I2S	    INTC_SRC_IRQ(35)
//#define   	 			INTC_SRC_IRQ(36)
//#define   	 			INTC_SRC_IRQ(37)
#define INTC_SRC_PDEINT     INTC_SRC_IRQ(38)
#define INTC_SRC_PEEINT     INTC_SRC_IRQ(39)
#define INTC_SRC_PFEINT     INTC_SRC_IRQ(40)
//#define      				INTC_SRC_IRQ(41)
//#define        			INTC_SRC_IRQ(42)
//#define        			INTC_SRC_IRQ(43)
//#define        			INTC_SRC_IRQ(44)
//#define      				INTC_SRC_IRQ(45)
//#define      				INTC_SRC_IRQ(46)
//#define 	    			INTC_SRC_IRQ(47)
//#define 					INTC_SRC_IRQ(48)
//#define         			INTC_SRC_IRQ(49)
//#define          			INTC_SRC_IRQ(50)
//#define       			INTC_SRC_IRQ(51)
//#define       			INTC_SRC_IRQ(52)
//#define       			INTC_SRC_IRQ(53)
//#define       			INTC_SRC_IRQ(54)
//#define       			INTC_SRC_IRQ(55)
//#define        			INTC_SRC_IRQ(56)
//#define        			INTC_SRC_IRQ(57)
//#define           		INTC_SRC_IRQ(58)
//#define       			INTC_SRC_IRQ(59)
//#define         			INTC_SRC_IRQ(60)
//#define         			INTC_SRC_IRQ(61)
//#define         			INTC_SRC_IRQ(62)
//#define         			INTC_SRC_IRQ(63)


#define INTC_IRQ_NUM        (64)

typedef void (*pIRQ_Handler)(void);
s32 irq_request(u32 irq_no, pIRQ_Handler hdle);
s32 irq_free(u32 irq_no);
s32 irq_enable(u32 irq_no);
s32 irq_disable(u32 irq_no);

void init_intc(void);
void intc_irq_handler(void);

#endif
