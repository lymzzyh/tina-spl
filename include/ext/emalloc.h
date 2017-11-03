/*
******************************************
*
* File    : emalloc.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
******************************************
*/
#ifndef __EMALLOC_H
#define __EMALLOC_H

s32 init_heap(u32 pHeapHead, u32 nHeapSize);
void *malloc(u32 size);
void *calloc(u32 size, u32 num_bytes);
void *realloc(void *p, u32 new_size);
void  free(void *p);

#endif
