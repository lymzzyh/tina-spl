/*
***********************************************
*
* File    : dma.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-28
* Descript:
***********************************************
*/

#ifndef __DMA_H
#define __DMA_H

#define DDMA_CH_START			(4)
/* register difine */
#define DMA_IRQ_EN_REG			(DMA_BASE + 0x00)
#define DMA_IRQ_PEND_REG		(DMA_BASE + 0x04)
#define NDMA_AUTO_GATE_REG		(DMA_BASE + 0x08)

#define NDMA_CTRL_REG(ch)		(DMA_BASE + 0x0100 + ((ch) << 5) + 0x00)
#define NDMA_SADDR_REG(ch)		(DMA_BASE + 0x0100 + ((ch) << 5) + 0x04)
#define NDMA_DADDR_REG(ch)		(DMA_BASE + 0x0100 + ((ch) << 5) + 0x08)
#define NDMA_BCNT_REG(ch)		(DMA_BASE + 0x0100 + ((ch) << 5) + 0x0c)

#define DDMA_CTRL_REG(ch)		(DMA_BASE + 0x0300 + ch*0x20 + 0x00)
#define DDMA_SADDR_REG(ch)		(DMA_BASE + 0x0300 + ch*0x20 + 0x04)
#define DDMA_DADDR_REG(ch)		(DMA_BASE + 0x0300 + ch*0x20 + 0x08)
#define DDMA_BCNT_REG(ch)		(DMA_BASE + 0x0300 + ch*0x20 + 0x0c)
#define DDMA_PARAM_REG(ch)		(DMA_BASE + 0x0300 + ch*0x20 + 0x18)
#define DDMA_DATA_REG(ch)		(DMA_BASE + 0x0300 + ch*0x20 + 0x1c)

#define DMA_CHANN_NUM			(8)
/* dma descriptor */
#define STATIC_ALLOC_DMA_DES
struct dma_des {
	u32 config;
	u32 saddr;
	u32 daddr;
	u32 bcnt;
	u32 param;
	struct dma_des *next;
};

enum {DMA_TYPE_NORMAL, DMA_TYPE_DEDICATE};
enum {DMA_CFG_BST1, DMA_CFG_BST4};
enum {DMA_CFG_WID8, DMA_CFG_WID16, DMA_CFG_WID32};
enum {DMA_LINEAR, DMA_IO};

#define DMA_CHAN_LOADING	(0x80000000)

/* DMA drq type */
#define NDMA_TYPE_IR				 ((DMA_TYPE_NORMAL << 8) | 0x00)
#define NDMA_TYPE_SPDIF				 ((DMA_TYPE_NORMAL << 8) | 0x01)
#define NDMA_TYPE_SPI0				 ((DMA_TYPE_NORMAL << 8) | 0x04)
#define NDMA_TYPE_SPI1				 ((DMA_TYPE_NORMAL << 8) | 0x05)
#define NDMA_TYPE_UART0				 ((DMA_TYPE_NORMAL << 8) | 0x08)
#define NDMA_TYPE_UART1				 ((DMA_TYPE_NORMAL << 8) | 0x09)
#define NDMA_TYPE_UART2				 ((DMA_TYPE_NORMAL << 8) | 0x0A)
#define NDMA_TYPE_CODEC				 ((DMA_TYPE_NORMAL << 8) | 0x0C)
#define NDMA_TYPE_DAUDIO			 ((DMA_TYPE_NORMAL << 8) | 0x0E)
#define NDMA_TYPE_SRAM				 ((DMA_TYPE_NORMAL << 8) | 0x10)
#define NDMA_TYPE_SDRAM				 ((DMA_TYPE_NORMAL << 8) | 0x11)
#define NDMA_TYPE_USB				 ((DMA_TYPE_NORMAL << 8) | 0x12)

#define DDMA_TYPE_SRAM				 ((DMA_TYPE_DEDICATE << 8) | 0x00)
#define DDMA_TYPE_SDRAM				 ((DMA_TYPE_DEDICATE << 8) | 0x01)
#define DDMA_TYPE_LCD				 ((DMA_TYPE_DEDICATE << 8) | 0x02)
#define DDMA_TYPE_USB				 ((DMA_TYPE_DEDICATE << 8) | 0x04)

