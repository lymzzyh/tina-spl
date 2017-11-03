/*
******************************************
*
* File    : serial.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
******************************************
*/
#ifndef __SERIAL_H
#define __SERIAL_H

void serial_init(void);
void serial_put_char(char c);
char serial_get_char(void);
u32 serial_puts(char* buf, u32 n);
u32 serial_gets(char* buf, u32 n);

#endif
