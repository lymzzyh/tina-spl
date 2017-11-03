/*
********************************************************************************************************
*
* File    : gpio.c
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
********************************************************************************************************
*/

#include "include.h"
/**
 *	static __inline void gpio_set_single_pio_cfg(u32 pio_no, u32 mode) ;
 *	Description:
 *
 *	Arguments:		NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  mode - config mode
 *	Return Value:
 */
static __inline void gpio_set_single_pio_cfg(u32 pio_no, u32 mode)
{
	u32 start = pio_no&0x1f;
	u32 cfg_addr = GPIO_CFG_REG(pio_no) + 4*(start>>3);
	u32 offs = (start&0x7)<<2;

	sr32(cfg_addr, offs, 4, mode);
}

/**
 *	__inline void gpio_set_single_pio_pull(u32 pio_no, u32 pull);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  pull - pull mode
 *	Return Value:
 */
static __inline void gpio_set_single_pio_pull(u32 pio_no, u32 pull)
{
	u32 start = pio_no&0x1f;
	u32 pull_addr = GPIO_PULL_REG(pio_no) + 4*(start>>4);
	u32 offs = (start&0xf)<<1;

	sr32(pull_addr, offs, 2, pull);
}

/**
 *	static __inline void gpio_set_single_pio_drv(u32 pio_no, u32 level);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  level - driver level
 *	Return Value:
 */
static __inline void gpio_set_single_pio_drv(u32 pio_no, u32 level)
{
	u32 start = pio_no&0x1f;
	u32 drv_addr = GPIO_DRV_REG(pio_no) + 4*(start>>4);
	u32 offs = (start&0xf)<<1;

	sr32(drv_addr, offs, 2, level);
}

/**
 *	void gpio_set_cfg(u32 pio_no, u32 num, u32 mode);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  num - number of continus pins to config
 *                  mode - config mode
 *	Return Value:
 */
void gpio_set_cfg(u32 pio_no, u32 num, u32 mode)
{
	u32 i;

	for (i=0; i<num; i++)
	    gpio_set_single_pio_cfg(pio_no+i, mode);
}

/**
 *	void gpio_set_pull(u32 pio_no, u32 num, u32 pull);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  num - number of continus pins to set
 *                  pull - pull mode
 *	Return Value:
 */
void gpio_set_pull(u32 pio_no, u32 num, u32 pull)
{
	u32 i;

	for (i=0; i<num; i++)
	    gpio_set_single_pio_pull(pio_no+i, pull);
}

/**
 *	void gpio_set_drv(u32 pio_no, u32 num, u32 level);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  num - number of continus pins to set
 *                  level - driver level
 *	Return Value:
 */
void gpio_set_drv(u32 pio_no, u32 num, u32 level)
{
	u32 i;

	for (i=0; i<num; i++)
	    gpio_set_single_pio_drv(pio_no+i, level);
}

/**
 *	void gpio_set_val(u32 pio_no, u32 val);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *                  val - value to set 0 or 1
 *	Return Value:
 */
void gpio_set_val(u32 pio_no, u32 val)
{
	u32 offs = pio_no&0x1f;
	u32 data_addr = GPIO_DATA_REG(pio_no);

	sr32(data_addr, offs, 1, val);
}

/**
 *	u32 gpio_get_val(u32 pio_no);
 *	Description:
 *
 *	Arguments:		pio_no - NO. of start pio. eg: GPIO_A(13), GPIO_B(21)
 *	Return Value:
 */
u32 gpio_get_val(u32 pio_no)
{
	u32 offs = pio_no&0x1f;

	return 0x1 & (readl(GPIO_DATA_REG(pio_no))>>offs);
}

