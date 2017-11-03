/*
*******************************************
*
* File    : printk.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
*******************************************
*/
#ifndef __PRINTK_H
#define __PRINTK_H

#ifdef DEBUG_ENABLE
void printk(const char *fmt, ...);
void init_printk_mutex(void);
#else
#define printk(...)
#define init_printk_mutex(...)
#endif

void hexdump(char *prompt, char *buf, int len);

#endif
