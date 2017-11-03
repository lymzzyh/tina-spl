#include <main.h>
#include <types.h>
#include <gpio.h>

extern void aw_delay(volatile unsigned n);

int xboot_main(int argc, char * argv[])
{
	int i = 0;

//	CPUFrq(1, 200);
	gpio_set_cfg(GPIO_A(0), 1, 1);
	gpio_set_pull(GPIO_A(0), 1, 1);

	while(i++ < 5)
	{
		gpio_set_val(GPIO_A(0), 0);
		aw_delay(50000);
		gpio_set_val(GPIO_A(0), 1);
		aw_delay(50000);
	}

//	serial_init();

	while(1)
	{
		gpio_set_val(GPIO_A(0), 0);
		aw_delay(10000);
		gpio_set_val(GPIO_A(0), 1);
		aw_delay(10000);
//		serial_put_char('a');
	}

	return 0;
}
