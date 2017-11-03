#include <xboot.h>

/*
 * console_write for low level function
 */
#define console_putc(c)		sys_uart_putc((char)(c))

static int vpf_str_to_num(const char * fmt, int * resnum)
{
	const char * cptr;
	int	res, digit, is_digit;

	res = 0;
	for(cptr = fmt; *fmt != '\0'; cptr++)
	{
		is_digit = (*cptr >= '0' && *cptr <= '9');
		if(!is_digit)
			break;
		digit = *cptr - '0';
		res *= 10;
		res += digit;
	}
	*resnum = res;
	return ((int)(cptr - fmt));
}

static void vpf_num_to_str(uint32_t a, int is_hex, int pad_len, int pad_char)
{
	char buf[32];
	uint32_t base;
	int	bufidx, i;

	for(i = 0; i < sizeof(buf); i++)
		buf[i] = pad_char;
	base = 10;
	if(is_hex)
		base = 16;

	bufidx = 0;
	do {
		buf[bufidx] = "0123456789abcdef" [ a % base ];
		a /= base;
		bufidx++;
	} while (a > 0);

	if(pad_len > 0)
	{
		if(pad_len >= sizeof(buf))
			pad_len = sizeof(buf) - 1;
		if(bufidx < pad_len)
			bufidx = pad_len;
	}
	buf[bufidx] = '\0';

	for(i = bufidx - 1; i >= 0; i--)
		console_putc(buf[i]);
}

static int vpf(const char * fmt, va_list va)
{
	const char * cptr, * prefmtptr;
	int	f, c, va_int, pad_len, pad_char, i;
	unsigned char t;
	
	pad_char = ' ';
	for(cptr = fmt; *cptr != '\0'; cptr++)
	{
		f = 0;
		pad_len = 0;
		c = *cptr;
		prefmtptr = cptr;
		if(*cptr == '%')
		{
			prefmtptr = cptr;
			cptr++;
			if(*cptr >= '0' && *cptr <= '9')
				cptr += vpf_str_to_num(cptr, &pad_len);
			f = *cptr;
		}
		if((f == 'd') || (f == 'x'))
		{
			va_int = va_arg(va, int);
			vpf_num_to_str(va_int, f == 'x', pad_len, pad_char);
		}
		else
		{
			for(i = 0; i < (cptr - prefmtptr); i++)
				console_putc(prefmtptr[i]);
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