#if 0
#ifndef FPGA_PLATFORM
static Eint_Map eint_map[] = {

	{PIO_INT_D(0 ), GPIO_D(0 ), 6},
	{PIO_INT_D(1 ), GPIO_D(1 ), 6},
	{PIO_INT_D(2 ), GPIO_D(2 ), 6},
	{PIO_INT_D(3 ), GPIO_D(3 ), 6},
	{PIO_INT_D(4 ), GPIO_D(4 ), 6},
	{PIO_INT_D(5 ), GPIO_D(5 ), 6},
	{PIO_INT_D(6 ), GPIO_D(6 ), 6},
	{PIO_INT_D(7 ), GPIO_D(7 ), 6},
	{PIO_INT_D(8 ), GPIO_D(8 ), 6},
	{PIO_INT_D(9 ), GPIO_D(9 ), 6},
	{PIO_INT_D(10), GPIO_D(10), 6},
	{PIO_INT_D(11), GPIO_D(11), 6},
	{PIO_INT_D(12), GPIO_D(12), 6},
	{PIO_INT_D(13), GPIO_D(13), 6},
	{PIO_INT_D(14), GPIO_D(14), 6},
	{PIO_INT_D(15), GPIO_D(15), 6},
	{PIO_INT_D(16), GPIO_D(16), 6},
	{PIO_INT_D(17), GPIO_D(17), 6},
	{PIO_INT_D(18), GPIO_D(18), 6},
	{PIO_INT_D(19), GPIO_D(19), 6},
	{PIO_INT_D(20), GPIO_D(20), 6},
	{PIO_INT_D(21), GPIO_D(21), 6},

	{PIO_INT_E(0 ), GPIO_E(0 ), 6},
	{PIO_INT_E(1 ), GPIO_E(1 ), 6},
	{PIO_INT_E(2 ), GPIO_E(2 ), 6},
	{PIO_INT_E(3 ), GPIO_E(3 ), 6},
	{PIO_INT_E(4 ), GPIO_E(4 ), 6},
	{PIO_INT_E(5 ), GPIO_E(5 ), 6},
	{PIO_INT_E(6 ), GPIO_E(6 ), 6},
	{PIO_INT_E(7 ), GPIO_E(7 ), 6},
	{PIO_INT_E(8 ), GPIO_E(8 ), 6},
	{PIO_INT_E(9 ), GPIO_E(9 ), 6},
	{PIO_INT_E(10), GPIO_E(10), 6},
	{PIO_INT_E(9 ), GPIO_E(11), 6},
	{PIO_INT_E(10), GPIO_E(12), 6},

	{PIO_INT_F(0 ), GPIO_F(0 ), 6},
	{PIO_INT_F(1 ), GPIO_F(1 ), 6},
	{PIO_INT_F(2 ), GPIO_F(2 ), 6},
	{PIO_INT_F(3 ), GPIO_F(3 ), 6},
	{PIO_INT_F(4 ), GPIO_F(4 ), 6},
	{PIO_INT_F(5 ), GPIO_F(5 ), 6},
};
#else
static Eint_Map eint_map[] = {
	{PIO_INT_D(0 ), GPIO_D(0 ), 6}
};
#endif

struct gpio_irq_vector {
	void (*callback)(u32 data);
	u32 data;
};

static struct gpio_irq_vector gpio_irq_d[PIO_EINTD_NUM];
static struct gpio_irq_vector gpio_irq_e[PIO_EINTE_NUM];
static struct gpio_irq_vector gpio_irq_f[PIO_EINTF_NUM];
static struct gpio_irq_vector* vector[] = {
	NULL, 
	gpio_irq_d,
	gpio_irq_e, 
	gpio_irq_f
};

static void gpio_irq_hdle(u32 group)
{
	u32 base = PIO_EINT_GRP_BASE(group);
	u32 en = readl(base + 0x10);
	u32 stat = readl(base + 0x14);
	u32 mskd_sta = en & stat;
	u32 i;
	
	for (i = 0; i < PIO_EINTx_NUM(group); i++) {
		if (mskd_sta & (1 << i)) {
			if (vector[group][i].callback)
				vector[group][i].callback(vector[group][i].data);
		}
	}
	writel(mskd_sta, base + 0x14);
}

static void gpio_d_irq_hdle(void)
{
	gpio_irq_hdle(PIO_INT_GRP_D);
}

static void gpio_e_irq_hdle(void)
{
	gpio_irq_hdle(PIO_INT_GRP_E);
}

