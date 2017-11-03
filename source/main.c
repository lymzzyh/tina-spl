#include <xboot.h>

static void  aw_delay(volatile unsigned n)
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
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
		__asm__ __volatile__("nop" ::: "memory", "cc");
	}
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
	fmt[5] = 'd';
	fmt[6] = '\r';
	fmt[7] = '\n';
	fmt[8] = 0;

	//gpio_set_cfg(GPIO_A(0), 1, 1);
	//gpio_set_pull(GPIO_A(0), 1, 1);

	for(i = 0; i < 5; i++)
	{
		//gpio_set_val(GPIO_A(0), 0);
		aw_delay(50000);
		//gpio_set_val(GPIO_A(0), 1);
		aw_delay(50000);
		sys_uart_putc('X');
	}

	for(i = 0; i < 500000; i++)
	{
		//gpio_set_val(GPIO_A(0), 0);
		aw_delay(50000);
	//	gpio_set_val(GPIO_A(0), 1);
		aw_delay(50000);
		printk(fmt, i);
	}

	while(1);
	return 0;
}
