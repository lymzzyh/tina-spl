/*
 * libc/string/memcpy.c
 */

#include <types.h>

void * memcpy(void * dest, const void * src, size_t len)
{
	char * tmp = dest;
	const char * s = src;

	while (len--)
		*tmp++ = *s++;
	return dest;
}
