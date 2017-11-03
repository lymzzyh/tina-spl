#include <xboot.h>

static void __delay(volatile uint32_t loop)
{
	for(; loop > 0; loop--);
}

void udelay(uint32_t us)
{
	__delay(us * 2);
}

void mdelay(uint32_t ms)
{
	udelay(ms * 1000);
}

void led_init(void)
{
	virtual_addr_t addr;
	u32_t val;

	/* Config GPIOA0 to GPIO output and pull up */
	addr = 0x01c20800 + 0x00;
	val = read32(addr);
	val &= ~(0xf << ((0 & 0x7) << 2));
	val |= ((0x1 & 0x7) << ((0 & 0x7) << 2));
	write32(addr, val);

	addr = 0x01c20800 + 0x1c;
	val = read32(addr);
	val &= ~(0x1 << ((0 & 0xf) << 1));
	val |= (0x1 << ((0 & 0xf) << 1));
	write32(addr, val);
}

void led_set_level(int level)
{
	virtual_addr_t addr;
	u32_t val;

	/* Set GPIOA0 level */
	addr = 0x01c20800 + 0x10;
	val = read32(addr);
	val &= ~(1 << 0);
	val |= (!!level) << 0;
	write32(addr, val);
}

int xboot_main(int argc, char * argv[])
{
	int i = 0;
	char fmt[16];
	fmt[0] = 'i';
	fmt[1] = ' ';
	fmt[2] = '=';
	fmt[3] = ' ';
	fmt[4] = '%';
	fmt[5] = 'x';
	fmt[6] = '\r';
	fmt[7] = '\n';
	fmt[8] = 0;

	led_init();

	for(i = 0; i < 5; i++)
	{
		led_set_level(0);
		mdelay(500);
		led_set_level(1);
		mdelay(500);

		sys_uart_putc('X');
	}

	for(i = 0; i < 10000; i++)
	{
		led_set_level(0);
		mdelay(500);
		led_set_level(1);
		mdelay(500);

		printk(fmt, i);
	}

	while(1);
	return 0;
}
