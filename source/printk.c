#include <xboot.h>

/*
 * console_write for low level function
 */
#define console_putc(c)	sys_uart_putc((char)(c))
extern void sys_uart_putc(char c);

static int vpf_str_to_num(const char * fmt, int * num)
{
	const char * p;
	int	res, d, isd;

	res = 0;
	for(p = fmt; *fmt != '\0'; p++)
	{
		isd = (*p >= '0' && *p <= '9');
		if(!isd)
			break;
		d = *p - '0';
		res *= 10;
		res += d;
	}
	*num = res;
	return ((int)(p - fmt));
}

static void vpf_num_to_str(uint32_t a, int ish, int pl, int pc)
{
	char buf[32];
	uint32_t base;
	int	idx, i;

	for(i = 0; i < sizeof(buf); i++)
		buf[i] = pc;
	base = 10;
	if(ish)
		base = 16;

	idx = 0;
	do {
		buf[idx] = "0123456789abcdef" [ a % base ];
		a /= base;
		idx++;
	} while (a > 0);

	if(pl > 0)
	{
		if(pl >= sizeof(buf))
			pl = sizeof(buf) - 1;
		if(idx < pl)
			idx = pl;
	}
	buf[idx] = '\0';

	for(i = idx - 1; i >= 0; i--)
		console_putc(buf[i]);
}

static int vpf(const char * fmt, va_list va)
{
	const char * p, * q;
	int	f, c, vai, pl, pc, i;
	unsigned char t;
	
	pc = ' ';
	for(p = fmt; *p != '\0'; p++)
	{
		f = 0;
		pl = 0;
		c = *p;
		q = p;
		if(*p == '%')
		{
			q = p;
			p++;
			if(*p >= '0' && *p <= '9')
				p += vpf_str_to_num(p, &pl);
			f = *p;
		}
		if((f == 'd') || (f == 'x'))
		{
			vai = va_arg(va, int);
			vpf_num_to_str(vai, f == 'x', pl, pc);
		}
		else
		{
			for(i = 0; i < (p - q); i++)
				console_putc(q[i]);
			t = (unsigned char)(f != 0 ? f : c);
			console_putc(t);
		}
	}
	return 0;
}

int printk(const char * fmt, ...)
{
	va_list	va;

	va_start(va, fmt);
	vpf(fmt, va);
	va_end(va);
	return 0;
}
