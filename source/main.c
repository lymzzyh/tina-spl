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
		printk("i = %d\r\n", i++);
	}

	while(1);
	return 0;
}
