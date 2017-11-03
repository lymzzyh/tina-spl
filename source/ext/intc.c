/*
***********************************************
*
* File    : timer.c
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-28
* Descript:
***********************************************
*/

#include "include.h"

#if 0

pIRQ_Handler irq_vector[INTC_IRQ_NUM];

static void null_irq_hdle(void)
{
	printk("No irq registered handler for this calling !!\n");
}

s32 irq_request(u32 irq, pIRQ_Handler handler)
{
	if (irq < INTC_IRQ_NUM) {
		irq_vector[irq] = handler;
		return irq;
	}
	printk("Wrong irq NO.(%d) to request\n", irq);
	return -1;
}

s32 irq_free(u32 irq)
{
	if (irq < INTC_IRQ_NUM) {
		irq_vector[irq] = null_irq_hdle;
	}
	return 0;
}

s32 irq_enable(u32 irq)
{
	u32 base_os = (irq >> 5) << 2;
	u32 bit_os = irq & 0x1f;

	if(irq >= INTC_IRQ_NUM)
		return -1;

	sr32(INTC_ENABLE_REG0 + base_os, bit_os, 1, 1);

	return 0;
}

s32 irq_disable(u32 irq)
{
	u32 base_os = (irq >> 5) << 2;
	u32 bit_os = irq & 0x1f;

	if(irq >= INTC_IRQ_NUM)
		return -1;

	sr32(INTC_ENABLE_REG0 + base_os, bit_os, 1, 0);

	return 0;
}

void intc_handler(void)
{
	u32 vect = readl(INTC_VECTOR_REG)>>2;
	if (irq_vector[vect] != null_irq_hdle)
		irq_vector[vect]();
}

void init_intc(void)
{
	u32 i;
	
	writel(0x0, INTC_PRIO_REG0);
	writel(0x0, INTC_PRIO_REG1);
	writel(0x0, INTC_PRIO_REG2);
	writel(0x0, INTC_PRIO_REG3);
	writel(0x0, INTC_FF_REG0);
	writel(0x0, INTC_FF_REG1);
	writel(0x0, INTC_RESP_REG0);
	writel(0x0, INTC_RESP_REG1);
	writel(0x0, INTC_MASK_REG0);
	writel(0x0, INTC_MASK_REG1);
	writel(0x0, INTC_ENABLE_REG0);
	writel(0x0, INTC_ENABLE_REG1);
	writel(0xffffffff, INTC_PEND_REG0);
	writel(0xffffffff, INTC_PEND_REG1);

	for(i=0; i<INTC_IRQ_NUM; i++)
		irq_vector[i] = null_irq_hdle;
}
#endif