/* NDMA source drq config */
#define NDMA_CFG_SRC_DRQ_IR			 ((0x1f & NDMA_TYPE_IR	   ) << 0)
#define NDMA_CFG_SRC_DRQ_SPDIF		 ((0x1f & NDMA_TYPE_SPDIF  ) << 0)
#define NDMA_CFG_SRC_DRQ_SPI0		 ((0x1f & NDMA_TYPE_SPI0   ) << 0)
#define NDMA_CFG_SRC_DRQ_SPI1		 ((0x1f & NDMA_TYPE_SPI1   ) << 0)
#define NDMA_CFG_SRC_DRQ_UART0		 ((0x1f & NDMA_TYPE_UART0  ) << 0)
#define NDMA_CFG_SRC_DRQ_UART1		 ((0x1f & NDMA_TYPE_UART1  ) << 0)
#define NDMA_CFG_SRC_DRQ_UART2		 ((0x1f & NDMA_TYPE_UART2  ) << 0)
#define NDMA_CFG_SRC_DRQ_CODEC		 ((0x1f & NDMA_TYPE_CODEC  ) << 0)
#define NDMA_CFG_SRC_DRQ_DAUDIO		 ((0x1f & NDMA_TYPE_DAUDIO ) << 0)
#define NDMA_CFG_SRC_DRQ_SRAM		 ((0x1f & NDMA_TYPE_SRAM   ) << 0)
#define NDMA_CFG_SRC_DRQ_SDRAM		 ((0x1f & NDMA_TYPE_SDRAM  ) << 0)
#define NDMA_CFG_SRC_DRQ_USB		 ((0x1f & NDMA_TYPE_USB    ) << 0)

/* NDMA destination drq config */
#define NDMA_CFG_DST_DRQ_IR			 ((0x1f & NDMA_TYPE_IR	   ) << 16)
#define NDMA_CFG_DST_DRQ_SPDIF		 ((0x1f & NDMA_TYPE_SPDIF  ) << 16)
#define NDMA_CFG_DST_DRQ_SPI0		 ((0x1f & NDMA_TYPE_SPI0   ) << 16)
#define NDMA_CFG_DST_DRQ_SPI1		 ((0x1f & NDMA_TYPE_SPI1   ) << 16)
#define NDMA_CFG_DST_DRQ_UART0		 ((0x1f & NDMA_TYPE_UART0  ) << 16)
#define NDMA_CFG_DST_DRQ_UART1		 ((0x1f & NDMA_TYPE_UART1  ) << 16)
#define NDMA_CFG_DST_DRQ_UART2		 ((0x1f & NDMA_TYPE_UART2  ) << 16)
#define NDMA_CFG_DST_DRQ_CODEC		 ((0x1f & NDMA_TYPE_CODEC  ) << 16)
#define NDMA_CFG_DST_DRQ_DAUDIO		 ((0x1f & NDMA_TYPE_DAUDIO ) << 16)
#define NDMA_CFG_DST_DRQ_SRAM		 ((0x1f & NDMA_TYPE_SRAM   ) << 16)
#define NDMA_CFG_DST_DRQ_SDRAM		 ((0x1f & NDMA_TYPE_SDRAM  ) << 16)
#define NDMA_CFG_DST_DRQ_USB		 ((0x1f & NDMA_TYPE_USB    ) << 16)

/* DDMA source drq config */
#define DDMA_CFG_SRC_DRQ_SRAM		 ((0x1f & DDMA_TYPE_SRAM   ) << 0)
#define DDMA_CFG_SRC_DRQ_SDRAM		 ((0x1f & DDMA_TYPE_SDRAM  ) << 0)
#define DDMA_CFG_SRC_DRQ_USB		 ((0x1f & DDMA_TYPE_USB    ) << 0)
#define DDMA_CFG_SRC_DRQ_LCD		 ((0x1f & DDMA_TYPE_LCD    ) << 0)

/* DDMA destination drq config */
#define DDMA_CFG_DST_DRQ_SRAM		 ((0x1f & DDMA_TYPE_SRAM   ) << 16)
#define DDMA_CFG_DST_DRQ_SDRAM		 ((0x1f & DDMA_TYPE_SDRAM  ) << 16)
#define DDMA_CFG_DST_DRQ_USB		 ((0x1f & DDMA_TYPE_USB    ) << 16)
#define DDMA_CFG_DST_DRQ_LCD		 ((0x1f & DDMA_TYPE_LCD    ) << 16)

/* DMA source burst length and width */
#define NDMA_CFG_SRC_BST1_WIDTH8     ((DMA_CFG_BST1 << 7) | (DMA_CFG_WID8 << 8))
#define NDMA_CFG_SRC_BST1_WIDTH16    ((DMA_CFG_BST1 << 7) | (DMA_CFG_WID16<< 8))
#define NDMA_CFG_SRC_BST1_WIDTH32    ((DMA_CFG_BST1 << 7) | (DMA_CFG_WID32<< 8))
#define NDMA_CFG_SRC_BST4_WIDTH8     ((DMA_CFG_BST4 << 7) | (DMA_CFG_WID8 << 8))
#define NDMA_CFG_SRC_BST4_WIDTH16    ((DMA_CFG_BST4 << 7) | (DMA_CFG_WID16<< 8))
#define NDMA_CFG_SRC_BST4_WIDTH32    ((DMA_CFG_BST4 << 7) | (DMA_CFG_WID32<< 8))

