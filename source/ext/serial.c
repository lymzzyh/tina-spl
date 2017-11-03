/*
********************************************************************************************************
*
* File    : serial.c
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript: Base address of moduels
********************************************************************************************************
*/

#include "include.h"
#include <stdarg.h>

#define SUART_BAUDRATE	(115200)

#define SUART_BASE	(UART0_BASE)
#define SUART_CKID	(UART0_CKID)


#define SUART_RBR	(SUART_BASE + 0x00)
#define SUART_THR	(SUART_BASE + 0x00)
#define SUART_DLL	(SUART_BASE + 0x00)
#define SUART_DLH	(SUART_BASE + 0x04)
#define SUART_FCR	(SUART_BASE + 0x08)
#define SUART_LCR	(SUART_BASE + 0x0c)
#define SUART_USR	(SUART_BASE + 0x7c)
#define SUART_HALT	(SUART_BASE + 0xa4)

void serial_setio(void)
{
	gpio_set_cfg(GPIO_F(2), 1, 3);
	gpio_set_pull(GPIO_F(2), 1, 1);
	gpio_set_cfg(GPIO_F(4), 1, 3);
	gpio_set_pull(GPIO_F(4), 1, 1);
}

void serial_init(void)
{
	u32 p2clk;
	u32 df;
	u32 lcr;
	
	/* io config */
	serial_setio();
	/* enable clock */
	ccm_module_reset(SUART_CKID);
	ccm_clock_enable(SUART_CKID);
	p2clk = ccm_get_apb_clk();
	/* set baudrate */

	df = (p2clk + (SUART_BAUDRATE<<3))/(SUART_BAUDRATE<<4);
	lcr = readl(SUART_LCR);
	writel(1, SUART_HALT);
	writel(lcr|0x80, SUART_LCR);
	writel(df>>8, SUART_DLH);
	writel(df&0xff, SUART_DLL);
	writel(lcr&(~0x80), SUART_LCR);
	writel(0, SUART_HALT);
	/* set mode */
	writel(3, SUART_LCR);
	/* enable fifo */
	writel(7, SUART_FCR);
}

void serial_put_char(char c)
{
	while (!(readl(SUART_USR) & 2));
	writel(c, SUART_THR);
}

char serial_get_char(void)
{
	u32 time = 0xffff;
	while(!(readl(SUART_USR)&0x08) && time);
	if (!time)
		return 0;
	return readl(SUART_RBR);
}

u32 serial_puts(char* buf, u32 n)
{
	u32 i;

	for (i=0; i<n; i++)
		serial_put_char(buf[i]);

	return n;
}

u32 serial_gets(char* buf, u32 n)
{
	u32 i;
	char c;
	
	for (i=0; i<n; i++) {
		c = serial_get_char();
		if (c == 0)
			break;
		buf[i] = c;
	}
	return i+1;
}
