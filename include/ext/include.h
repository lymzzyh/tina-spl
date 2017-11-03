/*
*********************************************
*
* File    : include.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
*********************************************
*/

#ifndef __INCLUDE_H
#define __INCLUDE_H

#include "configs.h"

/* c library */
#include "types.h"
#include "io.h"
#include "utils.h"
#include "emalloc.h"
#include "printk.h"
#include "command.h"

/* platform */
#include "platform.h"
#include "serial.h"
//#include "../arch/armv5/armv5.h"

#include "ccmu.h"
#include "dram.h"
#include "gpio.h"
#include "intc.h"
#include "timer.h"
#include "dma.h"
#include "sysctrl.h"
#include "pwm.h"


#define MY_CONFIG_SYS_CTRL_TEST
//#define CONFIG_DMA_TEST




#endif