#define DDMA_CFG_SRC_BST1_WIDTH8     ((DMA_CFG_BST1 << 7) | (DMA_CFG_WID8 << 8))
#define DDMA_CFG_SRC_BST1_WIDTH16    ((DMA_CFG_BST1 << 7) | (DMA_CFG_WID16<< 8))
#define DDMA_CFG_SRC_BST1_WIDTH32    ((DMA_CFG_BST1 << 7) | (DMA_CFG_WID32<< 8))
#define DDMA_CFG_SRC_BST4_WIDTH8     ((DMA_CFG_BST4 << 7) | (DMA_CFG_WID8 << 8))
#define DDMA_CFG_SRC_BST4_WIDTH16    ((DMA_CFG_BST4 << 7) | (DMA_CFG_WID16<< 8))
#define DDMA_CFG_SRC_BST4_WIDTH32    ((DMA_CFG_BST4 << 7) | (DMA_CFG_WID32<< 8))

/* DMA destination burst length and width */
#define NDMA_CFG_DST_BST1_WIDTH8     ((DMA_CFG_BST1 << 23) | (DMA_CFG_WID8 << 24))
#define NDMA_CFG_DST_BST1_WIDTH16    ((DMA_CFG_BST1 << 23) | (DMA_CFG_WID16<< 24))
#define NDMA_CFG_DST_BST1_WIDTH32    ((DMA_CFG_BST1 << 23) | (DMA_CFG_WID32<< 24))
#define NDMA_CFG_DST_BST4_WIDTH8     ((DMA_CFG_BST4 << 23) | (DMA_CFG_WID8 << 24))
#define NDMA_CFG_DST_BST4_WIDTH16    ((DMA_CFG_BST4 << 23) | (DMA_CFG_WID16<< 24))
#define NDMA_CFG_DST_BST4_WIDTH32    ((DMA_CFG_BST4 << 23) | (DMA_CFG_WID32<< 24))

#define DDMA_CFG_DST_BST1_WIDTH8     ((DMA_CFG_BST1 << 23) | (DMA_CFG_WID8 << 24))
#define DDMA_CFG_DST_BST1_WIDTH16    ((DMA_CFG_BST1 << 23) | (DMA_CFG_WID16<< 24))
#define DDMA_CFG_DST_BST1_WIDTH32    ((DMA_CFG_BST1 << 23) | (DMA_CFG_WID32<< 24))
#define DDMA_CFG_DST_BST4_WIDTH8     ((DMA_CFG_BST4 << 23) | (DMA_CFG_WID8 << 24))
#define DDMA_CFG_DST_BST4_WIDTH16    ((DMA_CFG_BST4 << 23) | (DMA_CFG_WID16<< 24))
#define DDMA_CFG_DST_BST4_WIDTH32    ((DMA_CFG_BST4 << 23) | (DMA_CFG_WID32<< 24))

/* IO mode */
#define NDMA_CFG_SRC_LINEAR          (DMA_LINEAR << 5)
#define NDMA_CFG_SRC_IO              (DMA_IO << 5)
#define NDMA_CFG_DST_LINEAR          (DMA_LINEAR << 21)
#define NDMA_CFG_DST_IO              (DMA_IO << 21)

#define DDMA_CFG_SRC_LINEAR          (DMA_LINEAR << 5)
#define DDMA_CFG_SRC_IO              (DMA_IO << 5)
#define DDMA_CFG_DST_LINEAR          (DMA_LINEAR << 21)
#define DDMA_CFG_DST_IO              (DMA_IO << 21)

/* NDMA wait */
#define NDMA_CFG_WAIT(x)			 ((x & 7) << 26)

/* DMA Continue */
#define NDMA_CFG_CONTINUE_MODE		 (1U << 29)
#define DDMA_CFG_CONTINUE_MODE		 (1U << 29)

/* DMA irq flags */
#define DMA_HALF_PKG_IRQFLAG		 (1 << 0)
#define DMA_FULL_PKG_IRQFLAG		 (1 << 1)
#define DMA_USE_CONTINUE_MODE		 (1 << 2)
#define DMA_IRQ_FLAG_MASK			 (DMA_HALF_PKG_IRQFLAG|DMA_FULL_PKG_IRQFLAG)

typedef void (*DMAHdle)(u32 data);

void init_dma(void);
s32 dma_request(u32 dma_type, DMAHdle hdle, u32 flag, u32 data);
s32 dma_release(u32 chan);
s32 dma_setup(u32 chan, u32 config, u32 param);
s32 dma_enqueue(u32 chan, u32 src, u32 dest, u32 len);
s32 dma_start(u32 chan);
u32 dma_finish(u32 chan);
void dma_stop(u32 chan);

void default_dma(void);
s32 dma_test(void);
#endif
