/*
***********************************************
*
* File    : timer.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-28
* Descript:
***********************************************
*/
#ifndef __TIMER__H
#define __TIMER__H

/* register define */
#define TIMER_IRQ_EN		(TIMER_BASE + 0x00)
#define TIMER_IRQ_PEND		(TIMER_BASE + 0x04)

#define TIMER_CTRL(_n)		(TIMER_BASE + 0x10*(_n) + 0x10)
#define TIMER_INTV(_n)		(TIMER_BASE + 0x10*(_n) + 0x14)
#define TIMER_CURR(_n)		(TIMER_BASE + 0x10*(_n) + 0x18)

#define TIMER0_CTRL   		(TIMER_BASE + 0x10)
#define TIMER0_INTV			(TIMER_BASE + 0x14)
#define TIMER0_CURR			(TIMER_BASE + 0x18)

#define TIMER1_CTRL   		(TIMER_BASE + 0x20)
#define TIMER1_INTV			(TIMER_BASE + 0x24)
#define TIMER1_CURR			(TIMER_BASE + 0x28)

#define TIMER2_CTRL   		(TIMER_BASE + 0x30)
#define TIMER2_INTV			(TIMER_BASE + 0x34)
#define TIMER2_CURR			(TIMER_BASE + 0x38)

struct Timer {
	u32 timer_no;
	u32 expires;
	volatile u32 jiffies;
	void (*function)(u32);
	u32 data;
	u32 irq;
};

void init_timer(void);
void default_timer(void);
void mdelay(u32 ms);
void udelay(u32 us);
u32 jiffies(void);

#endif
