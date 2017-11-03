/*
***********************************************
*
* File    : gpio.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
***********************************************
*/
#ifndef __GPIO_H
#define __GPIO_H

#include "types.h"

#define PIO_GPA                     (0)
#define PIO_GPB                     (1)
#define PIO_GPC                     (2)
#define PIO_GPD                     (3)
#define PIO_GPE                     (4)
#define PIO_GPF                     (5)

#define GPIO_A(_nr)                 (32*PIO_GPA + (_nr))
#define GPIO_B(_nr)                 (32*PIO_GPB + (_nr))
#define GPIO_C(_nr)                 (32*PIO_GPC + (_nr))
#define GPIO_D(_nr)                 (32*PIO_GPD + (_nr))
#define GPIO_E(_nr)                 (32*PIO_GPE + (_nr))
#define GPIO_F(_nr)                 (32*PIO_GPF + (_nr))

#define GPIO_A_NUM                  (4)
#define GPIO_B_NUM                  (4)
#define GPIO_C_NUM                  (4)
#define GPIO_D_NUM                  (22)
#define GPIO_E_NUM                  (13)
#define GPIO_F_NUM                  (6)

#define GET_GPIO_GRP(_nr)           ((_nr)>>5)            //nr/32
#define GET_GPIO_OS(_nr)            ((_nr)&0x1f)          //nr%32

#define GPIO_GRPBASE(_nr)           (PIO_BASE + 0x24*GET_GPIO_GRP(_nr) + 0x00)
#define GPIO_CFG_REG(_nr)           (GPIO_GRPBASE(_nr) + 0x00)
#define GPIO_DATA_REG(_nr)          (GPIO_GRPBASE(_nr) + 0x10)
#define GPIO_DRV_REG(_nr)           (GPIO_GRPBASE(_nr) + 0x14)
#define GPIO_PULL_REG(_nr)          (GPIO_GRPBASE(_nr) + 0x1c)

#define PIO_PULLUP                 (1)
#define PIO_PULLDOWN               (2)

/* gpio irq group */
#define PIO_INT_GRP_D              (1)
#define PIO_INT_GRP_E              (2)
#define PIO_INT_GRP_F              (3)

#define PIO_EINTD_NUM              (22)
#define PIO_EINTE_NUM              (13)
#define PIO_EINTF_NUM              (6)
#define PIO_EINTx_NUM(_grp)        (_grp == PIO_INT_GRP_D ? PIO_EINTD_NUM :	\
                                    _grp == PIO_INT_GRP_E ? PIO_EINTE_NUM :	\
                                    _grp == PIO_INT_GRP_F ? PIO_EINTF_NUM : 0)

#define PIO_EINT_TOTAL_NUM         (PIO_EINTD_NUM + PIO_EINTE_NUM + PIO_EINTF_NUM)

/* gpio irq number mapping */
#define PIO_INT_D(x)               ((PIO_INT_GRP_D << 8) | x)
#define PIO_INT_E(x)               ((PIO_INT_GRP_E << 8) | x)
#define PIO_INT_F(x)               ((PIO_INT_GRP_F << 8) | x)

/* gpio irq control base register */
#define PIO_EINT_GRP_BASE(_grp)    (PIO_BASE + 0x200 + 0x20 * ((_grp)-1) + 0x00)
#define PIO_EINT_CFG_REG(_nr)      (PIO_EINT_GRP_BASE((_nr) >> 8) + 0x00)
#define PIO_EINT_CTRL_REG(_nr)     (PIO_EINT_GRP_BASE((_nr) >> 8) + 0x10)
#define PIO_EINT_STA_REG(_nr)      (PIO_EINT_GRP_BASE((_nr) >> 8) + 0x14)
#define PIO_EINT_DBNC_REG(_nr)     (PIO_EINT_GRP_BASE((_nr) >> 8) + 0x18)

/* gpio irq trigger mode */
#define PIO_INT_POSEDGE             (0)
#define PIO_INT_NEGADGE             (1)
#define PIO_INT_HLEVEL              (2)
#define PIO_INT_LLEVEL              (3)
#define PIO_INT_DEDGE               (4)

typedef void (*gpio_callback)(u32 data);
void gpio_set_cfg(u32 pio_no, u32 num, u32 mode);
void gpio_set_pull(u32 pio_no, u32 num, u32 mode);
void gpio_set_drv(u32 pio_no, u32 num, u32 mode);
void gpio_set_val(u32 pio_no, u32 val);
u32 gpio_get_val(u32 pio_no);
s32 gpio_request_eintio(u32 eint_no, u32 mode, gpio_callback hdle, u32 data);
s32 gpio_free_eintio(u32 eint_no);

typedef void (*gpio_handler)(void* data);

typedef struct  {
	u32 eint;
	u32 gpio;
	u32 cfg;
} Eint_Map;

int init_gpio(void);
s32 init_gpio_irq(void);

/*************************************************************************
 * Examples 
 * gpio_set_cfg(GPIO_B(12), 1, 1); -  set GPIOB12 with config 1(only one gpio)
 * gpio_set_cfg(GPIO_B(12), 7, 3); -  set GPIOB12~B18 with config 3(7 gpios)
 * gpio_set_pull(GPIO_F(3), 1, PIO_PULLUP); -  pull high GPIOF3
 * gpio_set_pull(GPIO_I(2), 7, PIO_PULLDOWN); -  pull down gpioi2~8
 * gpio_set_val(GPIO_A(2), 1); output 1 on GPIOA2 
 **/
#endif