static void gpio_f_irq_hdle(void)
{
	gpio_irq_hdle(PIO_INT_GRP_F);
}

s32 gpio_request_eintio(u32 eint_no, u32 mode, gpio_callback hdle, u32 data)
{
	u32 i = 0;
	u32 group = (eint_no >> 8) & 0xff;
	u32 number = eint_no & 0xff;
	u32 cfg_base = PIO_EINT_CFG_REG(eint_no) + 4 * (number >> 3);
	u32 en_base = PIO_EINT_CTRL_REG(eint_no);
	u32 offs = (number & 7) << 2;
	
	/* find this EINT IO */
	if (group == PIO_INT_GRP_E)
		i = PIO_EINTD_NUM;
	else if (group == PIO_INT_GRP_F)
		i = PIO_EINTD_NUM + PIO_EINTE_NUM;
	i += number;
	if (eint_no != eint_map[i].eint) {
		printk("No GPIO eint for group %d, number %d\n", group, number);
		return -1;
	}
	
	/* config gpio mode for interrupt */
	gpio_set_cfg(eint_map[i].gpio, 1, eint_map[i].cfg);
	gpio_set_pull(eint_map[i].gpio, 1, 1);	// pull up
	
	/* config gpio irq trigger mode */
	sr32(cfg_base, offs, 4, mode);
	/* enable irq */
	sr32(en_base, number, 1, 1);
	vector[group][number].callback = hdle;
	vector[group][number].data = data;
	return 0;
}

s32 gpio_free_eintio(u32 eint_no)
{
	u32 i = 0;
	u32 group = (eint_no >> 8) & 0xff;
	u32 number = eint_no & 0xff;
	u32 cfg_base = PIO_EINT_CFG_REG(eint_no) + 4 * (number >> 3);
	u32 en_base = PIO_EINT_CTRL_REG(eint_no);
	u32 offs = (number & 7) << 2;
	
	/* find this EINT IO */
	if (group == PIO_INT_GRP_E)
		i = PIO_EINTD_NUM;
	else if (group == PIO_INT_GRP_F)
		i = PIO_EINTD_NUM + PIO_EINTE_NUM;
	i += number;
	if (eint_no != eint_map[i].eint) {
		printk("No GPIO eint for group %d, number %d\n", group, number);
		return -1;
	}
	
	/* config gpio mode for interrupt */
	gpio_set_cfg(eint_map[i].gpio, 1, 0);	// input
	gpio_set_pull(eint_map[i].gpio, 1, 0);	// no pull
	
	/* config gpio irq trigger mode */
	sr32(cfg_base, offs, 4, 0);
	/* disable irq */
	sr32(en_base, number, 1, 0);
	vector[group][number].callback = NULL;
	vector[group][number].data = 0;
	
	return 0;
}

s32 init_gpio_irq(void)
{
	u32 i = 0;
	s32 irq;

	for (i=0; i<PIO_EINTD_NUM; i++) {
		gpio_irq_d[i].callback = NULL;
		gpio_irq_d[i].data = 0;
	}
	for (i=0; i<PIO_EINTE_NUM; i++) {
		gpio_irq_e[i].callback = NULL;
		gpio_irq_e[i].data = 0;
	}
	for (i=0; i<PIO_EINTF_NUM; i++) {
		gpio_irq_f[i].callback = NULL;
		gpio_irq_f[i].data = 0;
	}
	
	irq = irq_request(INTC_SRC_PDEINT, gpio_d_irq_hdle);
	if (irq < 0) {
		printk("Request gpio eint d hdle failed\n");
	}
	irq_enable(irq);
	
	irq = irq_request(INTC_SRC_PEEINT, gpio_e_irq_hdle);
	if (irq < 0) {
		printk("Request gpio eint e hdle failed\n");
	}
	irq_enable(irq);
	
	irq = irq_request(INTC_SRC_PFEINT, gpio_f_irq_hdle);
	if (irq < 0) {
		printk("Request gpio eint f hdle failed\n");
	}
	irq_enable(irq);
	return 0;
}
#endif
