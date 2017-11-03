/*
********************************************
*
* File    : utils.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
********************************************
*/
#ifndef __ESTRING_H
#define __ESTRING_H

#define RET_OK		(0)
#define RET_FAIL	(-1)
#define RET_TRUE	(0)
#define RET_FALSE	(-1)

#define BIT0		(1U <<  0)
#define BIT1		(1U <<  1)
#define BIT2		(1U <<  2)
#define BIT3		(1U <<  3)
#define BIT4		(1U <<  4)
#define BIT5		(1U <<  5)
#define BIT6		(1U <<  6)
#define BIT7		(1U <<  7)
#define BIT8		(1U <<  8)
#define BIT9		(1U <<  9)
#define BIT10		(1U << 10)
#define BIT11		(1U << 11)
#define BIT12		(1U << 12)
#define BIT13		(1U << 13)
#define BIT14		(1U << 14)
#define BIT15		(1U << 15)
#define BIT16		(1U << 16)
#define BIT17		(1U << 17)
#define BIT18		(1U << 18)
#define BIT19		(1U << 19)
#define BIT20		(1U << 20)
#define BIT21		(1U << 21)
#define BIT22		(1U << 22)
#define BIT23		(1U << 23)
#define BIT24		(1U << 24)
#define BIT25		(1U << 25)
#define BIT26		(1U << 26)
#define BIT27		(1U << 27)
#define BIT28		(1U << 28)
#define BIT29		(1U << 29)
#define BIT30		(1U << 30)
#define BIT31		(1U << 31)

#define max(x, y)	(((x)<(y)) ? (y) : (x))
#define min(x, y)	(((x)<(y)) ? (x) : (y))
	
#define isdigit(c)	((c) >= '0' && (c) <= '9')
#define isupper(c)	((c) >= 'A' && (c) <= 'Z')
#define islower(c)	((c) >= 'a' && (c) <= 'z')
#define isxdigit(c)	(((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F') || ((c) >= '0' && (c) <= '9'))
#define toupper(c)	(islower(c) ? ((c) - ('a' - 'A')) : (c))
#define tolower(c)	(isupper(c) ? ((c) - ('A' - 'a')) : (c))
#define isascii(c)	(((unsigned char)(c))<=0x7f)
#define isprint(c)	((((unsigned char)(c))>=32 && ((unsigned char)(c))<=126) \
			|| (((unsigned char)(c))>=160 && ((unsigned char)(c))<=255))

void* _strcpy(void* dest, void * src);
int _strlen(const void* str);
int _strcmp(const void* dest, const void* src);
void* _memset(void* str, int c, u32 len);
void* _memcpy(void* dest, const void* src, u32 size);
int _memcmp(const void* dest, const void* src, u32 size);

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
int strict_strtoul(const char *cp, unsigned int base, unsigned long *res);
long simple_strtol(const char *cp,char **endp,unsigned int base);
int ustrtoul(const char *cp, char **endp, unsigned int base);
unsigned long long simple_strtoull (const char *cp, char **endp, unsigned int base);


static __inline void aw_clr_bitmap(u32* flags, u32 pos)
{
	flags[pos>>5] &= ~(0x1U<<(pos&0x1f));
}

static __inline void aw_set_bitmap(u32* flags, u32 pos)
{
	flags[pos>>5] |= 0x1U<<(pos&0x1f);
}

static __inline u32 aw_get_bitmap(u32* flags, u32 pos)
{
	return (flags[pos>>5]>>(pos&0x1f))& 0x1;
}

s16 aw_rand(s32 *seed);
//s32 aw_rand_byte_data_gen(s32 seed, u32 dst_addr, u32 byte_count);
void aw_delay (u32 n);
u32 aw_endian4(u32 data);
u32 aw_endian2(u32 data);
//u32 aw_hexformat(u32 data, u32 mask);
//u32 aw_hexunformat(u32 data, u32 mask);
//u32 aw_module(const u32 x, const u32 y);   
u32 aw_log2(const u32 x);
//u32 aw_hex2dec(const u32 x);
//u32 aw_divider(const u32 x, const u32 y);

u32 aw_reg_default_check(const u32 reg_base, const u32* reg_default_table);
u32 aw_reg_rw_check(const u32 reg_base, const u32* reg_rw_table);
u32 reg_wr_cmp(u32 addr, u32 wval, u32 cval);

void pattern_end(u32 flag);
void mem_init(u32 init_idx);
s32 mem_cmp(u32 saddr, u32 daddr, u32 len);
void mem_dump(u32 fd, u32 addr, u32 len);
void pattern_goto(u32 step);
void pattern_mod_goto(u32 mod, u32 step);

#endif
