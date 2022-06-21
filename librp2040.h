#ifndef LIBRP2040_H
#define LIBRP2040_H

/* functions declarations at the end */


#define NVIC ((struct mcu_nvic *)0xE000E100)

struct mcu_nvic {

	/* 0x00: Interrupt Set Enable Register */
	uint32_t volatile ISER;

	/* 0x04 */
	uint8_t RESERVED1[0x80-0x04];

	/* 0x80: Interrupt Clear Enable Register */
	uint32_t volatile ICER;

	/* 0x84 */
	uint8_t RESERVED2[0x100-0x84];

	/* 0x100: Interrupt Set-Pending Register */
	uint32_t volatile ISPR;

	/* 0x104 */
	uint8_t RESERVED3[0x180-0x104];

	/* 0x180: Interrupt Clear-Pending Register */
	uint32_t volatile ICPR;

	/* 0x184 */
	uint8_t RESERVED4[0x300-0x184];

	/* 0x300: Interrupt Priority Registers */
	uint32_t volatile IPR[8];

};


#define XIP_CTRL ((struct mcu_xip_ctrl *)0x14000000)

struct mcu_xip_ctrl {

	/* 0x00: Cache control */
	uint32_t volatile CTRL;
	/* When 1, the cache memories are powered down. */
#define XIP_CTRL_CTRL_POWER_DOWN				(1u << 3)
	/* When 1, writes to any alias other than 0x0 (caching, allocating) */
#define XIP_CTRL_CTRL_ERR_BADWRITE				(1u << 1)
	/* When 1, enable the cache. */
#define XIP_CTRL_CTRL_EN					(1u << 0)

	/* 0x04: Cache Flush control */
	uint32_t volatile FLUSH;
	/* Write 1 to flush the cache. */
#define XIP_CTRL_FLUSH_FLUSH					(1u << 0)

	/* 0x08: Cache Status */
	uint32_t volatile STAT;
	/* When 1, indicates the XIP streaming FIFO is completely full. */
#define XIP_CTRL_STAT_FIFO_FULL					(1u << 2)
	/* When 1, indicates the XIP streaming FIFO is completely empty. */
#define XIP_CTRL_STAT_FIFO_EMPTY				(1u << 1)
	/* Reads as 0 while a cache flush is in progress, and 1 otherwise. */
#define XIP_CTRL_STAT_FLUSH_READY				(1u << 0)

	/* 0x0C: Cache Hit counter */
	uint32_t volatile CTR_HIT;

	/* 0x10: Cache Access counter */
	uint32_t volatile CTR_ACC;

	/* 0x14: FIFO stream address */
	uint32_t volatile STREAM_ADDR;
	/* The address of the next word to be streamed from flash to the streaming FIFO. */
#define XIP_CTRL_STREAM_ADDR_STREAM_ADDR_Msk			(0x3FFFFFFFu << 2)
#define XIP_CTRL_STREAM_ADDR_STREAM_ADDR_Pos			2u

	/* 0x18: FIFO stream control */
	uint32_t volatile STREAM_CTR;
	/* Write a nonzero value to start a streaming read. */
#define XIP_CTRL_STREAM_CTR_STREAM_CTR_Msk			(0x3FFFFFu << 0)
#define XIP_CTRL_STREAM_CTR_STREAM_CTR_Pos			0u

	/* 0x1C: FIFO stream data */
	uint32_t volatile STREAM_FIFO;

};


#define XIP_SSI ((struct mcu_xip_ssi *)0x18000000)

struct mcu_xip_ssi {

	/* 0x00: Control register 0 */
	uint32_t volatile CTRLR0;
	/* Slave select toggle enable */
#define XIP_SSI_CTRLR0_SSTE					(1u << 24)
	/* SPI frame format */
#define XIP_SSI_CTRLR0_SPI_FRF_Msk				(0x3u << 21)
#define XIP_SSI_CTRLR0_SPI_FRF_Pos				21u
#define XIP_SSI_CTRLR0_SPI_FRF_STD				(0x0u << 21)
#define XIP_SSI_CTRLR0_SPI_FRF_DUAL				(0x1u << 21)
#define XIP_SSI_CTRLR0_SPI_FRF_QUAD				(0x2u << 21)
	/* Data frame size in 32b transfer mode */
#define XIP_SSI_CTRLR0_DFS_32_Msk				(0x1Fu << 16)
#define XIP_SSI_CTRLR0_DFS_32_Pos				16u
	/* Control frame size */
#define XIP_SSI_CTRLR0_CFS_Msk					(0xFu << 12)
#define XIP_SSI_CTRLR0_CFS_Pos					12u
	/* Shift register loop (test mode) */
#define XIP_SSI_CTRLR0_SRL					(1u << 11)
	/* Slave output enable */
#define XIP_SSI_CTRLR0_SLV_OE					(1u << 10)
	/* Transfer mode */
#define XIP_SSI_CTRLR0_TMOD_Msk					(0x3u << 8)
#define XIP_SSI_CTRLR0_TMOD_Pos					8u
#define XIP_SSI_CTRLR0_TMOD_TX_AND_RX				(0x0u << 8)
#define XIP_SSI_CTRLR0_TMOD_TX_ONLY				(0x1u << 8)
#define XIP_SSI_CTRLR0_TMOD_RX_ONLY				(0x2u << 8)
#define XIP_SSI_CTRLR0_TMOD_EEPROM_READ				(0x3u << 8)
	/* Serial clock polarity */
#define XIP_SSI_CTRLR0_SCPOL					(1u << 7)
	/* Serial clock phase */
#define XIP_SSI_CTRLR0_SCPH					(1u << 6)
	/* Frame format */
#define XIP_SSI_CTRLR0_FRF_Msk					(0x3u << 4)
#define XIP_SSI_CTRLR0_FRF_Pos					4u
	/* Data frame size */
#define XIP_SSI_CTRLR0_DFS_Msk					(0xFu << 0)
#define XIP_SSI_CTRLR0_DFS_Pos					0u

	/* 0x04: Master Control register 1 */
	uint32_t volatile CTRLR1;
	/* Number of data frames */
#define XIP_SSI_CTRLR1_NDF_Msk					(0xFFFFu << 0)
#define XIP_SSI_CTRLR1_NDF_Pos					0u

	/* 0x08: SSI Enable */
	uint32_t volatile SSIENR;
	/* SSI enable */
#define XIP_SSI_SSIENR_SSI_EN					(1u << 0)

	/* 0x0C: Microwire Control */
	uint32_t volatile MWCR;
	/* Microwire handshaking */
#define XIP_SSI_MWCR_MHS					(1u << 2)
	/* Microwire control */
#define XIP_SSI_MWCR_MDD					(1u << 1)
	/* Microwire transfer mode */
#define XIP_SSI_MWCR_MWMOD					(1u << 0)

	/* 0x10: Slave enable */
	uint32_t volatile SER;
	/* For each bit: */
#define XIP_SSI_SER_SER						(1u << 0)

	/* 0x14: Baud rate */
	uint32_t volatile BAUDR;
	/* SSI clock divider */
#define XIP_SSI_BAUDR_SCKDV_Msk					(0xFFFFu << 0)
#define XIP_SSI_BAUDR_SCKDV_Pos					0u

	/* 0x18: TX FIFO threshold level */
	uint32_t volatile TXFTLR;
	/* Transmit FIFO threshold */
#define XIP_SSI_TXFTLR_TFT_Msk					(0xFFu << 0)
#define XIP_SSI_TXFTLR_TFT_Pos					0u

	/* 0x1C: RX FIFO threshold level */
	uint32_t volatile RXFTLR;
	/* Receive FIFO threshold */
#define XIP_SSI_RXFTLR_RFT_Msk					(0xFFu << 0)
#define XIP_SSI_RXFTLR_RFT_Pos					0u

	/* 0x20: TX FIFO level */
	uint32_t volatile TXFLR;
	/* Transmit FIFO level */
#define XIP_SSI_TXFLR_TFTFL_Msk					(0xFFu << 0)
#define XIP_SSI_TXFLR_TFTFL_Pos					0u

	/* 0x24: RX FIFO level */
	uint32_t volatile RXFLR;
	/* Receive FIFO level */
#define XIP_SSI_RXFLR_RXTFL_Msk					(0xFFu << 0)
#define XIP_SSI_RXFLR_RXTFL_Pos					0u

	/* 0x28: Status register */
	uint32_t volatile SR;
	/* Data collision error */
#define XIP_SSI_SR_DCOL						(1u << 6)
	/* Transmission error */
#define XIP_SSI_SR_TXE						(1u << 5)
	/* Receive FIFO full */
#define XIP_SSI_SR_RFF						(1u << 4)
	/* Receive FIFO not empty */
#define XIP_SSI_SR_RFNE						(1u << 3)
	/* Transmit FIFO empty */
#define XIP_SSI_SR_TFE						(1u << 2)
	/* Transmit FIFO not full */
#define XIP_SSI_SR_TFNF						(1u << 1)
	/* SSI busy flag */
#define XIP_SSI_SR_BUSY						(1u << 0)

	/* 0x2C: Interrupt mask */
	uint32_t volatile IMR;
	/* Multi-master contention interrupt mask */
#define XIP_SSI_IMR_MSTIM					(1u << 5)
	/* Receive FIFO full interrupt mask */
#define XIP_SSI_IMR_RXFIM					(1u << 4)
	/* Receive FIFO overflow interrupt mask */
#define XIP_SSI_IMR_RXOIM					(1u << 3)
	/* Receive FIFO underflow interrupt mask */
#define XIP_SSI_IMR_RXUIM					(1u << 2)
	/* Transmit FIFO overflow interrupt mask */
#define XIP_SSI_IMR_TXOIM					(1u << 1)
	/* Transmit FIFO empty interrupt mask */
#define XIP_SSI_IMR_TXEIM					(1u << 0)

	/* 0x30: Interrupt status */
	uint32_t volatile ISR;
	/* Multi-master contention interrupt status */
#define XIP_SSI_ISR_MSTIS					(1u << 5)
	/* Receive FIFO full interrupt status */
#define XIP_SSI_ISR_RXFIS					(1u << 4)
	/* Receive FIFO overflow interrupt status */
#define XIP_SSI_ISR_RXOIS					(1u << 3)
	/* Receive FIFO underflow interrupt status */
#define XIP_SSI_ISR_RXUIS					(1u << 2)
	/* Transmit FIFO overflow interrupt status */
#define XIP_SSI_ISR_TXOIS					(1u << 1)
	/* Transmit FIFO empty interrupt status */
#define XIP_SSI_ISR_TXEIS					(1u << 0)

	/* 0x34: Raw interrupt status */
	uint32_t volatile RISR;
	/* Multi-master contention raw interrupt status */
#define XIP_SSI_RISR_MSTIR					(1u << 5)
	/* Receive FIFO full raw interrupt status */
#define XIP_SSI_RISR_RXFIR					(1u << 4)
	/* Receive FIFO overflow raw interrupt status */
#define XIP_SSI_RISR_RXOIR					(1u << 3)
	/* Receive FIFO underflow raw interrupt status */
#define XIP_SSI_RISR_RXUIR					(1u << 2)
	/* Transmit FIFO overflow raw interrupt status */
#define XIP_SSI_RISR_TXOIR					(1u << 1)
	/* Transmit FIFO empty raw interrupt status */
#define XIP_SSI_RISR_TXEIR					(1u << 0)

	/* 0x38: TX FIFO overflow interrupt clear */
	uint32_t volatile TXOICR;
	/* Clear-on-read transmit FIFO overflow interrupt */
#define XIP_SSI_TXOICR_TXOICR					(1u << 0)

	/* 0x3C: RX FIFO overflow interrupt clear */
	uint32_t volatile RXOICR;
	/* Clear-on-read receive FIFO overflow interrupt */
#define XIP_SSI_RXOICR_RXOICR					(1u << 0)

	/* 0x40: RX FIFO underflow interrupt clear */
	uint32_t volatile RXUICR;
	/* Clear-on-read receive FIFO underflow interrupt */
#define XIP_SSI_RXUICR_RXUICR					(1u << 0)

	/* 0x44: Multi-master interrupt clear */
	uint32_t volatile MSTICR;
	/* Clear-on-read multi-master contention interrupt */
#define XIP_SSI_MSTICR_MSTICR					(1u << 0)

	/* 0x48: Interrupt clear */
	uint32_t volatile ICR;
	/* Clear-on-read all active interrupts */
#define XIP_SSI_ICR_ICR						(1u << 0)

	/* 0x4C: DMA control */
	uint32_t volatile DMACR;
	/* Transmit DMA enable */
#define XIP_SSI_DMACR_TDMAE					(1u << 1)
	/* Receive DMA enable */
#define XIP_SSI_DMACR_RDMAE					(1u << 0)

	/* 0x50: DMA TX data level */
	uint32_t volatile DMATDLR;
	/* Transmit data watermark level */
#define XIP_SSI_DMATDLR_DMATDL_Msk				(0xFFu << 0)
#define XIP_SSI_DMATDLR_DMATDL_Pos				0u

	/* 0x54: DMA RX data level */
	uint32_t volatile DMARDLR;
	/* Receive data watermark level (DMARDLR+1) */
#define XIP_SSI_DMARDLR_DMARDL_Msk				(0xFFu << 0)
#define XIP_SSI_DMARDLR_DMARDL_Pos				0u

	/* 0x58: Identification register */
	uint32_t volatile IDR;
	/* Peripheral dentification code */
#define XIP_SSI_IDR_IDCODE_Msk					(0xFFFFFFFFu << 0)
#define XIP_SSI_IDR_IDCODE_Pos					0u

	/* 0x5C: Version ID */
	uint32_t volatile SSI_VERSION_ID;
	/* SNPS component version (format X.YY) */
#define XIP_SSI_SSI_VERSION_ID_SSI_COMP_VERSION_Msk		(0xFFFFFFFFu << 0)
#define XIP_SSI_SSI_VERSION_ID_SSI_COMP_VERSION_Pos		0u

	/* 0x60: Data Register 0 (of 36) */
	uint32_t volatile DR0;
	/* First data register of 36 */
#define XIP_SSI_DR0_DR_Msk					(0xFFFFFFFFu << 0)
#define XIP_SSI_DR0_DR_Pos					0u

	/* 0x64 */
	uint8_t RESERVED0[0xF0u-0x64u];

	/* 0xF0: RX sample delay */
	uint32_t volatile RX_SAMPLE_DLY;
	/* RXD sample delay (in SCLK cycles) */
#define XIP_SSI_RX_SAMPLE_DLY_RSD_Msk				(0xFFu << 0)
#define XIP_SSI_RX_SAMPLE_DLY_RSD_Pos				0u

	/* 0xF4: SPI control */
	uint32_t volatile SPI_CTRLR0;
	/* SPI Command to send in XIP mode (INST_L = 8-bit) or to append to Address (INST_L = 0-bit) */
#define XIP_SSI_SPI_CTRLR0_XIP_CMD_Msk				(0xFFu << 24)
#define XIP_SSI_SPI_CTRLR0_XIP_CMD_Pos				24u
	/* Read data strobe enable */
#define XIP_SSI_SPI_CTRLR0_SPI_RXDS_EN				(1u << 18)
	/* Instruction DDR transfer enable */
#define XIP_SSI_SPI_CTRLR0_INST_DDR_EN				(1u << 17)
	/* SPI DDR transfer enable */
#define XIP_SSI_SPI_CTRLR0_SPI_DDR_EN				(1u << 16)
	/* Wait cycles between control frame transmit and data reception (in SCLK cycles) */
#define XIP_SSI_SPI_CTRLR0_WAIT_CYCLES_Msk			(0x1Fu << 11)
#define XIP_SSI_SPI_CTRLR0_WAIT_CYCLES_Pos			11u
	/* Instruction length (0/4/8/16b) */
#define XIP_SSI_SPI_CTRLR0_INST_L_Msk				(0x3u << 8)
#define XIP_SSI_SPI_CTRLR0_INST_L_Pos				8u
#define XIP_SSI_SPI_CTRLR0_INST_L_NONE				(0x0u << 8)
#define XIP_SSI_SPI_CTRLR0_INST_L_4B				(0x1u << 8)
#define XIP_SSI_SPI_CTRLR0_INST_L_8B				(0x2u << 8)
#define XIP_SSI_SPI_CTRLR0_INST_L_16B				(0x3u << 8)
	/* Address length (0b-60b in 4b increments) */
#define XIP_SSI_SPI_CTRLR0_ADDR_L_Msk				(0xFu << 2)
#define XIP_SSI_SPI_CTRLR0_ADDR_L_Pos				2u
	/* Address and instruction transfer format */
#define XIP_SSI_SPI_CTRLR0_TRANS_TYPE_Msk			(0x3u << 0)
#define XIP_SSI_SPI_CTRLR0_TRANS_TYPE_Pos			0u
#define XIP_SSI_SPI_CTRLR0_TRANS_TYPE_1C1A			(0x0u << 0)
#define XIP_SSI_SPI_CTRLR0_TRANS_TYPE_1C2A			(0x1u << 0)
#define XIP_SSI_SPI_CTRLR0_TRANS_TYPE_2C2A			(0x2u << 0)

	/* 0xF8: TX drive edge */
	uint32_t volatile TXD_DRIVE_EDGE;
	/* TXD drive edge */
#define XIP_SSI_TXD_DRIVE_EDGE_TDE_Msk				(0xFFu << 0)
#define XIP_SSI_TXD_DRIVE_EDGE_TDE_Pos				0u

};


#define SYSINFO ((struct mcu_sysinfo *)0x40000000)

struct mcu_sysinfo {

	/* 0x00: JEDEC JEP-106 compliant chip identifier. */
	uint32_t volatile CHIP_ID;
	/*  */
#define SYSINFO_CHIP_ID_REVISION_Msk				(0xFu << 28)
#define SYSINFO_CHIP_ID_REVISION_Pos				28u
	/*  */
#define SYSINFO_CHIP_ID_PART_Msk				(0xFFFFu << 12)
#define SYSINFO_CHIP_ID_PART_Pos				12u
	/*  */
#define SYSINFO_CHIP_ID_MANUFACTURER_Msk			(0xFFFu << 0)
#define SYSINFO_CHIP_ID_MANUFACTURER_Pos			0u

	/* 0x04: Platform register. */
	uint32_t volatile PLATFORM;
	/*  */
#define SYSINFO_PLATFORM_ASIC					(1u << 1)
	/*  */
#define SYSINFO_PLATFORM_FPGA					(1u << 0)

	/* 0x08 */
	uint8_t RESERVED0[0x40u-0x08u];

	/* 0x40: Git hash of the chip source. */
	uint32_t volatile GITREF_RP2040;

};


#define SYSCFG ((struct mcu_syscfg *)0x40004000)

struct mcu_syscfg {

	/* 0x00: Processor core 0 NMI source mask */
	uint32_t volatile PROC0_NMI_MASK;

	/* 0x04: Processor core 1 NMI source mask */
	uint32_t volatile PROC1_NMI_MASK;

	/* 0x08: Configuration for processors */
	uint32_t volatile PROC_CONFIG;
	/* Configure proc1 DAP instance ID. */
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_Msk			(0xFu << 28)
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_Pos			28u
	/* Configure proc0 DAP instance ID. */
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_Msk			(0xFu << 24)
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_Pos			24u
	/* Indication that proc1 has halted */
#define SYSCFG_PROC_CONFIG_PROC1_HALTED				(1u << 1)
	/* Indication that proc0 has halted */
#define SYSCFG_PROC_CONFIG_PROC0_HALTED				(1u << 0)

	/* 0x0C: For each bit, if 1, bypass the input synchronizer between that GPIO */
	uint32_t volatile PROC_IN_SYNC_BYPASS;
	/*  */
#define SYSCFG_PROC_IN_SYNC_BYPASS_PROC_IN_SYNC_BYPASS_Msk	(0x3FFFFFFFu << 0)
#define SYSCFG_PROC_IN_SYNC_BYPASS_PROC_IN_SYNC_BYPASS_Pos	0u

	/* 0x10: For each bit, if 1, bypass the input synchronizer between that GPIO */
	uint32_t volatile PROC_IN_SYNC_BYPASS_HI;
	/*  */
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_PROC_IN_SYNC_BYPASS_HI_Msk	(0x3Fu << 0)
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_PROC_IN_SYNC_BYPASS_HI_Pos	0u

	/* 0x14: Directly control the SWD debug port of either processor */
	uint32_t volatile DBGFORCE;
	/* Attach processor 1 debug port to syscfg controls, and disconnect it from external SWD pads. */
#define SYSCFG_DBGFORCE_PROC1_ATTACH				(1u << 7)
	/* Directly drive processor 1 SWCLK, if PROC1_ATTACH is set */
#define SYSCFG_DBGFORCE_PROC1_SWCLK				(1u << 6)
	/* Directly drive processor 1 SWDIO input, if PROC1_ATTACH is set */
#define SYSCFG_DBGFORCE_PROC1_SWDI				(1u << 5)
	/* Observe the value of processor 1 SWDIO output. */
#define SYSCFG_DBGFORCE_PROC1_SWDO				(1u << 4)
	/* Attach processor 0 debug port to syscfg controls, and disconnect it from external SWD pads. */
#define SYSCFG_DBGFORCE_PROC0_ATTACH				(1u << 3)
	/* Directly drive processor 0 SWCLK, if PROC0_ATTACH is set */
#define SYSCFG_DBGFORCE_PROC0_SWCLK				(1u << 2)
	/* Directly drive processor 0 SWDIO input, if PROC0_ATTACH is set */
#define SYSCFG_DBGFORCE_PROC0_SWDI				(1u << 1)
	/* Observe the value of processor 0 SWDIO output. */
#define SYSCFG_DBGFORCE_PROC0_SWDO				(1u << 0)

	/* 0x18: Control power downs to memories. */
	uint32_t volatile MEMPOWERDOWN;
	/*  */
#define SYSCFG_MEMPOWERDOWN_ROM					(1u << 7)
	/*  */
#define SYSCFG_MEMPOWERDOWN_USB					(1u << 6)
	/*  */
#define SYSCFG_MEMPOWERDOWN_SRAM5				(1u << 5)
	/*  */
#define SYSCFG_MEMPOWERDOWN_SRAM4				(1u << 4)
	/*  */
#define SYSCFG_MEMPOWERDOWN_SRAM3				(1u << 3)
	/*  */
#define SYSCFG_MEMPOWERDOWN_SRAM2				(1u << 2)
	/*  */
#define SYSCFG_MEMPOWERDOWN_SRAM1				(1u << 1)
	/*  */
#define SYSCFG_MEMPOWERDOWN_SRAM0				(1u << 0)

};


#define CLOCKS ((struct mcu_clocks *)0x40008000)

enum {
	CLK_GPOUT0,
	CLK_GPOUT1,
	CLK_GPOUT2,
	CLK_GPOUT3,
	CLK_REF,
	CLK_SYS,
	CLK_PERI,
	CLK_USB,
	CLK_ADC,
	CLK_RTC
};

struct mcu_clocks {

	struct mcu_clocks_clk {

		/* 0x00: Clock control, can be changed on-the-fly (except for auxsrc) */
		uint32_t volatile CTRL;
		/* An edge on this signal shifts the phase of the output by 1 cycle of the input clock */
#define CLOCKS_CLK_GPOUT_CTRL_NUDGE				(1u << 20)
		/* This delays the enable signal by up to 3 cycles of the input clock */
#define CLOCKS_CLK_GPOUT_CTRL_PHASE_Msk			(0x3u << 16)
#define CLOCKS_CLK_GPOUT_CTRL_PHASE_Pos			16u
		/* Enables duty cycle correction for odd divisors */
#define CLOCKS_CLK_GPOUT_CTRL_DC50				(1u << 12)
		/* Starts and stops the clock generator cleanly */
#define CLOCKS_CLK_GPOUT_CTRL_ENABLE				(1u << 11)
		/* Asynchronously kills the clock generator */
#define CLOCKS_CLK_GPOUT_CTRL_KILL				(1u << 10)
		/* Selects the auxiliary clock source, will glitch when switching */
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_Msk			(0xFu << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_Pos			5u
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLKSRC_PLL_SYS		(0x0u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLKSRC_GPIN0		(0x1u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLKSRC_GPIN1		(0x2u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLKSRC_PLL_USB		(0x3u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_ROSC_CLKSRC		(0x4u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_XOSC_CLKSRC		(0x5u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLK_SYS			(0x6u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLK_USB			(0x7u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLK_ADC			(0x8u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLK_RTC			(0x9u << 5)
#define CLOCKS_CLK_GPOUT_CTRL_AUXSRC_CLK_REF			(0xAu << 5)
		/* Selects the auxiliary clock source, will glitch when switching */
#define CLOCKS_CLK_REF_CTRL_AUXSRC_Msk				(0x3u << 5)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_Pos				5u
#define CLOCKS_CLK_REF_CTRL_AUXSRC_CLKSRC_PLL_USB		(0x0u << 5)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_CLKSRC_GPIN0			(0x1u << 5)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_CLKSRC_GPIN1			(0x2u << 5)
		/* Selects the clock source glitchlessly, can be changed on-the-fly */
#define CLOCKS_CLK_REF_CTRL_SRC_Msk				(0x3u << 0)
#define CLOCKS_CLK_REF_CTRL_SRC_Pos				0u
#define CLOCKS_CLK_REF_CTRL_SRC_ROSC_CLKSRC_PH			(0x0u << 0)
#define CLOCKS_CLK_REF_CTRL_SRC_CLKSRC_CLK_REF_AUX		(0x1u << 0)
#define CLOCKS_CLK_REF_CTRL_SRC_XOSC_CLKSRC			(0x2u << 0)
		/* Selects the auxiliary clock source, will glitch when switching */
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_Msk				(0x7u << 5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_Pos				5u
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_CLKSRC_PLL_SYS		(0x0u << 5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_CLKSRC_PLL_USB		(0x1u << 5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_ROSC_CLKSRC			(0x2u << 5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_XOSC_CLKSRC			(0x3u << 5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_CLKSRC_GPIN0			(0x4u << 5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_CLKSRC_GPIN1			(0x5u << 5)
		/* Selects the clock source glitchlessly, can be changed on-the-fly */
#define CLOCKS_CLK_SYS_CTRL_SRC					(1u << 0)
#define CLOCKS_CLK_SYS_CTRL_SRC_CLK_REF				(0x0u << 0)
#define CLOCKS_CLK_SYS_CTRL_SRC_CLKSRC_CLK_SYS_AUX		(0x1u << 0)
		/* Starts and stops the clock generator cleanly */
#define CLOCKS_CLK_PERI_CTRL_ENABLE				(1u << 11)
		/* Asynchronously kills the clock generator */
#define CLOCKS_CLK_PERI_CTRL_KILL				(1u << 10)
		/* Selects the auxiliary clock source, will glitch when switching */
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_Msk				(0x7u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_Pos				5u
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_CLK_SYS			(0x0u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_CLKSRC_PLL_SYS		(0x1u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_CLKSRC_PLL_USB		(0x2u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_ROSC_CLKSRC_PH		(0x3u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_XOSC_CLKSRC			(0x4u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_CLKSRC_GPIN0		(0x5u << 5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_CLKSRC_GPIN1		(0x6u << 5)
		/* An edge on this signal shifts the phase of the output by 1 cycle of the input clock */
#define CLOCKS_CLK_USB_CTRL_NUDGE				(1u << 20)
		/* This delays the enable signal by up to 3 cycles of the input clock */
#define CLOCKS_CLK_USB_CTRL_PHASE_Msk				(0x3u << 16)
#define CLOCKS_CLK_USB_CTRL_PHASE_Pos				16u
		/* Starts and stops the clock generator cleanly */
#define CLOCKS_CLK_USB_CTRL_ENABLE				(1u << 11)
		/* Asynchronously kills the clock generator */
#define CLOCKS_CLK_USB_CTRL_KILL				(1u << 10)
		/* Selects the auxiliary clock source, will glitch when switching */
#define CLOCKS_CLK_USB_CTRL_AUXSRC_Msk				(0x7u << 5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_Pos				5u
#define CLOCKS_CLK_USB_CTRL_AUXSRC_CLKSRC_PLL_USB		(0x0u << 5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_CLKSRC_PLL_SYS		(0x1u << 5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_ROSC_CLKSRC_PH		(0x2u << 5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_XOSC_CLKSRC			(0x3u << 5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_CLKSRC_GPIN0			(0x4u << 5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_CLKSRC_GPIN1			(0x5u << 5)

		/* 0x04: Clock divisor, can be changed on-the-fly */
		uint32_t volatile DIV;
		/* Integer component of the divisor, 0 -> divide by 2^16 */
#define CLOCKS_CLK_GPOUT_DIV_INT_Msk				(0xFFFFFFu << 8)
#define CLOCKS_CLK_GPOUT_DIV_INT_Pos				8u
		/* Fractional component of the divisor */
#define CLOCKS_CLK_GPOUT_DIV_FRAC_Msk				(0xFFu << 0)
#define CLOCKS_CLK_GPOUT_DIV_FRAC_Pos				0u
		/* Integer component of the divisor, 0 -> divide by 2^16 */
#define CLOCKS_CLK_REF_DIV_INT_Msk				(0x3u << 8)
#define CLOCKS_CLK_REF_DIV_INT_Pos				8u
		/* Integer component of the divisor, 0 -> divide by 2^16 */
#define CLOCKS_CLK_SYS_DIV_INT_Msk				(0xFFFFFFu << 8)
#define CLOCKS_CLK_SYS_DIV_INT_Pos				8u
		/* Fractional component of the divisor */
#define CLOCKS_CLK_SYS_DIV_FRAC_Msk				(0xFFu << 0)
#define CLOCKS_CLK_SYS_DIV_FRAC_Pos				0u

		/* 0x08: Indicates which SRC is currently selected by the glitchless mux (one-hot). */
		uint32_t volatile SELECTED;

	} CLK[10];

	/* 0x78:  */
	uint32_t volatile CLK_SYS_RESUS_CTRL;
	/* For clearing the resus after the fault that triggered it has been corrected */
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR				(1u << 16)
	/* Force a resus, for test purposes only */
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE				(1u << 12)
	/* Enable resus */
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE			(1u << 8)
	/* This is expressed as a number of clk_ref cycles */
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_Msk			(0xFFu << 0)
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_Pos			0u

	/* 0x7C:  */
	uint32_t volatile CLK_SYS_RESUS_STATUS;
	/* Clock has been resuscitated, correct the error then send ctrl_clear=1 */
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED			(1u << 0)

	/* 0x80: Reference clock frequency in kHz */
	uint32_t volatile FC0_REF_KHZ;
	/*  */
#define CLOCKS_FC0_REF_KHZ_FC0_REF_KHZ_Msk			(0xFFFFFu << 0)
#define CLOCKS_FC0_REF_KHZ_FC0_REF_KHZ_Pos			0u

	/* 0x84: Minimum pass frequency in kHz. */
	uint32_t volatile FC0_MIN_KHZ;
	/*  */
#define CLOCKS_FC0_MIN_KHZ_FC0_MIN_KHZ_Msk			(0x1FFFFFFu << 0)
#define CLOCKS_FC0_MIN_KHZ_FC0_MIN_KHZ_Pos			0u

	/* 0x88: Maximum pass frequency in kHz. */
	uint32_t volatile FC0_MAX_KHZ;
	/*  */
#define CLOCKS_FC0_MAX_KHZ_FC0_MAX_KHZ_Msk			(0x1FFFFFFu << 0)
#define CLOCKS_FC0_MAX_KHZ_FC0_MAX_KHZ_Pos			0u

	/* 0x8C: Delays the start of frequency counting to allow the mux to settle */
	uint32_t volatile FC0_DELAY;
	/*  */
#define CLOCKS_FC0_DELAY_FC0_DELAY_Msk				(0x7u << 0)
#define CLOCKS_FC0_DELAY_FC0_DELAY_Pos				0u

	/* 0x90: The test interval is 0.98us * 2**interval, but let's call it 1us * 2**interval */
	uint32_t volatile FC0_INTERVAL;
	/*  */
#define CLOCKS_FC0_INTERVAL_FC0_INTERVAL_Msk			(0xFu << 0)
#define CLOCKS_FC0_INTERVAL_FC0_INTERVAL_Pos			0u

	/* 0x94: Clock sent to frequency counter, set to 0 when not required */
	uint32_t volatile FC0_SRC;
	/*  */
#define CLOCKS_FC0_SRC_FC0_SRC_Msk				(0xFFu << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_Pos				0u
#define CLOCKS_FC0_SRC_FC0_SRC_NULL				(0x0u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_PLL_SYS_CLKSRC_PRIMARY		(0x1u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_PLL_USB_CLKSRC_PRIMARY		(0x2u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_ROSC_CLKSRC			(0x3u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_ROSC_CLKSRC_PH			(0x4u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_XOSC_CLKSRC			(0x5u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLKSRC_GPIN0			(0x6u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLKSRC_GPIN1			(0x7u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLK_REF				(0x8u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLK_SYS				(0x9u << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLK_PERI				(0xAu << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLK_USB				(0xBu << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLK_ADC				(0xCu << 0)
#define CLOCKS_FC0_SRC_FC0_SRC_CLK_RTC				(0xDu << 0)

	/* 0x98: Frequency counter status */
	uint32_t volatile FC0_STATUS;
	/* Test clock stopped during test */
#define CLOCKS_FC0_STATUS_DIED					(1u << 28)
	/* Test clock faster than expected, only valid when status_done=1 */
#define CLOCKS_FC0_STATUS_FAST					(1u << 24)
	/* Test clock slower than expected, only valid when status_done=1 */
#define CLOCKS_FC0_STATUS_SLOW					(1u << 20)
	/* Test failed */
#define CLOCKS_FC0_STATUS_FAIL					(1u << 16)
	/* Waiting for test clock to start */
#define CLOCKS_FC0_STATUS_WAITING				(1u << 12)
	/* Test running */
#define CLOCKS_FC0_STATUS_RUNNING				(1u << 8)
	/* Test complete */
#define CLOCKS_FC0_STATUS_DONE					(1u << 4)
	/* Test passed */
#define CLOCKS_FC0_STATUS_PASS					(1u << 0)

	/* 0x9C: Result of frequency measurement, only valid when status_done=1 */
	uint32_t volatile FC0_RESULT;
	/*  */
#define CLOCKS_FC0_RESULT_KHZ_Msk				(0x1FFFFFFu << 5)
#define CLOCKS_FC0_RESULT_KHZ_Pos				5u
	/*  */
#define CLOCKS_FC0_RESULT_FRAC_Msk				(0x1Fu << 0)
#define CLOCKS_FC0_RESULT_FRAC_Pos				0u

	/* 0xA0: enable clock in wake mode */
	uint32_t volatile WAKE_EN0;
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3				(1u << 31)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2				(1u << 30)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1				(1u << 29)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0				(1u << 28)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1				(1u << 27)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1				(1u << 26)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0				(1u << 25)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0				(1u << 24)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO				(1u << 23)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC				(1u << 22)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC				(1u << 21)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC				(1u << 20)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM				(1u << 19)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS				(1u << 18)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM				(1u << 17)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM				(1u << 16)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB				(1u << 15)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS				(1u << 14)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1				(1u << 13)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0				(1u << 12)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS				(1u << 11)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET		(1u << 10)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG				(1u << 9)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_IO				(1u << 8)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1				(1u << 7)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0				(1u << 6)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA				(1u << 5)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC			(1u << 4)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL				(1u << 3)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC				(1u << 2)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC				(1u << 1)
	/*  */
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS				(1u << 0)

	/* 0xA4: enable clock in wake mode */
	uint32_t volatile WAKE_EN1;
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC				(1u << 14)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP				(1u << 13)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG			(1u << 12)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL				(1u << 11)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL				(1u << 10)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1				(1u << 9)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1				(1u << 8)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0				(1u << 7)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0				(1u << 6)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER				(1u << 5)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN				(1u << 4)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO				(1u << 3)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG				(1u << 2)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5				(1u << 1)
	/*  */
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4				(1u << 0)

	/* 0xA8: enable clock in sleep mode */
	uint32_t volatile SLEEP_EN0;
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3				(1u << 31)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2				(1u << 30)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1				(1u << 29)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0				(1u << 28)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1				(1u << 27)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1				(1u << 26)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0				(1u << 25)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0				(1u << 24)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO				(1u << 23)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC				(1u << 22)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC				(1u << 21)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC				(1u << 20)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM				(1u << 19)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS				(1u << 18)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM				(1u << 17)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM				(1u << 16)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB			(1u << 15)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS			(1u << 14)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1				(1u << 13)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0				(1u << 12)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS				(1u << 11)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET		(1u << 10)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG				(1u << 9)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO				(1u << 8)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1				(1u << 7)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0				(1u << 6)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA				(1u << 5)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC			(1u << 4)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL			(1u << 3)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC				(1u << 2)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC				(1u << 1)
	/*  */
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS				(1u << 0)

	/* 0xAC: enable clock in sleep mode */
	uint32_t volatile SLEEP_EN1;
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC				(1u << 14)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP				(1u << 13)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG			(1u << 12)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL			(1u << 11)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL			(1u << 10)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1				(1u << 9)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1				(1u << 8)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0				(1u << 7)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0				(1u << 6)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER				(1u << 5)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN				(1u << 4)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO			(1u << 3)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG				(1u << 2)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5				(1u << 1)
	/*  */
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4				(1u << 0)

	/* 0xB0: indicates the state of the clock enable */
	uint32_t volatile ENABLED0;
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3				(1u << 31)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2				(1u << 30)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1				(1u << 29)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0				(1u << 28)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SPI1				(1u << 27)
	/*  */
#define CLOCKS_ENABLED0_CLK_PERI_SPI1				(1u << 26)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SPI0				(1u << 25)
	/*  */
#define CLOCKS_ENABLED0_CLK_PERI_SPI0				(1u << 24)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_SIO				(1u << 23)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_RTC				(1u << 22)
	/*  */
#define CLOCKS_ENABLED0_CLK_RTC_RTC				(1u << 21)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_ROSC				(1u << 20)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_ROM				(1u << 19)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_RESETS				(1u << 18)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PWM				(1u << 17)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PSM				(1u << 16)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB				(1u << 15)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS				(1u << 14)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PIO1				(1u << 13)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PIO0				(1u << 12)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_PADS				(1u << 11)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET		(1u << 10)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_JTAG				(1u << 9)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_IO				(1u << 8)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_I2C1				(1u << 7)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_I2C0				(1u << 6)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_DMA				(1u << 5)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC			(1u << 4)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL				(1u << 3)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_ADC				(1u << 2)
	/*  */
#define CLOCKS_ENABLED0_CLK_ADC_ADC				(1u << 1)
	/*  */
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS				(1u << 0)

	/* 0xB4: indicates the state of the clock enable */
	uint32_t volatile ENABLED1;
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_XOSC				(1u << 14)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_XIP				(1u << 13)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG			(1u << 12)
	/*  */
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL				(1u << 11)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL				(1u << 10)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_UART1				(1u << 9)
	/*  */
#define CLOCKS_ENABLED1_CLK_PERI_UART1				(1u << 8)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_UART0				(1u << 7)
	/*  */
#define CLOCKS_ENABLED1_CLK_PERI_UART0				(1u << 6)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_TIMER				(1u << 5)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN				(1u << 4)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO				(1u << 3)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG				(1u << 2)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5				(1u << 1)
	/*  */
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4				(1u << 0)

	/* 0xB8: Raw Interrupts */
	uint32_t volatile INTR;
	/*  */
#define CLOCKS_INTR_CLK_SYS_RESUS				(1u << 0)

	/* 0xBC: Interrupt Enable */
	uint32_t volatile INTE;
	/*  */
#define CLOCKS_INTE_CLK_SYS_RESUS				(1u << 0)

	/* 0xC0: Interrupt Force */
	uint32_t volatile INTF;
	/*  */
#define CLOCKS_INTF_CLK_SYS_RESUS				(1u << 0)

	/* 0xC4: Interrupt status after masking & forcing */
	uint32_t volatile INTS;
	/*  */
#define CLOCKS_INTS_CLK_SYS_RESUS				(1u << 0)

};


#define RESETS ((struct mcu_resets *)0x4000C000)

struct mcu_resets {

	/* 0x00: Reset control. */
	uint32_t volatile RESET;
	/*  */
#define RESETS_RESET_USBCTRL					(1u << 24)
	/*  */
#define RESETS_RESET_UART1					(1u << 23)
	/*  */
#define RESETS_RESET_UART0					(1u << 22)
	/*  */
#define RESETS_RESET_TIMER					(1u << 21)
	/*  */
#define RESETS_RESET_TBMAN					(1u << 20)
	/*  */
#define RESETS_RESET_SYSINFO					(1u << 19)
	/*  */
#define RESETS_RESET_SYSCFG					(1u << 18)
	/*  */
#define RESETS_RESET_SPI1					(1u << 17)
	/*  */
#define RESETS_RESET_SPI0					(1u << 16)
	/*  */
#define RESETS_RESET_RTC					(1u << 15)
	/*  */
#define RESETS_RESET_PWM					(1u << 14)
	/*  */
#define RESETS_RESET_PLL_USB					(1u << 13)
	/*  */
#define RESETS_RESET_PLL_SYS					(1u << 12)
	/*  */
#define RESETS_RESET_PIO1					(1u << 11)
	/*  */
#define RESETS_RESET_PIO0					(1u << 10)
	/*  */
#define RESETS_RESET_PADS_QSPI					(1u << 9)
	/*  */
#define RESETS_RESET_PADS_BANK0					(1u << 8)
	/*  */
#define RESETS_RESET_JTAG					(1u << 7)
	/*  */
#define RESETS_RESET_IO_QSPI					(1u << 6)
	/*  */
#define RESETS_RESET_IO_BANK0					(1u << 5)
	/*  */
#define RESETS_RESET_I2C1					(1u << 4)
	/*  */
#define RESETS_RESET_I2C0					(1u << 3)
	/*  */
#define RESETS_RESET_DMA					(1u << 2)
	/*  */
#define RESETS_RESET_BUSCTRL					(1u << 1)
	/*  */
#define RESETS_RESET_ADC					(1u << 0)

	/* 0x04: Watchdog select. */
	uint32_t volatile WDSEL;
	/*  */
#define RESETS_WDSEL_USBCTRL					(1u << 24)
	/*  */
#define RESETS_WDSEL_UART1					(1u << 23)
	/*  */
#define RESETS_WDSEL_UART0					(1u << 22)
	/*  */
#define RESETS_WDSEL_TIMER					(1u << 21)
	/*  */
#define RESETS_WDSEL_TBMAN					(1u << 20)
	/*  */
#define RESETS_WDSEL_SYSINFO					(1u << 19)
	/*  */
#define RESETS_WDSEL_SYSCFG					(1u << 18)
	/*  */
#define RESETS_WDSEL_SPI1					(1u << 17)
	/*  */
#define RESETS_WDSEL_SPI0					(1u << 16)
	/*  */
#define RESETS_WDSEL_RTC					(1u << 15)
	/*  */
#define RESETS_WDSEL_PWM					(1u << 14)
	/*  */
#define RESETS_WDSEL_PLL_USB					(1u << 13)
	/*  */
#define RESETS_WDSEL_PLL_SYS					(1u << 12)
	/*  */
#define RESETS_WDSEL_PIO1					(1u << 11)
	/*  */
#define RESETS_WDSEL_PIO0					(1u << 10)
	/*  */
#define RESETS_WDSEL_PADS_QSPI					(1u << 9)
	/*  */
#define RESETS_WDSEL_PADS_BANK0					(1u << 8)
	/*  */
#define RESETS_WDSEL_JTAG					(1u << 7)
	/*  */
#define RESETS_WDSEL_IO_QSPI					(1u << 6)
	/*  */
#define RESETS_WDSEL_IO_BANK0					(1u << 5)
	/*  */
#define RESETS_WDSEL_I2C1					(1u << 4)
	/*  */
#define RESETS_WDSEL_I2C0					(1u << 3)
	/*  */
#define RESETS_WDSEL_DMA					(1u << 2)
	/*  */
#define RESETS_WDSEL_BUSCTRL					(1u << 1)
	/*  */
#define RESETS_WDSEL_ADC					(1u << 0)

	/* 0x08: Reset done. */
	uint32_t volatile RESET_DONE;
	/*  */
#define RESETS_RESET_DONE_USBCTRL				(1u << 24)
	/*  */
#define RESETS_RESET_DONE_UART1					(1u << 23)
	/*  */
#define RESETS_RESET_DONE_UART0					(1u << 22)
	/*  */
#define RESETS_RESET_DONE_TIMER					(1u << 21)
	/*  */
#define RESETS_RESET_DONE_TBMAN					(1u << 20)
	/*  */
#define RESETS_RESET_DONE_SYSINFO				(1u << 19)
	/*  */
#define RESETS_RESET_DONE_SYSCFG				(1u << 18)
	/*  */
#define RESETS_RESET_DONE_SPI1					(1u << 17)
	/*  */
#define RESETS_RESET_DONE_SPI0					(1u << 16)
	/*  */
#define RESETS_RESET_DONE_RTC					(1u << 15)
	/*  */
#define RESETS_RESET_DONE_PWM					(1u << 14)
	/*  */
#define RESETS_RESET_DONE_PLL_USB				(1u << 13)
	/*  */
#define RESETS_RESET_DONE_PLL_SYS				(1u << 12)
	/*  */
#define RESETS_RESET_DONE_PIO1					(1u << 11)
	/*  */
#define RESETS_RESET_DONE_PIO0					(1u << 10)
	/*  */
#define RESETS_RESET_DONE_PADS_QSPI				(1u << 9)
	/*  */
#define RESETS_RESET_DONE_PADS_BANK0				(1u << 8)
	/*  */
#define RESETS_RESET_DONE_JTAG					(1u << 7)
	/*  */
#define RESETS_RESET_DONE_IO_QSPI				(1u << 6)
	/*  */
#define RESETS_RESET_DONE_IO_BANK0				(1u << 5)
	/*  */
#define RESETS_RESET_DONE_I2C1					(1u << 4)
	/*  */
#define RESETS_RESET_DONE_I2C0					(1u << 3)
	/*  */
#define RESETS_RESET_DONE_DMA					(1u << 2)
	/*  */
#define RESETS_RESET_DONE_BUSCTRL				(1u << 1)
	/*  */
#define RESETS_RESET_DONE_ADC					(1u << 0)

};


#define PSM ((struct mcu_psm *)0x40010000)

struct mcu_psm {

	/* 0x00: Force block out of reset (i.e. power it on) */
	uint32_t volatile FRCE_ON;
	/*  */
#define PSM_FRCE_ON_PROC1					(1u << 16)
	/*  */
#define PSM_FRCE_ON_PROC0					(1u << 15)
	/*  */
#define PSM_FRCE_ON_SIO						(1u << 14)
	/*  */
#define PSM_FRCE_ON_VREG_AND_CHIP_RESET				(1u << 13)
	/*  */
#define PSM_FRCE_ON_XIP						(1u << 12)
	/*  */
#define PSM_FRCE_ON_SRAM5					(1u << 11)
	/*  */
#define PSM_FRCE_ON_SRAM4					(1u << 10)
	/*  */
#define PSM_FRCE_ON_SRAM3					(1u << 9)
	/*  */
#define PSM_FRCE_ON_SRAM2					(1u << 8)
	/*  */
#define PSM_FRCE_ON_SRAM1					(1u << 7)
	/*  */
#define PSM_FRCE_ON_SRAM0					(1u << 6)
	/*  */
#define PSM_FRCE_ON_ROM						(1u << 5)
	/*  */
#define PSM_FRCE_ON_BUSFABRIC					(1u << 4)
	/*  */
#define PSM_FRCE_ON_RESETS					(1u << 3)
	/*  */
#define PSM_FRCE_ON_CLOCKS					(1u << 2)
	/*  */
#define PSM_FRCE_ON_XOSC					(1u << 1)
	/*  */
#define PSM_FRCE_ON_ROSC					(1u << 0)

	/* 0x04: Force into reset (i.e. power it off) */
	uint32_t volatile FRCE_OFF;
	/*  */
#define PSM_FRCE_OFF_PROC1					(1u << 16)
	/*  */
#define PSM_FRCE_OFF_PROC0					(1u << 15)
	/*  */
#define PSM_FRCE_OFF_SIO					(1u << 14)
	/*  */
#define PSM_FRCE_OFF_VREG_AND_CHIP_RESET			(1u << 13)
	/*  */
#define PSM_FRCE_OFF_XIP					(1u << 12)
	/*  */
#define PSM_FRCE_OFF_SRAM5					(1u << 11)
	/*  */
#define PSM_FRCE_OFF_SRAM4					(1u << 10)
	/*  */
#define PSM_FRCE_OFF_SRAM3					(1u << 9)
	/*  */
#define PSM_FRCE_OFF_SRAM2					(1u << 8)
	/*  */
#define PSM_FRCE_OFF_SRAM1					(1u << 7)
	/*  */
#define PSM_FRCE_OFF_SRAM0					(1u << 6)
	/*  */
#define PSM_FRCE_OFF_ROM					(1u << 5)
	/*  */
#define PSM_FRCE_OFF_BUSFABRIC					(1u << 4)
	/*  */
#define PSM_FRCE_OFF_RESETS					(1u << 3)
	/*  */
#define PSM_FRCE_OFF_CLOCKS					(1u << 2)
	/*  */
#define PSM_FRCE_OFF_XOSC					(1u << 1)
	/*  */
#define PSM_FRCE_OFF_ROSC					(1u << 0)

	/* 0x08: Set to 1 if this peripheral should be reset when the watchdog fires. */
	uint32_t volatile WDSEL;
	/*  */
#define PSM_WDSEL_PROC1						(1u << 16)
	/*  */
#define PSM_WDSEL_PROC0						(1u << 15)
	/*  */
#define PSM_WDSEL_SIO						(1u << 14)
	/*  */
#define PSM_WDSEL_VREG_AND_CHIP_RESET				(1u << 13)
	/*  */
#define PSM_WDSEL_XIP						(1u << 12)
	/*  */
#define PSM_WDSEL_SRAM5						(1u << 11)
	/*  */
#define PSM_WDSEL_SRAM4						(1u << 10)
	/*  */
#define PSM_WDSEL_SRAM3						(1u << 9)
	/*  */
#define PSM_WDSEL_SRAM2						(1u << 8)
	/*  */
#define PSM_WDSEL_SRAM1						(1u << 7)
	/*  */
#define PSM_WDSEL_SRAM0						(1u << 6)
	/*  */
#define PSM_WDSEL_ROM						(1u << 5)
	/*  */
#define PSM_WDSEL_BUSFABRIC					(1u << 4)
	/*  */
#define PSM_WDSEL_RESETS					(1u << 3)
	/*  */
#define PSM_WDSEL_CLOCKS					(1u << 2)
	/*  */
#define PSM_WDSEL_XOSC						(1u << 1)
	/*  */
#define PSM_WDSEL_ROSC						(1u << 0)

	/* 0x0C: Indicates the peripheral's registers are ready to access. */
	uint32_t volatile DONE;
	/*  */
#define PSM_DONE_PROC1						(1u << 16)
	/*  */
#define PSM_DONE_PROC0						(1u << 15)
	/*  */
#define PSM_DONE_SIO						(1u << 14)
	/*  */
#define PSM_DONE_VREG_AND_CHIP_RESET				(1u << 13)
	/*  */
#define PSM_DONE_XIP						(1u << 12)
	/*  */
#define PSM_DONE_SRAM5						(1u << 11)
	/*  */
#define PSM_DONE_SRAM4						(1u << 10)
	/*  */
#define PSM_DONE_SRAM3						(1u << 9)
	/*  */
#define PSM_DONE_SRAM2						(1u << 8)
	/*  */
#define PSM_DONE_SRAM1						(1u << 7)
	/*  */
#define PSM_DONE_SRAM0						(1u << 6)
	/*  */
#define PSM_DONE_ROM						(1u << 5)
	/*  */
#define PSM_DONE_BUSFABRIC					(1u << 4)
	/*  */
#define PSM_DONE_RESETS						(1u << 3)
	/*  */
#define PSM_DONE_CLOCKS						(1u << 2)
	/*  */
#define PSM_DONE_XOSC						(1u << 1)
	/*  */
#define PSM_DONE_ROSC						(1u << 0)

};


#define IO_BANK0 ((struct mcu_io_bank0 *)0x40014000)

struct mcu_io_bank0 {

	struct mcu_io_bank0_gpio {

		/* 0x00: GPIO status */
		uint32_t volatile STATUS;
		/* interrupt to processors, after override is applied */
#define IO_BANK0_GPIO_STATUS_IRQTOPROC				(1u << 26)
		/* interrupt from pad before override is applied */
#define IO_BANK0_GPIO_STATUS_IRQFROMPAD				(1u << 24)
		/* input signal to peripheral, after override is applied */
#define IO_BANK0_GPIO_STATUS_INTOPERI				(1u << 19)
		/* input signal from pad, before override is applied */
#define IO_BANK0_GPIO_STATUS_INFROMPAD				(1u << 17)
		/* output enable to pad after register override is applied */
#define IO_BANK0_GPIO_STATUS_OETOPAD				(1u << 13)
		/* output enable from selected peripheral, before register override is applied */
#define IO_BANK0_GPIO_STATUS_OEFROMPERI				(1u << 12)
		/* output signal to pad after register override is applied */
#define IO_BANK0_GPIO_STATUS_OUTTOPAD				(1u << 9)
		/* output signal from selected peripheral, before register override is applied */
#define IO_BANK0_GPIO_STATUS_OUTFROMPERI			(1u << 8)

		/* 0x04: GPIO control including function select and overrides. */
		uint32_t volatile CTRL;
		/*  */
#define IO_BANK0_GPIO0_CTRL_IRQOVER_Msk				(0x3u << 28)
#define IO_BANK0_GPIO0_CTRL_IRQOVER_Pos				28u
#define IO_BANK0_GPIO0_CTRL_IRQOVER_NORMAL			(0x0u << 28)
#define IO_BANK0_GPIO0_CTRL_IRQOVER_INVERT			(0x1u << 28)
#define IO_BANK0_GPIO0_CTRL_IRQOVER_LOW				(0x2u << 28)
#define IO_BANK0_GPIO0_CTRL_IRQOVER_HIGH			(0x3u << 28)
		/*  */
#define IO_BANK0_GPIO0_CTRL_INOVER_Msk				(0x3u << 16)
#define IO_BANK0_GPIO0_CTRL_INOVER_Pos				16u
#define IO_BANK0_GPIO0_CTRL_INOVER_NORMAL			(0x0u << 16)
#define IO_BANK0_GPIO0_CTRL_INOVER_INVERT			(0x1u << 16)
#define IO_BANK0_GPIO0_CTRL_INOVER_LOW				(0x2u << 16)
#define IO_BANK0_GPIO0_CTRL_INOVER_HIGH				(0x3u << 16)
		/*  */
#define IO_BANK0_GPIO0_CTRL_OEOVER_Msk				(0x3u << 12)
#define IO_BANK0_GPIO0_CTRL_OEOVER_Pos				12u
#define IO_BANK0_GPIO0_CTRL_OEOVER_NORMAL			(0x0u << 12)
#define IO_BANK0_GPIO0_CTRL_OEOVER_INVERT			(0x1u << 12)
#define IO_BANK0_GPIO0_CTRL_OEOVER_DISABLE			(0x2u << 12)
#define IO_BANK0_GPIO0_CTRL_OEOVER_ENABLE			(0x3u << 12)
		/*  */
#define IO_BANK0_GPIO0_CTRL_OUTOVER_Msk				(0x3u << 8)
#define IO_BANK0_GPIO0_CTRL_OUTOVER_Pos				8u
#define IO_BANK0_GPIO0_CTRL_OUTOVER_NORMAL			(0x0u << 8)
#define IO_BANK0_GPIO0_CTRL_OUTOVER_INVERT			(0x1u << 8)
#define IO_BANK0_GPIO0_CTRL_OUTOVER_LOW				(0x2u << 8)
#define IO_BANK0_GPIO0_CTRL_OUTOVER_HIGH			(0x3u << 8)
		/* selects pin function according to the gpio table */
#define IO_BANK0_GPIO_CTRL_FUNCSEL_Msk				(0x1Fu << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_Pos				0u
#define IO_BANK0_GPIO_CTRL_FUNCSEL_JTAG				(0x0u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_SPI				(0x1u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_UART				(0x2u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_I2C				(0x3u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_PWM				(0x4u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_SIO				(0x5u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_PIO0				(0x6u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_PIO1				(0x7u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_CLOCKS			(0x8u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_USB_MUXING_DIGITAL		(0x8u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_USB_MUXING_EXTPHY		(0x8u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_USB_MUXING_OVERCURR		(0x9u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_USB_MUXING_VBUS		(0x9u << 0)
#define IO_BANK0_GPIO_CTRL_FUNCSEL_NULL				(0x1Fu << 0)

	} GPIO[29];

	/* 0xF0: Raw Interrupts */
	uint32_t volatile INTR0;
	/*  */
#define IO_BANK0_INTR0_GPIO7_EDGE_HIGH				(1u << 31)
	/*  */
#define IO_BANK0_INTR0_GPIO7_EDGE_LOW				(1u << 30)
	/*  */
#define IO_BANK0_INTR0_GPIO7_LEVEL_HIGH				(1u << 29)
	/*  */
#define IO_BANK0_INTR0_GPIO7_LEVEL_LOW				(1u << 28)
	/*  */
#define IO_BANK0_INTR0_GPIO6_EDGE_HIGH				(1u << 27)
	/*  */
#define IO_BANK0_INTR0_GPIO6_EDGE_LOW				(1u << 26)
	/*  */
#define IO_BANK0_INTR0_GPIO6_LEVEL_HIGH				(1u << 25)
	/*  */
#define IO_BANK0_INTR0_GPIO6_LEVEL_LOW				(1u << 24)
	/*  */
#define IO_BANK0_INTR0_GPIO5_EDGE_HIGH				(1u << 23)
	/*  */
#define IO_BANK0_INTR0_GPIO5_EDGE_LOW				(1u << 22)
	/*  */
#define IO_BANK0_INTR0_GPIO5_LEVEL_HIGH				(1u << 21)
	/*  */
#define IO_BANK0_INTR0_GPIO5_LEVEL_LOW				(1u << 20)
	/*  */
#define IO_BANK0_INTR0_GPIO4_EDGE_HIGH				(1u << 19)
	/*  */
#define IO_BANK0_INTR0_GPIO4_EDGE_LOW				(1u << 18)
	/*  */
#define IO_BANK0_INTR0_GPIO4_LEVEL_HIGH				(1u << 17)
	/*  */
#define IO_BANK0_INTR0_GPIO4_LEVEL_LOW				(1u << 16)
	/*  */
#define IO_BANK0_INTR0_GPIO3_EDGE_HIGH				(1u << 15)
	/*  */
#define IO_BANK0_INTR0_GPIO3_EDGE_LOW				(1u << 14)
	/*  */
#define IO_BANK0_INTR0_GPIO3_LEVEL_HIGH				(1u << 13)
	/*  */
#define IO_BANK0_INTR0_GPIO3_LEVEL_LOW				(1u << 12)
	/*  */
#define IO_BANK0_INTR0_GPIO2_EDGE_HIGH				(1u << 11)
	/*  */
#define IO_BANK0_INTR0_GPIO2_EDGE_LOW				(1u << 10)
	/*  */
#define IO_BANK0_INTR0_GPIO2_LEVEL_HIGH				(1u << 9)
	/*  */
#define IO_BANK0_INTR0_GPIO2_LEVEL_LOW				(1u << 8)
	/*  */
#define IO_BANK0_INTR0_GPIO1_EDGE_HIGH				(1u << 7)
	/*  */
#define IO_BANK0_INTR0_GPIO1_EDGE_LOW				(1u << 6)
	/*  */
#define IO_BANK0_INTR0_GPIO1_LEVEL_HIGH				(1u << 5)
	/*  */
#define IO_BANK0_INTR0_GPIO1_LEVEL_LOW				(1u << 4)
	/*  */
#define IO_BANK0_INTR0_GPIO0_EDGE_HIGH				(1u << 3)
	/*  */
#define IO_BANK0_INTR0_GPIO0_EDGE_LOW				(1u << 2)
	/*  */
#define IO_BANK0_INTR0_GPIO0_LEVEL_HIGH				(1u << 1)
	/*  */
#define IO_BANK0_INTR0_GPIO0_LEVEL_LOW				(1u << 0)

	/* 0xF4: Raw Interrupts */
	uint32_t volatile INTR1;
	/*  */
#define IO_BANK0_INTR1_GPIO15_EDGE_HIGH				(1u << 31)
	/*  */
#define IO_BANK0_INTR1_GPIO15_EDGE_LOW				(1u << 30)
	/*  */
#define IO_BANK0_INTR1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_INTR1_GPIO15_LEVEL_LOW				(1u << 28)
	/*  */
#define IO_BANK0_INTR1_GPIO14_EDGE_HIGH				(1u << 27)
	/*  */
#define IO_BANK0_INTR1_GPIO14_EDGE_LOW				(1u << 26)
	/*  */
#define IO_BANK0_INTR1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_INTR1_GPIO14_LEVEL_LOW				(1u << 24)
	/*  */
#define IO_BANK0_INTR1_GPIO13_EDGE_HIGH				(1u << 23)
	/*  */
#define IO_BANK0_INTR1_GPIO13_EDGE_LOW				(1u << 22)
	/*  */
#define IO_BANK0_INTR1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_INTR1_GPIO13_LEVEL_LOW				(1u << 20)
	/*  */
#define IO_BANK0_INTR1_GPIO12_EDGE_HIGH				(1u << 19)
	/*  */
#define IO_BANK0_INTR1_GPIO12_EDGE_LOW				(1u << 18)
	/*  */
#define IO_BANK0_INTR1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_INTR1_GPIO12_LEVEL_LOW				(1u << 16)
	/*  */
#define IO_BANK0_INTR1_GPIO11_EDGE_HIGH				(1u << 15)
	/*  */
#define IO_BANK0_INTR1_GPIO11_EDGE_LOW				(1u << 14)
	/*  */
#define IO_BANK0_INTR1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_INTR1_GPIO11_LEVEL_LOW				(1u << 12)
	/*  */
#define IO_BANK0_INTR1_GPIO10_EDGE_HIGH				(1u << 11)
	/*  */
#define IO_BANK0_INTR1_GPIO10_EDGE_LOW				(1u << 10)
	/*  */
#define IO_BANK0_INTR1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_INTR1_GPIO10_LEVEL_LOW				(1u << 8)
	/*  */
#define IO_BANK0_INTR1_GPIO9_EDGE_HIGH				(1u << 7)
	/*  */
#define IO_BANK0_INTR1_GPIO9_EDGE_LOW				(1u << 6)
	/*  */
#define IO_BANK0_INTR1_GPIO9_LEVEL_HIGH				(1u << 5)
	/*  */
#define IO_BANK0_INTR1_GPIO9_LEVEL_LOW				(1u << 4)
	/*  */
#define IO_BANK0_INTR1_GPIO8_EDGE_HIGH				(1u << 3)
	/*  */
#define IO_BANK0_INTR1_GPIO8_EDGE_LOW				(1u << 2)
	/*  */
#define IO_BANK0_INTR1_GPIO8_LEVEL_HIGH				(1u << 1)
	/*  */
#define IO_BANK0_INTR1_GPIO8_LEVEL_LOW				(1u << 0)

	/* 0xF8: Raw Interrupts */
	uint32_t volatile INTR2;
	/*  */
#define IO_BANK0_INTR2_GPIO23_EDGE_HIGH				(1u << 31)
	/*  */
#define IO_BANK0_INTR2_GPIO23_EDGE_LOW				(1u << 30)
	/*  */
#define IO_BANK0_INTR2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_INTR2_GPIO23_LEVEL_LOW				(1u << 28)
	/*  */
#define IO_BANK0_INTR2_GPIO22_EDGE_HIGH				(1u << 27)
	/*  */
#define IO_BANK0_INTR2_GPIO22_EDGE_LOW				(1u << 26)
	/*  */
#define IO_BANK0_INTR2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_INTR2_GPIO22_LEVEL_LOW				(1u << 24)
	/*  */
#define IO_BANK0_INTR2_GPIO21_EDGE_HIGH				(1u << 23)
	/*  */
#define IO_BANK0_INTR2_GPIO21_EDGE_LOW				(1u << 22)
	/*  */
#define IO_BANK0_INTR2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_INTR2_GPIO21_LEVEL_LOW				(1u << 20)
	/*  */
#define IO_BANK0_INTR2_GPIO20_EDGE_HIGH				(1u << 19)
	/*  */
#define IO_BANK0_INTR2_GPIO20_EDGE_LOW				(1u << 18)
	/*  */
#define IO_BANK0_INTR2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_INTR2_GPIO20_LEVEL_LOW				(1u << 16)
	/*  */
#define IO_BANK0_INTR2_GPIO19_EDGE_HIGH				(1u << 15)
	/*  */
#define IO_BANK0_INTR2_GPIO19_EDGE_LOW				(1u << 14)
	/*  */
#define IO_BANK0_INTR2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_INTR2_GPIO19_LEVEL_LOW				(1u << 12)
	/*  */
#define IO_BANK0_INTR2_GPIO18_EDGE_HIGH				(1u << 11)
	/*  */
#define IO_BANK0_INTR2_GPIO18_EDGE_LOW				(1u << 10)
	/*  */
#define IO_BANK0_INTR2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_INTR2_GPIO18_LEVEL_LOW				(1u << 8)
	/*  */
#define IO_BANK0_INTR2_GPIO17_EDGE_HIGH				(1u << 7)
	/*  */
#define IO_BANK0_INTR2_GPIO17_EDGE_LOW				(1u << 6)
	/*  */
#define IO_BANK0_INTR2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_INTR2_GPIO17_LEVEL_LOW				(1u << 4)
	/*  */
#define IO_BANK0_INTR2_GPIO16_EDGE_HIGH				(1u << 3)
	/*  */
#define IO_BANK0_INTR2_GPIO16_EDGE_LOW				(1u << 2)
	/*  */
#define IO_BANK0_INTR2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_INTR2_GPIO16_LEVEL_LOW				(1u << 0)

	/* 0xFC: Raw Interrupts */
	uint32_t volatile INTR3;
	/*  */
#define IO_BANK0_INTR3_GPIO29_EDGE_HIGH				(1u << 23)
	/*  */
#define IO_BANK0_INTR3_GPIO29_EDGE_LOW				(1u << 22)
	/*  */
#define IO_BANK0_INTR3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_INTR3_GPIO29_LEVEL_LOW				(1u << 20)
	/*  */
#define IO_BANK0_INTR3_GPIO28_EDGE_HIGH				(1u << 19)
	/*  */
#define IO_BANK0_INTR3_GPIO28_EDGE_LOW				(1u << 18)
	/*  */
#define IO_BANK0_INTR3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_INTR3_GPIO28_LEVEL_LOW				(1u << 16)
	/*  */
#define IO_BANK0_INTR3_GPIO27_EDGE_HIGH				(1u << 15)
	/*  */
#define IO_BANK0_INTR3_GPIO27_EDGE_LOW				(1u << 14)
	/*  */
#define IO_BANK0_INTR3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_INTR3_GPIO27_LEVEL_LOW				(1u << 12)
	/*  */
#define IO_BANK0_INTR3_GPIO26_EDGE_HIGH				(1u << 11)
	/*  */
#define IO_BANK0_INTR3_GPIO26_EDGE_LOW				(1u << 10)
	/*  */
#define IO_BANK0_INTR3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_INTR3_GPIO26_LEVEL_LOW				(1u << 8)
	/*  */
#define IO_BANK0_INTR3_GPIO25_EDGE_HIGH				(1u << 7)
	/*  */
#define IO_BANK0_INTR3_GPIO25_EDGE_LOW				(1u << 6)
	/*  */
#define IO_BANK0_INTR3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_INTR3_GPIO25_LEVEL_LOW				(1u << 4)
	/*  */
#define IO_BANK0_INTR3_GPIO24_EDGE_HIGH				(1u << 3)
	/*  */
#define IO_BANK0_INTR3_GPIO24_EDGE_LOW				(1u << 2)
	/*  */
#define IO_BANK0_INTR3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_INTR3_GPIO24_LEVEL_LOW				(1u << 0)

	/* 0x100: Interrupt Enable for proc0 */
	uint32_t volatile PROC0_INTE0;
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO7_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO7_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO7_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO7_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO6_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO6_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO6_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO6_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO5_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO5_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO5_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO5_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO4_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO4_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO4_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO4_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO3_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO3_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO3_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO3_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO2_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO2_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO2_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO2_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO1_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO1_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO1_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO1_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO0_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO0_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO0_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTE0_GPIO0_LEVEL_LOW			(1u << 0)

	/* 0x104: Interrupt Enable for proc0 */
	uint32_t volatile PROC0_INTE1;
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO15_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO15_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO15_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO14_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO14_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO14_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO13_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO13_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO13_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO12_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO12_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO12_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO11_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO11_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO11_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO10_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO10_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO10_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO9_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO9_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO9_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO9_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO8_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO8_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO8_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTE1_GPIO8_LEVEL_LOW			(1u << 0)

	/* 0x108: Interrupt Enable for proc0 */
	uint32_t volatile PROC0_INTE2;
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO23_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO23_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO23_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO22_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO22_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO22_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO21_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO21_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO21_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO20_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO20_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO20_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO19_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO19_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO19_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO18_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO18_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO18_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO17_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO17_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO17_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO16_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO16_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTE2_GPIO16_LEVEL_LOW			(1u << 0)

	/* 0x10C: Interrupt Enable for proc0 */
	uint32_t volatile PROC0_INTE3;
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO29_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO29_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO29_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO28_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO28_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO28_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO27_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO27_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO27_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO26_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO26_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO26_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO25_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO25_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO25_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO24_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO24_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTE3_GPIO24_LEVEL_LOW			(1u << 0)

	/* 0x110: Interrupt Force for proc0 */
	uint32_t volatile PROC0_INTF0;
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO7_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO7_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO7_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO7_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO6_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO6_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO6_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO6_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO5_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO5_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO5_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO5_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO4_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO4_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO4_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO4_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO3_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO3_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO3_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO3_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO2_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO2_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO2_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO2_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO1_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO1_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO1_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO1_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO0_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO0_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO0_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTF0_GPIO0_LEVEL_LOW			(1u << 0)

	/* 0x114: Interrupt Force for proc0 */
	uint32_t volatile PROC0_INTF1;
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO15_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO15_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO15_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO14_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO14_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO14_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO13_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO13_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO13_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO12_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO12_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO12_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO11_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO11_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO11_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO10_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO10_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO10_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO9_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO9_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO9_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO9_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO8_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO8_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO8_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTF1_GPIO8_LEVEL_LOW			(1u << 0)

	/* 0x118: Interrupt Force for proc0 */
	uint32_t volatile PROC0_INTF2;
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO23_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO23_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO23_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO22_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO22_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO22_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO21_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO21_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO21_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO20_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO20_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO20_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO19_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO19_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO19_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO18_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO18_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO18_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO17_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO17_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO17_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO16_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO16_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTF2_GPIO16_LEVEL_LOW			(1u << 0)

	/* 0x11C: Interrupt Force for proc0 */
	uint32_t volatile PROC0_INTF3;
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO29_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO29_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO29_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO28_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO28_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO28_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO27_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO27_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO27_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO26_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO26_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO26_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO25_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO25_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO25_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO24_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO24_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTF3_GPIO24_LEVEL_LOW			(1u << 0)

	/* 0x120: Interrupt status after masking & forcing for proc0 */
	uint32_t volatile PROC0_INTS0;
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO7_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO7_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO7_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO7_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO6_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO6_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO6_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO6_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO5_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO5_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO5_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO5_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO4_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO4_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO4_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO4_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO3_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO3_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO3_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO3_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO2_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO2_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO2_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO2_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO1_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO1_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO1_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO1_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO0_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO0_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO0_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTS0_GPIO0_LEVEL_LOW			(1u << 0)

	/* 0x124: Interrupt status after masking & forcing for proc0 */
	uint32_t volatile PROC0_INTS1;
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO15_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO15_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO15_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO14_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO14_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO14_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO13_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO13_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO13_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO12_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO12_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO12_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO11_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO11_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO11_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO10_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO10_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO10_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO9_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO9_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO9_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO9_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO8_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO8_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO8_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTS1_GPIO8_LEVEL_LOW			(1u << 0)

	/* 0x128: Interrupt status after masking & forcing for proc0 */
	uint32_t volatile PROC0_INTS2;
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO23_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO23_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO23_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO22_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO22_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO22_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO21_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO21_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO21_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO20_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO20_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO20_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO19_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO19_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO19_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO18_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO18_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO18_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO17_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO17_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO17_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO16_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO16_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTS2_GPIO16_LEVEL_LOW			(1u << 0)

	/* 0x12C: Interrupt status after masking & forcing for proc0 */
	uint32_t volatile PROC0_INTS3;
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO29_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO29_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO29_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO28_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO28_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO28_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO27_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO27_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO27_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO26_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO26_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO26_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO25_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO25_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO25_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO24_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO24_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC0_INTS3_GPIO24_LEVEL_LOW			(1u << 0)

	/* 0x130: Interrupt Enable for proc1 */
	uint32_t volatile PROC1_INTE0;
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO7_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO7_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO7_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO7_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO6_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO6_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO6_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO6_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO5_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO5_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO5_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO5_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO4_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO4_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO4_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO4_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO3_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO3_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO3_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO3_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO2_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO2_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO2_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO2_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO1_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO1_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO1_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO1_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO0_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO0_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO0_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTE0_GPIO0_LEVEL_LOW			(1u << 0)

	/* 0x134: Interrupt Enable for proc1 */
	uint32_t volatile PROC1_INTE1;
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO15_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO15_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO15_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO14_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO14_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO14_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO13_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO13_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO13_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO12_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO12_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO12_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO11_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO11_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO11_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO10_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO10_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO10_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO9_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO9_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO9_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO9_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO8_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO8_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO8_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTE1_GPIO8_LEVEL_LOW			(1u << 0)

	/* 0x138: Interrupt Enable for proc1 */
	uint32_t volatile PROC1_INTE2;
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO23_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO23_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO23_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO22_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO22_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO22_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO21_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO21_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO21_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO20_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO20_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO20_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO19_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO19_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO19_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO18_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO18_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO18_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO17_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO17_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO17_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO16_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO16_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTE2_GPIO16_LEVEL_LOW			(1u << 0)

	/* 0x13C: Interrupt Enable for proc1 */
	uint32_t volatile PROC1_INTE3;
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO29_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO29_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO29_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO28_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO28_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO28_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO27_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO27_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO27_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO26_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO26_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO26_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO25_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO25_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO25_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO24_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO24_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTE3_GPIO24_LEVEL_LOW			(1u << 0)

	/* 0x140: Interrupt Force for proc1 */
	uint32_t volatile PROC1_INTF0;
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO7_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO7_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO7_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO7_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO6_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO6_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO6_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO6_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO5_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO5_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO5_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO5_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO4_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO4_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO4_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO4_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO3_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO3_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO3_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO3_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO2_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO2_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO2_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO2_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO1_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO1_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO1_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO1_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO0_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO0_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO0_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTF0_GPIO0_LEVEL_LOW			(1u << 0)

	/* 0x144: Interrupt Force for proc1 */
	uint32_t volatile PROC1_INTF1;
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO15_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO15_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO15_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO14_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO14_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO14_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO13_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO13_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO13_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO12_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO12_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO12_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO11_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO11_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO11_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO10_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO10_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO10_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO9_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO9_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO9_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO9_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO8_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO8_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO8_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTF1_GPIO8_LEVEL_LOW			(1u << 0)

	/* 0x148: Interrupt Force for proc1 */
	uint32_t volatile PROC1_INTF2;
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO23_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO23_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO23_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO22_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO22_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO22_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO21_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO21_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO21_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO20_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO20_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO20_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO19_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO19_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO19_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO18_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO18_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO18_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO17_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO17_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO17_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO16_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO16_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTF2_GPIO16_LEVEL_LOW			(1u << 0)

	/* 0x14C: Interrupt Force for proc1 */
	uint32_t volatile PROC1_INTF3;
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO29_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO29_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO29_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO28_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO28_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO28_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO27_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO27_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO27_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO26_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO26_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO26_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO25_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO25_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO25_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO24_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO24_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTF3_GPIO24_LEVEL_LOW			(1u << 0)

	/* 0x150: Interrupt status after masking & forcing for proc1 */
	uint32_t volatile PROC1_INTS0;
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO7_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO7_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO7_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO7_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO6_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO6_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO6_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO6_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO5_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO5_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO5_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO5_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO4_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO4_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO4_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO4_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO3_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO3_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO3_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO3_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO2_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO2_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO2_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO2_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO1_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO1_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO1_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO1_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO0_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO0_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO0_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTS0_GPIO0_LEVEL_LOW			(1u << 0)

	/* 0x154: Interrupt status after masking & forcing for proc1 */
	uint32_t volatile PROC1_INTS1;
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO15_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO15_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO15_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO15_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO14_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO14_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO14_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO14_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO13_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO13_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO13_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO13_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO12_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO12_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO12_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO12_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO11_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO11_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO11_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO11_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO10_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO10_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO10_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO10_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO9_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO9_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO9_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO9_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO8_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO8_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO8_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTS1_GPIO8_LEVEL_LOW			(1u << 0)

	/* 0x158: Interrupt status after masking & forcing for proc1 */
	uint32_t volatile PROC1_INTS2;
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO23_EDGE_HIGH			(1u << 31)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO23_EDGE_LOW			(1u << 30)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO23_LEVEL_HIGH			(1u << 29)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO23_LEVEL_LOW			(1u << 28)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO22_EDGE_HIGH			(1u << 27)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO22_EDGE_LOW			(1u << 26)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO22_LEVEL_HIGH			(1u << 25)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO22_LEVEL_LOW			(1u << 24)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO21_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO21_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO21_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO21_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO20_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO20_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO20_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO20_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO19_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO19_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO19_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO19_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO18_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO18_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO18_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO18_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO17_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO17_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO17_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO17_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO16_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO16_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO16_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTS2_GPIO16_LEVEL_LOW			(1u << 0)

	/* 0x15C: Interrupt status after masking & forcing for proc1 */
	uint32_t volatile PROC1_INTS3;
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO29_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO29_EDGE_LOW			(1u << 22)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO29_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO29_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO28_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO28_EDGE_LOW			(1u << 18)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO28_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO28_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO27_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO27_EDGE_LOW			(1u << 14)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO27_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO27_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO26_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO26_EDGE_LOW			(1u << 10)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO26_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO26_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO25_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO25_EDGE_LOW			(1u << 6)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO25_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO25_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO24_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO24_EDGE_LOW			(1u << 2)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO24_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_BANK0_PROC1_INTS3_GPIO24_LEVEL_LOW			(1u << 0)

	/* 0x160: Interrupt Enable for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTE0;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO7_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO7_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO7_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO7_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO6_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO6_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO6_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO6_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO5_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO5_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO5_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO5_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO4_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO4_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO4_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO4_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO3_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO3_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO3_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO3_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO2_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO2_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO2_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO2_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO1_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO1_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO1_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO1_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_LEVEL_LOW		(1u << 0)

	/* 0x164: Interrupt Enable for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTE1;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO15_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO15_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO15_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO15_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO14_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO14_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO14_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO14_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO13_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO13_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO13_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO13_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO12_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO12_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO12_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO12_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO11_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO11_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO11_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO11_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO10_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO10_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO10_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO10_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO9_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO9_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO9_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO9_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO8_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO8_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO8_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE1_GPIO8_LEVEL_LOW		(1u << 0)

	/* 0x168: Interrupt Enable for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTE2;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO23_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO23_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO23_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO23_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO22_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO22_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO22_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO22_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO21_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO21_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO21_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO21_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO20_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO20_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO20_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO20_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO19_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO19_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO19_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO19_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO18_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO18_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO18_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO18_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO17_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO17_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO17_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO17_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO16_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO16_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO16_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE2_GPIO16_LEVEL_LOW		(1u << 0)

	/* 0x16C: Interrupt Enable for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTE3;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO29_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO29_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO29_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO29_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO28_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO28_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO28_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO28_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO27_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO27_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO27_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO27_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO26_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO26_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO26_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO26_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO25_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO25_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO25_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO25_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO24_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO24_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO24_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTE3_GPIO24_LEVEL_LOW		(1u << 0)

	/* 0x170: Interrupt Force for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTF0;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO7_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO7_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO7_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO7_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO6_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO6_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO6_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO6_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO5_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO5_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO5_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO5_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO4_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO4_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO4_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO4_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO3_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO3_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO3_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO3_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO2_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO2_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO2_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO2_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO1_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO1_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO1_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO1_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO0_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO0_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO0_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF0_GPIO0_LEVEL_LOW		(1u << 0)

	/* 0x174: Interrupt Force for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTF1;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO15_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO15_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO15_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO15_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO14_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO14_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO14_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO14_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO13_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO13_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO13_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO13_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO12_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO12_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO12_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO12_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO11_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO11_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO11_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO11_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO10_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO10_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO10_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO10_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO9_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO9_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO9_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO9_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO8_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO8_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO8_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF1_GPIO8_LEVEL_LOW		(1u << 0)

	/* 0x178: Interrupt Force for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTF2;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO23_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO23_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO23_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO23_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO22_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO22_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO22_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO22_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO21_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO21_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO21_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO21_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO20_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO20_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO20_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO20_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO19_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO19_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO19_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO19_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO18_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO18_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO18_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO18_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO17_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO17_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO17_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO17_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO16_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO16_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO16_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF2_GPIO16_LEVEL_LOW		(1u << 0)

	/* 0x17C: Interrupt Force for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTF3;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO29_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO29_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO29_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO29_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO28_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO28_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO28_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO28_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO27_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO27_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO27_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO27_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO26_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO26_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO26_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO26_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO25_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO25_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO25_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO25_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO24_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO24_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO24_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTF3_GPIO24_LEVEL_LOW		(1u << 0)

	/* 0x180: Interrupt status after masking & forcing for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTS0;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO7_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO7_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO7_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO7_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO6_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO6_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO6_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO6_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO5_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO5_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO5_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO5_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO4_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO4_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO4_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO4_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO3_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO3_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO3_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO3_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO2_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO2_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO2_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO2_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO1_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO1_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO1_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO1_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO0_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO0_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO0_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS0_GPIO0_LEVEL_LOW		(1u << 0)

	/* 0x184: Interrupt status after masking & forcing for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTS1;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO15_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO15_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO15_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO15_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO14_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO14_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO14_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO14_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO13_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO13_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO13_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO13_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO12_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO12_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO12_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO12_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO11_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO11_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO11_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO11_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO10_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO10_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO10_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO10_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO9_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO9_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO9_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO9_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO8_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO8_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO8_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS1_GPIO8_LEVEL_LOW		(1u << 0)

	/* 0x188: Interrupt status after masking & forcing for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTS2;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO23_EDGE_HIGH		(1u << 31)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO23_EDGE_LOW		(1u << 30)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO23_LEVEL_HIGH		(1u << 29)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO23_LEVEL_LOW		(1u << 28)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO22_EDGE_HIGH		(1u << 27)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO22_EDGE_LOW		(1u << 26)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO22_LEVEL_HIGH		(1u << 25)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO22_LEVEL_LOW		(1u << 24)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO21_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO21_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO21_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO21_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO20_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO20_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO20_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO20_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO19_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO19_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO19_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO19_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO18_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO18_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO18_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO18_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO17_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO17_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO17_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO17_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO16_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO16_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO16_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS2_GPIO16_LEVEL_LOW		(1u << 0)

	/* 0x18C: Interrupt status after masking & forcing for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTS3;
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO29_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO29_EDGE_LOW		(1u << 22)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO29_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO29_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO28_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO28_EDGE_LOW		(1u << 18)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO28_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO28_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO27_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO27_EDGE_LOW		(1u << 14)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO27_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO27_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO26_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO26_EDGE_LOW		(1u << 10)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO26_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO26_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO25_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO25_EDGE_LOW		(1u << 6)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO25_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO25_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO24_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO24_EDGE_LOW		(1u << 2)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO24_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_BANK0_DORMANT_WAKE_INTS3_GPIO24_LEVEL_LOW		(1u << 0)

};


#define IO_QSPI ((struct mcu_io_qspi *)0x40018000)

struct mcu_io_qspi {

	/* 0x00: GPIO status */
	uint32_t volatile GPIO_QSPI_SCLK_STATUS;
	/* interrupt to processors, after override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQTOPROC			(1u << 26)
	/* interrupt from pad before override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_IRQFROMPAD		(1u << 24)
	/* input signal to peripheral, after override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INTOPERI			(1u << 19)
	/* input signal from pad, before override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_INFROMPAD			(1u << 17)
	/* output enable to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OETOPAD			(1u << 13)
	/* output enable from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OEFROMPERI		(1u << 12)
	/* output signal to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTTOPAD			(1u << 9)
	/* output signal from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SCLK_STATUS_OUTFROMPERI		(1u << 8)

	/* 0x04: GPIO control including function select and overrides. */
	uint32_t volatile GPIO_QSPI_SCLK_CTRL;
	/*  */
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_Msk			(0x3u << 28)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_Pos			28u
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_NORMAL		(0x0u << 28)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_INVERT		(0x1u << 28)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_LOW			(0x2u << 28)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_IRQOVER_HIGH		(0x3u << 28)
	/*  */
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_Msk			(0x3u << 16)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_Pos			16u
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_NORMAL		(0x0u << 16)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_INVERT		(0x1u << 16)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_LOW			(0x2u << 16)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_INOVER_HIGH			(0x3u << 16)
	/*  */
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_Msk			(0x3u << 12)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_Pos			12u
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_NORMAL		(0x0u << 12)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_INVERT		(0x1u << 12)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_DISABLE		(0x2u << 12)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OEOVER_ENABLE		(0x3u << 12)
	/*  */
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_Msk			(0x3u << 8)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_Pos			8u
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_NORMAL		(0x0u << 8)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_INVERT		(0x1u << 8)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_LOW			(0x2u << 8)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_OUTOVER_HIGH		(0x3u << 8)
	/* 0-31 -> selects pin function according to the gpio table */
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_Msk			(0x1Fu << 0)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_Pos			0u
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_XIP_SCLK		(0x0u << 0)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_SIO_30		(0x5u << 0)
#define IO_QSPI_GPIO_QSPI_SCLK_CTRL_FUNCSEL_NULL		(0x1Fu << 0)

	/* 0x08: GPIO status */
	uint32_t volatile GPIO_QSPI_SS_STATUS;
	/* interrupt to processors, after override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQTOPROC			(1u << 26)
	/* interrupt from pad before override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_IRQFROMPAD			(1u << 24)
	/* input signal to peripheral, after override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INTOPERI			(1u << 19)
	/* input signal from pad, before override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_INFROMPAD			(1u << 17)
	/* output enable to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OETOPAD			(1u << 13)
	/* output enable from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OEFROMPERI			(1u << 12)
	/* output signal to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTTOPAD			(1u << 9)
	/* output signal from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SS_STATUS_OUTFROMPERI			(1u << 8)

	/* 0x0C: GPIO control including function select and overrides. */
	uint32_t volatile GPIO_QSPI_SS_CTRL;
	/*  */
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_Msk			(0x3u << 28)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_Pos			28u
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_NORMAL		(0x0u << 28)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_INVERT		(0x1u << 28)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_LOW			(0x2u << 28)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_IRQOVER_HIGH			(0x3u << 28)
	/*  */
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_Msk			(0x3u << 16)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_Pos			16u
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_NORMAL			(0x0u << 16)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_INVERT			(0x1u << 16)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_LOW			(0x2u << 16)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_INOVER_HIGH			(0x3u << 16)
	/*  */
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_Msk			(0x3u << 12)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_Pos			12u
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_NORMAL			(0x0u << 12)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_INVERT			(0x1u << 12)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_DISABLE		(0x2u << 12)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_ENABLE			(0x3u << 12)
	/*  */
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_Msk			(0x3u << 8)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_Pos			8u
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_NORMAL		(0x0u << 8)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_INVERT		(0x1u << 8)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_LOW			(0x2u << 8)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_HIGH			(0x3u << 8)
	/* 0-31 -> selects pin function according to the gpio table */
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_Msk			(0x1Fu << 0)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_Pos			0u
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_XIP_SS_N		(0x0u << 0)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_SIO_31		(0x5u << 0)
#define IO_QSPI_GPIO_QSPI_SS_CTRL_FUNCSEL_NULL			(0x1Fu << 0)

	/* 0x10: GPIO status */
	uint32_t volatile GPIO_QSPI_SD0_STATUS;
	/* interrupt to processors, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQTOPROC			(1u << 26)
	/* interrupt from pad before override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_IRQFROMPAD			(1u << 24)
	/* input signal to peripheral, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INTOPERI			(1u << 19)
	/* input signal from pad, before override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_INFROMPAD			(1u << 17)
	/* output enable to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OETOPAD			(1u << 13)
	/* output enable from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OEFROMPERI			(1u << 12)
	/* output signal to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTTOPAD			(1u << 9)
	/* output signal from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD0_STATUS_OUTFROMPERI		(1u << 8)

	/* 0x14: GPIO control including function select and overrides. */
	uint32_t volatile GPIO_QSPI_SD0_CTRL;
	/*  */
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_Msk			(0x3u << 28)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_Pos			28u
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_NORMAL		(0x0u << 28)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_INVERT		(0x1u << 28)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_LOW			(0x2u << 28)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_IRQOVER_HIGH			(0x3u << 28)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_Msk			(0x3u << 16)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_Pos			16u
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_NORMAL		(0x0u << 16)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_INVERT		(0x1u << 16)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_LOW			(0x2u << 16)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_INOVER_HIGH			(0x3u << 16)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_Msk			(0x3u << 12)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_Pos			12u
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_NORMAL		(0x0u << 12)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_INVERT		(0x1u << 12)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_DISABLE		(0x2u << 12)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OEOVER_ENABLE		(0x3u << 12)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_Msk			(0x3u << 8)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_Pos			8u
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_NORMAL		(0x0u << 8)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_INVERT		(0x1u << 8)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_LOW			(0x2u << 8)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_OUTOVER_HIGH			(0x3u << 8)
	/* 0-31 -> selects pin function according to the gpio table */
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_Msk			(0x1Fu << 0)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_Pos			0u
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_XIP_SD0		(0x0u << 0)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_SIO_32		(0x5u << 0)
#define IO_QSPI_GPIO_QSPI_SD0_CTRL_FUNCSEL_NULL			(0x1Fu << 0)

	/* 0x18: GPIO status */
	uint32_t volatile GPIO_QSPI_SD1_STATUS;
	/* interrupt to processors, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQTOPROC			(1u << 26)
	/* interrupt from pad before override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_IRQFROMPAD			(1u << 24)
	/* input signal to peripheral, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INTOPERI			(1u << 19)
	/* input signal from pad, before override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_INFROMPAD			(1u << 17)
	/* output enable to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OETOPAD			(1u << 13)
	/* output enable from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OEFROMPERI			(1u << 12)
	/* output signal to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTTOPAD			(1u << 9)
	/* output signal from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD1_STATUS_OUTFROMPERI		(1u << 8)

	/* 0x1C: GPIO control including function select and overrides. */
	uint32_t volatile GPIO_QSPI_SD1_CTRL;
	/*  */
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_Msk			(0x3u << 28)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_Pos			28u
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_NORMAL		(0x0u << 28)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_INVERT		(0x1u << 28)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_LOW			(0x2u << 28)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_IRQOVER_HIGH			(0x3u << 28)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_Msk			(0x3u << 16)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_Pos			16u
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_NORMAL		(0x0u << 16)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_INVERT		(0x1u << 16)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_LOW			(0x2u << 16)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_HIGH			(0x3u << 16)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_Msk			(0x3u << 12)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_Pos			12u
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_NORMAL		(0x0u << 12)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_INVERT		(0x1u << 12)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_DISABLE		(0x2u << 12)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OEOVER_ENABLE		(0x3u << 12)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_Msk			(0x3u << 8)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_Pos			8u
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_NORMAL		(0x0u << 8)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_INVERT		(0x1u << 8)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_LOW			(0x2u << 8)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_OUTOVER_HIGH			(0x3u << 8)
	/* 0-31 -> selects pin function according to the gpio table */
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_Msk			(0x1Fu << 0)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_Pos			0u
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_XIP_SD1		(0x0u << 0)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_SIO_33		(0x5u << 0)
#define IO_QSPI_GPIO_QSPI_SD1_CTRL_FUNCSEL_NULL			(0x1Fu << 0)

	/* 0x20: GPIO status */
	uint32_t volatile GPIO_QSPI_SD2_STATUS;
	/* interrupt to processors, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQTOPROC			(1u << 26)
	/* interrupt from pad before override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_IRQFROMPAD			(1u << 24)
	/* input signal to peripheral, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INTOPERI			(1u << 19)
	/* input signal from pad, before override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_INFROMPAD			(1u << 17)
	/* output enable to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OETOPAD			(1u << 13)
	/* output enable from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OEFROMPERI			(1u << 12)
	/* output signal to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTTOPAD			(1u << 9)
	/* output signal from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD2_STATUS_OUTFROMPERI		(1u << 8)

	/* 0x24: GPIO control including function select and overrides. */
	uint32_t volatile GPIO_QSPI_SD2_CTRL;
	/*  */
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_Msk			(0x3u << 28)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_Pos			28u
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_NORMAL		(0x0u << 28)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_INVERT		(0x1u << 28)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_LOW			(0x2u << 28)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_IRQOVER_HIGH			(0x3u << 28)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_Msk			(0x3u << 16)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_Pos			16u
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_NORMAL		(0x0u << 16)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_INVERT		(0x1u << 16)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_LOW			(0x2u << 16)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_INOVER_HIGH			(0x3u << 16)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_Msk			(0x3u << 12)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_Pos			12u
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_NORMAL		(0x0u << 12)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_INVERT		(0x1u << 12)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_DISABLE		(0x2u << 12)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OEOVER_ENABLE		(0x3u << 12)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_Msk			(0x3u << 8)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_Pos			8u
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_NORMAL		(0x0u << 8)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_INVERT		(0x1u << 8)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_LOW			(0x2u << 8)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_OUTOVER_HIGH			(0x3u << 8)
	/* 0-31 -> selects pin function according to the gpio table */
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_Msk			(0x1Fu << 0)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_Pos			0u
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_XIP_SD2		(0x0u << 0)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_SIO_34		(0x5u << 0)
#define IO_QSPI_GPIO_QSPI_SD2_CTRL_FUNCSEL_NULL			(0x1Fu << 0)

	/* 0x28: GPIO status */
	uint32_t volatile GPIO_QSPI_SD3_STATUS;
	/* interrupt to processors, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQTOPROC			(1u << 26)
	/* interrupt from pad before override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_IRQFROMPAD			(1u << 24)
	/* input signal to peripheral, after override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INTOPERI			(1u << 19)
	/* input signal from pad, before override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_INFROMPAD			(1u << 17)
	/* output enable to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OETOPAD			(1u << 13)
	/* output enable from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OEFROMPERI			(1u << 12)
	/* output signal to pad after register override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTTOPAD			(1u << 9)
	/* output signal from selected peripheral, before register override is applied */
#define IO_QSPI_GPIO_QSPI_SD3_STATUS_OUTFROMPERI		(1u << 8)

	/* 0x2C: GPIO control including function select and overrides. */
	uint32_t volatile GPIO_QSPI_SD3_CTRL;
	/*  */
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_Msk			(0x3u << 28)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_Pos			28u
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_NORMAL		(0x0u << 28)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_INVERT		(0x1u << 28)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_LOW			(0x2u << 28)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_IRQOVER_HIGH			(0x3u << 28)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_Msk			(0x3u << 16)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_Pos			16u
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_NORMAL		(0x0u << 16)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_INVERT		(0x1u << 16)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_LOW			(0x2u << 16)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_INOVER_HIGH			(0x3u << 16)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_Msk			(0x3u << 12)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_Pos			12u
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_NORMAL		(0x0u << 12)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_INVERT		(0x1u << 12)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_DISABLE		(0x2u << 12)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OEOVER_ENABLE		(0x3u << 12)
	/*  */
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_Msk			(0x3u << 8)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_Pos			8u
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_NORMAL		(0x0u << 8)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_INVERT		(0x1u << 8)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_LOW			(0x2u << 8)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_OUTOVER_HIGH			(0x3u << 8)
	/* 0-31 -> selects pin function according to the gpio table */
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_Msk			(0x1Fu << 0)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_Pos			0u
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_XIP_SD3		(0x0u << 0)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_SIO_35		(0x5u << 0)
#define IO_QSPI_GPIO_QSPI_SD3_CTRL_FUNCSEL_NULL			(0x1Fu << 0)

	/* 0x30: Raw Interrupts */
	uint32_t volatile INTR;
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_HIGH			(1u << 23)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD3_EDGE_LOW			(1u << 22)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_HIGH			(1u << 21)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD3_LEVEL_LOW			(1u << 20)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_HIGH			(1u << 19)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD2_EDGE_LOW			(1u << 18)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_HIGH			(1u << 17)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD2_LEVEL_LOW			(1u << 16)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_HIGH			(1u << 15)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD1_EDGE_LOW			(1u << 14)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_HIGH			(1u << 13)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD1_LEVEL_LOW			(1u << 12)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_HIGH			(1u << 11)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD0_EDGE_LOW			(1u << 10)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_HIGH			(1u << 9)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SD0_LEVEL_LOW			(1u << 8)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_HIGH			(1u << 7)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SS_EDGE_LOW			(1u << 6)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_HIGH			(1u << 5)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SS_LEVEL_LOW			(1u << 4)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_HIGH			(1u << 3)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_EDGE_LOW			(1u << 2)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_HIGH			(1u << 1)
	/*  */
#define IO_QSPI_INTR_GPIO_QSPI_SCLK_LEVEL_LOW			(1u << 0)

	/* 0x34: Interrupt Enable for proc0 */
	uint32_t volatile PROC0_INTE;
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_EDGE_LOW		(1u << 22)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD3_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_EDGE_LOW		(1u << 18)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD2_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_EDGE_LOW		(1u << 14)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD1_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_EDGE_LOW		(1u << 10)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SD0_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SS_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_EDGE_LOW		(1u << 2)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_QSPI_PROC0_INTE_GPIO_QSPI_SCLK_LEVEL_LOW		(1u << 0)

	/* 0x38: Interrupt Force for proc0 */
	uint32_t volatile PROC0_INTF;
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_EDGE_LOW		(1u << 22)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD3_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_EDGE_LOW		(1u << 18)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD2_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_EDGE_LOW		(1u << 14)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD1_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_EDGE_LOW		(1u << 10)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SD0_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SS_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_EDGE_LOW		(1u << 2)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_QSPI_PROC0_INTF_GPIO_QSPI_SCLK_LEVEL_LOW		(1u << 0)

	/* 0x3C: Interrupt status after masking & forcing for proc0 */
	uint32_t volatile PROC0_INTS;
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_EDGE_LOW		(1u << 22)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD3_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_EDGE_LOW		(1u << 18)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD2_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_EDGE_LOW		(1u << 14)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD1_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_EDGE_LOW		(1u << 10)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SD0_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SS_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_EDGE_LOW		(1u << 2)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_QSPI_PROC0_INTS_GPIO_QSPI_SCLK_LEVEL_LOW		(1u << 0)

	/* 0x40: Interrupt Enable for proc1 */
	uint32_t volatile PROC1_INTE;
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_EDGE_LOW		(1u << 22)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD3_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_EDGE_LOW		(1u << 18)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD2_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_EDGE_LOW		(1u << 14)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD1_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_EDGE_LOW		(1u << 10)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SD0_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SS_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_EDGE_LOW		(1u << 2)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_QSPI_PROC1_INTE_GPIO_QSPI_SCLK_LEVEL_LOW		(1u << 0)

	/* 0x44: Interrupt Force for proc1 */
	uint32_t volatile PROC1_INTF;
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_EDGE_LOW		(1u << 22)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD3_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_EDGE_LOW		(1u << 18)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD2_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_EDGE_LOW		(1u << 14)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD1_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_EDGE_LOW		(1u << 10)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SD0_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SS_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_EDGE_LOW		(1u << 2)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_QSPI_PROC1_INTF_GPIO_QSPI_SCLK_LEVEL_LOW		(1u << 0)

	/* 0x48: Interrupt status after masking & forcing for proc1 */
	uint32_t volatile PROC1_INTS;
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_HIGH		(1u << 23)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_EDGE_LOW		(1u << 22)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_HIGH		(1u << 21)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD3_LEVEL_LOW		(1u << 20)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_HIGH		(1u << 19)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_EDGE_LOW		(1u << 18)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_HIGH		(1u << 17)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD2_LEVEL_LOW		(1u << 16)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_HIGH		(1u << 15)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_EDGE_LOW		(1u << 14)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_HIGH		(1u << 13)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD1_LEVEL_LOW		(1u << 12)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_HIGH		(1u << 11)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_EDGE_LOW		(1u << 10)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_HIGH		(1u << 9)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SD0_LEVEL_LOW		(1u << 8)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_HIGH		(1u << 7)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_HIGH		(1u << 5)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SS_LEVEL_LOW		(1u << 4)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_HIGH		(1u << 3)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_EDGE_LOW		(1u << 2)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH		(1u << 1)
	/*  */
#define IO_QSPI_PROC1_INTS_GPIO_QSPI_SCLK_LEVEL_LOW		(1u << 0)

	/* 0x4C: Interrupt Enable for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTE;
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_HIGH	(1u << 23)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_EDGE_LOW	(1u << 22)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_HIGH	(1u << 21)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD3_LEVEL_LOW	(1u << 20)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_HIGH	(1u << 19)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_EDGE_LOW	(1u << 18)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_HIGH	(1u << 17)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD2_LEVEL_LOW	(1u << 16)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_HIGH	(1u << 15)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_EDGE_LOW	(1u << 14)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_HIGH	(1u << 13)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD1_LEVEL_LOW	(1u << 12)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_HIGH	(1u << 11)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_EDGE_LOW	(1u << 10)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_HIGH	(1u << 9)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SD0_LEVEL_LOW	(1u << 8)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_HIGH	(1u << 7)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_HIGH	(1u << 5)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SS_LEVEL_LOW	(1u << 4)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_HIGH	(1u << 3)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_EDGE_LOW	(1u << 2)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_HIGH	(1u << 1)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTE_GPIO_QSPI_SCLK_LEVEL_LOW	(1u << 0)

	/* 0x50: Interrupt Force for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTF;
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_HIGH	(1u << 23)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_EDGE_LOW	(1u << 22)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_HIGH	(1u << 21)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD3_LEVEL_LOW	(1u << 20)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_HIGH	(1u << 19)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_EDGE_LOW	(1u << 18)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_HIGH	(1u << 17)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD2_LEVEL_LOW	(1u << 16)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_HIGH	(1u << 15)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_EDGE_LOW	(1u << 14)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_HIGH	(1u << 13)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD1_LEVEL_LOW	(1u << 12)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_HIGH	(1u << 11)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_EDGE_LOW	(1u << 10)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_HIGH	(1u << 9)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SD0_LEVEL_LOW	(1u << 8)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_HIGH	(1u << 7)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_HIGH	(1u << 5)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SS_LEVEL_LOW	(1u << 4)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_HIGH	(1u << 3)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_EDGE_LOW	(1u << 2)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_HIGH	(1u << 1)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTF_GPIO_QSPI_SCLK_LEVEL_LOW	(1u << 0)

	/* 0x54: Interrupt status after masking & forcing for dormant_wake */
	uint32_t volatile DORMANT_WAKE_INTS;
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_HIGH	(1u << 23)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_EDGE_LOW	(1u << 22)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_HIGH	(1u << 21)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD3_LEVEL_LOW	(1u << 20)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_HIGH	(1u << 19)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_EDGE_LOW	(1u << 18)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_HIGH	(1u << 17)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD2_LEVEL_LOW	(1u << 16)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_HIGH	(1u << 15)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_EDGE_LOW	(1u << 14)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_HIGH	(1u << 13)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD1_LEVEL_LOW	(1u << 12)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_HIGH	(1u << 11)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_EDGE_LOW	(1u << 10)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_HIGH	(1u << 9)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SD0_LEVEL_LOW	(1u << 8)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_HIGH	(1u << 7)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_EDGE_LOW		(1u << 6)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_HIGH	(1u << 5)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SS_LEVEL_LOW	(1u << 4)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_HIGH	(1u << 3)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_EDGE_LOW	(1u << 2)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_HIGH	(1u << 1)
	/*  */
#define IO_QSPI_DORMANT_WAKE_INTS_GPIO_QSPI_SCLK_LEVEL_LOW	(1u << 0)

};


#define PADS_BANK0 ((struct mcu_pads_bank0 *)0x4001C000)

struct mcu_pads_bank0 {

	/* 0x00: Voltage select. */
	uint32_t volatile VOLTAGE_SELECT;
	/*  */
#define PADS_BANK0_VOLTAGE_SELECT_VOLTAGE_SELECT		(1u << 0)
#define PADS_BANK0_VOLTAGE_SELECT_VOLTAGE_SELECT_3V3		(0x0u << 0)
#define PADS_BANK0_VOLTAGE_SELECT_VOLTAGE_SELECT_1V8		(0x1u << 0)

	/* 0x04: Pad control register */
	uint32_t volatile GPIO0;
	/* Output disable. */
#define PADS_BANK0_GPIO0_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO0_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO0_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO0_DRIVE_Pos				4u
#define PADS_BANK0_GPIO0_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO0_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO0_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO0_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO0_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO0_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO0_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO0_SLEWFAST				(1u << 0)

	/* 0x08: Pad control register */
	uint32_t volatile GPIO1;
	/* Output disable. */
#define PADS_BANK0_GPIO1_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO1_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO1_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO1_DRIVE_Pos				4u
#define PADS_BANK0_GPIO1_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO1_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO1_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO1_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO1_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO1_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO1_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO1_SLEWFAST				(1u << 0)

	/* 0x0C: Pad control register */
	uint32_t volatile GPIO2;
	/* Output disable. */
#define PADS_BANK0_GPIO2_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO2_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO2_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO2_DRIVE_Pos				4u
#define PADS_BANK0_GPIO2_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO2_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO2_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO2_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO2_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO2_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO2_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO2_SLEWFAST				(1u << 0)

	/* 0x10: Pad control register */
	uint32_t volatile GPIO3;
	/* Output disable. */
#define PADS_BANK0_GPIO3_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO3_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO3_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO3_DRIVE_Pos				4u
#define PADS_BANK0_GPIO3_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO3_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO3_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO3_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO3_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO3_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO3_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO3_SLEWFAST				(1u << 0)

	/* 0x14: Pad control register */
	uint32_t volatile GPIO4;
	/* Output disable. */
#define PADS_BANK0_GPIO4_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO4_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO4_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO4_DRIVE_Pos				4u
#define PADS_BANK0_GPIO4_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO4_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO4_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO4_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO4_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO4_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO4_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO4_SLEWFAST				(1u << 0)

	/* 0x18: Pad control register */
	uint32_t volatile GPIO5;
	/* Output disable. */
#define PADS_BANK0_GPIO5_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO5_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO5_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO5_DRIVE_Pos				4u
#define PADS_BANK0_GPIO5_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO5_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO5_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO5_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO5_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO5_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO5_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO5_SLEWFAST				(1u << 0)

	/* 0x1C: Pad control register */
	uint32_t volatile GPIO6;
	/* Output disable. */
#define PADS_BANK0_GPIO6_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO6_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO6_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO6_DRIVE_Pos				4u
#define PADS_BANK0_GPIO6_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO6_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO6_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO6_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO6_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO6_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO6_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO6_SLEWFAST				(1u << 0)

	/* 0x20: Pad control register */
	uint32_t volatile GPIO7;
	/* Output disable. */
#define PADS_BANK0_GPIO7_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO7_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO7_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO7_DRIVE_Pos				4u
#define PADS_BANK0_GPIO7_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO7_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO7_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO7_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO7_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO7_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO7_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO7_SLEWFAST				(1u << 0)

	/* 0x24: Pad control register */
	uint32_t volatile GPIO8;
	/* Output disable. */
#define PADS_BANK0_GPIO8_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO8_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO8_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO8_DRIVE_Pos				4u
#define PADS_BANK0_GPIO8_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO8_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO8_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO8_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO8_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO8_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO8_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO8_SLEWFAST				(1u << 0)

	/* 0x28: Pad control register */
	uint32_t volatile GPIO9;
	/* Output disable. */
#define PADS_BANK0_GPIO9_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO9_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO9_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO9_DRIVE_Pos				4u
#define PADS_BANK0_GPIO9_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO9_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO9_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO9_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO9_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO9_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO9_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO9_SLEWFAST				(1u << 0)

	/* 0x2C: Pad control register */
	uint32_t volatile GPIO10;
	/* Output disable. */
#define PADS_BANK0_GPIO10_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO10_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO10_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO10_DRIVE_Pos				4u
#define PADS_BANK0_GPIO10_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO10_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO10_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO10_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO10_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO10_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO10_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO10_SLEWFAST				(1u << 0)

	/* 0x30: Pad control register */
	uint32_t volatile GPIO11;
	/* Output disable. */
#define PADS_BANK0_GPIO11_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO11_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO11_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO11_DRIVE_Pos				4u
#define PADS_BANK0_GPIO11_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO11_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO11_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO11_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO11_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO11_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO11_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO11_SLEWFAST				(1u << 0)

	/* 0x34: Pad control register */
	uint32_t volatile GPIO12;
	/* Output disable. */
#define PADS_BANK0_GPIO12_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO12_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO12_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO12_DRIVE_Pos				4u
#define PADS_BANK0_GPIO12_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO12_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO12_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO12_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO12_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO12_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO12_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO12_SLEWFAST				(1u << 0)

	/* 0x38: Pad control register */
	uint32_t volatile GPIO13;
	/* Output disable. */
#define PADS_BANK0_GPIO13_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO13_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO13_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO13_DRIVE_Pos				4u
#define PADS_BANK0_GPIO13_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO13_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO13_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO13_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO13_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO13_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO13_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO13_SLEWFAST				(1u << 0)

	/* 0x3C: Pad control register */
	uint32_t volatile GPIO14;
	/* Output disable. */
#define PADS_BANK0_GPIO14_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO14_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO14_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO14_DRIVE_Pos				4u
#define PADS_BANK0_GPIO14_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO14_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO14_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO14_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO14_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO14_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO14_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO14_SLEWFAST				(1u << 0)

	/* 0x40: Pad control register */
	uint32_t volatile GPIO15;
	/* Output disable. */
#define PADS_BANK0_GPIO15_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO15_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO15_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO15_DRIVE_Pos				4u
#define PADS_BANK0_GPIO15_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO15_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO15_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO15_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO15_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO15_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO15_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO15_SLEWFAST				(1u << 0)

	/* 0x44: Pad control register */
	uint32_t volatile GPIO16;
	/* Output disable. */
#define PADS_BANK0_GPIO16_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO16_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO16_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO16_DRIVE_Pos				4u
#define PADS_BANK0_GPIO16_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO16_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO16_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO16_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO16_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO16_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO16_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO16_SLEWFAST				(1u << 0)

	/* 0x48: Pad control register */
	uint32_t volatile GPIO17;
	/* Output disable. */
#define PADS_BANK0_GPIO17_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO17_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO17_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO17_DRIVE_Pos				4u
#define PADS_BANK0_GPIO17_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO17_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO17_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO17_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO17_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO17_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO17_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO17_SLEWFAST				(1u << 0)

	/* 0x4C: Pad control register */
	uint32_t volatile GPIO18;
	/* Output disable. */
#define PADS_BANK0_GPIO18_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO18_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO18_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO18_DRIVE_Pos				4u
#define PADS_BANK0_GPIO18_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO18_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO18_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO18_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO18_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO18_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO18_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO18_SLEWFAST				(1u << 0)

	/* 0x50: Pad control register */
	uint32_t volatile GPIO19;
	/* Output disable. */
#define PADS_BANK0_GPIO19_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO19_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO19_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO19_DRIVE_Pos				4u
#define PADS_BANK0_GPIO19_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO19_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO19_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO19_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO19_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO19_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO19_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO19_SLEWFAST				(1u << 0)

	/* 0x54: Pad control register */
	uint32_t volatile GPIO20;
	/* Output disable. */
#define PADS_BANK0_GPIO20_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO20_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO20_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO20_DRIVE_Pos				4u
#define PADS_BANK0_GPIO20_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO20_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO20_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO20_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO20_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO20_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO20_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO20_SLEWFAST				(1u << 0)

	/* 0x58: Pad control register */
	uint32_t volatile GPIO21;
	/* Output disable. */
#define PADS_BANK0_GPIO21_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO21_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO21_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO21_DRIVE_Pos				4u
#define PADS_BANK0_GPIO21_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO21_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO21_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO21_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO21_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO21_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO21_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO21_SLEWFAST				(1u << 0)

	/* 0x5C: Pad control register */
	uint32_t volatile GPIO22;
	/* Output disable. */
#define PADS_BANK0_GPIO22_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO22_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO22_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO22_DRIVE_Pos				4u
#define PADS_BANK0_GPIO22_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO22_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO22_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO22_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO22_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO22_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO22_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO22_SLEWFAST				(1u << 0)

	/* 0x60: Pad control register */
	uint32_t volatile GPIO23;
	/* Output disable. */
#define PADS_BANK0_GPIO23_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO23_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO23_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO23_DRIVE_Pos				4u
#define PADS_BANK0_GPIO23_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO23_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO23_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO23_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO23_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO23_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO23_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO23_SLEWFAST				(1u << 0)

	/* 0x64: Pad control register */
	uint32_t volatile GPIO24;
	/* Output disable. */
#define PADS_BANK0_GPIO24_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO24_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO24_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO24_DRIVE_Pos				4u
#define PADS_BANK0_GPIO24_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO24_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO24_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO24_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO24_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO24_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO24_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO24_SLEWFAST				(1u << 0)

	/* 0x68: Pad control register */
	uint32_t volatile GPIO25;
	/* Output disable. */
#define PADS_BANK0_GPIO25_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO25_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO25_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO25_DRIVE_Pos				4u
#define PADS_BANK0_GPIO25_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO25_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO25_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO25_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO25_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO25_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO25_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO25_SLEWFAST				(1u << 0)

	/* 0x6C: Pad control register */
	uint32_t volatile GPIO26;
	/* Output disable. */
#define PADS_BANK0_GPIO26_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO26_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO26_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO26_DRIVE_Pos				4u
#define PADS_BANK0_GPIO26_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO26_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO26_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO26_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO26_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO26_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO26_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO26_SLEWFAST				(1u << 0)

	/* 0x70: Pad control register */
	uint32_t volatile GPIO27;
	/* Output disable. */
#define PADS_BANK0_GPIO27_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO27_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO27_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO27_DRIVE_Pos				4u
#define PADS_BANK0_GPIO27_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO27_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO27_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO27_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO27_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO27_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO27_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO27_SLEWFAST				(1u << 0)

	/* 0x74: Pad control register */
	uint32_t volatile GPIO28;
	/* Output disable. */
#define PADS_BANK0_GPIO28_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO28_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO28_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO28_DRIVE_Pos				4u
#define PADS_BANK0_GPIO28_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO28_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO28_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO28_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO28_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO28_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO28_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO28_SLEWFAST				(1u << 0)

	/* 0x78: Pad control register */
	uint32_t volatile GPIO29;
	/* Output disable. */
#define PADS_BANK0_GPIO29_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_GPIO29_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_GPIO29_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_GPIO29_DRIVE_Pos				4u
#define PADS_BANK0_GPIO29_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_GPIO29_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_GPIO29_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_GPIO29_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_GPIO29_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_GPIO29_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_GPIO29_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_GPIO29_SLEWFAST				(1u << 0)

	/* 0x7C: Pad control register */
	uint32_t volatile SWCLK;
	/* Output disable. */
#define PADS_BANK0_SWCLK_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_SWCLK_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_SWCLK_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_SWCLK_DRIVE_Pos				4u
#define PADS_BANK0_SWCLK_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_SWCLK_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_SWCLK_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_SWCLK_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_SWCLK_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_SWCLK_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_SWCLK_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_SWCLK_SLEWFAST				(1u << 0)

	/* 0x80: Pad control register */
	uint32_t volatile SWD;
	/* Output disable. */
#define PADS_BANK0_SWD_OD					(1u << 7)
	/* Input enable */
#define PADS_BANK0_SWD_IE					(1u << 6)
	/* Drive strength. */
#define PADS_BANK0_SWD_DRIVE_Msk				(0x3u << 4)
#define PADS_BANK0_SWD_DRIVE_Pos				4u
#define PADS_BANK0_SWD_DRIVE_2MA				(0x0u << 4)
#define PADS_BANK0_SWD_DRIVE_4MA				(0x1u << 4)
#define PADS_BANK0_SWD_DRIVE_8MA				(0x2u << 4)
#define PADS_BANK0_SWD_DRIVE_12MA				(0x3u << 4)
	/* Pull up enable */
#define PADS_BANK0_SWD_PUE					(1u << 3)
	/* Pull down enable */
#define PADS_BANK0_SWD_PDE					(1u << 2)
	/* Enable schmitt trigger */
#define PADS_BANK0_SWD_SCHMITT					(1u << 1)
	/* Slew rate control. */
#define PADS_BANK0_SWD_SLEWFAST					(1u << 0)

};


#define PADS_QSPI ((struct mcu_pads_qspi *)0x40020000)

struct mcu_pads_qspi {

	/* 0x00: Voltage select. */
	uint32_t volatile VOLTAGE_SELECT;
	/*  */
#define PADS_QSPI_VOLTAGE_SELECT_VOLTAGE_SELECT			(1u << 0)
#define PADS_QSPI_VOLTAGE_SELECT_VOLTAGE_SELECT_3V3		(0x0u << 0)
#define PADS_QSPI_VOLTAGE_SELECT_VOLTAGE_SELECT_1V8		(0x1u << 0)

	/* 0x04: Pad control register */
	uint32_t volatile GPIO_QSPI_SCLK;
	/* Output disable. */
#define PADS_QSPI_GPIO_QSPI_SCLK_OD				(1u << 7)
	/* Input enable */
#define PADS_QSPI_GPIO_QSPI_SCLK_IE				(1u << 6)
	/* Drive strength. */
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_Msk			(0x3u << 4)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_Pos			4u
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_2MA			(0x0u << 4)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_4MA			(0x1u << 4)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_8MA			(0x2u << 4)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_12MA			(0x3u << 4)
	/* Pull up enable */
#define PADS_QSPI_GPIO_QSPI_SCLK_PUE				(1u << 3)
	/* Pull down enable */
#define PADS_QSPI_GPIO_QSPI_SCLK_PDE				(1u << 2)
	/* Enable schmitt trigger */
#define PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT			(1u << 1)
	/* Slew rate control. */
#define PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST			(1u << 0)

	/* 0x08: Pad control register */
	uint32_t volatile GPIO_QSPI_SD0;
	/* Output disable. */
#define PADS_QSPI_GPIO_QSPI_SD0_OD				(1u << 7)
	/* Input enable */
#define PADS_QSPI_GPIO_QSPI_SD0_IE				(1u << 6)
	/* Drive strength. */
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_Msk			(0x3u << 4)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_Pos			4u
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_2MA			(0x0u << 4)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_4MA			(0x1u << 4)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_8MA			(0x2u << 4)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_12MA			(0x3u << 4)
	/* Pull up enable */
#define PADS_QSPI_GPIO_QSPI_SD0_PUE				(1u << 3)
	/* Pull down enable */
#define PADS_QSPI_GPIO_QSPI_SD0_PDE				(1u << 2)
	/* Enable schmitt trigger */
#define PADS_QSPI_GPIO_QSPI_SD0_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST			(1u << 0)

	/* 0x0C: Pad control register */
	uint32_t volatile GPIO_QSPI_SD1;
	/* Output disable. */
#define PADS_QSPI_GPIO_QSPI_SD1_OD				(1u << 7)
	/* Input enable */
#define PADS_QSPI_GPIO_QSPI_SD1_IE				(1u << 6)
	/* Drive strength. */
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_Msk			(0x3u << 4)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_Pos			4u
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_2MA			(0x0u << 4)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_4MA			(0x1u << 4)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_8MA			(0x2u << 4)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_12MA			(0x3u << 4)
	/* Pull up enable */
#define PADS_QSPI_GPIO_QSPI_SD1_PUE				(1u << 3)
	/* Pull down enable */
#define PADS_QSPI_GPIO_QSPI_SD1_PDE				(1u << 2)
	/* Enable schmitt trigger */
#define PADS_QSPI_GPIO_QSPI_SD1_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST			(1u << 0)

	/* 0x10: Pad control register */
	uint32_t volatile GPIO_QSPI_SD2;
	/* Output disable. */
#define PADS_QSPI_GPIO_QSPI_SD2_OD				(1u << 7)
	/* Input enable */
#define PADS_QSPI_GPIO_QSPI_SD2_IE				(1u << 6)
	/* Drive strength. */
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_Msk			(0x3u << 4)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_Pos			4u
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_2MA			(0x0u << 4)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_4MA			(0x1u << 4)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_8MA			(0x2u << 4)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_12MA			(0x3u << 4)
	/* Pull up enable */
#define PADS_QSPI_GPIO_QSPI_SD2_PUE				(1u << 3)
	/* Pull down enable */
#define PADS_QSPI_GPIO_QSPI_SD2_PDE				(1u << 2)
	/* Enable schmitt trigger */
#define PADS_QSPI_GPIO_QSPI_SD2_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST			(1u << 0)

	/* 0x14: Pad control register */
	uint32_t volatile GPIO_QSPI_SD3;
	/* Output disable. */
#define PADS_QSPI_GPIO_QSPI_SD3_OD				(1u << 7)
	/* Input enable */
#define PADS_QSPI_GPIO_QSPI_SD3_IE				(1u << 6)
	/* Drive strength. */
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_Msk			(0x3u << 4)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_Pos			4u
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_2MA			(0x0u << 4)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_4MA			(0x1u << 4)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_8MA			(0x2u << 4)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_12MA			(0x3u << 4)
	/* Pull up enable */
#define PADS_QSPI_GPIO_QSPI_SD3_PUE				(1u << 3)
	/* Pull down enable */
#define PADS_QSPI_GPIO_QSPI_SD3_PDE				(1u << 2)
	/* Enable schmitt trigger */
#define PADS_QSPI_GPIO_QSPI_SD3_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST			(1u << 0)

	/* 0x18: Pad control register */
	uint32_t volatile GPIO_QSPI_SS;
	/* Output disable. */
#define PADS_QSPI_GPIO_QSPI_SS_OD				(1u << 7)
	/* Input enable */
#define PADS_QSPI_GPIO_QSPI_SS_IE				(1u << 6)
	/* Drive strength. */
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_Msk			(0x3u << 4)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_Pos			4u
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_2MA			(0x0u << 4)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_4MA			(0x1u << 4)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_8MA			(0x2u << 4)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_12MA			(0x3u << 4)
	/* Pull up enable */
#define PADS_QSPI_GPIO_QSPI_SS_PUE				(1u << 3)
	/* Pull down enable */
#define PADS_QSPI_GPIO_QSPI_SS_PDE				(1u << 2)
	/* Enable schmitt trigger */
#define PADS_QSPI_GPIO_QSPI_SS_SCHMITT				(1u << 1)
	/* Slew rate control. */
#define PADS_QSPI_GPIO_QSPI_SS_SLEWFAST				(1u << 0)

};


#define XOSC ((struct mcu_xosc *)0x40024000)

struct mcu_xosc {

	/* 0x00: Crystal Oscillator Control */
	uint32_t volatile CTRL;
	/* On power-up this field is initialised to DISABLE and the chip runs from the ROSC. */
#define XOSC_CTRL_ENABLE_Msk					(0xFFFu << 12)
#define XOSC_CTRL_ENABLE_Pos					12u
#define XOSC_CTRL_ENABLE_DISABLE				(0xD1Eu << 12)
#define XOSC_CTRL_ENABLE_ENABLE					(0xFABu << 12)
	/* Frequency range. */
#define XOSC_CTRL_FREQ_RANGE_Msk				(0xFFFu << 0)
#define XOSC_CTRL_FREQ_RANGE_Pos				0u
#define XOSC_CTRL_FREQ_RANGE_1_15MHZ				(0xAA0u << 0)
#define XOSC_CTRL_FREQ_RANGE_RESERVED_1				(0xAA1u << 0)
#define XOSC_CTRL_FREQ_RANGE_RESERVED_2				(0xAA2u << 0)
#define XOSC_CTRL_FREQ_RANGE_RESERVED_3				(0xAA3u << 0)

	/* 0x04: Crystal Oscillator Status */
	uint32_t volatile STATUS;
	/* Oscillator is running and stable */
#define XOSC_STATUS_STABLE					(1u << 31)
	/* An invalid value has been written to CTRL_ENABLE or CTRL_FREQ_RANGE or DORMANT */
#define XOSC_STATUS_BADWRITE					(1u << 24)
	/* Oscillator is enabled but not necessarily running and stable, resets to 0 */
#define XOSC_STATUS_ENABLED					(1u << 12)
	/* The current frequency range setting, always reads 0 */
#define XOSC_STATUS_FREQ_RANGE_Msk				(0x3u << 0)
#define XOSC_STATUS_FREQ_RANGE_Pos				0u
#define XOSC_STATUS_FREQ_RANGE_1_15MHZ				(0x0u << 0)
#define XOSC_STATUS_FREQ_RANGE_RESERVED_1			(0x1u << 0)
#define XOSC_STATUS_FREQ_RANGE_RESERVED_2			(0x2u << 0)
#define XOSC_STATUS_FREQ_RANGE_RESERVED_3			(0x3u << 0)

	/* 0x08: Crystal Oscillator pause control */
	uint32_t volatile DORMANT;

	/* 0x0C: Controls the startup delay */
	uint32_t volatile STARTUP;
	/* Multiplies the startup_delay by 4. */
#define XOSC_STARTUP_X4						(1u << 20)
	/* in multiples of 256*xtal_period. */
#define XOSC_STARTUP_DELAY_Msk					(0x3FFFu << 0)
#define XOSC_STARTUP_DELAY_Pos					0u

	/* 0x10 */
	uint8_t RESERVED0[0x1Cu-0x10u];

	/* 0x1C: A down counter running at the xosc frequency which counts to zero and stops. */
	uint32_t volatile COUNT;
	/*  */
#define XOSC_COUNT_COUNT_Msk					(0xFFu << 0)
#define XOSC_COUNT_COUNT_Pos					0u

};


#define PLL_SYS ((struct mcu_pll *)0x40028000)
#define PLL_USB ((struct mcu_pll *)0x4002C000)

struct mcu_pll {

	/* 0x00: Control and Status */
	uint32_t volatile CS;
	/* PLL is locked */
#define PLL_SYS_CS_LOCK						(1u << 31)
	/* Passes the reference clock to the output instead of the divided VCO. */
#define PLL_SYS_CS_BYPASS					(1u << 8)
	/* Divides the PLL input reference clock. */
#define PLL_SYS_CS_REFDIV_Msk					(0x3Fu << 0)
#define PLL_SYS_CS_REFDIV_Pos					0u

	/* 0x04: Controls the PLL power modes. */
	uint32_t volatile PWR;
	/* PLL VCO powerdown */
#define PLL_SYS_PWR_VCOPD					(1u << 5)
	/* PLL post divider powerdown */
#define PLL_SYS_PWR_POSTDIVPD					(1u << 3)
	/* PLL DSM powerdown */
#define PLL_SYS_PWR_DSMPD					(1u << 2)
	/* PLL powerdown */
#define PLL_SYS_PWR_PD						(1u << 0)

	/* 0x08: Feedback divisor */
	uint32_t volatile FBDIV_INT;
	/* see ctrl reg description for constraints */
#define PLL_SYS_FBDIV_INT_FBDIV_INT_Msk				(0xFFFu << 0)
#define PLL_SYS_FBDIV_INT_FBDIV_INT_Pos				0u

	/* 0x0C: Controls the PLL post dividers for the primary output */
	uint32_t volatile PRIM;
	/* divide by 1-7 */
#define PLL_SYS_PRIM_POSTDIV1_Msk				(0x7u << 16)
#define PLL_SYS_PRIM_POSTDIV1_Pos				16u
	/* divide by 1-7 */
#define PLL_SYS_PRIM_POSTDIV2_Msk				(0x7u << 12)
#define PLL_SYS_PRIM_POSTDIV2_Pos				12u

};


#define BUSCTRL ((struct mcu_busctrl *)0x40030000)

struct mcu_busctrl {

	/* 0x00: Set the priority of each master for bus arbitration. */
	uint32_t volatile BUS_PRIORITY;
	/* 0 - low priority, 1 - high priority */
#define BUSCTRL_BUS_PRIORITY_DMA_W				(1u << 12)
	/* 0 - low priority, 1 - high priority */
#define BUSCTRL_BUS_PRIORITY_DMA_R				(1u << 8)
	/* 0 - low priority, 1 - high priority */
#define BUSCTRL_BUS_PRIORITY_PROC1				(1u << 4)
	/* 0 - low priority, 1 - high priority */
#define BUSCTRL_BUS_PRIORITY_PROC0				(1u << 0)

	/* 0x04: Bus priority acknowledge */
	uint32_t volatile BUS_PRIORITY_ACK;
	/* Goes to 1 once all arbiters have registered the new global priority levels. */
#define BUSCTRL_BUS_PRIORITY_ACK_BUS_PRIORITY_ACK		(1u << 0)

	/* 0x08: Bus fabric performance counter 0 */
	uint32_t volatile PERFCTR0;
	/* Busfabric saturating performance counter 0 */
#define BUSCTRL_PERFCTR0_PERFCTR0_Msk				(0xFFFFFFu << 0)
#define BUSCTRL_PERFCTR0_PERFCTR0_Pos				0u

	/* 0x0C: Bus fabric performance event select for PERFCTR0 */
	uint32_t volatile PERFSEL0;
	/* Select an event for PERFCTR0. */
#define BUSCTRL_PERFSEL0_PERFSEL0_Msk				(0x1Fu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_Pos				0u
#define BUSCTRL_PERFSEL0_PERFSEL0_APB_CONTESTED			(0x0u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_APB				(0x1u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_FASTPERI_CONTESTED		(0x2u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_FASTPERI			(0x3u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM5_CONTESTED		(0x4u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM5				(0x5u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM4_CONTESTED		(0x6u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM4				(0x7u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM3_CONTESTED		(0x8u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM3				(0x9u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM2_CONTESTED		(0xAu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM2				(0xBu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM1_CONTESTED		(0xCu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM1				(0xDu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM0_CONTESTED		(0xEu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_SRAM0				(0xFu << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_XIP_MAIN_CONTESTED		(0x10u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_XIP_MAIN			(0x11u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_ROM_CONTESTED			(0x12u << 0)
#define BUSCTRL_PERFSEL0_PERFSEL0_ROM				(0x13u << 0)

	/* 0x10: Bus fabric performance counter 1 */
	uint32_t volatile PERFCTR1;
	/* Busfabric saturating performance counter 1 */
#define BUSCTRL_PERFCTR1_PERFCTR1_Msk				(0xFFFFFFu << 0)
#define BUSCTRL_PERFCTR1_PERFCTR1_Pos				0u

	/* 0x14: Bus fabric performance event select for PERFCTR1 */
	uint32_t volatile PERFSEL1;
	/* Select an event for PERFCTR1. */
#define BUSCTRL_PERFSEL1_PERFSEL1_Msk				(0x1Fu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_Pos				0u
#define BUSCTRL_PERFSEL1_PERFSEL1_APB_CONTESTED			(0x0u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_APB				(0x1u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_FASTPERI_CONTESTED		(0x2u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_FASTPERI			(0x3u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM5_CONTESTED		(0x4u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM5				(0x5u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM4_CONTESTED		(0x6u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM4				(0x7u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM3_CONTESTED		(0x8u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM3				(0x9u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM2_CONTESTED		(0xAu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM2				(0xBu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM1_CONTESTED		(0xCu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM1				(0xDu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM0_CONTESTED		(0xEu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_SRAM0				(0xFu << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_XIP_MAIN_CONTESTED		(0x10u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_XIP_MAIN			(0x11u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_ROM_CONTESTED			(0x12u << 0)
#define BUSCTRL_PERFSEL1_PERFSEL1_ROM				(0x13u << 0)

	/* 0x18: Bus fabric performance counter 2 */
	uint32_t volatile PERFCTR2;
	/* Busfabric saturating performance counter 2 */
#define BUSCTRL_PERFCTR2_PERFCTR2_Msk				(0xFFFFFFu << 0)
#define BUSCTRL_PERFCTR2_PERFCTR2_Pos				0u

	/* 0x1C: Bus fabric performance event select for PERFCTR2 */
	uint32_t volatile PERFSEL2;
	/* Select an event for PERFCTR2. */
#define BUSCTRL_PERFSEL2_PERFSEL2_Msk				(0x1Fu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_Pos				0u
#define BUSCTRL_PERFSEL2_PERFSEL2_APB_CONTESTED			(0x0u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_APB				(0x1u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_FASTPERI_CONTESTED		(0x2u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_FASTPERI			(0x3u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM5_CONTESTED		(0x4u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM5				(0x5u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM4_CONTESTED		(0x6u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM4				(0x7u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM3_CONTESTED		(0x8u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM3				(0x9u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM2_CONTESTED		(0xAu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM2				(0xBu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM1_CONTESTED		(0xCu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM1				(0xDu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM0_CONTESTED		(0xEu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_SRAM0				(0xFu << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_XIP_MAIN_CONTESTED		(0x10u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_XIP_MAIN			(0x11u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_ROM_CONTESTED			(0x12u << 0)
#define BUSCTRL_PERFSEL2_PERFSEL2_ROM				(0x13u << 0)

	/* 0x20: Bus fabric performance counter 3 */
	uint32_t volatile PERFCTR3;
	/* Busfabric saturating performance counter 3 */
#define BUSCTRL_PERFCTR3_PERFCTR3_Msk				(0xFFFFFFu << 0)
#define BUSCTRL_PERFCTR3_PERFCTR3_Pos				0u

	/* 0x24: Bus fabric performance event select for PERFCTR3 */
	uint32_t volatile PERFSEL3;
	/* Select an event for PERFCTR3. */
#define BUSCTRL_PERFSEL3_PERFSEL3_Msk				(0x1Fu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_Pos				0u
#define BUSCTRL_PERFSEL3_PERFSEL3_APB_CONTESTED			(0x0u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_APB				(0x1u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_FASTPERI_CONTESTED		(0x2u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_FASTPERI			(0x3u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM5_CONTESTED		(0x4u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM5				(0x5u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM4_CONTESTED		(0x6u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM4				(0x7u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM3_CONTESTED		(0x8u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM3				(0x9u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM2_CONTESTED		(0xAu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM2				(0xBu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM1_CONTESTED		(0xCu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM1				(0xDu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM0_CONTESTED		(0xEu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_SRAM0				(0xFu << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_XIP_MAIN_CONTESTED		(0x10u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_XIP_MAIN			(0x11u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_ROM_CONTESTED			(0x12u << 0)
#define BUSCTRL_PERFSEL3_PERFSEL3_ROM				(0x13u << 0)

};


#define UART0 ((struct mcu_uart *)0x40034000)
#define UART1 ((struct mcu_uart *)0x40038000)

struct mcu_uart {

	/* 0x00: Data Register, UARTDR */
	uint32_t volatile UARTDR;
	/* Overrun error. */
#define UART0_UARTDR_OE						(1u << 11)
	/* Break error. This bit is set to 1 if a break condition was detected, indicating that the received data input was held LOW for longer than a full-word transmission time (defined as start, data, parity and stop bits). In FIFO mode, this error is associated with the character at the top of the FIFO. When a break occurs, only one 0 character is loaded into the FIFO. The next character is only enabled after the receive data input goes to a 1 (marking state), and the next valid start bit is received. */
#define UART0_UARTDR_BE						(1u << 10)
	/* Parity error. */
#define UART0_UARTDR_PE						(1u << 9)
	/* Framing error. When set to 1, it indicates that the received character did not have a valid stop bit (a valid stop bit is 1). */
#define UART0_UARTDR_FE						(1u << 8)
	/* Receive (read) data character. Transmit (write) data character. */
#define UART0_UARTDR_DATA_Msk					(0xFFu << 0)
#define UART0_UARTDR_DATA_Pos					0u

	/* 0x04: Receive Status Register/Error Clear Register, UARTRSR/UARTECR */
	uint32_t volatile UARTRSR;
	/* Overrun error. */
#define UART0_UARTRSR_OE					(1u << 3)
	/* Break error. This bit is set to 1 if a break condition was detected, indicating that the received data input was held LOW for longer than a full-word transmission time (defined as start, data, parity, and stop bits). This bit is cleared to 0 after a write to UARTECR. In FIFO mode, this error is associated with the character at the top of the FIFO. When a break occurs, only one 0 character is loaded into the FIFO. The next character is only enabled after the receive data input goes to a 1 (marking state) and the next valid start bit is received. */
#define UART0_UARTRSR_BE					(1u << 2)
	/* Parity error. */
#define UART0_UARTRSR_PE					(1u << 1)
	/* Framing error. When set to 1, it indicates that the received character did not have a valid stop bit (a valid stop bit is 1). */
#define UART0_UARTRSR_FE					(1u << 0)

	/* 0x08 */
	uint8_t RESERVED0[0x18u-0x08u];

	/* 0x18: Flag Register, UARTFR */
	uint32_t volatile UARTFR;
	/* Ring indicator. */
#define UART0_UARTFR_RI						(1u << 8)
	/* Transmit FIFO empty. */
#define UART0_UARTFR_TXFE					(1u << 7)
	/* Receive FIFO full. */
#define UART0_UARTFR_RXFF					(1u << 6)
	/* Transmit FIFO full. */
#define UART0_UARTFR_TXFF					(1u << 5)
	/* Receive FIFO empty. */
#define UART0_UARTFR_RXFE					(1u << 4)
	/* UART busy. */
#define UART0_UARTFR_BUSY					(1u << 3)
	/* Data carrier detect. */
#define UART0_UARTFR_DCD					(1u << 2)
	/* Data set ready. */
#define UART0_UARTFR_DSR					(1u << 1)
	/* Clear to send. */
#define UART0_UARTFR_CTS					(1u << 0)

	/* 0x1C */
	uint8_t RESERVED1[0x20u-0x1Cu];

	/* 0x20: IrDA Low-Power Counter Register, UARTILPR */
	uint32_t volatile UARTILPR;
	/* 8-bit low-power divisor value. */
#define UART0_UARTILPR_ILPDVSR_Msk				(0xFFu << 0)
#define UART0_UARTILPR_ILPDVSR_Pos				0u

	/* 0x24: Integer Baud Rate Register, UARTIBRD */
	uint32_t volatile UARTIBRD;
	/* The integer baud rate divisor. */
#define UART0_UARTIBRD_BAUD_DIVINT_Msk				(0xFFFFu << 0)
#define UART0_UARTIBRD_BAUD_DIVINT_Pos				0u

	/* 0x28: Fractional Baud Rate Register, UARTFBRD */
	uint32_t volatile UARTFBRD;
	/* The fractional baud rate divisor. */
#define UART0_UARTFBRD_BAUD_DIVFRAC_Msk				(0x3Fu << 0)
#define UART0_UARTFBRD_BAUD_DIVFRAC_Pos				0u

	/* 0x2C: Line Control Register, UARTLCR_H */
	uint32_t volatile UARTLCR_H;
	/* Stick parity select. */
#define UART0_UARTLCR_H_SPS					(1u << 7)
	/* Word length. */
#define UART0_UARTLCR_H_WLEN_Msk				(0x3u << 5)
#define UART0_UARTLCR_H_WLEN_Pos				5u
	/* Enable FIFOs: 0 = FIFOs are disabled (character mode) that is, the FIFOs become 1-byte-deep holding registers 1 = transmit and receive FIFO buffers are enabled (FIFO mode). */
#define UART0_UARTLCR_H_FEN					(1u << 4)
	/* Two stop bits select. */
#define UART0_UARTLCR_H_STP2					(1u << 3)
	/* Even parity select. */
#define UART0_UARTLCR_H_EPS					(1u << 2)
	/* Parity enable: 0 = parity is disabled and no parity bit added to the data frame 1 = parity checking and generation is enabled. */
#define UART0_UARTLCR_H_PEN					(1u << 1)
	/* Send break. */
#define UART0_UARTLCR_H_BRK					(1u << 0)

	/* 0x30: Control Register, UARTCR */
	uint32_t volatile UARTCR;
	/* CTS hardware flow control enable. */
#define UART0_UARTCR_CTSEN					(1u << 15)
	/* RTS hardware flow control enable. */
#define UART0_UARTCR_RTSEN					(1u << 14)
	/* This bit is the complement of the UART Out2 (nUARTOut2) modem status output. That is, when the bit is programmed to a 1, the output is 0. For DTE this can be used as Ring Indicator (RI). */
#define UART0_UARTCR_OUT2					(1u << 13)
	/* This bit is the complement of the UART Out1 (nUARTOut1) modem status output. That is, when the bit is programmed to a 1 the output is 0. For DTE this can be used as Data Carrier Detect (DCD). */
#define UART0_UARTCR_OUT1					(1u << 12)
	/* Request to send. */
#define UART0_UARTCR_RTS					(1u << 11)
	/* Data transmit ready. */
#define UART0_UARTCR_DTR					(1u << 10)
	/* Receive enable. */
#define UART0_UARTCR_RXE					(1u << 9)
	/* Transmit enable. */
#define UART0_UARTCR_TXE					(1u << 8)
	/* Loopback enable. */
#define UART0_UARTCR_LBE					(1u << 7)
	/* SIR low-power IrDA mode. */
#define UART0_UARTCR_SIRLP					(1u << 2)
	/* SIR enable: 0 = IrDA SIR ENDEC is disabled. nSIROUT remains LOW (no light pulse generated), and signal transitions on SIRIN have no effect. */
#define UART0_UARTCR_SIREN					(1u << 1)
	/* UART enable: 0 = UART is disabled. */
#define UART0_UARTCR_UARTEN					(1u << 0)

	/* 0x34: Interrupt FIFO Level Select Register, UARTIFLS */
	uint32_t volatile UARTIFLS;
	/* Receive interrupt FIFO level select. */
#define UART0_UARTIFLS_RXIFLSEL_Msk				(0x7u << 3)
#define UART0_UARTIFLS_RXIFLSEL_Pos				3u
	/* Transmit interrupt FIFO level select. */
#define UART0_UARTIFLS_TXIFLSEL_Msk				(0x7u << 0)
#define UART0_UARTIFLS_TXIFLSEL_Pos				0u

	/* 0x38: Interrupt Mask Set/Clear Register, UARTIMSC */
	uint32_t volatile UARTIMSC;
	/* Overrun error interrupt mask. */
#define UART0_UARTIMSC_OEIM					(1u << 10)
	/* Break error interrupt mask. */
#define UART0_UARTIMSC_BEIM					(1u << 9)
	/* Parity error interrupt mask. */
#define UART0_UARTIMSC_PEIM					(1u << 8)
	/* Framing error interrupt mask. */
#define UART0_UARTIMSC_FEIM					(1u << 7)
	/* Receive timeout interrupt mask. */
#define UART0_UARTIMSC_RTIM					(1u << 6)
	/* Transmit interrupt mask. */
#define UART0_UARTIMSC_TXIM					(1u << 5)
	/* Receive interrupt mask. */
#define UART0_UARTIMSC_RXIM					(1u << 4)
	/* nUARTDSR modem interrupt mask. */
#define UART0_UARTIMSC_DSRMIM					(1u << 3)
	/* nUARTDCD modem interrupt mask. */
#define UART0_UARTIMSC_DCDMIM					(1u << 2)
	/* nUARTCTS modem interrupt mask. */
#define UART0_UARTIMSC_CTSMIM					(1u << 1)
	/* nUARTRI modem interrupt mask. */
#define UART0_UARTIMSC_RIMIM					(1u << 0)

	/* 0x3C: Raw Interrupt Status Register, UARTRIS */
	uint32_t volatile UARTRIS;
	/* Overrun error interrupt status. */
#define UART0_UARTRIS_OERIS					(1u << 10)
	/* Break error interrupt status. */
#define UART0_UARTRIS_BERIS					(1u << 9)
	/* Parity error interrupt status. */
#define UART0_UARTRIS_PERIS					(1u << 8)
	/* Framing error interrupt status. */
#define UART0_UARTRIS_FERIS					(1u << 7)
	/* Receive timeout interrupt status. */
#define UART0_UARTRIS_RTRIS					(1u << 6)
	/* Transmit interrupt status. */
#define UART0_UARTRIS_TXRIS					(1u << 5)
	/* Receive interrupt status. */
#define UART0_UARTRIS_RXRIS					(1u << 4)
	/* nUARTDSR modem interrupt status. */
#define UART0_UARTRIS_DSRRMIS					(1u << 3)
	/* nUARTDCD modem interrupt status. */
#define UART0_UARTRIS_DCDRMIS					(1u << 2)
	/* nUARTCTS modem interrupt status. */
#define UART0_UARTRIS_CTSRMIS					(1u << 1)
	/* nUARTRI modem interrupt status. */
#define UART0_UARTRIS_RIRMIS					(1u << 0)

	/* 0x40: Masked Interrupt Status Register, UARTMIS */
	uint32_t volatile UARTMIS;
	/* Overrun error masked interrupt status. */
#define UART0_UARTMIS_OEMIS					(1u << 10)
	/* Break error masked interrupt status. */
#define UART0_UARTMIS_BEMIS					(1u << 9)
	/* Parity error masked interrupt status. */
#define UART0_UARTMIS_PEMIS					(1u << 8)
	/* Framing error masked interrupt status. */
#define UART0_UARTMIS_FEMIS					(1u << 7)
	/* Receive timeout masked interrupt status. */
#define UART0_UARTMIS_RTMIS					(1u << 6)
	/* Transmit masked interrupt status. */
#define UART0_UARTMIS_TXMIS					(1u << 5)
	/* Receive masked interrupt status. */
#define UART0_UARTMIS_RXMIS					(1u << 4)
	/* nUARTDSR modem masked interrupt status. */
#define UART0_UARTMIS_DSRMMIS					(1u << 3)
	/* nUARTDCD modem masked interrupt status. */
#define UART0_UARTMIS_DCDMMIS					(1u << 2)
	/* nUARTCTS modem masked interrupt status. */
#define UART0_UARTMIS_CTSMMIS					(1u << 1)
	/* nUARTRI modem masked interrupt status. */
#define UART0_UARTMIS_RIMMIS					(1u << 0)

	/* 0x44: Interrupt Clear Register, UARTICR */
	uint32_t volatile UARTICR;
	/* Overrun error interrupt clear. */
#define UART0_UARTICR_OEIC					(1u << 10)
	/* Break error interrupt clear. */
#define UART0_UARTICR_BEIC					(1u << 9)
	/* Parity error interrupt clear. */
#define UART0_UARTICR_PEIC					(1u << 8)
	/* Framing error interrupt clear. */
#define UART0_UARTICR_FEIC					(1u << 7)
	/* Receive timeout interrupt clear. */
#define UART0_UARTICR_RTIC					(1u << 6)
	/* Transmit interrupt clear. */
#define UART0_UARTICR_TXIC					(1u << 5)
	/* Receive interrupt clear. */
#define UART0_UARTICR_RXIC					(1u << 4)
	/* nUARTDSR modem interrupt clear. */
#define UART0_UARTICR_DSRMIC					(1u << 3)
	/* nUARTDCD modem interrupt clear. */
#define UART0_UARTICR_DCDMIC					(1u << 2)
	/* nUARTCTS modem interrupt clear. */
#define UART0_UARTICR_CTSMIC					(1u << 1)
	/* nUARTRI modem interrupt clear. */
#define UART0_UARTICR_RIMIC					(1u << 0)

	/* 0x48: DMA Control Register, UARTDMACR */
	uint32_t volatile UARTDMACR;
	/* DMA on error. */
#define UART0_UARTDMACR_DMAONERR				(1u << 2)
	/* Transmit DMA enable. */
#define UART0_UARTDMACR_TXDMAE					(1u << 1)
	/* Receive DMA enable. */
#define UART0_UARTDMACR_RXDMAE					(1u << 0)

	/* 0x4C */
	uint8_t RESERVED2[0xFE0u-0x4Cu];

	/* 0xFE0: UARTPeriphID0 Register */
	uint32_t volatile UARTPERIPHID0;
	/* These bits read back as 0x11 */
#define UART0_UARTPERIPHID0_PARTNUMBER0_Msk			(0xFFu << 0)
#define UART0_UARTPERIPHID0_PARTNUMBER0_Pos			0u

	/* 0xFE4: UARTPeriphID1 Register */
	uint32_t volatile UARTPERIPHID1;
	/* These bits read back as 0x1 */
#define UART0_UARTPERIPHID1_DESIGNER0_Msk			(0xFu << 4)
#define UART0_UARTPERIPHID1_DESIGNER0_Pos			4u
	/* These bits read back as 0x0 */
#define UART0_UARTPERIPHID1_PARTNUMBER1_Msk			(0xFu << 0)
#define UART0_UARTPERIPHID1_PARTNUMBER1_Pos			0u

	/* 0xFE8: UARTPeriphID2 Register */
	uint32_t volatile UARTPERIPHID2;
	/* This field depends on the revision of the UART: r1p0 0x0 r1p1 0x1 r1p3 0x2 r1p4 0x2 r1p5 0x3 */
#define UART0_UARTPERIPHID2_REVISION_Msk			(0xFu << 4)
#define UART0_UARTPERIPHID2_REVISION_Pos			4u
	/* These bits read back as 0x4 */
#define UART0_UARTPERIPHID2_DESIGNER1_Msk			(0xFu << 0)
#define UART0_UARTPERIPHID2_DESIGNER1_Pos			0u

	/* 0xFEC: UARTPeriphID3 Register */
	uint32_t volatile UARTPERIPHID3;
	/* These bits read back as 0x00 */
#define UART0_UARTPERIPHID3_CONFIGURATION_Msk			(0xFFu << 0)
#define UART0_UARTPERIPHID3_CONFIGURATION_Pos			0u

	/* 0xFF0: UARTPCellID0 Register */
	uint32_t volatile UARTPCELLID0;
	/* These bits read back as 0x0D */
#define UART0_UARTPCELLID0_UARTPCELLID0_Msk			(0xFFu << 0)
#define UART0_UARTPCELLID0_UARTPCELLID0_Pos			0u

	/* 0xFF4: UARTPCellID1 Register */
	uint32_t volatile UARTPCELLID1;
	/* These bits read back as 0xF0 */
#define UART0_UARTPCELLID1_UARTPCELLID1_Msk			(0xFFu << 0)
#define UART0_UARTPCELLID1_UARTPCELLID1_Pos			0u

	/* 0xFF8: UARTPCellID2 Register */
	uint32_t volatile UARTPCELLID2;
	/* These bits read back as 0x05 */
#define UART0_UARTPCELLID2_UARTPCELLID2_Msk			(0xFFu << 0)
#define UART0_UARTPCELLID2_UARTPCELLID2_Pos			0u

	/* 0xFFC: UARTPCellID3 Register */
	uint32_t volatile UARTPCELLID3;
	/* These bits read back as 0xB1 */
#define UART0_UARTPCELLID3_UARTPCELLID3_Msk			(0xFFu << 0)
#define UART0_UARTPCELLID3_UARTPCELLID3_Pos			0u

};


#define SPI0 ((struct mcu_spi *)0x4003C000)
#define SPI1 ((struct mcu_spi *)0x40040000)

struct mcu_spi {

	/* 0x00: Control register 0, SSPCR0 on page 3-4 */
	uint32_t volatile SSPCR0;
	/* Serial clock rate. The value SCR is used to generate the transmit and receive bit rate of the PrimeCell SSP. The bit rate is: F SSPCLK CPSDVSR x (1+SCR) where CPSDVSR is an even value from 2-254, programmed through the SSPCPSR register and SCR is a value from 0-255. */
#define SPI_SSPCR0_SCR_Msk					(0xFFu << 8)
#define SPI_SSPCR0_SCR_Pos					8u
	/* SSPCLKOUT phase, applicable to Motorola SPI frame format only. */
#define SPI_SSPCR0_SPH						(1u << 7)
	/* SSPCLKOUT polarity, applicable to Motorola SPI frame format only. */
#define SPI_SSPCR0_SPO						(1u << 6)
	/* Frame format: 00 Motorola SPI frame format. */
#define SPI_SSPCR0_FRF_Msk					(0x3u << 4)
#define SPI_SSPCR0_FRF_Pos					4u
#define SPI_SSPCR0_FRF_MOTOROLA					(0x0u << 4)
#define SPI_SSPCR0_FRF_TI_SYNC_SERIAL				(0x1u << 4)
#define SPI_SSPCR0_FRF_NATIONAL_MICROWIRE			(0x2u << 4)
	/* Data Size Select: 0000 Reserved, undefined operation. */
#define SPI_SSPCR0_DSS_Msk					(0xFu << 0)
#define SPI_SSPCR0_DSS_Pos					0u

	/* 0x04: Control register 1, SSPCR1 on page 3-5 */
	uint32_t volatile SSPCR1;
	/* Slave-mode output disable. */
#define SPI_SSPCR1_SOD						(1u << 3)
	/* Master or slave mode select. */
#define SPI_SSPCR1_MS						(1u << 2)
	/* Synchronous serial port enable: 0 SSP operation disabled. */
#define SPI_SSPCR1_SSE						(1u << 1)
	/* Loop back mode: 0 Normal serial port operation enabled. */
#define SPI_SSPCR1_LBM						(1u << 0)

	/* 0x08: Data register, SSPDR on page 3-6 */
	uint32_t volatile SSPDR;
	/* Transmit/Receive FIFO: Read Receive FIFO. */
#define SPI_SSPDR_DATA_Msk					(0xFFFFu << 0)
#define SPI_SSPDR_DATA_Pos					0u

	/* 0x0C: Status register, SSPSR on page 3-7 */
	uint32_t volatile SSPSR;
	/* PrimeCell SSP busy flag, RO: 0 SSP is idle. */
#define SPI_SSPSR_BSY						(1u << 4)
	/* Receive FIFO full, RO: 0 Receive FIFO is not full. */
#define SPI_SSPSR_RFF						(1u << 3)
	/* Receive FIFO not empty, RO: 0 Receive FIFO is empty. */
#define SPI_SSPSR_RNE						(1u << 2)
	/* Transmit FIFO not full, RO: 0 Transmit FIFO is full. */
#define SPI_SSPSR_TNF						(1u << 1)
	/* Transmit FIFO empty, RO: 0 Transmit FIFO is not empty. */
#define SPI_SSPSR_TFE						(1u << 0)

	/* 0x10: Clock prescale register, SSPCPSR on page 3-8 */
	uint32_t volatile SSPCPSR;
	/* Clock prescale divisor. */
#define SPI_SSPCPSR_CPSDVSR_Msk				(0xFFu << 0)
#define SPI_SSPCPSR_CPSDVSR_Pos				0u

	/* 0x14: Interrupt mask set or clear register, SSPIMSC on page 3-9 */
	uint32_t volatile SSPIMSC;
	/* Transmit FIFO interrupt mask: 0 Transmit FIFO half empty or less condition interrupt is masked. */
#define SPI_SSPIMSC_TXIM					(1u << 3)
	/* Receive FIFO interrupt mask: 0 Receive FIFO half full or less condition interrupt is masked. */
#define SPI_SSPIMSC_RXIM					(1u << 2)
	/* Receive timeout interrupt mask: 0 Receive FIFO not empty and no read prior to timeout period interrupt is masked. */
#define SPI_SSPIMSC_RTIM					(1u << 1)
	/* Receive overrun interrupt mask: 0 Receive FIFO written to while full condition interrupt is masked. */
#define SPI_SSPIMSC_RORIM					(1u << 0)

	/* 0x18: Raw interrupt status register, SSPRIS on page 3-10 */
	uint32_t volatile SSPRIS;
	/* Gives the raw interrupt state, prior to masking, of the SSPTXINTR interrupt */
#define SPI_SSPRIS_TXRIS					(1u << 3)
	/* Gives the raw interrupt state, prior to masking, of the SSPRXINTR interrupt */
#define SPI_SSPRIS_RXRIS					(1u << 2)
	/* Gives the raw interrupt state, prior to masking, of the SSPRTINTR interrupt */
#define SPI_SSPRIS_RTRIS					(1u << 1)
	/* Gives the raw interrupt state, prior to masking, of the SSPRORINTR interrupt */
#define SPI_SSPRIS_RORRIS					(1u << 0)

	/* 0x1C: Masked interrupt status register, SSPMIS on page 3-11 */
	uint32_t volatile SSPMIS;
	/* Gives the transmit FIFO masked interrupt state, after masking, of the SSPTXINTR interrupt */
#define SPI_SSPMIS_TXMIS					(1u << 3)
	/* Gives the receive FIFO masked interrupt state, after masking, of the SSPRXINTR interrupt */
#define SPI_SSPMIS_RXMIS					(1u << 2)
	/* Gives the receive timeout masked interrupt state, after masking, of the SSPRTINTR interrupt */
#define SPI_SSPMIS_RTMIS					(1u << 1)
	/* Gives the receive over run masked interrupt status, after masking, of the SSPRORINTR interrupt */
#define SPI_SSPMIS_RORMIS					(1u << 0)

	/* 0x20: Interrupt clear register, SSPICR on page 3-11 */
	uint32_t volatile SSPICR;
	/* Clears the SSPRTINTR interrupt */
#define SPI_SSPICR_RTIC					(1u << 1)
	/* Clears the SSPRORINTR interrupt */
#define SPI_SSPICR_RORIC					(1u << 0)

	/* 0x24: DMA control register, SSPDMACR on page 3-12 */
	uint32_t volatile SSPDMACR;
	/* Transmit DMA Enable. */
#define SPI_SSPDMACR_TXDMAE					(1u << 1)
	/* Receive DMA Enable. */
#define SPI_SSPDMACR_RXDMAE					(1u << 0)

	/* 0x28 */
	uint8_t RESERVED0[0xFE0u-0x28u];

	/* 0xFE0: Peripheral identification registers, SSPPeriphID0-3 on page 3-13 */
	uint32_t volatile SSPPERIPHID0;
	/* These bits read back as 0x22 */
#define SPI_SSPPERIPHID0_PARTNUMBER0_Msk			(0xFFu << 0)
#define SPI_SSPPERIPHID0_PARTNUMBER0_Pos			0u

	/* 0xFE4: Peripheral identification registers, SSPPeriphID0-3 on page 3-13 */
	uint32_t volatile SSPPERIPHID1;
	/* These bits read back as 0x1 */
#define SPI_SSPPERIPHID1_DESIGNER0_Msk				(0xFu << 4)
#define SPI_SSPPERIPHID1_DESIGNER0_Pos				4u
	/* These bits read back as 0x0 */
#define SPI_SSPPERIPHID1_PARTNUMBER1_Msk			(0xFu << 0)
#define SPI_SSPPERIPHID1_PARTNUMBER1_Pos			0u

	/* 0xFE8: Peripheral identification registers, SSPPeriphID0-3 on page 3-13 */
	uint32_t volatile SSPPERIPHID2;
	/* These bits return the peripheral revision */
#define SPI_SSPPERIPHID2_REVISION_Msk				(0xFu << 4)
#define SPI_SSPPERIPHID2_REVISION_Pos				4u
	/* These bits read back as 0x4 */
#define SPI_SSPPERIPHID2_DESIGNER1_Msk				(0xFu << 0)
#define SPI_SSPPERIPHID2_DESIGNER1_Pos				0u

	/* 0xFEC: Peripheral identification registers, SSPPeriphID0-3 on page 3-13 */
	uint32_t volatile SSPPERIPHID3;
	/* These bits read back as 0x00 */
#define SPI_SSPPERIPHID3_CONFIGURATION_Msk			(0xFFu << 0)
#define SPI_SSPPERIPHID3_CONFIGURATION_Pos			0u

	/* 0xFF0: PrimeCell identification registers, SSPPCellID0-3 on page 3-16 */
	uint32_t volatile SSPPCELLID0;
	/* These bits read back as 0x0D */
#define SPI_SSPPCELLID0_SSPPCELLID0_Msk			(0xFFu << 0)
#define SPI_SSPPCELLID0_SSPPCELLID0_Pos			0u

	/* 0xFF4: PrimeCell identification registers, SSPPCellID0-3 on page 3-16 */
	uint32_t volatile SSPPCELLID1;
	/* These bits read back as 0xF0 */
#define SPI_SSPPCELLID1_SSPPCELLID1_Msk			(0xFFu << 0)
#define SPI_SSPPCELLID1_SSPPCELLID1_Pos			0u

	/* 0xFF8: PrimeCell identification registers, SSPPCellID0-3 on page 3-16 */
	uint32_t volatile SSPPCELLID2;
	/* These bits read back as 0x05 */
#define SPI_SSPPCELLID2_SSPPCELLID2_Msk			(0xFFu << 0)
#define SPI_SSPPCELLID2_SSPPCELLID2_Pos			0u

	/* 0xFFC: PrimeCell identification registers, SSPPCellID0-3 on page 3-16 */
	uint32_t volatile SSPPCELLID3;
	/* These bits read back as 0xB1 */
#define SPI_SSPPCELLID3_SSPPCELLID3_Msk			(0xFFu << 0)
#define SPI_SSPPCELLID3_SSPPCELLID3_Pos			0u

};


#define I2C0 ((struct mcu_i2c *)0x40044000)
#define I2C1 ((struct mcu_i2c *)0x40048000)

struct mcu_i2c {

	/* 0x00: I2C Control Register. */
	uint32_t volatile IC_CON;
	/* Master issues the STOP_DET interrupt irrespective of whether master is active or not */
#define I2C0_IC_CON_STOP_DET_IF_MASTER_ACTIVE			(1u << 10)
	/* This bit controls whether DW_apb_i2c should hold the bus when the Rx FIFO is physically full to its RX_BUFFER_DEPTH, as described in the IC_RX_FULL_HLD_BUS_EN parameter. */
#define I2C0_IC_CON_RX_FIFO_FULL_HLD_CTRL			(1u << 9)
#define I2C0_IC_CON_RX_FIFO_FULL_HLD_CTRL_DISABLED		(0x0u << 9)
#define I2C0_IC_CON_RX_FIFO_FULL_HLD_CTRL_ENABLED		(0x1u << 9)
	/* This bit controls the generation of the TX_EMPTY interrupt, as described in the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CON_TX_EMPTY_CTRL				(1u << 8)
#define I2C0_IC_CON_TX_EMPTY_CTRL_DISABLED			(0x0u << 8)
#define I2C0_IC_CON_TX_EMPTY_CTRL_ENABLED			(0x1u << 8)
	/* In slave mode: - 1'b1:  issues the STOP_DET interrupt only when it is addressed. */
#define I2C0_IC_CON_STOP_DET_IFADDRESSED			(1u << 7)
#define I2C0_IC_CON_STOP_DET_IFADDRESSED_DISABLED		(0x0u << 7)
#define I2C0_IC_CON_STOP_DET_IFADDRESSED_ENABLED		(0x1u << 7)
	/* This bit controls whether I2C has its slave disabled, which means once the presetn signal is applied, then this bit is set and the slave is disabled. */
#define I2C0_IC_CON_IC_SLAVE_DISABLE				(1u << 6)
#define I2C0_IC_CON_IC_SLAVE_DISABLE_SLAVE_ENABLED		(0x0u << 6)
#define I2C0_IC_CON_IC_SLAVE_DISABLE_SLAVE_DISABLED		(0x1u << 6)
	/* Determines whether RESTART conditions may be sent when acting as a master. Some older slaves do not support handling RESTART conditions; however, RESTART conditions are used in several DW_apb_i2c operations. When RESTART is disabled, the master is prohibited from performing the following functions: - Sending a START BYTE - Performing any high-speed mode operation - High-speed mode operation - Performing direction changes in combined format mode - Performing a read operation with a 10-bit address By replacing RESTART condition followed by a STOP and a subsequent START condition, split operations are broken down into multiple DW_apb_i2c transfers. If the above operations are performed, it will result in setting bit 6 (TX_ABRT) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CON_IC_RESTART_EN				(1u << 5)
#define I2C0_IC_CON_IC_RESTART_EN_DISABLED			(0x0u << 5)
#define I2C0_IC_CON_IC_RESTART_EN_ENABLED			(0x1u << 5)
	/* Controls whether the DW_apb_i2c starts its transfers in 7- or 10-bit addressing mode when acting as a master. */
#define I2C0_IC_CON_IC_10BITADDR_MASTER				(1u << 4)
#define I2C0_IC_CON_IC_10BITADDR_MASTER_ADDR_7BITS		(0x0u << 4)
#define I2C0_IC_CON_IC_10BITADDR_MASTER_ADDR_10BITS		(0x1u << 4)
	/* When acting as a slave, this bit controls whether the DW_apb_i2c responds to 7- or 10-bit addresses. */
#define I2C0_IC_CON_IC_10BITADDR_SLAVE				(1u << 3)
#define I2C0_IC_CON_IC_10BITADDR_SLAVE_ADDR_7BITS		(0x0u << 3)
#define I2C0_IC_CON_IC_10BITADDR_SLAVE_ADDR_10BITS		(0x1u << 3)
	/* These bits control at which speed the DW_apb_i2c operates; its setting is relevant only if one is operating the DW_apb_i2c in master mode. */
#define I2C0_IC_CON_SPEED_Msk					(0x3u << 1)
#define I2C0_IC_CON_SPEED_Pos					1u
#define I2C0_IC_CON_SPEED_STANDARD				(0x1u << 1)
#define I2C0_IC_CON_SPEED_FAST					(0x2u << 1)
#define I2C0_IC_CON_SPEED_HIGH					(0x3u << 1)
	/* This bit controls whether the DW_apb_i2c master is enabled. */
#define I2C0_IC_CON_MASTER_MODE					(1u << 0)
#define I2C0_IC_CON_MASTER_MODE_DISABLED			(0x0u << 0)
#define I2C0_IC_CON_MASTER_MODE_ENABLED				(0x1u << 0)

	/* 0x04: I2C Target Address Register */
	uint32_t volatile IC_TAR;
	/* This bit indicates whether software performs a Device-ID or General Call or START BYTE command. */
#define I2C0_IC_TAR_SPECIAL					(1u << 11)
#define I2C0_IC_TAR_SPECIAL_DISABLED				(0x0u << 11)
#define I2C0_IC_TAR_SPECIAL_ENABLED				(0x1u << 11)
	/* If bit 11 (SPECIAL) is set to 1 and bit 13(Device-ID) is set to 0, then this bit indicates whether a General Call or START byte command is to be performed by the DW_apb_i2c. - 0: General Call Address - after issuing a General Call, only writes may be performed. Attempting to issue a read command results in setting bit 6 (TX_ABRT) of the IC_RAW_INTR_STAT register. The DW_apb_i2c remains in General Call mode until the SPECIAL bit value (bit 11) is cleared. */
#define I2C0_IC_TAR_GC_OR_START					(1u << 10)
#define I2C0_IC_TAR_GC_OR_START_GENERAL_CALL			(0x0u << 10)
#define I2C0_IC_TAR_GC_OR_START_START_BYTE			(0x1u << 10)
	/* This is the target address for any master transaction. */
#define I2C0_IC_TAR_IC_TAR_Msk					(0x3FFu << 0)
#define I2C0_IC_TAR_IC_TAR_Pos					0u

	/* 0x08: I2C Slave Address Register */
	uint32_t volatile IC_SAR;
	/* The IC_SAR holds the slave address when the I2C is operating as a slave. */
#define I2C0_IC_SAR_IC_SAR_Msk					(0x3FFu << 0)
#define I2C0_IC_SAR_IC_SAR_Pos					0u

	/* 0x0C */
	uint8_t RESERVED0[0x10u-0x0Cu];

	/* 0x10: I2C Rx/Tx Data Buffer and Command Register; this is the register the CPU writes to when filling the TX FIFO and the CPU reads from when retrieving bytes from RX FIFO. */
	uint32_t volatile IC_DATA_CMD;
	/* Indicates the first data byte received after the address phase for receive transfer in Master receiver or Slave receiver mode. */
#define I2C0_IC_DATA_CMD_FIRST_DATA_BYTE			(1u << 11)
#define I2C0_IC_DATA_CMD_FIRST_DATA_BYTE_INACTIVE		(0x0u << 11)
#define I2C0_IC_DATA_CMD_FIRST_DATA_BYTE_ACTIVE			(0x1u << 11)
	/* This bit controls whether a RESTART is issued before the byte is sent or received. */
#define I2C0_IC_DATA_CMD_RESTART				(1u << 10)
#define I2C0_IC_DATA_CMD_RESTART_DISABLE			(0x0u << 10)
#define I2C0_IC_DATA_CMD_RESTART_ENABLE				(0x1u << 10)
	/* This bit controls whether a STOP is issued after the byte is sent or received. */
#define I2C0_IC_DATA_CMD_STOP					(1u << 9)
#define I2C0_IC_DATA_CMD_STOP_DISABLE				(0x0u << 9)
#define I2C0_IC_DATA_CMD_STOP_ENABLE				(0x1u << 9)
	/* This bit controls whether a read or a write is performed. */
#define I2C0_IC_DATA_CMD_CMD					(1u << 8)
#define I2C0_IC_DATA_CMD_CMD_WRITE				(0x0u << 8)
#define I2C0_IC_DATA_CMD_CMD_READ				(0x1u << 8)
	/* This register contains the data to be transmitted or received on the I2C bus. If you are writing to this register and want to perform a read, bits 7:0 (DAT) are ignored by the DW_apb_i2c. */
#define I2C0_IC_DATA_CMD_DAT_Msk				(0xFFu << 0)
#define I2C0_IC_DATA_CMD_DAT_Pos				0u

	/* 0x14: Standard Speed I2C Clock SCL High Count Register */
	uint32_t volatile IC_SS_SCL_HCNT;
	/* This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. */
#define I2C0_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Msk			(0xFFFFu << 0)
#define I2C0_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Pos			0u

	/* 0x18: Standard Speed I2C Clock SCL Low Count Register */
	uint32_t volatile IC_SS_SCL_LCNT;
	/* This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. */
#define I2C0_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Msk			(0xFFFFu << 0)
#define I2C0_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Pos			0u

	/* 0x1C: Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register */
	uint32_t volatile IC_FS_SCL_HCNT;
	/* This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. */
#define I2C0_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Msk			(0xFFFFu << 0)
#define I2C0_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Pos			0u

	/* 0x20: Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register */
	uint32_t volatile IC_FS_SCL_LCNT;
	/* This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. */
#define I2C0_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Msk			(0xFFFFu << 0)
#define I2C0_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Pos			0u

	/* 0x24 */
	uint8_t RESERVED1[0x2Cu-0x24u];

	/* 0x2C: I2C Interrupt Status Register */
	uint32_t volatile IC_INTR_STAT;
	/* See IC_RAW_INTR_STAT for a detailed description of R_RESTART_DET bit. */
#define I2C0_IC_INTR_STAT_R_RESTART_DET				(1u << 12)
#define I2C0_IC_INTR_STAT_R_RESTART_DET_INACTIVE		(0x0u << 12)
#define I2C0_IC_INTR_STAT_R_RESTART_DET_ACTIVE			(0x1u << 12)
	/* See IC_RAW_INTR_STAT for a detailed description of R_GEN_CALL bit. */
#define I2C0_IC_INTR_STAT_R_GEN_CALL				(1u << 11)
#define I2C0_IC_INTR_STAT_R_GEN_CALL_INACTIVE			(0x0u << 11)
#define I2C0_IC_INTR_STAT_R_GEN_CALL_ACTIVE			(0x1u << 11)
	/* See IC_RAW_INTR_STAT for a detailed description of R_START_DET bit. */
#define I2C0_IC_INTR_STAT_R_START_DET				(1u << 10)
#define I2C0_IC_INTR_STAT_R_START_DET_INACTIVE			(0x0u << 10)
#define I2C0_IC_INTR_STAT_R_START_DET_ACTIVE			(0x1u << 10)
	/* See IC_RAW_INTR_STAT for a detailed description of R_STOP_DET bit. */
#define I2C0_IC_INTR_STAT_R_STOP_DET				(1u << 9)
#define I2C0_IC_INTR_STAT_R_STOP_DET_INACTIVE			(0x0u << 9)
#define I2C0_IC_INTR_STAT_R_STOP_DET_ACTIVE			(0x1u << 9)
	/* See IC_RAW_INTR_STAT for a detailed description of R_ACTIVITY bit. */
#define I2C0_IC_INTR_STAT_R_ACTIVITY				(1u << 8)
#define I2C0_IC_INTR_STAT_R_ACTIVITY_INACTIVE			(0x0u << 8)
#define I2C0_IC_INTR_STAT_R_ACTIVITY_ACTIVE			(0x1u << 8)
	/* See IC_RAW_INTR_STAT for a detailed description of R_RX_DONE bit. */
#define I2C0_IC_INTR_STAT_R_RX_DONE				(1u << 7)
#define I2C0_IC_INTR_STAT_R_RX_DONE_INACTIVE			(0x0u << 7)
#define I2C0_IC_INTR_STAT_R_RX_DONE_ACTIVE			(0x1u << 7)
	/* See IC_RAW_INTR_STAT for a detailed description of R_TX_ABRT bit. */
#define I2C0_IC_INTR_STAT_R_TX_ABRT				(1u << 6)
#define I2C0_IC_INTR_STAT_R_TX_ABRT_INACTIVE			(0x0u << 6)
#define I2C0_IC_INTR_STAT_R_TX_ABRT_ACTIVE			(0x1u << 6)
	/* See IC_RAW_INTR_STAT for a detailed description of R_RD_REQ bit. */
#define I2C0_IC_INTR_STAT_R_RD_REQ				(1u << 5)
#define I2C0_IC_INTR_STAT_R_RD_REQ_INACTIVE			(0x0u << 5)
#define I2C0_IC_INTR_STAT_R_RD_REQ_ACTIVE			(0x1u << 5)
	/* See IC_RAW_INTR_STAT for a detailed description of R_TX_EMPTY bit. */
#define I2C0_IC_INTR_STAT_R_TX_EMPTY				(1u << 4)
#define I2C0_IC_INTR_STAT_R_TX_EMPTY_INACTIVE			(0x0u << 4)
#define I2C0_IC_INTR_STAT_R_TX_EMPTY_ACTIVE			(0x1u << 4)
	/* See IC_RAW_INTR_STAT for a detailed description of R_TX_OVER bit. */
#define I2C0_IC_INTR_STAT_R_TX_OVER				(1u << 3)
#define I2C0_IC_INTR_STAT_R_TX_OVER_INACTIVE			(0x0u << 3)
#define I2C0_IC_INTR_STAT_R_TX_OVER_ACTIVE			(0x1u << 3)
	/* See IC_RAW_INTR_STAT for a detailed description of R_RX_FULL bit. */
#define I2C0_IC_INTR_STAT_R_RX_FULL				(1u << 2)
#define I2C0_IC_INTR_STAT_R_RX_FULL_INACTIVE			(0x0u << 2)
#define I2C0_IC_INTR_STAT_R_RX_FULL_ACTIVE			(0x1u << 2)
	/* See IC_RAW_INTR_STAT for a detailed description of R_RX_OVER bit. */
#define I2C0_IC_INTR_STAT_R_RX_OVER				(1u << 1)
#define I2C0_IC_INTR_STAT_R_RX_OVER_INACTIVE			(0x0u << 1)
#define I2C0_IC_INTR_STAT_R_RX_OVER_ACTIVE			(0x1u << 1)
	/* See IC_RAW_INTR_STAT for a detailed description of R_RX_UNDER bit. */
#define I2C0_IC_INTR_STAT_R_RX_UNDER				(1u << 0)
#define I2C0_IC_INTR_STAT_R_RX_UNDER_INACTIVE			(0x0u << 0)
#define I2C0_IC_INTR_STAT_R_RX_UNDER_ACTIVE			(0x1u << 0)

	/* 0x30: I2C Interrupt Mask Register. */
	uint32_t volatile IC_INTR_MASK;
	/* This bit masks the R_RESTART_DET interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_RESTART_DET				(1u << 12)
#define I2C0_IC_INTR_MASK_M_RESTART_DET_ENABLED			(0x0u << 12)
#define I2C0_IC_INTR_MASK_M_RESTART_DET_DISABLED		(0x1u << 12)
	/* This bit masks the R_GEN_CALL interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_GEN_CALL				(1u << 11)
#define I2C0_IC_INTR_MASK_M_GEN_CALL_ENABLED			(0x0u << 11)
#define I2C0_IC_INTR_MASK_M_GEN_CALL_DISABLED			(0x1u << 11)
	/* This bit masks the R_START_DET interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_START_DET				(1u << 10)
#define I2C0_IC_INTR_MASK_M_START_DET_ENABLED			(0x0u << 10)
#define I2C0_IC_INTR_MASK_M_START_DET_DISABLED			(0x1u << 10)
	/* This bit masks the R_STOP_DET interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_STOP_DET				(1u << 9)
#define I2C0_IC_INTR_MASK_M_STOP_DET_ENABLED			(0x0u << 9)
#define I2C0_IC_INTR_MASK_M_STOP_DET_DISABLED			(0x1u << 9)
	/* This bit masks the R_ACTIVITY interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_ACTIVITY				(1u << 8)
#define I2C0_IC_INTR_MASK_M_ACTIVITY_ENABLED			(0x0u << 8)
#define I2C0_IC_INTR_MASK_M_ACTIVITY_DISABLED			(0x1u << 8)
	/* This bit masks the R_RX_DONE interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_RX_DONE				(1u << 7)
#define I2C0_IC_INTR_MASK_M_RX_DONE_ENABLED			(0x0u << 7)
#define I2C0_IC_INTR_MASK_M_RX_DONE_DISABLED			(0x1u << 7)
	/* This bit masks the R_TX_ABRT interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_TX_ABRT				(1u << 6)
#define I2C0_IC_INTR_MASK_M_TX_ABRT_ENABLED			(0x0u << 6)
#define I2C0_IC_INTR_MASK_M_TX_ABRT_DISABLED			(0x1u << 6)
	/* This bit masks the R_RD_REQ interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_RD_REQ				(1u << 5)
#define I2C0_IC_INTR_MASK_M_RD_REQ_ENABLED			(0x0u << 5)
#define I2C0_IC_INTR_MASK_M_RD_REQ_DISABLED			(0x1u << 5)
	/* This bit masks the R_TX_EMPTY interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_TX_EMPTY				(1u << 4)
#define I2C0_IC_INTR_MASK_M_TX_EMPTY_ENABLED			(0x0u << 4)
#define I2C0_IC_INTR_MASK_M_TX_EMPTY_DISABLED			(0x1u << 4)
	/* This bit masks the R_TX_OVER interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_TX_OVER				(1u << 3)
#define I2C0_IC_INTR_MASK_M_TX_OVER_ENABLED			(0x0u << 3)
#define I2C0_IC_INTR_MASK_M_TX_OVER_DISABLED			(0x1u << 3)
	/* This bit masks the R_RX_FULL interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_RX_FULL				(1u << 2)
#define I2C0_IC_INTR_MASK_M_RX_FULL_ENABLED			(0x0u << 2)
#define I2C0_IC_INTR_MASK_M_RX_FULL_DISABLED			(0x1u << 2)
	/* This bit masks the R_RX_OVER interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_RX_OVER				(1u << 1)
#define I2C0_IC_INTR_MASK_M_RX_OVER_ENABLED			(0x0u << 1)
#define I2C0_IC_INTR_MASK_M_RX_OVER_DISABLED			(0x1u << 1)
	/* This bit masks the R_RX_UNDER interrupt in IC_INTR_STAT register. */
#define I2C0_IC_INTR_MASK_M_RX_UNDER				(1u << 0)
#define I2C0_IC_INTR_MASK_M_RX_UNDER_ENABLED			(0x0u << 0)
#define I2C0_IC_INTR_MASK_M_RX_UNDER_DISABLED			(0x1u << 0)

	/* 0x34: I2C Raw Interrupt Status Register */
	uint32_t volatile IC_RAW_INTR_STAT;
	/* Indicates whether a RESTART condition has occurred on the I2C interface when DW_apb_i2c is operating in Slave mode and the slave is being addressed. */
#define I2C0_IC_RAW_INTR_STAT_RESTART_DET			(1u << 12)
#define I2C0_IC_RAW_INTR_STAT_RESTART_DET_INACTIVE		(0x0u << 12)
#define I2C0_IC_RAW_INTR_STAT_RESTART_DET_ACTIVE		(0x1u << 12)
	/* Set only when a General Call address is received and it is acknowledged. */
#define I2C0_IC_RAW_INTR_STAT_GEN_CALL				(1u << 11)
#define I2C0_IC_RAW_INTR_STAT_GEN_CALL_INACTIVE			(0x0u << 11)
#define I2C0_IC_RAW_INTR_STAT_GEN_CALL_ACTIVE			(0x1u << 11)
	/* Indicates whether a START or RESTART condition has occurred on the I2C interface regardless of whether DW_apb_i2c is operating in slave or master mode. */
#define I2C0_IC_RAW_INTR_STAT_START_DET				(1u << 10)
#define I2C0_IC_RAW_INTR_STAT_START_DET_INACTIVE		(0x0u << 10)
#define I2C0_IC_RAW_INTR_STAT_START_DET_ACTIVE			(0x1u << 10)
	/* Indicates whether a STOP condition has occurred on the I2C interface regardless of whether DW_apb_i2c is operating in slave or master mode. */
#define I2C0_IC_RAW_INTR_STAT_STOP_DET				(1u << 9)
#define I2C0_IC_RAW_INTR_STAT_STOP_DET_INACTIVE			(0x0u << 9)
#define I2C0_IC_RAW_INTR_STAT_STOP_DET_ACTIVE			(0x1u << 9)
	/* This bit captures DW_apb_i2c activity and stays set until it is cleared. */
#define I2C0_IC_RAW_INTR_STAT_ACTIVITY				(1u << 8)
#define I2C0_IC_RAW_INTR_STAT_ACTIVITY_INACTIVE			(0x0u << 8)
#define I2C0_IC_RAW_INTR_STAT_ACTIVITY_ACTIVE			(0x1u << 8)
	/* When the DW_apb_i2c is acting as a slave-transmitter, this bit is set to 1 if the master does not acknowledge a transmitted byte. */
#define I2C0_IC_RAW_INTR_STAT_RX_DONE				(1u << 7)
#define I2C0_IC_RAW_INTR_STAT_RX_DONE_INACTIVE			(0x0u << 7)
#define I2C0_IC_RAW_INTR_STAT_RX_DONE_ACTIVE			(0x1u << 7)
	/* This bit indicates if DW_apb_i2c, as an I2C transmitter, is unable to complete the intended actions on the contents of the transmit FIFO. */
#define I2C0_IC_RAW_INTR_STAT_TX_ABRT				(1u << 6)
#define I2C0_IC_RAW_INTR_STAT_TX_ABRT_INACTIVE			(0x0u << 6)
#define I2C0_IC_RAW_INTR_STAT_TX_ABRT_ACTIVE			(0x1u << 6)
	/* This bit is set to 1 when DW_apb_i2c is acting as a slave and another I2C master is attempting to read data from DW_apb_i2c. The DW_apb_i2c holds the I2C bus in a wait state (SCL=0) until this interrupt is serviced, which means that the slave has been addressed by a remote master that is asking for data to be transferred. */
#define I2C0_IC_RAW_INTR_STAT_RD_REQ				(1u << 5)
#define I2C0_IC_RAW_INTR_STAT_RD_REQ_INACTIVE			(0x0u << 5)
#define I2C0_IC_RAW_INTR_STAT_RD_REQ_ACTIVE			(0x1u << 5)
	/* The behavior of the TX_EMPTY interrupt status differs based on the TX_EMPTY_CTRL selection in the IC_CON register. */
#define I2C0_IC_RAW_INTR_STAT_TX_EMPTY				(1u << 4)
#define I2C0_IC_RAW_INTR_STAT_TX_EMPTY_INACTIVE			(0x0u << 4)
#define I2C0_IC_RAW_INTR_STAT_TX_EMPTY_ACTIVE			(0x1u << 4)
	/* Set during transmit if the transmit buffer is filled to IC_TX_BUFFER_DEPTH and the processor attempts to issue another I2C command by writing to the IC_DATA_CMD register. */
#define I2C0_IC_RAW_INTR_STAT_TX_OVER				(1u << 3)
#define I2C0_IC_RAW_INTR_STAT_TX_OVER_INACTIVE			(0x0u << 3)
#define I2C0_IC_RAW_INTR_STAT_TX_OVER_ACTIVE			(0x1u << 3)
	/* Set when the receive buffer reaches or goes above the RX_TL threshold in the IC_RX_TL register. It is automatically cleared by hardware when buffer level goes below the threshold. If the module is disabled (IC_ENABLE[0]=0), the RX FIFO is flushed and held in reset; therefore the RX FIFO is not full. */
#define I2C0_IC_RAW_INTR_STAT_RX_FULL				(1u << 2)
#define I2C0_IC_RAW_INTR_STAT_RX_FULL_INACTIVE			(0x0u << 2)
#define I2C0_IC_RAW_INTR_STAT_RX_FULL_ACTIVE			(0x1u << 2)
	/* Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and an additional byte is received from an external I2C device. The DW_apb_i2c acknowledges this, but any data bytes received after the FIFO is full are lost. If the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared. */
#define I2C0_IC_RAW_INTR_STAT_RX_OVER				(1u << 1)
#define I2C0_IC_RAW_INTR_STAT_RX_OVER_INACTIVE			(0x0u << 1)
#define I2C0_IC_RAW_INTR_STAT_RX_OVER_ACTIVE			(0x1u << 1)
	/* Set if the processor attempts to read the receive buffer when it is empty by reading from the IC_DATA_CMD register. If the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared. */
#define I2C0_IC_RAW_INTR_STAT_RX_UNDER				(1u << 0)
#define I2C0_IC_RAW_INTR_STAT_RX_UNDER_INACTIVE			(0x0u << 0)
#define I2C0_IC_RAW_INTR_STAT_RX_UNDER_ACTIVE			(0x1u << 0)

	/* 0x38: I2C Receive FIFO Threshold Register */
	uint32_t volatile IC_RX_TL;
	/* Receive FIFO Threshold Level. */
#define I2C0_IC_RX_TL_RX_TL_Msk					(0xFFu << 0)
#define I2C0_IC_RX_TL_RX_TL_Pos					0u

	/* 0x3C: I2C Transmit FIFO Threshold Register */
	uint32_t volatile IC_TX_TL;
	/* Transmit FIFO Threshold Level. */
#define I2C0_IC_TX_TL_TX_TL_Msk					(0xFFu << 0)
#define I2C0_IC_TX_TL_TX_TL_Pos					0u

	/* 0x40: Clear Combined and Individual Interrupt Register */
	uint32_t volatile IC_CLR_INTR;
	/* Read this register to clear the combined interrupt, all individual interrupts, and the IC_TX_ABRT_SOURCE register. */
#define I2C0_IC_CLR_INTR_CLR_INTR				(1u << 0)

	/* 0x44: Clear RX_UNDER Interrupt Register */
	uint32_t volatile IC_CLR_RX_UNDER;
	/* Read this register to clear the RX_UNDER interrupt (bit 0) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_RX_UNDER_CLR_RX_UNDER			(1u << 0)

	/* 0x48: Clear RX_OVER Interrupt Register */
	uint32_t volatile IC_CLR_RX_OVER;
	/* Read this register to clear the RX_OVER interrupt (bit 1) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_RX_OVER_CLR_RX_OVER				(1u << 0)

	/* 0x4C: Clear TX_OVER Interrupt Register */
	uint32_t volatile IC_CLR_TX_OVER;
	/* Read this register to clear the TX_OVER interrupt (bit 3) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_TX_OVER_CLR_TX_OVER				(1u << 0)

	/* 0x50: Clear RD_REQ Interrupt Register */
	uint32_t volatile IC_CLR_RD_REQ;
	/* Read this register to clear the RD_REQ interrupt (bit 5) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_RD_REQ_CLR_RD_REQ				(1u << 0)

	/* 0x54: Clear TX_ABRT Interrupt Register */
	uint32_t volatile IC_CLR_TX_ABRT;
	/* Read this register to clear the TX_ABRT interrupt (bit 6) of the IC_RAW_INTR_STAT register, and the IC_TX_ABRT_SOURCE register. */
#define I2C0_IC_CLR_TX_ABRT_CLR_TX_ABRT				(1u << 0)

	/* 0x58: Clear RX_DONE Interrupt Register */
	uint32_t volatile IC_CLR_RX_DONE;
	/* Read this register to clear the RX_DONE interrupt (bit 7) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_RX_DONE_CLR_RX_DONE				(1u << 0)

	/* 0x5C: Clear ACTIVITY Interrupt Register */
	uint32_t volatile IC_CLR_ACTIVITY;
	/* Reading this register clears the ACTIVITY interrupt if the I2C is not active anymore. If the I2C module is still active on the bus, the ACTIVITY interrupt bit continues to be set. It is automatically cleared by hardware if the module is disabled and if there is no further activity on the bus. The value read from this register to get status of the ACTIVITY interrupt (bit 8) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_ACTIVITY_CLR_ACTIVITY			(1u << 0)

	/* 0x60: Clear STOP_DET Interrupt Register */
	uint32_t volatile IC_CLR_STOP_DET;
	/* Read this register to clear the STOP_DET interrupt (bit 9) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_STOP_DET_CLR_STOP_DET			(1u << 0)

	/* 0x64: Clear START_DET Interrupt Register */
	uint32_t volatile IC_CLR_START_DET;
	/* Read this register to clear the START_DET interrupt (bit 10) of the IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_START_DET_CLR_START_DET			(1u << 0)

	/* 0x68: Clear GEN_CALL Interrupt Register */
	uint32_t volatile IC_CLR_GEN_CALL;
	/* Read this register to clear the GEN_CALL interrupt (bit 11) of IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_GEN_CALL_CLR_GEN_CALL			(1u << 0)

	/* 0x6C: I2C Enable Register */
	uint32_t volatile IC_ENABLE;
	/* In Master mode: - 1'b1: Blocks the transmission of data on I2C bus even if Tx FIFO has data to transmit. - 1'b0: The transmission of data starts on I2C bus automatically, as soon as the first data is available in the Tx FIFO. Note: To block the execution of Master commands, set the TX_CMD_BLOCK bit only when Tx FIFO is empty (IC_STATUS[2]==1) and Master is in Idle state (IC_STATUS[5] == 0). */
#define I2C0_IC_ENABLE_TX_CMD_BLOCK				(1u << 2)
#define I2C0_IC_ENABLE_TX_CMD_BLOCK_NOT_BLOCKED			(0x0u << 2)
#define I2C0_IC_ENABLE_TX_CMD_BLOCK_BLOCKED			(0x1u << 2)
	/* When set, the controller initiates the transfer abort. */
#define I2C0_IC_ENABLE_ABORT					(1u << 1)
#define I2C0_IC_ENABLE_ABORT_DISABLE				(0x0u << 1)
#define I2C0_IC_ENABLE_ABORT_ENABLED				(0x1u << 1)
	/* Controls whether the DW_apb_i2c is enabled. - 0: Disables DW_apb_i2c (TX and RX FIFOs are held in an erased state) - 1: Enables DW_apb_i2c Software can disable DW_apb_i2c while it is active. */
#define I2C0_IC_ENABLE_ENABLE					(1u << 0)
#define I2C0_IC_ENABLE_ENABLE_DISABLED				(0x0u << 0)
#define I2C0_IC_ENABLE_ENABLE_ENABLED				(0x1u << 0)

	/* 0x70: I2C Status Register */
	uint32_t volatile IC_STATUS;
	/* Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is not in the IDLE state, this bit is set. */
#define I2C0_IC_STATUS_SLV_ACTIVITY				(1u << 6)
#define I2C0_IC_STATUS_SLV_ACTIVITY_IDLE			(0x0u << 6)
#define I2C0_IC_STATUS_SLV_ACTIVITY_ACTIVE			(0x1u << 6)
	/* Master FSM Activity Status. When the Master Finite State Machine (FSM) is not in the IDLE state, this bit is set. */
#define I2C0_IC_STATUS_MST_ACTIVITY				(1u << 5)
#define I2C0_IC_STATUS_MST_ACTIVITY_IDLE			(0x0u << 5)
#define I2C0_IC_STATUS_MST_ACTIVITY_ACTIVE			(0x1u << 5)
	/* Receive FIFO Completely Full. */
#define I2C0_IC_STATUS_RFF					(1u << 4)
#define I2C0_IC_STATUS_RFF_NOT_FULL				(0x0u << 4)
#define I2C0_IC_STATUS_RFF_FULL					(0x1u << 4)
	/* Receive FIFO Not Empty. */
#define I2C0_IC_STATUS_RFNE					(1u << 3)
#define I2C0_IC_STATUS_RFNE_EMPTY				(0x0u << 3)
#define I2C0_IC_STATUS_RFNE_NOT_EMPTY				(0x1u << 3)
	/* Transmit FIFO Completely Empty. */
#define I2C0_IC_STATUS_TFE					(1u << 2)
#define I2C0_IC_STATUS_TFE_NON_EMPTY				(0x0u << 2)
#define I2C0_IC_STATUS_TFE_EMPTY				(0x1u << 2)
	/* Transmit FIFO Not Full. */
#define I2C0_IC_STATUS_TFNF					(1u << 1)
#define I2C0_IC_STATUS_TFNF_FULL				(0x0u << 1)
#define I2C0_IC_STATUS_TFNF_NOT_FULL				(0x1u << 1)
	/* I2C Activity Status. */
#define I2C0_IC_STATUS_ACTIVITY					(1u << 0)
#define I2C0_IC_STATUS_ACTIVITY_INACTIVE			(0x0u << 0)
#define I2C0_IC_STATUS_ACTIVITY_ACTIVE				(0x1u << 0)

	/* 0x74: I2C Transmit FIFO Level Register This register contains the number of valid data entries in the transmit FIFO buffer. */
	uint32_t volatile IC_TXFLR;
	/* Transmit FIFO Level. */
#define I2C0_IC_TXFLR_TXFLR_Msk					(0x1Fu << 0)
#define I2C0_IC_TXFLR_TXFLR_Pos					0u

	/* 0x78: I2C Receive FIFO Level Register This register contains the number of valid data entries in the receive FIFO buffer. */
	uint32_t volatile IC_RXFLR;
	/* Receive FIFO Level. */
#define I2C0_IC_RXFLR_RXFLR_Msk					(0x1Fu << 0)
#define I2C0_IC_RXFLR_RXFLR_Pos					0u

	/* 0x7C: I2C SDA Hold Time Length Register */
	uint32_t volatile IC_SDA_HOLD;
	/* Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a receiver. */
#define I2C0_IC_SDA_HOLD_IC_SDA_RX_HOLD_Msk			(0xFFu << 16)
#define I2C0_IC_SDA_HOLD_IC_SDA_RX_HOLD_Pos			16u
	/* Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a transmitter. */
#define I2C0_IC_SDA_HOLD_IC_SDA_TX_HOLD_Msk			(0xFFFFu << 0)
#define I2C0_IC_SDA_HOLD_IC_SDA_TX_HOLD_Pos			0u

	/* 0x80: I2C Transmit Abort Source Register */
	uint32_t volatile IC_TX_ABRT_SOURCE;
	/* This field indicates the number of Tx FIFO Data Commands which are flushed due to TX_ABRT interrupt. */
#define I2C0_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_Msk			(0x1FFu << 23)
#define I2C0_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_Pos			23u
	/* This is a master-mode-only bit. Master has detected the transfer abort (IC_ENABLE[1]) */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_USER_ABRT			(1u << 16)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_USER_ABRT_ABRT_USER_ABRT_VOID	(0x0u << 16)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_USER_ABRT_ABRT_USER_ABRT_GENERATED	(0x1u << 16)
	/* 1: When the processor side responds to a slave mode request for data to be transmitted to a remote master and user writes a 1 in CMD (bit 8) of IC_DATA_CMD register. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX			(1u << 15)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_ABRT_SLVRD_INTX_VOID	(0x0u << 15)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_ABRT_SLVRD_INTX_GENERATED	(0x1u << 15)
	/* This field indicates that a Slave has lost the bus while transmitting data to a remote master. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST			(1u << 14)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_ABRT_SLV_ARBLOST_VOID	(0x0u << 14)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_ABRT_SLV_ARBLOST_GENERATED	(0x1u << 14)
	/* This field specifies that the Slave has received a read command and some data exists in the TX FIFO, so the slave issues a TX_ABRT interrupt to flush old data in TX FIFO. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO		(1u << 13)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_ABRT_SLVFLUSH_TXFIFO_VOID	(0x0u << 13)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_ABRT_SLVFLUSH_TXFIFO_GENERATED	(0x1u << 13)
	/* This field specifies that the Master has lost arbitration, or if IC_TX_ABRT_SOURCE[14] is also set, then the slave transmitter has lost arbitration. */
#define I2C0_IC_TX_ABRT_SOURCE_ARB_LOST				(1u << 12)
#define I2C0_IC_TX_ABRT_SOURCE_ARB_LOST_ABRT_LOST_VOID		(0x0u << 12)
#define I2C0_IC_TX_ABRT_SOURCE_ARB_LOST_ABRT_LOST_GENERATED	(0x1u << 12)
	/* This field indicates that the User tries to initiate a Master operation with the Master mode disabled. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS			(1u << 11)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS_ABRT_MASTER_DIS_VOID	(0x0u << 11)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS_ABRT_MASTER_DIS_GENERATED	(0x1u << 11)
	/* This field indicates that the restart is disabled (IC_RESTART_EN bit (IC_CON[5]) =0) and the master sends a read command in 10-bit addressing mode. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT		(1u << 10)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_ABRT_10B_RD_VOID	(0x0u << 10)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_ABRT_10B_RD_GENERATED	(0x1u << 10)
	/* To clear Bit 9, the source of the ABRT_SBYTE_NORSTRT must be fixed first; restart must be enabled (IC_CON[5]=1), the SPECIAL bit must be cleared (IC_TAR[11]), or the GC_OR_START bit must be cleared (IC_TAR[10]). Once the source of the ABRT_SBYTE_NORSTRT is fixed, then this bit can be cleared in the same manner as other bits in this register. If the source of the ABRT_SBYTE_NORSTRT is not fixed before attempting to clear this bit, bit 9 clears for one cycle and then gets reasserted. When this field is set to 1, the restart is disabled (IC_RESTART_EN bit (IC_CON[5]) =0) and the user is trying to send a START Byte. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT		(1u << 9)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_ABRT_SBYTE_NORSTRT_VOID	(0x0u << 9)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_ABRT_SBYTE_NORSTRT_GENERATED	(0x1u << 9)
	/* This field indicates that the restart is disabled (IC_RESTART_EN bit (IC_CON[5]) =0) and the user is trying to use the master to transfer data in High Speed mode. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT			(1u << 8)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_ABRT_HS_NORSTRT_VOID	(0x0u << 8)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_ABRT_HS_NORSTRT_GENERATED	(0x1u << 8)
	/* This field indicates that the Master has sent a START Byte and the START Byte was acknowledged (wrong behavior). */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET		(1u << 7)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_ABRT_SBYTE_ACKDET_VOID	(0x0u << 7)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_ABRT_SBYTE_ACKDET_GENERATED	(0x1u << 7)
	/* This field indicates that the Master is in High Speed mode and the High Speed Master code was acknowledged (wrong behavior). */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET			(1u << 6)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET_ABRT_HS_ACK_VOID	(0x0u << 6)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET_ABRT_HS_ACK_GENERATED	(0x1u << 6)
	/* This field indicates that DW_apb_i2c in the master mode has sent a General Call but the user programmed the byte following the General Call to be a read from the bus (IC_DATA_CMD[9] is set to 1). */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ			(1u << 5)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ_ABRT_GCALL_READ_VOID	(0x0u << 5)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ_ABRT_GCALL_READ_GENERATED	(0x1u << 5)
	/* This field indicates that DW_apb_i2c in master mode has sent a General Call and no slave on the bus acknowledged the General Call. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK			(1u << 4)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_ABRT_GCALL_NOACK_VOID	(0x0u << 4)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_ABRT_GCALL_NOACK_GENERATED	(0x1u << 4)
	/* This field indicates the master-mode only bit. When the master receives an acknowledgement for the address, but when it sends data byte(s) following the address, it did not receive an acknowledge from the remote slave(s). */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK		(1u << 3)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_ABRT_TXDATA_NOACK_VOID	(0x0u << 3)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_ABRT_TXDATA_NOACK_GENERATED	(0x1u << 3)
	/* This field indicates that the Master is in 10-bit address mode and that the second address byte of the 10-bit address was not acknowledged by any slave. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK		(1u << 2)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_INACTIVE	(0x0u << 2)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_ACTIVE	(0x1u << 2)
	/* This field indicates that the Master is in 10-bit address mode and the first 10-bit address byte was not acknowledged by any slave. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK		(1u << 1)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_INACTIVE	(0x0u << 1)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_ACTIVE	(0x1u << 1)
	/* This field indicates that the Master is in 7-bit addressing mode and the address sent was not acknowledged by any slave. */
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK		(1u << 0)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_INACTIVE	(0x0u << 0)
#define I2C0_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_ACTIVE	(0x1u << 0)

	/* 0x84: Generate Slave Data NACK Register */
	uint32_t volatile IC_SLV_DATA_NACK_ONLY;
	/* Generate NACK. */
#define I2C0_IC_SLV_DATA_NACK_ONLY_NACK				(1u << 0)
#define I2C0_IC_SLV_DATA_NACK_ONLY_NACK_DISABLED		(0x0u << 0)
#define I2C0_IC_SLV_DATA_NACK_ONLY_NACK_ENABLED			(0x1u << 0)

	/* 0x88: DMA Control Register */
	uint32_t volatile IC_DMA_CR;
	/* Transmit DMA Enable. */
#define I2C0_IC_DMA_CR_TDMAE					(1u << 1)
#define I2C0_IC_DMA_CR_TDMAE_DISABLED				(0x0u << 1)
#define I2C0_IC_DMA_CR_TDMAE_ENABLED				(0x1u << 1)
	/* Receive DMA Enable. */
#define I2C0_IC_DMA_CR_RDMAE					(1u << 0)
#define I2C0_IC_DMA_CR_RDMAE_DISABLED				(0x0u << 0)
#define I2C0_IC_DMA_CR_RDMAE_ENABLED				(0x1u << 0)

	/* 0x8C: DMA Transmit Data Level Register */
	uint32_t volatile IC_DMA_TDLR;
	/* Transmit Data Level. */
#define I2C0_IC_DMA_TDLR_DMATDL_Msk				(0xFu << 0)
#define I2C0_IC_DMA_TDLR_DMATDL_Pos				0u

	/* 0x90: I2C Receive Data Level Register */
	uint32_t volatile IC_DMA_RDLR;
	/* Receive Data Level. */
#define I2C0_IC_DMA_RDLR_DMARDL_Msk				(0xFu << 0)
#define I2C0_IC_DMA_RDLR_DMARDL_Pos				0u

	/* 0x94: I2C SDA Setup Register */
	uint32_t volatile IC_SDA_SETUP;
	/* SDA Setup. */
#define I2C0_IC_SDA_SETUP_SDA_SETUP_Msk				(0xFFu << 0)
#define I2C0_IC_SDA_SETUP_SDA_SETUP_Pos				0u

	/* 0x98: I2C ACK General Call Register */
	uint32_t volatile IC_ACK_GENERAL_CALL;
	/* ACK General Call. When set to 1, DW_apb_i2c responds with a ACK (by asserting ic_data_oe) when it receives a General Call. Otherwise, DW_apb_i2c responds with a NACK (by negating ic_data_oe). */
#define I2C0_IC_ACK_GENERAL_CALL_ACK_GEN_CALL			(1u << 0)
#define I2C0_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_DISABLED		(0x0u << 0)
#define I2C0_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_ENABLED		(0x1u << 0)

	/* 0x9C: I2C Enable Status Register */
	uint32_t volatile IC_ENABLE_STATUS;
	/* Slave Received Data Lost. This bit indicates if a Slave-Receiver operation has been aborted with at least one data byte received from an I2C transfer due to the setting bit 0 of IC_ENABLE from 1 to 0. When read as 1, DW_apb_i2c is deemed to have been actively engaged in an aborted I2C transfer (with matching address) and the data phase of the I2C transfer has been entered, even though a data byte has been responded with a NACK. */
#define I2C0_IC_ENABLE_STATUS_SLV_RX_DATA_LOST			(1u << 2)
#define I2C0_IC_ENABLE_STATUS_SLV_RX_DATA_LOST_INACTIVE		(0x0u << 2)
#define I2C0_IC_ENABLE_STATUS_SLV_RX_DATA_LOST_ACTIVE		(0x1u << 2)
	/* Slave Disabled While Busy (Transmit, Receive). */
#define I2C0_IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY		(1u << 1)
#define I2C0_IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_INACTIVE	(0x0u << 1)
#define I2C0_IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_ACTIVE	(0x1u << 1)
	/* ic_en Status. This bit always reflects the value driven on the output port ic_en. - When read as 1, DW_apb_i2c is deemed to be in an enabled state. - When read as 0, DW_apb_i2c is deemed completely inactive. Note:  The CPU can safely read this bit anytime. When this bit is read as 0, the CPU can safely read SLV_RX_DATA_LOST (bit 2) and SLV_DISABLED_WHILE_BUSY (bit 1). */
#define I2C0_IC_ENABLE_STATUS_IC_EN				(1u << 0)
#define I2C0_IC_ENABLE_STATUS_IC_EN_DISABLED			(0x0u << 0)
#define I2C0_IC_ENABLE_STATUS_IC_EN_ENABLED			(0x1u << 0)

	/* 0xA0: I2C SS, FS or FM+ spike suppression limit */
	uint32_t volatile IC_FS_SPKLEN;
	/* This register must be set before any I2C bus transaction can take place to ensure stable operation. */
#define I2C0_IC_FS_SPKLEN_IC_FS_SPKLEN_Msk			(0xFFu << 0)
#define I2C0_IC_FS_SPKLEN_IC_FS_SPKLEN_Pos			0u

	/* 0xA4 */
	uint8_t RESERVED2[0xA8u-0xA4u];

	/* 0xA8: Clear RESTART_DET Interrupt Register */
	uint32_t volatile IC_CLR_RESTART_DET;
	/* Read this register to clear the RESTART_DET interrupt (bit 12) of IC_RAW_INTR_STAT register. */
#define I2C0_IC_CLR_RESTART_DET_CLR_RESTART_DET			(1u << 0)

	/* 0xAC */
	uint8_t RESERVED3[0xF4u-0xACu];

	/* 0xF4: Component Parameter Register 1 */
	uint32_t volatile IC_COMP_PARAM_1;
	/* TX Buffer Depth = 16 */
#define I2C0_IC_COMP_PARAM_1_TX_BUFFER_DEPTH_Msk		(0xFFu << 16)
#define I2C0_IC_COMP_PARAM_1_TX_BUFFER_DEPTH_Pos		16u
	/* RX Buffer Depth = 16 */
#define I2C0_IC_COMP_PARAM_1_RX_BUFFER_DEPTH_Msk		(0xFFu << 8)
#define I2C0_IC_COMP_PARAM_1_RX_BUFFER_DEPTH_Pos		8u
	/* Encoded parameters not visible */
#define I2C0_IC_COMP_PARAM_1_ADD_ENCODED_PARAMS			(1u << 7)
	/* DMA handshaking signals are enabled */
#define I2C0_IC_COMP_PARAM_1_HAS_DMA				(1u << 6)
	/* COMBINED Interrupt outputs */
#define I2C0_IC_COMP_PARAM_1_INTR_IO				(1u << 5)
	/* Programmable count values for each mode. */
#define I2C0_IC_COMP_PARAM_1_HC_COUNT_VALUES			(1u << 4)
	/* MAX SPEED MODE = FAST MODE */
#define I2C0_IC_COMP_PARAM_1_MAX_SPEED_MODE_Msk			(0x3u << 2)
#define I2C0_IC_COMP_PARAM_1_MAX_SPEED_MODE_Pos			2u
	/* APB data bus width is 32 bits */
#define I2C0_IC_COMP_PARAM_1_APB_DATA_WIDTH_Msk			(0x3u << 0)
#define I2C0_IC_COMP_PARAM_1_APB_DATA_WIDTH_Pos			0u

	/* 0xF8: I2C Component Version Register */
	uint32_t volatile IC_COMP_VERSION;
	/*  */
#define I2C0_IC_COMP_VERSION_IC_COMP_VERSION_Msk		(0xFFFFFFFFu << 0)
#define I2C0_IC_COMP_VERSION_IC_COMP_VERSION_Pos		0u

	/* 0xFC: I2C Component Type Register */
	uint32_t volatile IC_COMP_TYPE;
	/* Designware Component Type number = 0x44_57_01_40. */
#define I2C0_IC_COMP_TYPE_IC_COMP_TYPE_Msk			(0xFFFFFFFFu << 0)
#define I2C0_IC_COMP_TYPE_IC_COMP_TYPE_Pos			0u

};


#define ADC ((struct mcu_adc *)0x4004C000)

struct mcu_adc {

	/* 0x00: ADC Control and Status */
	uint32_t volatile CS;
	/* Round-robin sampling. */
#define ADC_CS_RROBIN_Msk					(0x1Fu << 16)
#define ADC_CS_RROBIN_Pos					16u
	/* Select analog mux input. */
#define ADC_CS_AINSEL_Msk					(0x7u << 12)
#define ADC_CS_AINSEL_Pos					12u
	/* Some past ADC conversion encountered an error. */
#define ADC_CS_ERR_STICKY					(1u << 10)
	/* The most recent ADC conversion encountered an error; result is undefined or noisy. */
#define ADC_CS_ERR						(1u << 9)
	/* 1 if the ADC is ready to start a new conversion. */
#define ADC_CS_READY						(1u << 8)
	/* Continuously perform conversions whilst this bit is 1. */
#define ADC_CS_START_MANY					(1u << 3)
	/* Start a single conversion. */
#define ADC_CS_START_ONCE					(1u << 2)
	/* Power on temperature sensor. */
#define ADC_CS_TS_EN						(1u << 1)
	/* Power on ADC and enable its clock. */
#define ADC_CS_EN						(1u << 0)

	/* 0x04: Result of most recent ADC conversion */
	uint32_t volatile RESULT;
	/*  */
#define ADC_RESULT_RESULT_Msk					(0xFFFu << 0)
#define ADC_RESULT_RESULT_Pos					0u

	/* 0x08: FIFO control and status */
	uint32_t volatile FCS;
	/* DREQ/IRQ asserted when level >= threshold */
#define ADC_FCS_THRESH_Msk					(0xFu << 24)
#define ADC_FCS_THRESH_Pos					24u
	/* The number of conversion results currently waiting in the FIFO */
#define ADC_FCS_LEVEL_Msk					(0xFu << 16)
#define ADC_FCS_LEVEL_Pos					16u
	/* 1 if the FIFO has been overflowed. */
#define ADC_FCS_OVER						(1u << 11)
	/* 1 if the FIFO has been underflowed. */
#define ADC_FCS_UNDER						(1u << 10)
	/*  */
#define ADC_FCS_FULL						(1u << 9)
	/*  */
#define ADC_FCS_EMPTY						(1u << 8)
	/* If 1: assert DMA requests when FIFO contains data */
#define ADC_FCS_DREQ_EN						(1u << 3)
	/* If 1: conversion error bit appears in the FIFO alongside the result */
#define ADC_FCS_ERR						(1u << 2)
	/* If 1: FIFO results are right-shifted to be one byte in size. */
#define ADC_FCS_SHIFT						(1u << 1)
	/* If 1: write result to the FIFO after each conversion. */
#define ADC_FCS_EN						(1u << 0)

	/* 0x0C: Conversion result FIFO */
	uint32_t volatile FIFO;
	/* 1 if this particular sample experienced a conversion error. */
#define ADC_FIFO_ERR						(1u << 15)
	/*  */
#define ADC_FIFO_VAL_Msk					(0xFFFu << 0)
#define ADC_FIFO_VAL_Pos					0u

	/* 0x10: Clock divider. */
	uint32_t volatile DIV;
	/* Integer part of clock divisor. */
#define ADC_DIV_INT_Msk						(0xFFFFu << 8)
#define ADC_DIV_INT_Pos						8u
	/* Fractional part of clock divisor. */
#define ADC_DIV_FRAC_Msk					(0xFFu << 0)
#define ADC_DIV_FRAC_Pos					0u

	/* 0x14: Raw Interrupts */
	uint32_t volatile INTR;
	/* Triggered when the sample FIFO reaches a certain level. */
#define ADC_INTR_FIFO						(1u << 0)

	/* 0x18: Interrupt Enable */
	uint32_t volatile INTE;
	/* Triggered when the sample FIFO reaches a certain level. */
#define ADC_INTE_FIFO						(1u << 0)

	/* 0x1C: Interrupt Force */
	uint32_t volatile INTF;
	/* Triggered when the sample FIFO reaches a certain level. */
#define ADC_INTF_FIFO						(1u << 0)

	/* 0x20: Interrupt status after masking & forcing */
	uint32_t volatile INTS;
	/* Triggered when the sample FIFO reaches a certain level. */
#define ADC_INTS_FIFO						(1u << 0)

};


#define PWM ((struct mcu_pwm *)0x40050000)

struct mcu_pwm {

	/* 0x00: Control and status register */
	uint32_t volatile CH0_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH0_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH0_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH0_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH0_CSR_DIVMODE_Pos					4u
#define PWM_CH0_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH0_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH0_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH0_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH0_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH0_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH0_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH0_CSR_EN						(1u << 0)

	/* 0x04: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH0_DIV;
	/*  */
#define PWM_CH0_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH0_DIV_INT_Pos					4u
	/*  */
#define PWM_CH0_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH0_DIV_FRAC_Pos					0u

	/* 0x08: Direct access to the PWM counter */
	uint32_t volatile CH0_CTR;
	/*  */
#define PWM_CH0_CTR_CH0_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH0_CTR_CH0_CTR_Pos					0u

	/* 0x0C: Counter compare values */
	uint32_t volatile CH0_CC;
	/*  */
#define PWM_CH0_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH0_CC_B_Pos					16u
	/*  */
#define PWM_CH0_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH0_CC_A_Pos					0u

	/* 0x10: Counter wrap value */
	uint32_t volatile CH0_TOP;
	/*  */
#define PWM_CH0_TOP_CH0_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH0_TOP_CH0_TOP_Pos					0u

	/* 0x14: Control and status register */
	uint32_t volatile CH1_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH1_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH1_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH1_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH1_CSR_DIVMODE_Pos					4u
#define PWM_CH1_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH1_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH1_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH1_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH1_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH1_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH1_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH1_CSR_EN						(1u << 0)

	/* 0x18: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH1_DIV;
	/*  */
#define PWM_CH1_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH1_DIV_INT_Pos					4u
	/*  */
#define PWM_CH1_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH1_DIV_FRAC_Pos					0u

	/* 0x1C: Direct access to the PWM counter */
	uint32_t volatile CH1_CTR;
	/*  */
#define PWM_CH1_CTR_CH1_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH1_CTR_CH1_CTR_Pos					0u

	/* 0x20: Counter compare values */
	uint32_t volatile CH1_CC;
	/*  */
#define PWM_CH1_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH1_CC_B_Pos					16u
	/*  */
#define PWM_CH1_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH1_CC_A_Pos					0u

	/* 0x24: Counter wrap value */
	uint32_t volatile CH1_TOP;
	/*  */
#define PWM_CH1_TOP_CH1_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH1_TOP_CH1_TOP_Pos					0u

	/* 0x28: Control and status register */
	uint32_t volatile CH2_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH2_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH2_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH2_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH2_CSR_DIVMODE_Pos					4u
#define PWM_CH2_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH2_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH2_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH2_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH2_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH2_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH2_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH2_CSR_EN						(1u << 0)

	/* 0x2C: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH2_DIV;
	/*  */
#define PWM_CH2_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH2_DIV_INT_Pos					4u
	/*  */
#define PWM_CH2_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH2_DIV_FRAC_Pos					0u

	/* 0x30: Direct access to the PWM counter */
	uint32_t volatile CH2_CTR;
	/*  */
#define PWM_CH2_CTR_CH2_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH2_CTR_CH2_CTR_Pos					0u

	/* 0x34: Counter compare values */
	uint32_t volatile CH2_CC;
	/*  */
#define PWM_CH2_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH2_CC_B_Pos					16u
	/*  */
#define PWM_CH2_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH2_CC_A_Pos					0u

	/* 0x38: Counter wrap value */
	uint32_t volatile CH2_TOP;
	/*  */
#define PWM_CH2_TOP_CH2_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH2_TOP_CH2_TOP_Pos					0u

	/* 0x3C: Control and status register */
	uint32_t volatile CH3_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH3_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH3_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH3_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH3_CSR_DIVMODE_Pos					4u
#define PWM_CH3_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH3_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH3_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH3_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH3_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH3_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH3_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH3_CSR_EN						(1u << 0)

	/* 0x40: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH3_DIV;
	/*  */
#define PWM_CH3_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH3_DIV_INT_Pos					4u
	/*  */
#define PWM_CH3_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH3_DIV_FRAC_Pos					0u

	/* 0x44: Direct access to the PWM counter */
	uint32_t volatile CH3_CTR;
	/*  */
#define PWM_CH3_CTR_CH3_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH3_CTR_CH3_CTR_Pos					0u

	/* 0x48: Counter compare values */
	uint32_t volatile CH3_CC;
	/*  */
#define PWM_CH3_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH3_CC_B_Pos					16u
	/*  */
#define PWM_CH3_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH3_CC_A_Pos					0u

	/* 0x4C: Counter wrap value */
	uint32_t volatile CH3_TOP;
	/*  */
#define PWM_CH3_TOP_CH3_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH3_TOP_CH3_TOP_Pos					0u

	/* 0x50: Control and status register */
	uint32_t volatile CH4_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH4_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH4_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH4_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH4_CSR_DIVMODE_Pos					4u
#define PWM_CH4_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH4_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH4_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH4_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH4_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH4_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH4_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH4_CSR_EN						(1u << 0)

	/* 0x54: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH4_DIV;
	/*  */
#define PWM_CH4_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH4_DIV_INT_Pos					4u
	/*  */
#define PWM_CH4_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH4_DIV_FRAC_Pos					0u

	/* 0x58: Direct access to the PWM counter */
	uint32_t volatile CH4_CTR;
	/*  */
#define PWM_CH4_CTR_CH4_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH4_CTR_CH4_CTR_Pos					0u

	/* 0x5C: Counter compare values */
	uint32_t volatile CH4_CC;
	/*  */
#define PWM_CH4_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH4_CC_B_Pos					16u
	/*  */
#define PWM_CH4_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH4_CC_A_Pos					0u

	/* 0x60: Counter wrap value */
	uint32_t volatile CH4_TOP;
	/*  */
#define PWM_CH4_TOP_CH4_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH4_TOP_CH4_TOP_Pos					0u

	/* 0x64: Control and status register */
	uint32_t volatile CH5_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH5_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH5_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH5_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH5_CSR_DIVMODE_Pos					4u
#define PWM_CH5_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH5_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH5_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH5_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH5_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH5_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH5_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH5_CSR_EN						(1u << 0)

	/* 0x68: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH5_DIV;
	/*  */
#define PWM_CH5_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH5_DIV_INT_Pos					4u
	/*  */
#define PWM_CH5_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH5_DIV_FRAC_Pos					0u

	/* 0x6C: Direct access to the PWM counter */
	uint32_t volatile CH5_CTR;
	/*  */
#define PWM_CH5_CTR_CH5_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH5_CTR_CH5_CTR_Pos					0u

	/* 0x70: Counter compare values */
	uint32_t volatile CH5_CC;
	/*  */
#define PWM_CH5_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH5_CC_B_Pos					16u
	/*  */
#define PWM_CH5_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH5_CC_A_Pos					0u

	/* 0x74: Counter wrap value */
	uint32_t volatile CH5_TOP;
	/*  */
#define PWM_CH5_TOP_CH5_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH5_TOP_CH5_TOP_Pos					0u

	/* 0x78: Control and status register */
	uint32_t volatile CH6_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH6_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH6_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH6_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH6_CSR_DIVMODE_Pos					4u
#define PWM_CH6_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH6_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH6_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH6_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH6_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH6_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH6_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH6_CSR_EN						(1u << 0)

	/* 0x7C: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH6_DIV;
	/*  */
#define PWM_CH6_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH6_DIV_INT_Pos					4u
	/*  */
#define PWM_CH6_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH6_DIV_FRAC_Pos					0u

	/* 0x80: Direct access to the PWM counter */
	uint32_t volatile CH6_CTR;
	/*  */
#define PWM_CH6_CTR_CH6_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH6_CTR_CH6_CTR_Pos					0u

	/* 0x84: Counter compare values */
	uint32_t volatile CH6_CC;
	/*  */
#define PWM_CH6_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH6_CC_B_Pos					16u
	/*  */
#define PWM_CH6_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH6_CC_A_Pos					0u

	/* 0x88: Counter wrap value */
	uint32_t volatile CH6_TOP;
	/*  */
#define PWM_CH6_TOP_CH6_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH6_TOP_CH6_TOP_Pos					0u

	/* 0x8C: Control and status register */
	uint32_t volatile CH7_CSR;
	/* Advance the phase of the counter by 1 count, while it is running. */
#define PWM_CH7_CSR_PH_ADV					(1u << 7)
	/* Retard the phase of the counter by 1 count, while it is running. */
#define PWM_CH7_CSR_PH_RET					(1u << 6)
	/*  */
#define PWM_CH7_CSR_DIVMODE_Msk					(0x3u << 4)
#define PWM_CH7_CSR_DIVMODE_Pos					4u
#define PWM_CH7_CSR_DIVMODE_DIV					(0x0u << 4)
#define PWM_CH7_CSR_DIVMODE_LEVEL				(0x1u << 4)
#define PWM_CH7_CSR_DIVMODE_RISE				(0x2u << 4)
#define PWM_CH7_CSR_DIVMODE_FALL				(0x3u << 4)
	/* Invert output B */
#define PWM_CH7_CSR_B_INV					(1u << 3)
	/* Invert output A */
#define PWM_CH7_CSR_A_INV					(1u << 2)
	/* 1: Enable phase-correct modulation. */
#define PWM_CH7_CSR_PH_CORRECT					(1u << 1)
	/* Enable the PWM channel. */
#define PWM_CH7_CSR_EN						(1u << 0)

	/* 0x90: INT and FRAC form a fixed-point fractional number. */
	uint32_t volatile CH7_DIV;
	/*  */
#define PWM_CH7_DIV_INT_Msk					(0xFFu << 4)
#define PWM_CH7_DIV_INT_Pos					4u
	/*  */
#define PWM_CH7_DIV_FRAC_Msk					(0xFu << 0)
#define PWM_CH7_DIV_FRAC_Pos					0u

	/* 0x94: Direct access to the PWM counter */
	uint32_t volatile CH7_CTR;
	/*  */
#define PWM_CH7_CTR_CH7_CTR_Msk					(0xFFFFu << 0)
#define PWM_CH7_CTR_CH7_CTR_Pos					0u

	/* 0x98: Counter compare values */
	uint32_t volatile CH7_CC;
	/*  */
#define PWM_CH7_CC_B_Msk					(0xFFFFu << 16)
#define PWM_CH7_CC_B_Pos					16u
	/*  */
#define PWM_CH7_CC_A_Msk					(0xFFFFu << 0)
#define PWM_CH7_CC_A_Pos					0u

	/* 0x9C: Counter wrap value */
	uint32_t volatile CH7_TOP;
	/*  */
#define PWM_CH7_TOP_CH7_TOP_Msk					(0xFFFFu << 0)
#define PWM_CH7_TOP_CH7_TOP_Pos					0u

	/* 0xA0: This register aliases the CSR_EN bits for all channels. */
	uint32_t volatile EN;
	/*  */
#define PWM_EN_CH7						(1u << 7)
	/*  */
#define PWM_EN_CH6						(1u << 6)
	/*  */
#define PWM_EN_CH5						(1u << 5)
	/*  */
#define PWM_EN_CH4						(1u << 4)
	/*  */
#define PWM_EN_CH3						(1u << 3)
	/*  */
#define PWM_EN_CH2						(1u << 2)
	/*  */
#define PWM_EN_CH1						(1u << 1)
	/*  */
#define PWM_EN_CH0						(1u << 0)

	/* 0xA4: Raw Interrupts */
	uint32_t volatile INTR;
	/*  */
#define PWM_INTR_CH7						(1u << 7)
	/*  */
#define PWM_INTR_CH6						(1u << 6)
	/*  */
#define PWM_INTR_CH5						(1u << 5)
	/*  */
#define PWM_INTR_CH4						(1u << 4)
	/*  */
#define PWM_INTR_CH3						(1u << 3)
	/*  */
#define PWM_INTR_CH2						(1u << 2)
	/*  */
#define PWM_INTR_CH1						(1u << 1)
	/*  */
#define PWM_INTR_CH0						(1u << 0)

	/* 0xA8: Interrupt Enable */
	uint32_t volatile INTE;
	/*  */
#define PWM_INTE_CH7						(1u << 7)
	/*  */
#define PWM_INTE_CH6						(1u << 6)
	/*  */
#define PWM_INTE_CH5						(1u << 5)
	/*  */
#define PWM_INTE_CH4						(1u << 4)
	/*  */
#define PWM_INTE_CH3						(1u << 3)
	/*  */
#define PWM_INTE_CH2						(1u << 2)
	/*  */
#define PWM_INTE_CH1						(1u << 1)
	/*  */
#define PWM_INTE_CH0						(1u << 0)

	/* 0xAC: Interrupt Force */
	uint32_t volatile INTF;
	/*  */
#define PWM_INTF_CH7						(1u << 7)
	/*  */
#define PWM_INTF_CH6						(1u << 6)
	/*  */
#define PWM_INTF_CH5						(1u << 5)
	/*  */
#define PWM_INTF_CH4						(1u << 4)
	/*  */
#define PWM_INTF_CH3						(1u << 3)
	/*  */
#define PWM_INTF_CH2						(1u << 2)
	/*  */
#define PWM_INTF_CH1						(1u << 1)
	/*  */
#define PWM_INTF_CH0						(1u << 0)

	/* 0xB0: Interrupt status after masking & forcing */
	uint32_t volatile INTS;
	/*  */
#define PWM_INTS_CH7						(1u << 7)
	/*  */
#define PWM_INTS_CH6						(1u << 6)
	/*  */
#define PWM_INTS_CH5						(1u << 5)
	/*  */
#define PWM_INTS_CH4						(1u << 4)
	/*  */
#define PWM_INTS_CH3						(1u << 3)
	/*  */
#define PWM_INTS_CH2						(1u << 2)
	/*  */
#define PWM_INTS_CH1						(1u << 1)
	/*  */
#define PWM_INTS_CH0						(1u << 0)

};


#define TIMER ((struct mcu_timer *)0x40054000)

struct mcu_timer {

	/* 0x00: Write to bits 63:32 of time */
	uint32_t volatile TIMEHW;

	/* 0x04: Write to bits 31:0 of time */
	uint32_t volatile TIMELW;

	/* 0x08: Read from bits 63:32 of time */
	uint32_t volatile TIMEHR;

	/* 0x0C: Read from bits 31:0 of time */
	uint32_t volatile TIMELR;

	/* 0x10: Arm alarm 0, and configure the time it will fire. */
	uint32_t volatile ALARM0;

	/* 0x14: Arm alarm 1, and configure the time it will fire. */
	uint32_t volatile ALARM1;

	/* 0x18: Arm alarm 2, and configure the time it will fire. */
	uint32_t volatile ALARM2;

	/* 0x1C: Arm alarm 3, and configure the time it will fire. */
	uint32_t volatile ALARM3;

	/* 0x20: Indicates the armed/disarmed status of each alarm. */
	uint32_t volatile ARMED;
	/*  */
#define TIMER_ARMED_ARMED_Msk					(0xFu << 0)
#define TIMER_ARMED_ARMED_Pos					0u

	/* 0x24: Raw read from bits 63:32 of time (no side effects) */
	uint32_t volatile TIMERAWH;

	/* 0x28: Raw read from bits 31:0 of time (no side effects) */
	uint32_t volatile TIMERAWL;

	/* 0x2C: Set bits high to enable pause when the corresponding debug ports are active */
	uint32_t volatile DBGPAUSE;
	/* Pause when processor 1 is in debug mode */
#define TIMER_DBGPAUSE_DBG1					(1u << 2)
	/* Pause when processor 0 is in debug mode */
#define TIMER_DBGPAUSE_DBG0					(1u << 1)

	/* 0x30: Set high to pause the timer */
	uint32_t volatile PAUSE;
	/*  */
#define TIMER_PAUSE_PAUSE					(1u << 0)

	/* 0x34: Raw Interrupts */
	uint32_t volatile INTR;
	/*  */
#define TIMER_INTR_ALARM_3					(1u << 3)
	/*  */
#define TIMER_INTR_ALARM_2					(1u << 2)
	/*  */
#define TIMER_INTR_ALARM_1					(1u << 1)
	/*  */
#define TIMER_INTR_ALARM_0					(1u << 0)

	/* 0x38: Interrupt Enable */
	uint32_t volatile INTE;
	/*  */
#define TIMER_INTE_ALARM_3					(1u << 3)
	/*  */
#define TIMER_INTE_ALARM_2					(1u << 2)
	/*  */
#define TIMER_INTE_ALARM_1					(1u << 1)
	/*  */
#define TIMER_INTE_ALARM_0					(1u << 0)

	/* 0x3C: Interrupt Force */
	uint32_t volatile INTF;
	/*  */
#define TIMER_INTF_ALARM_3					(1u << 3)
	/*  */
#define TIMER_INTF_ALARM_2					(1u << 2)
	/*  */
#define TIMER_INTF_ALARM_1					(1u << 1)
	/*  */
#define TIMER_INTF_ALARM_0					(1u << 0)

	/* 0x40: Interrupt status after masking & forcing */
	uint32_t volatile INTS;
	/*  */
#define TIMER_INTS_ALARM_3					(1u << 3)
	/*  */
#define TIMER_INTS_ALARM_2					(1u << 2)
	/*  */
#define TIMER_INTS_ALARM_1					(1u << 1)
	/*  */
#define TIMER_INTS_ALARM_0					(1u << 0)

};


#define WATCHDOG ((struct mcu_watchdog *)0x40058000)

struct mcu_watchdog {

	/* 0x00: Watchdog control */
	uint32_t volatile CTRL;
	/* Trigger a watchdog reset */
#define WATCHDOG_CTRL_TRIGGER					(1u << 31)
	/* When not enabled the watchdog timer is paused */
#define WATCHDOG_CTRL_ENABLE					(1u << 30)
	/* Pause the watchdog timer when processor 1 is in debug mode */
#define WATCHDOG_CTRL_PAUSE_DBG1				(1u << 26)
	/* Pause the watchdog timer when processor 0 is in debug mode */
#define WATCHDOG_CTRL_PAUSE_DBG0				(1u << 25)
	/* Pause the watchdog timer when JTAG is accessing the bus fabric */
#define WATCHDOG_CTRL_PAUSE_JTAG				(1u << 24)
	/* Indicates the number of ticks / 2 (see errata RP2040-E1) before a watchdog reset will be triggered */
#define WATCHDOG_CTRL_TIME_Msk					(0xFFFFFFu << 0)
#define WATCHDOG_CTRL_TIME_Pos					0u

	/* 0x04: Load the watchdog timer. The maximum setting is 0xffffff which corresponds to 0xffffff / 2 ticks before triggering a watchdog reset (see errata RP2040-E1). */
	uint32_t volatile LOAD;
	/*  */
#define WATCHDOG_LOAD_LOAD_Msk					(0xFFFFFFu << 0)
#define WATCHDOG_LOAD_LOAD_Pos					0u

	/* 0x08: Logs the reason for the last reset. */
	uint32_t volatile REASON;
	/*  */
#define WATCHDOG_REASON_FORCE					(1u << 1)
	/*  */
#define WATCHDOG_REASON_TIMER					(1u << 0)

	/* 0x0C: Scratch register. */
	uint32_t volatile SCRATCH0;

	/* 0x10: Scratch register. */
	uint32_t volatile SCRATCH1;

	/* 0x14: Scratch register. */
	uint32_t volatile SCRATCH2;

	/* 0x18: Scratch register. */
	uint32_t volatile SCRATCH3;

	/* 0x1C: Scratch register. */
	uint32_t volatile SCRATCH4;

	/* 0x20: Scratch register. */
	uint32_t volatile SCRATCH5;

	/* 0x24: Scratch register. */
	uint32_t volatile SCRATCH6;

	/* 0x28: Scratch register. */
	uint32_t volatile SCRATCH7;

	/* 0x2C: Controls the tick generator */
	uint32_t volatile TICK;
	/* Count down timer: the remaining number clk_tick cycles before the next tick is generated. */
#define WATCHDOG_TICK_COUNT_Msk					(0x1FFu << 11)
#define WATCHDOG_TICK_COUNT_Pos					11u
	/* Is the tick generator running? */
#define WATCHDOG_TICK_RUNNING					(1u << 10)
	/* start / stop tick generation */
#define WATCHDOG_TICK_ENABLE					(1u << 9)
	/* Total number of clk_tick cycles before the next tick. */
#define WATCHDOG_TICK_CYCLES_Msk				(0x1FFu << 0)
#define WATCHDOG_TICK_CYCLES_Pos				0u

};


#define RTC ((struct mcu_rtc *)0x4005C000)

struct mcu_rtc {

	/* 0x00: Divider minus 1 for the 1 second counter. */
	uint32_t volatile CLKDIV_M1;
	/*  */
#define RTC_CLKDIV_M1_CLKDIV_M1_Msk				(0xFFFFu << 0)
#define RTC_CLKDIV_M1_CLKDIV_M1_Pos				0u

	/* 0x04: RTC setup register 0 */
	uint32_t volatile SETUP_0;
	/* Year */
#define RTC_SETUP_0_YEAR_Msk					(0xFFFu << 12)
#define RTC_SETUP_0_YEAR_Pos					12u
	/* Month (1..12) */
#define RTC_SETUP_0_MONTH_Msk					(0xFu << 8)
#define RTC_SETUP_0_MONTH_Pos					8u
	/* Day of the month (1..31) */
#define RTC_SETUP_0_DAY_Msk					(0x1Fu << 0)
#define RTC_SETUP_0_DAY_Pos					0u

	/* 0x08: RTC setup register 1 */
	uint32_t volatile SETUP_1;
	/* Day of the week: 1-Monday...0-Sunday ISO 8601 mod 7 */
#define RTC_SETUP_1_DOTW_Msk					(0x7u << 24)
#define RTC_SETUP_1_DOTW_Pos					24u
	/* Hours */
#define RTC_SETUP_1_HOUR_Msk					(0x1Fu << 16)
#define RTC_SETUP_1_HOUR_Pos					16u
	/* Minutes */
#define RTC_SETUP_1_MIN_Msk					(0x3Fu << 8)
#define RTC_SETUP_1_MIN_Pos					8u
	/* Seconds */
#define RTC_SETUP_1_SEC_Msk					(0x3Fu << 0)
#define RTC_SETUP_1_SEC_Pos					0u

	/* 0x0C: RTC Control and status */
	uint32_t volatile CTRL;
	/* If set, leapyear is forced off. */
#define RTC_CTRL_FORCE_NOTLEAPYEAR				(1u << 8)
	/* Load RTC */
#define RTC_CTRL_LOAD						(1u << 4)
	/* RTC enabled (running) */
#define RTC_CTRL_RTC_ACTIVE					(1u << 1)
	/* Enable RTC */
#define RTC_CTRL_RTC_ENABLE					(1u << 0)

	/* 0x10: Interrupt setup register 0 */
	uint32_t volatile IRQ_SETUP_0;
	/*  */
#define RTC_IRQ_SETUP_0_MATCH_ACTIVE				(1u << 29)
	/* Global match enable. */
#define RTC_IRQ_SETUP_0_MATCH_ENA				(1u << 28)
	/* Enable year matching */
#define RTC_IRQ_SETUP_0_YEAR_ENA				(1u << 26)
	/* Enable month matching */
#define RTC_IRQ_SETUP_0_MONTH_ENA				(1u << 25)
	/* Enable day matching */
#define RTC_IRQ_SETUP_0_DAY_ENA					(1u << 24)
	/* Year */
#define RTC_IRQ_SETUP_0_YEAR_Msk				(0xFFFu << 12)
#define RTC_IRQ_SETUP_0_YEAR_Pos				12u
	/* Month (1..12) */
#define RTC_IRQ_SETUP_0_MONTH_Msk				(0xFu << 8)
#define RTC_IRQ_SETUP_0_MONTH_Pos				8u
	/* Day of the month (1..31) */
#define RTC_IRQ_SETUP_0_DAY_Msk					(0x1Fu << 0)
#define RTC_IRQ_SETUP_0_DAY_Pos					0u

	/* 0x14: Interrupt setup register 1 */
	uint32_t volatile IRQ_SETUP_1;
	/* Enable day of the week matching */
#define RTC_IRQ_SETUP_1_DOTW_ENA				(1u << 31)
	/* Enable hour matching */
#define RTC_IRQ_SETUP_1_HOUR_ENA				(1u << 30)
	/* Enable minute matching */
#define RTC_IRQ_SETUP_1_MIN_ENA					(1u << 29)
	/* Enable second matching */
#define RTC_IRQ_SETUP_1_SEC_ENA					(1u << 28)
	/* Day of the week */
#define RTC_IRQ_SETUP_1_DOTW_Msk				(0x7u << 24)
#define RTC_IRQ_SETUP_1_DOTW_Pos				24u
	/* Hours */
#define RTC_IRQ_SETUP_1_HOUR_Msk				(0x1Fu << 16)
#define RTC_IRQ_SETUP_1_HOUR_Pos				16u
	/* Minutes */
#define RTC_IRQ_SETUP_1_MIN_Msk					(0x3Fu << 8)
#define RTC_IRQ_SETUP_1_MIN_Pos					8u
	/* Seconds */
#define RTC_IRQ_SETUP_1_SEC_Msk					(0x3Fu << 0)
#define RTC_IRQ_SETUP_1_SEC_Pos					0u

	/* 0x18: RTC register 1. */
	uint32_t volatile RTC_1;
	/* Year */
#define RTC_RTC_1_YEAR_Msk					(0xFFFu << 12)
#define RTC_RTC_1_YEAR_Pos					12u
	/* Month (1..12) */
#define RTC_RTC_1_MONTH_Msk					(0xFu << 8)
#define RTC_RTC_1_MONTH_Pos					8u
	/* Day of the month (1..31) */
#define RTC_RTC_1_DAY_Msk					(0x1Fu << 0)
#define RTC_RTC_1_DAY_Pos					0u

	/* 0x1C: RTC register 0 */
	uint32_t volatile RTC_0;
	/* Day of the week */
#define RTC_RTC_0_DOTW_Msk					(0x7u << 24)
#define RTC_RTC_0_DOTW_Pos					24u
	/* Hours */
#define RTC_RTC_0_HOUR_Msk					(0x1Fu << 16)
#define RTC_RTC_0_HOUR_Pos					16u
	/* Minutes */
#define RTC_RTC_0_MIN_Msk					(0x3Fu << 8)
#define RTC_RTC_0_MIN_Pos					8u
	/* Seconds */
#define RTC_RTC_0_SEC_Msk					(0x3Fu << 0)
#define RTC_RTC_0_SEC_Pos					0u

	/* 0x20: Raw Interrupts */
	uint32_t volatile INTR;
	/*  */
#define RTC_INTR_RTC						(1u << 0)

	/* 0x24: Interrupt Enable */
	uint32_t volatile INTE;
	/*  */
#define RTC_INTE_RTC						(1u << 0)

	/* 0x28: Interrupt Force */
	uint32_t volatile INTF;
	/*  */
#define RTC_INTF_RTC						(1u << 0)

	/* 0x2C: Interrupt status after masking & forcing */
	uint32_t volatile INTS;
	/*  */
#define RTC_INTS_RTC						(1u << 0)

};


#define ROSC ((struct mcu_rosc *)0x40060000)

struct mcu_rosc {

	/* 0x00: Ring Oscillator control */
	uint32_t volatile CTRL;
	/* On power-up this field is initialised to ENABLE */
#define ROSC_CTRL_ENABLE_Msk					(0xFFFu << 12)
#define ROSC_CTRL_ENABLE_Pos					12u
#define ROSC_CTRL_ENABLE_DISABLE				(0xD1Eu << 12)
#define ROSC_CTRL_ENABLE_ENABLE					(0xFABu << 12)
	/* Controls the number of delay stages in the ROSC ring */
#define ROSC_CTRL_FREQ_RANGE_Msk				(0xFFFu << 0)
#define ROSC_CTRL_FREQ_RANGE_Pos				0u
#define ROSC_CTRL_FREQ_RANGE_LOW				(0xFA4u << 0)
#define ROSC_CTRL_FREQ_RANGE_MEDIUM				(0xFA5u << 0)
#define ROSC_CTRL_FREQ_RANGE_HIGH				(0xFA7u << 0)
#define ROSC_CTRL_FREQ_RANGE_TOOHIGH				(0xFA6u << 0)

	/* 0x04: The FREQA & FREQB registers control the frequency by controlling the drive strength of each stage */
	uint32_t volatile FREQA;
	/* Set to 0x9696 to apply the settings */
#define ROSC_FREQA_PASSWD_Msk					(0xFFFFu << 16)
#define ROSC_FREQA_PASSWD_Pos					16u
#define ROSC_FREQA_PASSWD_PASS					(0x9696u << 16)
	/* Stage 3 drive strength */
#define ROSC_FREQA_DS3_Msk					(0x7u << 12)
#define ROSC_FREQA_DS3_Pos					12u
	/* Stage 2 drive strength */
#define ROSC_FREQA_DS2_Msk					(0x7u << 8)
#define ROSC_FREQA_DS2_Pos					8u
	/* Stage 1 drive strength */
#define ROSC_FREQA_DS1_Msk					(0x7u << 4)
#define ROSC_FREQA_DS1_Pos					4u
	/* Stage 0 drive strength */
#define ROSC_FREQA_DS0_Msk					(0x7u << 0)
#define ROSC_FREQA_DS0_Pos					0u

	/* 0x08: For a detailed description see freqa register */
	uint32_t volatile FREQB;
	/* Set to 0x9696 to apply the settings */
#define ROSC_FREQB_PASSWD_Msk					(0xFFFFu << 16)
#define ROSC_FREQB_PASSWD_Pos					16u
#define ROSC_FREQB_PASSWD_PASS					(0x9696u << 16)
	/* Stage 7 drive strength */
#define ROSC_FREQB_DS7_Msk					(0x7u << 12)
#define ROSC_FREQB_DS7_Pos					12u
	/* Stage 6 drive strength */
#define ROSC_FREQB_DS6_Msk					(0x7u << 8)
#define ROSC_FREQB_DS6_Pos					8u
	/* Stage 5 drive strength */
#define ROSC_FREQB_DS5_Msk					(0x7u << 4)
#define ROSC_FREQB_DS5_Pos					4u
	/* Stage 4 drive strength */
#define ROSC_FREQB_DS4_Msk					(0x7u << 0)
#define ROSC_FREQB_DS4_Pos					0u

	/* 0x0C: Ring Oscillator pause control */
	uint32_t volatile DORMANT;

	/* 0x10: Controls the output divider */
	uint32_t volatile DIV;
	/* set to 0xaa0 + div where */
#define ROSC_DIV_DIV_Msk					(0xFFFu << 0)
#define ROSC_DIV_DIV_Pos					0u
#define ROSC_DIV_DIV_PASS					(0xAA0u << 0)

	/* 0x14: Controls the phase shifted output */
	uint32_t volatile PHASE;
	/* set to 0xaa */
#define ROSC_PHASE_PASSWD_Msk					(0xFFu << 4)
#define ROSC_PHASE_PASSWD_Pos					4u
	/* enable the phase-shifted output */
#define ROSC_PHASE_ENABLE					(1u << 3)
	/* invert the phase-shifted output */
#define ROSC_PHASE_FLIP						(1u << 2)
	/* phase shift the phase-shifted output by SHIFT input clocks */
#define ROSC_PHASE_SHIFT_Msk					(0x3u << 0)
#define ROSC_PHASE_SHIFT_Pos					0u

	/* 0x18: Ring Oscillator Status */
	uint32_t volatile STATUS;
	/* Oscillator is running and stable */
#define ROSC_STATUS_STABLE					(1u << 31)
	/* An invalid value has been written to CTRL_ENABLE or CTRL_FREQ_RANGE or FREQA or FREQB or DIV or PHASE or DORMANT */
#define ROSC_STATUS_BADWRITE					(1u << 24)
	/* post-divider is running */
#define ROSC_STATUS_DIV_RUNNING					(1u << 16)
	/* Oscillator is enabled but not necessarily running and stable */
#define ROSC_STATUS_ENABLED					(1u << 12)

	/* 0x1C: This just reads the state of the oscillator output so randomness is compromised if the ring oscillator is stopped or run at a harmonic of the bus frequency */
	uint32_t volatile RANDOMBIT;
	/*  */
#define ROSC_RANDOMBIT_RANDOMBIT				(1u << 0)

	/* 0x20: A down counter running at the ROSC frequency which counts to zero and stops. */
	uint32_t volatile COUNT;
	/*  */
#define ROSC_COUNT_COUNT_Msk					(0xFFu << 0)
#define ROSC_COUNT_COUNT_Pos					0u

};


#define VREG_AND_CHIP_RESET ((struct mcu_vreg_and_chip_reset *)0x40064000)

struct mcu_vreg_and_chip_reset {

	/* 0x00: Voltage regulator control and status */
	uint32_t volatile VREG;
	/* regulation status */
#define VREG_AND_CHIP_RESET_VREG_ROK				(1u << 12)
	/* output voltage select */
#define VREG_AND_CHIP_RESET_VREG_VSEL_Msk			(0xFu << 4)
#define VREG_AND_CHIP_RESET_VREG_VSEL_Pos			4u
	/* high impedance mode select */
#define VREG_AND_CHIP_RESET_VREG_HIZ				(1u << 1)
	/* enable */
#define VREG_AND_CHIP_RESET_VREG_EN				(1u << 0)

	/* 0x04: brown-out detection control */
	uint32_t volatile BOD;
	/* threshold select */
#define VREG_AND_CHIP_RESET_BOD_VSEL_Msk			(0xFu << 4)
#define VREG_AND_CHIP_RESET_BOD_VSEL_Pos			4u
	/* enable */
#define VREG_AND_CHIP_RESET_BOD_EN				(1u << 0)

	/* 0x08: Chip reset control and status */
	uint32_t volatile CHIP_RESET;
	/* This is set by psm_restart from the debugger. */
#define VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG		(1u << 24)
	/* Last reset was from the debug port */
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART		(1u << 20)
	/* Last reset was from the RUN pin */
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN			(1u << 16)
	/* Last reset was from the power-on reset or brown-out detection blocks */
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR			(1u << 8)

};


#define TBMAN ((struct mcu_tbman *)0x4006C000)

struct mcu_tbman {

	/* 0x00: Indicates the type of platform in use */
	uint32_t volatile PLATFORM;
	/* Indicates the platform is an FPGA */
#define TBMAN_PLATFORM_FPGA					(1u << 1)
	/* Indicates the platform is an ASIC */
#define TBMAN_PLATFORM_ASIC					(1u << 0)

};


#define DMA ((struct mcu_dma *)0x50000000)

struct mcu_dma {

	/* 0x00: DMA Channel 0 Read Address pointer */
	uint32_t volatile CH0_READ_ADDR;

	/* 0x04: DMA Channel 0 Write Address pointer */
	uint32_t volatile CH0_WRITE_ADDR;

	/* 0x08: DMA Channel 0 Transfer Count */
	uint32_t volatile CH0_TRANS_COUNT;

	/* 0x0C: DMA Channel 0 Control and Status */
	uint32_t volatile CH0_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH0_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH0_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH0_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH0_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH0_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH0_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH0_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH0_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH0_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH0_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH0_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH0_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH0_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH0_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH0_CTRL_TRIG_EN					(1u << 0)

	/* 0x10: Alias for channel 0 CTRL register */
	uint32_t volatile CH0_AL1_CTRL;

	/* 0x14: Alias for channel 0 READ_ADDR register */
	uint32_t volatile CH0_AL1_READ_ADDR;

	/* 0x18: Alias for channel 0 WRITE_ADDR register */
	uint32_t volatile CH0_AL1_WRITE_ADDR;

	/* 0x1C: Alias for channel 0 TRANS_COUNT register */
	uint32_t volatile CH0_AL1_TRANS_COUNT_TRIG;

	/* 0x20: Alias for channel 0 CTRL register */
	uint32_t volatile CH0_AL2_CTRL;

	/* 0x24: Alias for channel 0 TRANS_COUNT register */
	uint32_t volatile CH0_AL2_TRANS_COUNT;

	/* 0x28: Alias for channel 0 READ_ADDR register */
	uint32_t volatile CH0_AL2_READ_ADDR;

	/* 0x2C: Alias for channel 0 WRITE_ADDR register */
	uint32_t volatile CH0_AL2_WRITE_ADDR_TRIG;

	/* 0x30: Alias for channel 0 CTRL register */
	uint32_t volatile CH0_AL3_CTRL;

	/* 0x34: Alias for channel 0 WRITE_ADDR register */
	uint32_t volatile CH0_AL3_WRITE_ADDR;

	/* 0x38: Alias for channel 0 TRANS_COUNT register */
	uint32_t volatile CH0_AL3_TRANS_COUNT;

	/* 0x3C: Alias for channel 0 READ_ADDR register */
	uint32_t volatile CH0_AL3_READ_ADDR_TRIG;

	/* 0x40: DMA Channel 1 Read Address pointer */
	uint32_t volatile CH1_READ_ADDR;

	/* 0x44: DMA Channel 1 Write Address pointer */
	uint32_t volatile CH1_WRITE_ADDR;

	/* 0x48: DMA Channel 1 Transfer Count */
	uint32_t volatile CH1_TRANS_COUNT;

	/* 0x4C: DMA Channel 1 Control and Status */
	uint32_t volatile CH1_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH1_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH1_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH1_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH1_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH1_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH1_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH1_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH1_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH1_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH1_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH1_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH1_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH1_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH1_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH1_CTRL_TRIG_EN					(1u << 0)

	/* 0x50: Alias for channel 1 CTRL register */
	uint32_t volatile CH1_AL1_CTRL;

	/* 0x54: Alias for channel 1 READ_ADDR register */
	uint32_t volatile CH1_AL1_READ_ADDR;

	/* 0x58: Alias for channel 1 WRITE_ADDR register */
	uint32_t volatile CH1_AL1_WRITE_ADDR;

	/* 0x5C: Alias for channel 1 TRANS_COUNT register */
	uint32_t volatile CH1_AL1_TRANS_COUNT_TRIG;

	/* 0x60: Alias for channel 1 CTRL register */
	uint32_t volatile CH1_AL2_CTRL;

	/* 0x64: Alias for channel 1 TRANS_COUNT register */
	uint32_t volatile CH1_AL2_TRANS_COUNT;

	/* 0x68: Alias for channel 1 READ_ADDR register */
	uint32_t volatile CH1_AL2_READ_ADDR;

	/* 0x6C: Alias for channel 1 WRITE_ADDR register */
	uint32_t volatile CH1_AL2_WRITE_ADDR_TRIG;

	/* 0x70: Alias for channel 1 CTRL register */
	uint32_t volatile CH1_AL3_CTRL;

	/* 0x74: Alias for channel 1 WRITE_ADDR register */
	uint32_t volatile CH1_AL3_WRITE_ADDR;

	/* 0x78: Alias for channel 1 TRANS_COUNT register */
	uint32_t volatile CH1_AL3_TRANS_COUNT;

	/* 0x7C: Alias for channel 1 READ_ADDR register */
	uint32_t volatile CH1_AL3_READ_ADDR_TRIG;

	/* 0x80: DMA Channel 2 Read Address pointer */
	uint32_t volatile CH2_READ_ADDR;

	/* 0x84: DMA Channel 2 Write Address pointer */
	uint32_t volatile CH2_WRITE_ADDR;

	/* 0x88: DMA Channel 2 Transfer Count */
	uint32_t volatile CH2_TRANS_COUNT;

	/* 0x8C: DMA Channel 2 Control and Status */
	uint32_t volatile CH2_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH2_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH2_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH2_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH2_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH2_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH2_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH2_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH2_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH2_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH2_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH2_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH2_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH2_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH2_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH2_CTRL_TRIG_EN					(1u << 0)

	/* 0x90: Alias for channel 2 CTRL register */
	uint32_t volatile CH2_AL1_CTRL;

	/* 0x94: Alias for channel 2 READ_ADDR register */
	uint32_t volatile CH2_AL1_READ_ADDR;

	/* 0x98: Alias for channel 2 WRITE_ADDR register */
	uint32_t volatile CH2_AL1_WRITE_ADDR;

	/* 0x9C: Alias for channel 2 TRANS_COUNT register */
	uint32_t volatile CH2_AL1_TRANS_COUNT_TRIG;

	/* 0xA0: Alias for channel 2 CTRL register */
	uint32_t volatile CH2_AL2_CTRL;

	/* 0xA4: Alias for channel 2 TRANS_COUNT register */
	uint32_t volatile CH2_AL2_TRANS_COUNT;

	/* 0xA8: Alias for channel 2 READ_ADDR register */
	uint32_t volatile CH2_AL2_READ_ADDR;

	/* 0xAC: Alias for channel 2 WRITE_ADDR register */
	uint32_t volatile CH2_AL2_WRITE_ADDR_TRIG;

	/* 0xB0: Alias for channel 2 CTRL register */
	uint32_t volatile CH2_AL3_CTRL;

	/* 0xB4: Alias for channel 2 WRITE_ADDR register */
	uint32_t volatile CH2_AL3_WRITE_ADDR;

	/* 0xB8: Alias for channel 2 TRANS_COUNT register */
	uint32_t volatile CH2_AL3_TRANS_COUNT;

	/* 0xBC: Alias for channel 2 READ_ADDR register */
	uint32_t volatile CH2_AL3_READ_ADDR_TRIG;

	/* 0xC0: DMA Channel 3 Read Address pointer */
	uint32_t volatile CH3_READ_ADDR;

	/* 0xC4: DMA Channel 3 Write Address pointer */
	uint32_t volatile CH3_WRITE_ADDR;

	/* 0xC8: DMA Channel 3 Transfer Count */
	uint32_t volatile CH3_TRANS_COUNT;

	/* 0xCC: DMA Channel 3 Control and Status */
	uint32_t volatile CH3_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH3_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH3_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH3_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH3_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH3_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH3_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH3_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH3_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH3_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH3_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH3_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH3_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH3_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH3_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH3_CTRL_TRIG_EN					(1u << 0)

	/* 0xD0: Alias for channel 3 CTRL register */
	uint32_t volatile CH3_AL1_CTRL;

	/* 0xD4: Alias for channel 3 READ_ADDR register */
	uint32_t volatile CH3_AL1_READ_ADDR;

	/* 0xD8: Alias for channel 3 WRITE_ADDR register */
	uint32_t volatile CH3_AL1_WRITE_ADDR;

	/* 0xDC: Alias for channel 3 TRANS_COUNT register */
	uint32_t volatile CH3_AL1_TRANS_COUNT_TRIG;

	/* 0xE0: Alias for channel 3 CTRL register */
	uint32_t volatile CH3_AL2_CTRL;

	/* 0xE4: Alias for channel 3 TRANS_COUNT register */
	uint32_t volatile CH3_AL2_TRANS_COUNT;

	/* 0xE8: Alias for channel 3 READ_ADDR register */
	uint32_t volatile CH3_AL2_READ_ADDR;

	/* 0xEC: Alias for channel 3 WRITE_ADDR register */
	uint32_t volatile CH3_AL2_WRITE_ADDR_TRIG;

	/* 0xF0: Alias for channel 3 CTRL register */
	uint32_t volatile CH3_AL3_CTRL;

	/* 0xF4: Alias for channel 3 WRITE_ADDR register */
	uint32_t volatile CH3_AL3_WRITE_ADDR;

	/* 0xF8: Alias for channel 3 TRANS_COUNT register */
	uint32_t volatile CH3_AL3_TRANS_COUNT;

	/* 0xFC: Alias for channel 3 READ_ADDR register */
	uint32_t volatile CH3_AL3_READ_ADDR_TRIG;

	/* 0x100: DMA Channel 4 Read Address pointer */
	uint32_t volatile CH4_READ_ADDR;

	/* 0x104: DMA Channel 4 Write Address pointer */
	uint32_t volatile CH4_WRITE_ADDR;

	/* 0x108: DMA Channel 4 Transfer Count */
	uint32_t volatile CH4_TRANS_COUNT;

	/* 0x10C: DMA Channel 4 Control and Status */
	uint32_t volatile CH4_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH4_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH4_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH4_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH4_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH4_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH4_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH4_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH4_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH4_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH4_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH4_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH4_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH4_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH4_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH4_CTRL_TRIG_EN					(1u << 0)

	/* 0x110: Alias for channel 4 CTRL register */
	uint32_t volatile CH4_AL1_CTRL;

	/* 0x114: Alias for channel 4 READ_ADDR register */
	uint32_t volatile CH4_AL1_READ_ADDR;

	/* 0x118: Alias for channel 4 WRITE_ADDR register */
	uint32_t volatile CH4_AL1_WRITE_ADDR;

	/* 0x11C: Alias for channel 4 TRANS_COUNT register */
	uint32_t volatile CH4_AL1_TRANS_COUNT_TRIG;

	/* 0x120: Alias for channel 4 CTRL register */
	uint32_t volatile CH4_AL2_CTRL;

	/* 0x124: Alias for channel 4 TRANS_COUNT register */
	uint32_t volatile CH4_AL2_TRANS_COUNT;

	/* 0x128: Alias for channel 4 READ_ADDR register */
	uint32_t volatile CH4_AL2_READ_ADDR;

	/* 0x12C: Alias for channel 4 WRITE_ADDR register */
	uint32_t volatile CH4_AL2_WRITE_ADDR_TRIG;

	/* 0x130: Alias for channel 4 CTRL register */
	uint32_t volatile CH4_AL3_CTRL;

	/* 0x134: Alias for channel 4 WRITE_ADDR register */
	uint32_t volatile CH4_AL3_WRITE_ADDR;

	/* 0x138: Alias for channel 4 TRANS_COUNT register */
	uint32_t volatile CH4_AL3_TRANS_COUNT;

	/* 0x13C: Alias for channel 4 READ_ADDR register */
	uint32_t volatile CH4_AL3_READ_ADDR_TRIG;

	/* 0x140: DMA Channel 5 Read Address pointer */
	uint32_t volatile CH5_READ_ADDR;

	/* 0x144: DMA Channel 5 Write Address pointer */
	uint32_t volatile CH5_WRITE_ADDR;

	/* 0x148: DMA Channel 5 Transfer Count */
	uint32_t volatile CH5_TRANS_COUNT;

	/* 0x14C: DMA Channel 5 Control and Status */
	uint32_t volatile CH5_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH5_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH5_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH5_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH5_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH5_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH5_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH5_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH5_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH5_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH5_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH5_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH5_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH5_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH5_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH5_CTRL_TRIG_EN					(1u << 0)

	/* 0x150: Alias for channel 5 CTRL register */
	uint32_t volatile CH5_AL1_CTRL;

	/* 0x154: Alias for channel 5 READ_ADDR register */
	uint32_t volatile CH5_AL1_READ_ADDR;

	/* 0x158: Alias for channel 5 WRITE_ADDR register */
	uint32_t volatile CH5_AL1_WRITE_ADDR;

	/* 0x15C: Alias for channel 5 TRANS_COUNT register */
	uint32_t volatile CH5_AL1_TRANS_COUNT_TRIG;

	/* 0x160: Alias for channel 5 CTRL register */
	uint32_t volatile CH5_AL2_CTRL;

	/* 0x164: Alias for channel 5 TRANS_COUNT register */
	uint32_t volatile CH5_AL2_TRANS_COUNT;

	/* 0x168: Alias for channel 5 READ_ADDR register */
	uint32_t volatile CH5_AL2_READ_ADDR;

	/* 0x16C: Alias for channel 5 WRITE_ADDR register */
	uint32_t volatile CH5_AL2_WRITE_ADDR_TRIG;

	/* 0x170: Alias for channel 5 CTRL register */
	uint32_t volatile CH5_AL3_CTRL;

	/* 0x174: Alias for channel 5 WRITE_ADDR register */
	uint32_t volatile CH5_AL3_WRITE_ADDR;

	/* 0x178: Alias for channel 5 TRANS_COUNT register */
	uint32_t volatile CH5_AL3_TRANS_COUNT;

	/* 0x17C: Alias for channel 5 READ_ADDR register */
	uint32_t volatile CH5_AL3_READ_ADDR_TRIG;

	/* 0x180: DMA Channel 6 Read Address pointer */
	uint32_t volatile CH6_READ_ADDR;

	/* 0x184: DMA Channel 6 Write Address pointer */
	uint32_t volatile CH6_WRITE_ADDR;

	/* 0x188: DMA Channel 6 Transfer Count */
	uint32_t volatile CH6_TRANS_COUNT;

	/* 0x18C: DMA Channel 6 Control and Status */
	uint32_t volatile CH6_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH6_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH6_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH6_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH6_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH6_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH6_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH6_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH6_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH6_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH6_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH6_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH6_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH6_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH6_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH6_CTRL_TRIG_EN					(1u << 0)

	/* 0x190: Alias for channel 6 CTRL register */
	uint32_t volatile CH6_AL1_CTRL;

	/* 0x194: Alias for channel 6 READ_ADDR register */
	uint32_t volatile CH6_AL1_READ_ADDR;

	/* 0x198: Alias for channel 6 WRITE_ADDR register */
	uint32_t volatile CH6_AL1_WRITE_ADDR;

	/* 0x19C: Alias for channel 6 TRANS_COUNT register */
	uint32_t volatile CH6_AL1_TRANS_COUNT_TRIG;

	/* 0x1A0: Alias for channel 6 CTRL register */
	uint32_t volatile CH6_AL2_CTRL;

	/* 0x1A4: Alias for channel 6 TRANS_COUNT register */
	uint32_t volatile CH6_AL2_TRANS_COUNT;

	/* 0x1A8: Alias for channel 6 READ_ADDR register */
	uint32_t volatile CH6_AL2_READ_ADDR;

	/* 0x1AC: Alias for channel 6 WRITE_ADDR register */
	uint32_t volatile CH6_AL2_WRITE_ADDR_TRIG;

	/* 0x1B0: Alias for channel 6 CTRL register */
	uint32_t volatile CH6_AL3_CTRL;

	/* 0x1B4: Alias for channel 6 WRITE_ADDR register */
	uint32_t volatile CH6_AL3_WRITE_ADDR;

	/* 0x1B8: Alias for channel 6 TRANS_COUNT register */
	uint32_t volatile CH6_AL3_TRANS_COUNT;

	/* 0x1BC: Alias for channel 6 READ_ADDR register */
	uint32_t volatile CH6_AL3_READ_ADDR_TRIG;

	/* 0x1C0: DMA Channel 7 Read Address pointer */
	uint32_t volatile CH7_READ_ADDR;

	/* 0x1C4: DMA Channel 7 Write Address pointer */
	uint32_t volatile CH7_WRITE_ADDR;

	/* 0x1C8: DMA Channel 7 Transfer Count */
	uint32_t volatile CH7_TRANS_COUNT;

	/* 0x1CC: DMA Channel 7 Control and Status */
	uint32_t volatile CH7_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH7_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH7_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH7_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH7_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH7_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH7_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH7_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH7_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH7_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH7_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH7_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH7_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH7_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH7_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH7_CTRL_TRIG_EN					(1u << 0)

	/* 0x1D0: Alias for channel 7 CTRL register */
	uint32_t volatile CH7_AL1_CTRL;

	/* 0x1D4: Alias for channel 7 READ_ADDR register */
	uint32_t volatile CH7_AL1_READ_ADDR;

	/* 0x1D8: Alias for channel 7 WRITE_ADDR register */
	uint32_t volatile CH7_AL1_WRITE_ADDR;

	/* 0x1DC: Alias for channel 7 TRANS_COUNT register */
	uint32_t volatile CH7_AL1_TRANS_COUNT_TRIG;

	/* 0x1E0: Alias for channel 7 CTRL register */
	uint32_t volatile CH7_AL2_CTRL;

	/* 0x1E4: Alias for channel 7 TRANS_COUNT register */
	uint32_t volatile CH7_AL2_TRANS_COUNT;

	/* 0x1E8: Alias for channel 7 READ_ADDR register */
	uint32_t volatile CH7_AL2_READ_ADDR;

	/* 0x1EC: Alias for channel 7 WRITE_ADDR register */
	uint32_t volatile CH7_AL2_WRITE_ADDR_TRIG;

	/* 0x1F0: Alias for channel 7 CTRL register */
	uint32_t volatile CH7_AL3_CTRL;

	/* 0x1F4: Alias for channel 7 WRITE_ADDR register */
	uint32_t volatile CH7_AL3_WRITE_ADDR;

	/* 0x1F8: Alias for channel 7 TRANS_COUNT register */
	uint32_t volatile CH7_AL3_TRANS_COUNT;

	/* 0x1FC: Alias for channel 7 READ_ADDR register */
	uint32_t volatile CH7_AL3_READ_ADDR_TRIG;

	/* 0x200: DMA Channel 8 Read Address pointer */
	uint32_t volatile CH8_READ_ADDR;

	/* 0x204: DMA Channel 8 Write Address pointer */
	uint32_t volatile CH8_WRITE_ADDR;

	/* 0x208: DMA Channel 8 Transfer Count */
	uint32_t volatile CH8_TRANS_COUNT;

	/* 0x20C: DMA Channel 8 Control and Status */
	uint32_t volatile CH8_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH8_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH8_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH8_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH8_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH8_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH8_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH8_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH8_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH8_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH8_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH8_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH8_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH8_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH8_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH8_CTRL_TRIG_EN					(1u << 0)

	/* 0x210: Alias for channel 8 CTRL register */
	uint32_t volatile CH8_AL1_CTRL;

	/* 0x214: Alias for channel 8 READ_ADDR register */
	uint32_t volatile CH8_AL1_READ_ADDR;

	/* 0x218: Alias for channel 8 WRITE_ADDR register */
	uint32_t volatile CH8_AL1_WRITE_ADDR;

	/* 0x21C: Alias for channel 8 TRANS_COUNT register */
	uint32_t volatile CH8_AL1_TRANS_COUNT_TRIG;

	/* 0x220: Alias for channel 8 CTRL register */
	uint32_t volatile CH8_AL2_CTRL;

	/* 0x224: Alias for channel 8 TRANS_COUNT register */
	uint32_t volatile CH8_AL2_TRANS_COUNT;

	/* 0x228: Alias for channel 8 READ_ADDR register */
	uint32_t volatile CH8_AL2_READ_ADDR;

	/* 0x22C: Alias for channel 8 WRITE_ADDR register */
	uint32_t volatile CH8_AL2_WRITE_ADDR_TRIG;

	/* 0x230: Alias for channel 8 CTRL register */
	uint32_t volatile CH8_AL3_CTRL;

	/* 0x234: Alias for channel 8 WRITE_ADDR register */
	uint32_t volatile CH8_AL3_WRITE_ADDR;

	/* 0x238: Alias for channel 8 TRANS_COUNT register */
	uint32_t volatile CH8_AL3_TRANS_COUNT;

	/* 0x23C: Alias for channel 8 READ_ADDR register */
	uint32_t volatile CH8_AL3_READ_ADDR_TRIG;

	/* 0x240: DMA Channel 9 Read Address pointer */
	uint32_t volatile CH9_READ_ADDR;

	/* 0x244: DMA Channel 9 Write Address pointer */
	uint32_t volatile CH9_WRITE_ADDR;

	/* 0x248: DMA Channel 9 Transfer Count */
	uint32_t volatile CH9_TRANS_COUNT;

	/* 0x24C: DMA Channel 9 Control and Status */
	uint32_t volatile CH9_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH9_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH9_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH9_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH9_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH9_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH9_CTRL_TRIG_BSWAP					(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH9_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH9_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH9_CTRL_TRIG_RING_SIZE_Msk				(0xFu << 6)
#define DMA_CH9_CTRL_TRIG_RING_SIZE_Pos				6u
#define DMA_CH9_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH9_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH9_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_Msk				(0x3u << 2)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_Pos				2u
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH9_CTRL_TRIG_HIGH_PRIORITY				(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH9_CTRL_TRIG_EN					(1u << 0)

	/* 0x250: Alias for channel 9 CTRL register */
	uint32_t volatile CH9_AL1_CTRL;

	/* 0x254: Alias for channel 9 READ_ADDR register */
	uint32_t volatile CH9_AL1_READ_ADDR;

	/* 0x258: Alias for channel 9 WRITE_ADDR register */
	uint32_t volatile CH9_AL1_WRITE_ADDR;

	/* 0x25C: Alias for channel 9 TRANS_COUNT register */
	uint32_t volatile CH9_AL1_TRANS_COUNT_TRIG;

	/* 0x260: Alias for channel 9 CTRL register */
	uint32_t volatile CH9_AL2_CTRL;

	/* 0x264: Alias for channel 9 TRANS_COUNT register */
	uint32_t volatile CH9_AL2_TRANS_COUNT;

	/* 0x268: Alias for channel 9 READ_ADDR register */
	uint32_t volatile CH9_AL2_READ_ADDR;

	/* 0x26C: Alias for channel 9 WRITE_ADDR register */
	uint32_t volatile CH9_AL2_WRITE_ADDR_TRIG;

	/* 0x270: Alias for channel 9 CTRL register */
	uint32_t volatile CH9_AL3_CTRL;

	/* 0x274: Alias for channel 9 WRITE_ADDR register */
	uint32_t volatile CH9_AL3_WRITE_ADDR;

	/* 0x278: Alias for channel 9 TRANS_COUNT register */
	uint32_t volatile CH9_AL3_TRANS_COUNT;

	/* 0x27C: Alias for channel 9 READ_ADDR register */
	uint32_t volatile CH9_AL3_READ_ADDR_TRIG;

	/* 0x280: DMA Channel 10 Read Address pointer */
	uint32_t volatile CH10_READ_ADDR;

	/* 0x284: DMA Channel 10 Write Address pointer */
	uint32_t volatile CH10_WRITE_ADDR;

	/* 0x288: DMA Channel 10 Transfer Count */
	uint32_t volatile CH10_TRANS_COUNT;

	/* 0x28C: DMA Channel 10 Control and Status */
	uint32_t volatile CH10_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH10_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH10_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH10_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH10_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH10_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH10_CTRL_TRIG_BSWAP				(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH10_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH10_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH10_CTRL_TRIG_RING_SIZE_Msk			(0xFu << 6)
#define DMA_CH10_CTRL_TRIG_RING_SIZE_Pos			6u
#define DMA_CH10_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH10_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH10_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_Msk			(0x3u << 2)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_Pos			2u
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH10_CTRL_TRIG_HIGH_PRIORITY			(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH10_CTRL_TRIG_EN					(1u << 0)

	/* 0x290: Alias for channel 10 CTRL register */
	uint32_t volatile CH10_AL1_CTRL;

	/* 0x294: Alias for channel 10 READ_ADDR register */
	uint32_t volatile CH10_AL1_READ_ADDR;

	/* 0x298: Alias for channel 10 WRITE_ADDR register */
	uint32_t volatile CH10_AL1_WRITE_ADDR;

	/* 0x29C: Alias for channel 10 TRANS_COUNT register */
	uint32_t volatile CH10_AL1_TRANS_COUNT_TRIG;

	/* 0x2A0: Alias for channel 10 CTRL register */
	uint32_t volatile CH10_AL2_CTRL;

	/* 0x2A4: Alias for channel 10 TRANS_COUNT register */
	uint32_t volatile CH10_AL2_TRANS_COUNT;

	/* 0x2A8: Alias for channel 10 READ_ADDR register */
	uint32_t volatile CH10_AL2_READ_ADDR;

	/* 0x2AC: Alias for channel 10 WRITE_ADDR register */
	uint32_t volatile CH10_AL2_WRITE_ADDR_TRIG;

	/* 0x2B0: Alias for channel 10 CTRL register */
	uint32_t volatile CH10_AL3_CTRL;

	/* 0x2B4: Alias for channel 10 WRITE_ADDR register */
	uint32_t volatile CH10_AL3_WRITE_ADDR;

	/* 0x2B8: Alias for channel 10 TRANS_COUNT register */
	uint32_t volatile CH10_AL3_TRANS_COUNT;

	/* 0x2BC: Alias for channel 10 READ_ADDR register */
	uint32_t volatile CH10_AL3_READ_ADDR_TRIG;

	/* 0x2C0: DMA Channel 11 Read Address pointer */
	uint32_t volatile CH11_READ_ADDR;

	/* 0x2C4: DMA Channel 11 Write Address pointer */
	uint32_t volatile CH11_WRITE_ADDR;

	/* 0x2C8: DMA Channel 11 Transfer Count */
	uint32_t volatile CH11_TRANS_COUNT;

	/* 0x2CC: DMA Channel 11 Control and Status */
	uint32_t volatile CH11_CTRL_TRIG;
	/* Logical OR of the READ_ERROR and WRITE_ERROR flags. */
#define DMA_CH11_CTRL_TRIG_AHB_ERROR				(1u << 31)
	/* If 1, the channel received a read bus error. */
#define DMA_CH11_CTRL_TRIG_READ_ERROR				(1u << 30)
	/* If 1, the channel received a write bus error. */
#define DMA_CH11_CTRL_TRIG_WRITE_ERROR				(1u << 29)
	/* This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. */
#define DMA_CH11_CTRL_TRIG_BUSY					(1u << 24)
	/* If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. */
#define DMA_CH11_CTRL_TRIG_SNIFF_EN				(1u << 23)
	/* Apply byte-swap transformation to DMA data. */
#define DMA_CH11_CTRL_TRIG_BSWAP				(1u << 22)
	/* In QUIET mode, the channel does not generate IRQs at the end of every transfer block. */
#define DMA_CH11_CTRL_TRIG_IRQ_QUIET				(1u << 21)
	/* Select a Transfer Request signal. */
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_Msk				(0x3Fu << 15)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_Pos				15u
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_TIMER0			(0x3Bu << 15)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_TIMER1			(0x3Cu << 15)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_TIMER2			(0x3Du << 15)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_TIMER3			(0x3Eu << 15)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_PERMANENT			(0x3Fu << 15)
	/* When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_. */
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_Msk				(0xFu << 11)
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_Pos				11u
	/* Select whether RING_SIZE applies to read or write addresses. */
#define DMA_CH11_CTRL_TRIG_RING_SEL				(1u << 10)
	/* Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers. */
#define DMA_CH11_CTRL_TRIG_RING_SIZE_Msk			(0xFu << 6)
#define DMA_CH11_CTRL_TRIG_RING_SIZE_Pos			6u
#define DMA_CH11_CTRL_TRIG_RING_SIZE_RING_NONE			(0x0u << 6)
	/* If 1, the write address increments with each transfer. */
#define DMA_CH11_CTRL_TRIG_INCR_WRITE				(1u << 5)
	/* If 1, the read address increments with each transfer. */
#define DMA_CH11_CTRL_TRIG_INCR_READ				(1u << 4)
	/* Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer. */
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_Msk			(0x3u << 2)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_Pos			2u
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_SIZE_BYTE			(0x0u << 2)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_SIZE_HALFWORD		(0x1u << 2)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_SIZE_WORD			(0x2u << 2)
	/* HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels. */
#define DMA_CH11_CTRL_TRIG_HIGH_PRIORITY			(1u << 1)
	/* DMA Channel Enable. */
#define DMA_CH11_CTRL_TRIG_EN					(1u << 0)

	/* 0x2D0: Alias for channel 11 CTRL register */
	uint32_t volatile CH11_AL1_CTRL;

	/* 0x2D4: Alias for channel 11 READ_ADDR register */
	uint32_t volatile CH11_AL1_READ_ADDR;

	/* 0x2D8: Alias for channel 11 WRITE_ADDR register */
	uint32_t volatile CH11_AL1_WRITE_ADDR;

	/* 0x2DC: Alias for channel 11 TRANS_COUNT register */
	uint32_t volatile CH11_AL1_TRANS_COUNT_TRIG;

	/* 0x2E0: Alias for channel 11 CTRL register */
	uint32_t volatile CH11_AL2_CTRL;

	/* 0x2E4: Alias for channel 11 TRANS_COUNT register */
	uint32_t volatile CH11_AL2_TRANS_COUNT;

	/* 0x2E8: Alias for channel 11 READ_ADDR register */
	uint32_t volatile CH11_AL2_READ_ADDR;

	/* 0x2EC: Alias for channel 11 WRITE_ADDR register */
	uint32_t volatile CH11_AL2_WRITE_ADDR_TRIG;

	/* 0x2F0: Alias for channel 11 CTRL register */
	uint32_t volatile CH11_AL3_CTRL;

	/* 0x2F4: Alias for channel 11 WRITE_ADDR register */
	uint32_t volatile CH11_AL3_WRITE_ADDR;

	/* 0x2F8: Alias for channel 11 TRANS_COUNT register */
	uint32_t volatile CH11_AL3_TRANS_COUNT;

	/* 0x2FC: Alias for channel 11 READ_ADDR register */
	uint32_t volatile CH11_AL3_READ_ADDR_TRIG;

	/* 0x300 */
	uint8_t RESERVED0[0x400u-0x300u];

	/* 0x400: Interrupt Status (raw) */
	uint32_t volatile INTR;
	/* Raw interrupt status for DMA Channels 0..15. */
#define DMA_INTR_INTR_Msk					(0xFFFFu << 0)
#define DMA_INTR_INTR_Pos					0u

	/* 0x404: Interrupt Enables for IRQ 0 */
	uint32_t volatile INTE0;
	/* Set bit n to pass interrupts from channel n to DMA IRQ 0. */
#define DMA_INTE0_INTE0_Msk					(0xFFFFu << 0)
#define DMA_INTE0_INTE0_Pos					0u

	/* 0x408: Force Interrupts */
	uint32_t volatile INTF0;
	/* Write 1s to force the corresponding bits in INTE0. */
#define DMA_INTF0_INTF0_Msk					(0xFFFFu << 0)
#define DMA_INTF0_INTF0_Pos					0u

	/* 0x40C: Interrupt Status for IRQ 0 */
	uint32_t volatile INTS0;
	/* Indicates active channel interrupt requests which are currently causing IRQ 0 to be asserted. */
#define DMA_INTS0_INTS0_Msk					(0xFFFFu << 0)
#define DMA_INTS0_INTS0_Pos					0u

	/* 0x410 */
	uint8_t RESERVED1[0x414u-0x410u];

	/* 0x414: Interrupt Enables for IRQ 1 */
	uint32_t volatile INTE1;
	/* Set bit n to pass interrupts from channel n to DMA IRQ 1. */
#define DMA_INTE1_INTE1_Msk					(0xFFFFu << 0)
#define DMA_INTE1_INTE1_Pos					0u

	/* 0x418: Force Interrupts for IRQ 1 */
	uint32_t volatile INTF1;
	/* Write 1s to force the corresponding bits in INTE0. */
#define DMA_INTF1_INTF1_Msk					(0xFFFFu << 0)
#define DMA_INTF1_INTF1_Pos					0u

	/* 0x41C: Interrupt Status (masked) for IRQ 1 */
	uint32_t volatile INTS1;
	/* Indicates active channel interrupt requests which are currently causing IRQ 1 to be asserted. */
#define DMA_INTS1_INTS1_Msk					(0xFFFFu << 0)
#define DMA_INTS1_INTS1_Pos					0u

	/* 0x420: Pacing (X/Y) Fractional Timer */
	uint32_t volatile TIMER0;
	/* Pacing Timer Dividend. Specifies the X value for the (X/Y) fractional timer. */
#define DMA_TIMER0_X_Msk					(0xFFFFu << 16)
#define DMA_TIMER0_X_Pos					16u
	/* Pacing Timer Divisor. Specifies the Y value for the (X/Y) fractional timer. */
#define DMA_TIMER0_Y_Msk					(0xFFFFu << 0)
#define DMA_TIMER0_Y_Pos					0u

	/* 0x424: Pacing (X/Y) Fractional Timer */
	uint32_t volatile TIMER1;
	/* Pacing Timer Dividend. Specifies the X value for the (X/Y) fractional timer. */
#define DMA_TIMER1_X_Msk					(0xFFFFu << 16)
#define DMA_TIMER1_X_Pos					16u
	/* Pacing Timer Divisor. Specifies the Y value for the (X/Y) fractional timer. */
#define DMA_TIMER1_Y_Msk					(0xFFFFu << 0)
#define DMA_TIMER1_Y_Pos					0u

	/* 0x428: Pacing (X/Y) Fractional Timer */
	uint32_t volatile TIMER2;
	/* Pacing Timer Dividend. Specifies the X value for the (X/Y) fractional timer. */
#define DMA_TIMER2_X_Msk					(0xFFFFu << 16)
#define DMA_TIMER2_X_Pos					16u
	/* Pacing Timer Divisor. Specifies the Y value for the (X/Y) fractional timer. */
#define DMA_TIMER2_Y_Msk					(0xFFFFu << 0)
#define DMA_TIMER2_Y_Pos					0u

	/* 0x42C: Pacing (X/Y) Fractional Timer */
	uint32_t volatile TIMER3;
	/* Pacing Timer Dividend. Specifies the X value for the (X/Y) fractional timer. */
#define DMA_TIMER3_X_Msk					(0xFFFFu << 16)
#define DMA_TIMER3_X_Pos					16u
	/* Pacing Timer Divisor. Specifies the Y value for the (X/Y) fractional timer. */
#define DMA_TIMER3_Y_Msk					(0xFFFFu << 0)
#define DMA_TIMER3_Y_Pos					0u

	/* 0x430: Trigger one or more channels simultaneously */
	uint32_t volatile MULTI_CHAN_TRIGGER;
	/* Each bit in this register corresponds to a DMA channel. */
#define DMA_MULTI_CHAN_TRIGGER_MULTI_CHAN_TRIGGER_Msk		(0xFFFFu << 0)
#define DMA_MULTI_CHAN_TRIGGER_MULTI_CHAN_TRIGGER_Pos		0u

	/* 0x434: Sniffer Control */
	uint32_t volatile SNIFF_CTRL;
	/* If set, the result appears inverted (bitwise complement) when read. */
#define DMA_SNIFF_CTRL_OUT_INV					(1u << 11)
	/* If set, the result appears bit-reversed when read. */
#define DMA_SNIFF_CTRL_OUT_REV					(1u << 10)
	/* Locally perform a byte reverse on the sniffed data, before feeding into checksum. */
#define DMA_SNIFF_CTRL_BSWAP					(1u << 9)
	/*  */
#define DMA_SNIFF_CTRL_CALC_Msk					(0xFu << 5)
#define DMA_SNIFF_CTRL_CALC_Pos					5u
#define DMA_SNIFF_CTRL_CALC_CRC32				(0x0u << 5)
#define DMA_SNIFF_CTRL_CALC_CRC32R				(0x1u << 5)
#define DMA_SNIFF_CTRL_CALC_CRC16				(0x2u << 5)
#define DMA_SNIFF_CTRL_CALC_CRC16R				(0x3u << 5)
#define DMA_SNIFF_CTRL_CALC_EVEN				(0xEu << 5)
#define DMA_SNIFF_CTRL_CALC_SUM					(0xFu << 5)
	/* DMA channel for Sniffer to observe */
#define DMA_SNIFF_CTRL_DMACH_Msk				(0xFu << 1)
#define DMA_SNIFF_CTRL_DMACH_Pos				1u
	/* Enable sniffer */
#define DMA_SNIFF_CTRL_EN					(1u << 0)

	/* 0x438: Data accumulator for sniff hardware */
	uint32_t volatile SNIFF_DATA;

	/* 0x43C */
	uint8_t RESERVED2[0x440u-0x43Cu];

	/* 0x440: Debug RAF, WAF, TDF levels */
	uint32_t volatile FIFO_LEVELS;
	/* Current Read-Address-FIFO fill level */
#define DMA_FIFO_LEVELS_RAF_LVL_Msk				(0xFFu << 16)
#define DMA_FIFO_LEVELS_RAF_LVL_Pos				16u
	/* Current Write-Address-FIFO fill level */
#define DMA_FIFO_LEVELS_WAF_LVL_Msk				(0xFFu << 8)
#define DMA_FIFO_LEVELS_WAF_LVL_Pos				8u
	/* Current Transfer-Data-FIFO fill level */
#define DMA_FIFO_LEVELS_TDF_LVL_Msk				(0xFFu << 0)
#define DMA_FIFO_LEVELS_TDF_LVL_Pos				0u

	/* 0x444: Abort an in-progress transfer sequence on one or more channels */
	uint32_t volatile CHAN_ABORT;
	/* Each bit corresponds to a channel. */
#define DMA_CHAN_ABORT_CHAN_ABORT_Msk				(0xFFFFu << 0)
#define DMA_CHAN_ABORT_CHAN_ABORT_Pos				0u

	/* 0x448: The number of channels this DMA instance is equipped with. */
	uint32_t volatile N_CHANNELS;
	/*  */
#define DMA_N_CHANNELS_N_CHANNELS_Msk				(0x1Fu << 0)
#define DMA_N_CHANNELS_N_CHANNELS_Pos				0u

	/* 0x44C */
	uint8_t RESERVED3[0x800u-0x44Cu];

	/* 0x800: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH0_DBG_CTDREQ;
	/*  */
#define DMA_CH0_DBG_CTDREQ_CH0_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH0_DBG_CTDREQ_CH0_DBG_CTDREQ_Pos			0u

	/* 0x804: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH0_DBG_TCR;

	/* 0x808 */
	uint8_t RESERVED4[0x840u-0x808u];

	/* 0x840: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH1_DBG_CTDREQ;
	/*  */
#define DMA_CH1_DBG_CTDREQ_CH1_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH1_DBG_CTDREQ_CH1_DBG_CTDREQ_Pos			0u

	/* 0x844: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH1_DBG_TCR;

	/* 0x848 */
	uint8_t RESERVED5[0x880u-0x848u];

	/* 0x880: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH2_DBG_CTDREQ;
	/*  */
#define DMA_CH2_DBG_CTDREQ_CH2_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH2_DBG_CTDREQ_CH2_DBG_CTDREQ_Pos			0u

	/* 0x884: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH2_DBG_TCR;

	/* 0x888 */
	uint8_t RESERVED6[0x8C0u-0x888u];

	/* 0x8C0: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH3_DBG_CTDREQ;
	/*  */
#define DMA_CH3_DBG_CTDREQ_CH3_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH3_DBG_CTDREQ_CH3_DBG_CTDREQ_Pos			0u

	/* 0x8C4: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH3_DBG_TCR;

	/* 0x8C8 */
	uint8_t RESERVED7[0x900u-0x8C8u];

	/* 0x900: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH4_DBG_CTDREQ;
	/*  */
#define DMA_CH4_DBG_CTDREQ_CH4_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH4_DBG_CTDREQ_CH4_DBG_CTDREQ_Pos			0u

	/* 0x904: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH4_DBG_TCR;

	/* 0x908 */
	uint8_t RESERVED8[0x940u-0x908u];

	/* 0x940: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH5_DBG_CTDREQ;
	/*  */
#define DMA_CH5_DBG_CTDREQ_CH5_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH5_DBG_CTDREQ_CH5_DBG_CTDREQ_Pos			0u

	/* 0x944: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH5_DBG_TCR;

	/* 0x948 */
	uint8_t RESERVED9[0x980u-0x948u];

	/* 0x980: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH6_DBG_CTDREQ;
	/*  */
#define DMA_CH6_DBG_CTDREQ_CH6_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH6_DBG_CTDREQ_CH6_DBG_CTDREQ_Pos			0u

	/* 0x984: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH6_DBG_TCR;

	/* 0x988 */
	uint8_t RESERVED10[0x9C0u-0x988u];

	/* 0x9C0: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH7_DBG_CTDREQ;
	/*  */
#define DMA_CH7_DBG_CTDREQ_CH7_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH7_DBG_CTDREQ_CH7_DBG_CTDREQ_Pos			0u

	/* 0x9C4: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH7_DBG_TCR;

	/* 0x9C8 */
	uint8_t RESERVED11[0xA00u-0x9C8u];

	/* 0xA00: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH8_DBG_CTDREQ;
	/*  */
#define DMA_CH8_DBG_CTDREQ_CH8_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH8_DBG_CTDREQ_CH8_DBG_CTDREQ_Pos			0u

	/* 0xA04: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH8_DBG_TCR;

	/* 0xA08 */
	uint8_t RESERVED12[0xA40u-0xA08u];

	/* 0xA40: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH9_DBG_CTDREQ;
	/*  */
#define DMA_CH9_DBG_CTDREQ_CH9_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH9_DBG_CTDREQ_CH9_DBG_CTDREQ_Pos			0u

	/* 0xA44: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH9_DBG_TCR;

	/* 0xA48 */
	uint8_t RESERVED13[0xA80u-0xA48u];

	/* 0xA80: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH10_DBG_CTDREQ;
	/*  */
#define DMA_CH10_DBG_CTDREQ_CH10_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH10_DBG_CTDREQ_CH10_DBG_CTDREQ_Pos			0u

	/* 0xA84: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH10_DBG_TCR;

	/* 0xA88 */
	uint8_t RESERVED14[0xAC0u-0xA88u];

	/* 0xAC0: Read: get channel DREQ counter (i.e. */
	uint32_t volatile CH11_DBG_CTDREQ;
	/*  */
#define DMA_CH11_DBG_CTDREQ_CH11_DBG_CTDREQ_Msk			(0x3Fu << 0)
#define DMA_CH11_DBG_CTDREQ_CH11_DBG_CTDREQ_Pos			0u

	/* 0xAC4: Read to get channel TRANS_COUNT reload value, i.e. */
	uint32_t volatile CH11_DBG_TCR;

};


#define USBCTRL_DPRAM ((struct mcu_usbctrl_dpram *)0x50100000)

struct mcu_usbctrl_dpram {

	/* 0x00: Bytes 0-3 of the SETUP packet from the host. */
	uint32_t volatile SETUP_PACKET_LOW;
	/*  */
#define USBCTRL_DPRAM_SETUP_PACKET_LOW_WVALUE_Msk		(0xFFFFu << 16)
#define USBCTRL_DPRAM_SETUP_PACKET_LOW_WVALUE_Pos		16u
	/*  */
#define USBCTRL_DPRAM_SETUP_PACKET_LOW_BREQUEST_Msk		(0xFFu << 8)
#define USBCTRL_DPRAM_SETUP_PACKET_LOW_BREQUEST_Pos		8u
	/*  */
#define USBCTRL_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_Msk	(0xFFu << 0)
#define USBCTRL_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_Pos	0u

	/* 0x04: Bytes 4-7 of the setup packet from the host. */
	uint32_t volatile SETUP_PACKET_HIGH;
	/*  */
#define USBCTRL_DPRAM_SETUP_PACKET_HIGH_WLENGTH_Msk		(0xFFFFu << 16)
#define USBCTRL_DPRAM_SETUP_PACKET_HIGH_WLENGTH_Pos		16u
	/*  */
#define USBCTRL_DPRAM_SETUP_PACKET_HIGH_WINDEX_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_SETUP_PACKET_HIGH_WINDEX_Pos		0u

	/* 0x08:  */
	uint32_t volatile EP1_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x0C:  */
	uint32_t volatile EP1_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x10:  */
	uint32_t volatile EP2_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x14:  */
	uint32_t volatile EP2_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x18:  */
	uint32_t volatile EP3_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x1C:  */
	uint32_t volatile EP3_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x20:  */
	uint32_t volatile EP4_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x24:  */
	uint32_t volatile EP4_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x28:  */
	uint32_t volatile EP5_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x2C:  */
	uint32_t volatile EP5_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x30:  */
	uint32_t volatile EP6_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x34:  */
	uint32_t volatile EP6_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x38:  */
	uint32_t volatile EP7_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x3C:  */
	uint32_t volatile EP7_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x40:  */
	uint32_t volatile EP8_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x44:  */
	uint32_t volatile EP8_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x48:  */
	uint32_t volatile EP9_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF		(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_BULK		(0x2u << 26)
#define USBCTRL_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL		(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_Msk		(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_Pos		0u

	/* 0x4C:  */
	uint32_t volatile EP9_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x50:  */
	uint32_t volatile EP10_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x54:  */
	uint32_t volatile EP10_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_Msk	(0x3u << 26)
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_Pos	26u
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x58:  */
	uint32_t volatile EP11_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x5C:  */
	uint32_t volatile EP11_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_Msk	(0x3u << 26)
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_Pos	26u
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x60:  */
	uint32_t volatile EP12_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x64:  */
	uint32_t volatile EP12_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_Msk	(0x3u << 26)
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_Pos	26u
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x68:  */
	uint32_t volatile EP13_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x6C:  */
	uint32_t volatile EP13_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_Msk	(0x3u << 26)
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_Pos	26u
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x70:  */
	uint32_t volatile EP14_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x74:  */
	uint32_t volatile EP14_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_Msk	(0x3u << 26)
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_Pos	26u
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x78:  */
	uint32_t volatile EP15_IN_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_Msk		(0x3u << 26)
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_Pos		26u
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x7C:  */
	uint32_t volatile EP15_OUT_CONTROL;
	/* Enable this endpoint. */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENABLE			(1u << 31)
	/* This endpoint is double buffered. */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED		(1u << 30)
	/* Trigger an interrupt each time a buffer is done. */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF	(1u << 29)
	/* Trigger an interrupt each time both buffers are done. */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF	(1u << 28)
	/*  */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_Msk	(0x3u << 26)
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_Pos	26u
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_CONTROL	(0x0u << 26)
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_ISOCHRONOUS	(0x1u << 26)
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_BULK	(0x2u << 26)
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_INTERRUPT	(0x3u << 26)
	/* Trigger an interrupt if a STALL is sent. */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL	(1u << 17)
	/* Trigger an interrupt if a NAK is sent. */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK		(1u << 16)
	/* 64 byte aligned buffer address for this EP (bits 0-5 are ignored). */
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_Msk	(0xFFFFu << 0)
#define USBCTRL_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_Pos	0u

	/* 0x80: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP0_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x84: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP0_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x88: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP1_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x8C: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP1_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x90: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP2_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x94: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP2_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x98: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP3_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0x9C: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP3_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xA0: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP4_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xA4: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP4_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xA8: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP5_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xAC: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP5_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xB0: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP6_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xB4: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP6_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xB8: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP7_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xBC: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP7_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xC0: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP8_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xC4: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP8_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xC8: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP9_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1		(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0		(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xCC: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP9_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xD0: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP10_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xD4: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP10_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xD8: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP11_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xDC: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP11_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xE0: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP12_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xE4: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP12_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xE8: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP13_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xEC: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP13_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xF0: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP14_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xF4: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP14_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xF8: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP15_IN_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_Pos	0u

	/* 0xFC: Buffer control for both buffers of an endpoint. */
	uint32_t volatile EP15_OUT_BUFFER_CONTROL;
	/* Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1		(1u << 31)
	/* Buffer 1 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1		(1u << 30)
	/* The data pid of buffer 1. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1		(1u << 29)
	/* The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Msk	(0x3u << 27)
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_Pos	27u
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_128	(0x0u << 27)
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_256	(0x1u << 27)
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_512	(0x2u << 27)
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_1024	(0x3u << 27)
	/* Buffer 1 is available. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1	(1u << 26)
	/* The length of the data in buffer 1. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_Msk	(0x3FFu << 16)
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_Pos	16u
	/* Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0		(1u << 15)
	/* Buffer 0 is the last buffer of the transfer. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0		(1u << 14)
	/* The data pid of buffer 0. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0		(1u << 13)
	/* Reset the buffer selector to buffer 0. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET		(1u << 12)
	/* Reply with a stall (valid for both buffers). */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL		(1u << 11)
	/* Buffer 0 is available. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0	(1u << 10)
	/* The length of the data in buffer 0. */
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_Msk	(0x3FFu << 0)
#define USBCTRL_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_Pos	0u

};


#define USBCTRL_REGS ((struct mcu_usbctrl_regs *)0x50110000)

struct mcu_usbctrl_regs {

	/* 0x00: Device address and endpoint control */
	uint32_t volatile ADDR_ENDP;
	/* Device endpoint to send data to. */
#define USBCTRL_REGS_ADDR_ENDP_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP_ENDPOINT_Pos			16u
	/* In device mode, the address that the device should respond to. */
#define USBCTRL_REGS_ADDR_ENDP_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP_ADDRESS_Pos			0u

	/* 0x04: Interrupt endpoint 1. */
	uint32_t volatile ADDR_ENDP1;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP1_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP1_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP1_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP1_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP1_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP1_ADDRESS_Pos			0u

	/* 0x08: Interrupt endpoint 2. */
	uint32_t volatile ADDR_ENDP2;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP2_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP2_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP2_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP2_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP2_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP2_ADDRESS_Pos			0u

	/* 0x0C: Interrupt endpoint 3. */
	uint32_t volatile ADDR_ENDP3;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP3_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP3_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP3_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP3_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP3_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP3_ADDRESS_Pos			0u

	/* 0x10: Interrupt endpoint 4. */
	uint32_t volatile ADDR_ENDP4;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP4_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP4_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP4_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP4_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP4_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP4_ADDRESS_Pos			0u

	/* 0x14: Interrupt endpoint 5. */
	uint32_t volatile ADDR_ENDP5;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP5_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP5_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP5_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP5_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP5_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP5_ADDRESS_Pos			0u

	/* 0x18: Interrupt endpoint 6. */
	uint32_t volatile ADDR_ENDP6;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP6_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP6_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP6_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP6_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP6_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP6_ADDRESS_Pos			0u

	/* 0x1C: Interrupt endpoint 7. */
	uint32_t volatile ADDR_ENDP7;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP7_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP7_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP7_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP7_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP7_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP7_ADDRESS_Pos			0u

	/* 0x20: Interrupt endpoint 8. */
	uint32_t volatile ADDR_ENDP8;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP8_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP8_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP8_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP8_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP8_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP8_ADDRESS_Pos			0u

	/* 0x24: Interrupt endpoint 9. */
	uint32_t volatile ADDR_ENDP9;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP9_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP9_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP9_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP9_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP9_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP9_ADDRESS_Pos			0u

	/* 0x28: Interrupt endpoint 10. */
	uint32_t volatile ADDR_ENDP10;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP10_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP10_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP10_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP10_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP10_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP10_ADDRESS_Pos			0u

	/* 0x2C: Interrupt endpoint 11. */
	uint32_t volatile ADDR_ENDP11;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP11_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP11_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP11_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP11_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP11_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP11_ADDRESS_Pos			0u

	/* 0x30: Interrupt endpoint 12. */
	uint32_t volatile ADDR_ENDP12;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP12_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP12_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP12_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP12_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP12_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP12_ADDRESS_Pos			0u

	/* 0x34: Interrupt endpoint 13. */
	uint32_t volatile ADDR_ENDP13;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP13_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP13_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP13_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP13_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP13_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP13_ADDRESS_Pos			0u

	/* 0x38: Interrupt endpoint 14. */
	uint32_t volatile ADDR_ENDP14;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP14_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP14_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP14_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP14_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP14_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP14_ADDRESS_Pos			0u

	/* 0x3C: Interrupt endpoint 15. */
	uint32_t volatile ADDR_ENDP15;
	/* Interrupt EP requires preamble (is a low speed device on a full speed hub) */
#define USBCTRL_REGS_ADDR_ENDP15_INTEP_PREAMBLE			(1u << 26)
	/* Direction of the interrupt endpoint. */
#define USBCTRL_REGS_ADDR_ENDP15_INTEP_DIR			(1u << 25)
	/* Endpoint number of the interrupt endpoint */
#define USBCTRL_REGS_ADDR_ENDP15_ENDPOINT_Msk			(0xFu << 16)
#define USBCTRL_REGS_ADDR_ENDP15_ENDPOINT_Pos			16u
	/* Device address */
#define USBCTRL_REGS_ADDR_ENDP15_ADDRESS_Msk			(0x7Fu << 0)
#define USBCTRL_REGS_ADDR_ENDP15_ADDRESS_Pos			0u

	/* 0x40: Main control register */
	uint32_t volatile MAIN_CTRL;
	/* Reduced timings for simulation */
#define USBCTRL_REGS_MAIN_CTRL_SIM_TIMING			(1u << 31)
	/* Device mode = 0, Host mode = 1 */
#define USBCTRL_REGS_MAIN_CTRL_HOST_NDEVICE			(1u << 1)
	/* Enable controller */
#define USBCTRL_REGS_MAIN_CTRL_CONTROLLER_EN			(1u << 0)

	/* 0x44: Set the SOF (Start of Frame) frame number in the host controller. */
	uint32_t volatile SOF_WR;
	/*  */
#define USBCTRL_REGS_SOF_WR_COUNT_Msk				(0x7FFu << 0)
#define USBCTRL_REGS_SOF_WR_COUNT_Pos				0u

	/* 0x48: Read the last SOF (Start of Frame) frame number seen. */
	uint32_t volatile SOF_RD;
	/*  */
#define USBCTRL_REGS_SOF_RD_COUNT_Msk				(0x7FFu << 0)
#define USBCTRL_REGS_SOF_RD_COUNT_Pos				0u

	/* 0x4C: SIE control register */
	uint32_t volatile SIE_CTRL;
	/* Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a STALL */
#define USBCTRL_REGS_SIE_CTRL_EP0_INT_STALL			(1u << 31)
	/* Device: EP0 single buffered = 0, double buffered = 1 */
#define USBCTRL_REGS_SIE_CTRL_EP0_DOUBLE_BUF			(1u << 30)
	/* Device: Set bit in BUFF_STATUS for every buffer completed on EP0 */
#define USBCTRL_REGS_SIE_CTRL_EP0_INT_1BUF			(1u << 29)
	/* Device: Set bit in BUFF_STATUS for every 2 buffers completed on EP0 */
#define USBCTRL_REGS_SIE_CTRL_EP0_INT_2BUF			(1u << 28)
	/* Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a NAK */
#define USBCTRL_REGS_SIE_CTRL_EP0_INT_NAK			(1u << 27)
	/* Direct bus drive enable */
#define USBCTRL_REGS_SIE_CTRL_DIRECT_EN				(1u << 26)
	/* Direct control of DP */
#define USBCTRL_REGS_SIE_CTRL_DIRECT_DP				(1u << 25)
	/* Direct control of DM */
#define USBCTRL_REGS_SIE_CTRL_DIRECT_DM				(1u << 24)
	/* Power down bus transceiver */
#define USBCTRL_REGS_SIE_CTRL_TRANSCEIVER_PD			(1u << 18)
	/* Device: Pull-up strength (0=1K2, 1=2k3) */
#define USBCTRL_REGS_SIE_CTRL_RPU_OPT				(1u << 17)
	/* Device: Enable pull up resistor */
#define USBCTRL_REGS_SIE_CTRL_PULLUP_EN				(1u << 16)
	/* Host: Enable pull down resistors */
#define USBCTRL_REGS_SIE_CTRL_PULLDOWN_EN			(1u << 15)
	/* Host: Reset bus */
#define USBCTRL_REGS_SIE_CTRL_RESET_BUS				(1u << 13)
	/* Device: Remote wakeup. */
#define USBCTRL_REGS_SIE_CTRL_RESUME				(1u << 12)
	/* Host: Enable VBUS */
#define USBCTRL_REGS_SIE_CTRL_VBUS_EN				(1u << 11)
	/* Host: Enable keep alive packet (for low speed bus) */
#define USBCTRL_REGS_SIE_CTRL_KEEP_ALIVE_EN			(1u << 10)
	/* Host: Enable SOF generation (for full speed bus) */
#define USBCTRL_REGS_SIE_CTRL_SOF_EN				(1u << 9)
	/* Host: Delay packet(s) until after SOF */
#define USBCTRL_REGS_SIE_CTRL_SOF_SYNC				(1u << 8)
	/* Host: Preable enable for LS device on FS hub */
#define USBCTRL_REGS_SIE_CTRL_PREAMBLE_EN			(1u << 6)
	/* Host: Stop transaction */
#define USBCTRL_REGS_SIE_CTRL_STOP_TRANS			(1u << 4)
	/* Host: Receive transaction (IN to host) */
#define USBCTRL_REGS_SIE_CTRL_RECEIVE_DATA			(1u << 3)
	/* Host: Send transaction (OUT from host) */
#define USBCTRL_REGS_SIE_CTRL_SEND_DATA				(1u << 2)
	/* Host: Send Setup packet */
#define USBCTRL_REGS_SIE_CTRL_SEND_SETUP			(1u << 1)
	/* Host: Start transaction */
#define USBCTRL_REGS_SIE_CTRL_START_TRANS			(1u << 0)

	/* 0x50: SIE status register */
	uint32_t volatile SIE_STATUS;
	/* Data Sequence Error. */
#define USBCTRL_REGS_SIE_STATUS_DATA_SEQ_ERROR			(1u << 31)
	/* ACK received. */
#define USBCTRL_REGS_SIE_STATUS_ACK_REC				(1u << 30)
	/* Host: STALL received */
#define USBCTRL_REGS_SIE_STATUS_STALL_REC			(1u << 29)
	/* Host: NAK received */
#define USBCTRL_REGS_SIE_STATUS_NAK_REC				(1u << 28)
	/* RX timeout is raised by both the host and device if an ACK is not received in the maximum time specified by the USB spec. */
#define USBCTRL_REGS_SIE_STATUS_RX_TIMEOUT			(1u << 27)
	/* RX overflow is raised by the Serial RX engine if the incoming data is too fast. */
#define USBCTRL_REGS_SIE_STATUS_RX_OVERFLOW			(1u << 26)
	/* Bit Stuff Error. */
#define USBCTRL_REGS_SIE_STATUS_BIT_STUFF_ERROR			(1u << 25)
	/* CRC Error. */
#define USBCTRL_REGS_SIE_STATUS_CRC_ERROR			(1u << 24)
	/* Device: bus reset received */
#define USBCTRL_REGS_SIE_STATUS_BUS_RESET			(1u << 19)
	/* Transaction complete. */
#define USBCTRL_REGS_SIE_STATUS_TRANS_COMPLETE			(1u << 18)
	/* Device: Setup packet received */
#define USBCTRL_REGS_SIE_STATUS_SETUP_REC			(1u << 17)
	/* Device: connected */
#define USBCTRL_REGS_SIE_STATUS_CONNECTED			(1u << 16)
	/* Host: Device has initiated a remote resume. */
#define USBCTRL_REGS_SIE_STATUS_RESUME				(1u << 11)
	/* VBUS over current detected */
#define USBCTRL_REGS_SIE_STATUS_VBUS_OVER_CURR			(1u << 10)
	/* Host: device speed. */
#define USBCTRL_REGS_SIE_STATUS_SPEED_Msk			(0x3u << 8)
#define USBCTRL_REGS_SIE_STATUS_SPEED_Pos			8u
	/* Bus in suspended state. */
#define USBCTRL_REGS_SIE_STATUS_SUSPENDED			(1u << 4)
	/* USB bus line state */
#define USBCTRL_REGS_SIE_STATUS_LINE_STATE_Msk			(0x3u << 2)
#define USBCTRL_REGS_SIE_STATUS_LINE_STATE_Pos			2u
	/* Device: VBUS Detected */
#define USBCTRL_REGS_SIE_STATUS_VBUS_DETECTED			(1u << 0)

	/* 0x54: interrupt endpoint control register */
	uint32_t volatile INT_EP_CTRL;
	/* Host: Enable interrupt endpoint 1 -> 15 */
#define USBCTRL_REGS_INT_EP_CTRL_INT_EP_ACTIVE_Msk		(0x7FFFu << 1)
#define USBCTRL_REGS_INT_EP_CTRL_INT_EP_ACTIVE_Pos		1u

	/* 0x58: Buffer status register. A bit set here indicates that a buffer has completed on the endpoint (if the buffer interrupt is enabled). */
	uint32_t volatile BUFF_STATUS;
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP15_OUT			(1u << 31)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP15_IN			(1u << 30)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP14_OUT			(1u << 29)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP14_IN			(1u << 28)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP13_OUT			(1u << 27)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP13_IN			(1u << 26)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP12_OUT			(1u << 25)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP12_IN			(1u << 24)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP11_OUT			(1u << 23)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP11_IN			(1u << 22)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP10_OUT			(1u << 21)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP10_IN			(1u << 20)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP9_OUT			(1u << 19)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP9_IN				(1u << 18)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP8_OUT			(1u << 17)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP8_IN				(1u << 16)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP7_OUT			(1u << 15)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP7_IN				(1u << 14)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP6_OUT			(1u << 13)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP6_IN				(1u << 12)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP5_OUT			(1u << 11)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP5_IN				(1u << 10)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP4_OUT			(1u << 9)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP4_IN				(1u << 8)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP3_OUT			(1u << 7)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP3_IN				(1u << 6)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP2_OUT			(1u << 5)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP2_IN				(1u << 4)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP1_OUT			(1u << 3)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP1_IN				(1u << 2)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP0_OUT			(1u << 1)
	/*  */
#define USBCTRL_REGS_BUFF_STATUS_EP0_IN				(1u << 0)

	/* 0x5C: Which of the double buffers should be handled. Only valid if using an interrupt per buffer (i.e. not per 2 buffers). */
	uint32_t volatile BUFF_CPU_SHOULD_HANDLE;
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP15_OUT		(1u << 31)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP15_IN		(1u << 30)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP14_OUT		(1u << 29)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP14_IN		(1u << 28)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP13_OUT		(1u << 27)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP13_IN		(1u << 26)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP12_OUT		(1u << 25)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP12_IN		(1u << 24)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP11_OUT		(1u << 23)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP11_IN		(1u << 22)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP10_OUT		(1u << 21)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP10_IN		(1u << 20)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP9_OUT		(1u << 19)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP9_IN		(1u << 18)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP8_OUT		(1u << 17)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP8_IN		(1u << 16)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP7_OUT		(1u << 15)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP7_IN		(1u << 14)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP6_OUT		(1u << 13)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP6_IN		(1u << 12)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP5_OUT		(1u << 11)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP5_IN		(1u << 10)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP4_OUT		(1u << 9)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP4_IN		(1u << 8)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP3_OUT		(1u << 7)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP3_IN		(1u << 6)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP2_OUT		(1u << 5)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP2_IN		(1u << 4)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP1_OUT		(1u << 3)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP1_IN		(1u << 2)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP0_OUT		(1u << 1)
	/*  */
#define USBCTRL_REGS_BUFF_CPU_SHOULD_HANDLE_EP0_IN		(1u << 0)

	/* 0x60: Device only: Can be set to ignore the buffer control register for this endpoint in case you would like to revoke a buffer. */
	uint32_t volatile EP_ABORT;
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP15_OUT				(1u << 31)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP15_IN				(1u << 30)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP14_OUT				(1u << 29)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP14_IN				(1u << 28)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP13_OUT				(1u << 27)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP13_IN				(1u << 26)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP12_OUT				(1u << 25)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP12_IN				(1u << 24)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP11_OUT				(1u << 23)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP11_IN				(1u << 22)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP10_OUT				(1u << 21)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP10_IN				(1u << 20)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP9_OUT				(1u << 19)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP9_IN				(1u << 18)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP8_OUT				(1u << 17)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP8_IN				(1u << 16)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP7_OUT				(1u << 15)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP7_IN				(1u << 14)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP6_OUT				(1u << 13)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP6_IN				(1u << 12)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP5_OUT				(1u << 11)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP5_IN				(1u << 10)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP4_OUT				(1u << 9)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP4_IN				(1u << 8)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP3_OUT				(1u << 7)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP3_IN				(1u << 6)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP2_OUT				(1u << 5)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP2_IN				(1u << 4)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP1_OUT				(1u << 3)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP1_IN				(1u << 2)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP0_OUT				(1u << 1)
	/*  */
#define USBCTRL_REGS_EP_ABORT_EP0_IN				(1u << 0)

	/* 0x64: Device only: Used in conjunction with `EP_ABORT`. */
	uint32_t volatile EP_ABORT_DONE;
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP15_OUT			(1u << 31)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP15_IN			(1u << 30)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP14_OUT			(1u << 29)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP14_IN			(1u << 28)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP13_OUT			(1u << 27)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP13_IN			(1u << 26)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP12_OUT			(1u << 25)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP12_IN			(1u << 24)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP11_OUT			(1u << 23)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP11_IN			(1u << 22)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP10_OUT			(1u << 21)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP10_IN			(1u << 20)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP9_OUT			(1u << 19)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP9_IN			(1u << 18)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP8_OUT			(1u << 17)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP8_IN			(1u << 16)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP7_OUT			(1u << 15)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP7_IN			(1u << 14)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP6_OUT			(1u << 13)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP6_IN			(1u << 12)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP5_OUT			(1u << 11)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP5_IN			(1u << 10)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP4_OUT			(1u << 9)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP4_IN			(1u << 8)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP3_OUT			(1u << 7)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP3_IN			(1u << 6)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP2_OUT			(1u << 5)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP2_IN			(1u << 4)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP1_OUT			(1u << 3)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP1_IN			(1u << 2)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP0_OUT			(1u << 1)
	/*  */
#define USBCTRL_REGS_EP_ABORT_DONE_EP0_IN			(1u << 0)

	/* 0x68: Device: this bit must be set in conjunction with the `STALL` bit in the buffer control register to send a STALL on EP0. */
	uint32_t volatile EP_STALL_ARM;
	/*  */
#define USBCTRL_REGS_EP_STALL_ARM_EP0_OUT			(1u << 1)
	/*  */
#define USBCTRL_REGS_EP_STALL_ARM_EP0_IN			(1u << 0)

	/* 0x6C: Used by the host controller. */
	uint32_t volatile NAK_POLL;
	/* NAK polling interval for a full speed device */
#define USBCTRL_REGS_NAK_POLL_DELAY_FS_Msk			(0x3FFu << 16)
#define USBCTRL_REGS_NAK_POLL_DELAY_FS_Pos			16u
	/* NAK polling interval for a low speed device */
#define USBCTRL_REGS_NAK_POLL_DELAY_LS_Msk			(0x3FFu << 0)
#define USBCTRL_REGS_NAK_POLL_DELAY_LS_Pos			0u

	/* 0x70: Device: bits are set when the `IRQ_ON_NAK` or `IRQ_ON_STALL` bits are set. */
	uint32_t volatile EP_STATUS_STALL_NAK;
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP15_OUT		(1u << 31)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP15_IN		(1u << 30)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP14_OUT		(1u << 29)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP14_IN		(1u << 28)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP13_OUT		(1u << 27)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP13_IN		(1u << 26)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP12_OUT		(1u << 25)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP12_IN		(1u << 24)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP11_OUT		(1u << 23)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP11_IN		(1u << 22)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP10_OUT		(1u << 21)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP10_IN		(1u << 20)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP9_OUT		(1u << 19)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP9_IN			(1u << 18)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP8_OUT		(1u << 17)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP8_IN			(1u << 16)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP7_OUT		(1u << 15)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP7_IN			(1u << 14)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP6_OUT		(1u << 13)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP6_IN			(1u << 12)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP5_OUT		(1u << 11)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP5_IN			(1u << 10)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP4_OUT		(1u << 9)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP4_IN			(1u << 8)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP3_OUT		(1u << 7)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP3_IN			(1u << 6)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP2_OUT		(1u << 5)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP2_IN			(1u << 4)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP1_OUT		(1u << 3)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP1_IN			(1u << 2)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP0_OUT		(1u << 1)
	/*  */
#define USBCTRL_REGS_EP_STATUS_STALL_NAK_EP0_IN			(1u << 0)

	/* 0x74: Where to connect the USB controller. */
	uint32_t volatile USB_MUXING;
	/*  */
#define USBCTRL_REGS_USB_MUXING_SOFTCON				(1u << 3)
	/*  */
#define USBCTRL_REGS_USB_MUXING_TO_DIGITAL_PAD			(1u << 2)
	/*  */
#define USBCTRL_REGS_USB_MUXING_TO_EXTPHY			(1u << 1)
	/*  */
#define USBCTRL_REGS_USB_MUXING_TO_PHY				(1u << 0)

	/* 0x78: Overrides for the power signals in the event that the VBUS signals are not hooked up to GPIO. */
	uint32_t volatile USB_PWR;
	/*  */
#define USBCTRL_REGS_USB_PWR_OVERCURR_DETECT_EN			(1u << 5)
	/*  */
#define USBCTRL_REGS_USB_PWR_OVERCURR_DETECT			(1u << 4)
	/*  */
#define USBCTRL_REGS_USB_PWR_VBUS_DETECT_OVERRIDE_EN		(1u << 3)
	/*  */
#define USBCTRL_REGS_USB_PWR_VBUS_DETECT			(1u << 2)
	/*  */
#define USBCTRL_REGS_USB_PWR_VBUS_EN_OVERRIDE_EN		(1u << 1)
	/*  */
#define USBCTRL_REGS_USB_PWR_VBUS_EN				(1u << 0)

	/* 0x7C: This register allows for direct control of the USB phy. */
	uint32_t volatile USBPHY_DIRECT;
	/* DM over voltage */
#define USBCTRL_REGS_USBPHY_DIRECT_DM_OVV			(1u << 22)
	/* DP over voltage */
#define USBCTRL_REGS_USBPHY_DIRECT_DP_OVV			(1u << 21)
	/* DM overcurrent */
#define USBCTRL_REGS_USBPHY_DIRECT_DM_OVCN			(1u << 20)
	/* DP overcurrent */
#define USBCTRL_REGS_USBPHY_DIRECT_DP_OVCN			(1u << 19)
	/* DPM pin state */
#define USBCTRL_REGS_USBPHY_DIRECT_RX_DM			(1u << 18)
	/* DPP pin state */
#define USBCTRL_REGS_USBPHY_DIRECT_RX_DP			(1u << 17)
	/* Differential RX */
#define USBCTRL_REGS_USBPHY_DIRECT_RX_DD			(1u << 16)
	/* TX_DIFFMODE=0: Single ended mode */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_DIFFMODE			(1u << 15)
	/* TX_FSSLEW=0: Low speed slew rate */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_FSSLEW			(1u << 14)
	/* TX power down override (if override enable is set). */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_PD			(1u << 13)
	/* RX power down override (if override enable is set). */
#define USBCTRL_REGS_USBPHY_DIRECT_RX_PD			(1u << 12)
	/* Output data. */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_DM			(1u << 11)
	/* Output data. */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_DP			(1u << 10)
	/* Output enable. */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_DM_OE			(1u << 9)
	/* Output enable. */
#define USBCTRL_REGS_USBPHY_DIRECT_TX_DP_OE			(1u << 8)
	/* DM pull down enable */
#define USBCTRL_REGS_USBPHY_DIRECT_DM_PULLDN_EN			(1u << 6)
	/* DM pull up enable */
#define USBCTRL_REGS_USBPHY_DIRECT_DM_PULLUP_EN			(1u << 5)
	/* Enable the second DM pull up resistor. */
#define USBCTRL_REGS_USBPHY_DIRECT_DM_PULLUP_HISEL		(1u << 4)
	/* DP pull down enable */
#define USBCTRL_REGS_USBPHY_DIRECT_DP_PULLDN_EN			(1u << 2)
	/* DP pull up enable */
#define USBCTRL_REGS_USBPHY_DIRECT_DP_PULLUP_EN			(1u << 1)
	/* Enable the second DP pull up resistor. */
#define USBCTRL_REGS_USBPHY_DIRECT_DP_PULLUP_HISEL		(1u << 0)

	/* 0x80: Override enable for each control in usbphy_direct */
	uint32_t volatile USBPHY_DIRECT_OVERRIDE;
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN	(1u << 15)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN	(1u << 12)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN	(1u << 11)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN	(1u << 10)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN	(1u << 9)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN	(1u << 8)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN	(1u << 7)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN	(1u << 6)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN	(1u << 5)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN	(1u << 4)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN	(1u << 3)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN	(1u << 2)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN	(1u << 1)
	/*  */
#define USBCTRL_REGS_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN	(1u << 0)

	/* 0x84: Used to adjust trim values of USB phy pull down resistors. */
	uint32_t volatile USBPHY_TRIM;
	/* Value to drive to USB PHY */
#define USBCTRL_REGS_USBPHY_TRIM_DM_PULLDN_TRIM_Msk		(0x1Fu << 8)
#define USBCTRL_REGS_USBPHY_TRIM_DM_PULLDN_TRIM_Pos		8u
	/* Value to drive to USB PHY */
#define USBCTRL_REGS_USBPHY_TRIM_DP_PULLDN_TRIM_Msk		(0x1Fu << 0)
#define USBCTRL_REGS_USBPHY_TRIM_DP_PULLDN_TRIM_Pos		0u

	/* 0x88 */
	uint8_t RESERVED0[0x8Cu-0x88u];

	/* 0x8C: Raw Interrupts */
	uint32_t volatile INTR;
	/* Raised when any bit in EP_STATUS_STALL_NAK is set. */
#define USBCTRL_REGS_INTR_EP_STALL_NAK				(1u << 19)
	/* Raised when any bit in ABORT_DONE is set. */
#define USBCTRL_REGS_INTR_ABORT_DONE				(1u << 18)
	/* Set every time the device receives a SOF (Start of Frame) packet. */
#define USBCTRL_REGS_INTR_DEV_SOF				(1u << 17)
	/* Device. */
#define USBCTRL_REGS_INTR_SETUP_REQ				(1u << 16)
	/* Set when the device receives a resume from the host. */
#define USBCTRL_REGS_INTR_DEV_RESUME_FROM_HOST			(1u << 15)
	/* Set when the device suspend state changes. */
#define USBCTRL_REGS_INTR_DEV_SUSPEND				(1u << 14)
	/* Set when the device connection state changes. */
#define USBCTRL_REGS_INTR_DEV_CONN_DIS				(1u << 13)
	/* Source: SIE_STATUS.BUS_RESET */
#define USBCTRL_REGS_INTR_BUS_RESET				(1u << 12)
	/* Source: SIE_STATUS.VBUS_DETECTED */
#define USBCTRL_REGS_INTR_VBUS_DETECT				(1u << 11)
	/* Source: SIE_STATUS.STALL_REC */
#define USBCTRL_REGS_INTR_STALL					(1u << 10)
	/* Source: SIE_STATUS.CRC_ERROR */
#define USBCTRL_REGS_INTR_ERROR_CRC				(1u << 9)
	/* Source: SIE_STATUS.BIT_STUFF_ERROR */
#define USBCTRL_REGS_INTR_ERROR_BIT_STUFF			(1u << 8)
	/* Source: SIE_STATUS.RX_OVERFLOW */
#define USBCTRL_REGS_INTR_ERROR_RX_OVERFLOW			(1u << 7)
	/* Source: SIE_STATUS.RX_TIMEOUT */
#define USBCTRL_REGS_INTR_ERROR_RX_TIMEOUT			(1u << 6)
	/* Source: SIE_STATUS.DATA_SEQ_ERROR */
#define USBCTRL_REGS_INTR_ERROR_DATA_SEQ			(1u << 5)
	/* Raised when any bit in BUFF_STATUS is set. */
#define USBCTRL_REGS_INTR_BUFF_STATUS				(1u << 4)
	/* Raised every time SIE_STATUS.TRANS_COMPLETE is set. */
#define USBCTRL_REGS_INTR_TRANS_COMPLETE			(1u << 3)
	/* Host: raised every time the host sends a SOF (Start of Frame). */
#define USBCTRL_REGS_INTR_HOST_SOF				(1u << 2)
	/* Host: raised when a device wakes up the host. */
#define USBCTRL_REGS_INTR_HOST_RESUME				(1u << 1)
	/* Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). */
#define USBCTRL_REGS_INTR_HOST_CONN_DIS				(1u << 0)

	/* 0x90: Interrupt Enable */
	uint32_t volatile INTE;
	/* Raised when any bit in EP_STATUS_STALL_NAK is set. */
#define USBCTRL_REGS_INTE_EP_STALL_NAK				(1u << 19)
	/* Raised when any bit in ABORT_DONE is set. */
#define USBCTRL_REGS_INTE_ABORT_DONE				(1u << 18)
	/* Set every time the device receives a SOF (Start of Frame) packet. */
#define USBCTRL_REGS_INTE_DEV_SOF				(1u << 17)
	/* Device. */
#define USBCTRL_REGS_INTE_SETUP_REQ				(1u << 16)
	/* Set when the device receives a resume from the host. */
#define USBCTRL_REGS_INTE_DEV_RESUME_FROM_HOST			(1u << 15)
	/* Set when the device suspend state changes. */
#define USBCTRL_REGS_INTE_DEV_SUSPEND				(1u << 14)
	/* Set when the device connection state changes. */
#define USBCTRL_REGS_INTE_DEV_CONN_DIS				(1u << 13)
	/* Source: SIE_STATUS.BUS_RESET */
#define USBCTRL_REGS_INTE_BUS_RESET				(1u << 12)
	/* Source: SIE_STATUS.VBUS_DETECTED */
#define USBCTRL_REGS_INTE_VBUS_DETECT				(1u << 11)
	/* Source: SIE_STATUS.STALL_REC */
#define USBCTRL_REGS_INTE_STALL					(1u << 10)
	/* Source: SIE_STATUS.CRC_ERROR */
#define USBCTRL_REGS_INTE_ERROR_CRC				(1u << 9)
	/* Source: SIE_STATUS.BIT_STUFF_ERROR */
#define USBCTRL_REGS_INTE_ERROR_BIT_STUFF			(1u << 8)
	/* Source: SIE_STATUS.RX_OVERFLOW */
#define USBCTRL_REGS_INTE_ERROR_RX_OVERFLOW			(1u << 7)
	/* Source: SIE_STATUS.RX_TIMEOUT */
#define USBCTRL_REGS_INTE_ERROR_RX_TIMEOUT			(1u << 6)
	/* Source: SIE_STATUS.DATA_SEQ_ERROR */
#define USBCTRL_REGS_INTE_ERROR_DATA_SEQ			(1u << 5)
	/* Raised when any bit in BUFF_STATUS is set. */
#define USBCTRL_REGS_INTE_BUFF_STATUS				(1u << 4)
	/* Raised every time SIE_STATUS.TRANS_COMPLETE is set. */
#define USBCTRL_REGS_INTE_TRANS_COMPLETE			(1u << 3)
	/* Host: raised every time the host sends a SOF (Start of Frame). */
#define USBCTRL_REGS_INTE_HOST_SOF				(1u << 2)
	/* Host: raised when a device wakes up the host. */
#define USBCTRL_REGS_INTE_HOST_RESUME				(1u << 1)
	/* Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). */
#define USBCTRL_REGS_INTE_HOST_CONN_DIS				(1u << 0)

	/* 0x94: Interrupt Force */
	uint32_t volatile INTF;
	/* Raised when any bit in EP_STATUS_STALL_NAK is set. */
#define USBCTRL_REGS_INTF_EP_STALL_NAK				(1u << 19)
	/* Raised when any bit in ABORT_DONE is set. */
#define USBCTRL_REGS_INTF_ABORT_DONE				(1u << 18)
	/* Set every time the device receives a SOF (Start of Frame) packet. */
#define USBCTRL_REGS_INTF_DEV_SOF				(1u << 17)
	/* Device. */
#define USBCTRL_REGS_INTF_SETUP_REQ				(1u << 16)
	/* Set when the device receives a resume from the host. */
#define USBCTRL_REGS_INTF_DEV_RESUME_FROM_HOST			(1u << 15)
	/* Set when the device suspend state changes. */
#define USBCTRL_REGS_INTF_DEV_SUSPEND				(1u << 14)
	/* Set when the device connection state changes. */
#define USBCTRL_REGS_INTF_DEV_CONN_DIS				(1u << 13)
	/* Source: SIE_STATUS.BUS_RESET */
#define USBCTRL_REGS_INTF_BUS_RESET				(1u << 12)
	/* Source: SIE_STATUS.VBUS_DETECTED */
#define USBCTRL_REGS_INTF_VBUS_DETECT				(1u << 11)
	/* Source: SIE_STATUS.STALL_REC */
#define USBCTRL_REGS_INTF_STALL					(1u << 10)
	/* Source: SIE_STATUS.CRC_ERROR */
#define USBCTRL_REGS_INTF_ERROR_CRC				(1u << 9)
	/* Source: SIE_STATUS.BIT_STUFF_ERROR */
#define USBCTRL_REGS_INTF_ERROR_BIT_STUFF			(1u << 8)
	/* Source: SIE_STATUS.RX_OVERFLOW */
#define USBCTRL_REGS_INTF_ERROR_RX_OVERFLOW			(1u << 7)
	/* Source: SIE_STATUS.RX_TIMEOUT */
#define USBCTRL_REGS_INTF_ERROR_RX_TIMEOUT			(1u << 6)
	/* Source: SIE_STATUS.DATA_SEQ_ERROR */
#define USBCTRL_REGS_INTF_ERROR_DATA_SEQ			(1u << 5)
	/* Raised when any bit in BUFF_STATUS is set. */
#define USBCTRL_REGS_INTF_BUFF_STATUS				(1u << 4)
	/* Raised every time SIE_STATUS.TRANS_COMPLETE is set. */
#define USBCTRL_REGS_INTF_TRANS_COMPLETE			(1u << 3)
	/* Host: raised every time the host sends a SOF (Start of Frame). */
#define USBCTRL_REGS_INTF_HOST_SOF				(1u << 2)
	/* Host: raised when a device wakes up the host. */
#define USBCTRL_REGS_INTF_HOST_RESUME				(1u << 1)
	/* Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). */
#define USBCTRL_REGS_INTF_HOST_CONN_DIS				(1u << 0)

	/* 0x98: Interrupt status after masking & forcing */
	uint32_t volatile INTS;
	/* Raised when any bit in EP_STATUS_STALL_NAK is set. */
#define USBCTRL_REGS_INTS_EP_STALL_NAK				(1u << 19)
	/* Raised when any bit in ABORT_DONE is set. */
#define USBCTRL_REGS_INTS_ABORT_DONE				(1u << 18)
	/* Set every time the device receives a SOF (Start of Frame) packet. */
#define USBCTRL_REGS_INTS_DEV_SOF				(1u << 17)
	/* Device. */
#define USBCTRL_REGS_INTS_SETUP_REQ				(1u << 16)
	/* Set when the device receives a resume from the host. */
#define USBCTRL_REGS_INTS_DEV_RESUME_FROM_HOST			(1u << 15)
	/* Set when the device suspend state changes. */
#define USBCTRL_REGS_INTS_DEV_SUSPEND				(1u << 14)
	/* Set when the device connection state changes. */
#define USBCTRL_REGS_INTS_DEV_CONN_DIS				(1u << 13)
	/* Source: SIE_STATUS.BUS_RESET */
#define USBCTRL_REGS_INTS_BUS_RESET				(1u << 12)
	/* Source: SIE_STATUS.VBUS_DETECTED */
#define USBCTRL_REGS_INTS_VBUS_DETECT				(1u << 11)
	/* Source: SIE_STATUS.STALL_REC */
#define USBCTRL_REGS_INTS_STALL					(1u << 10)
	/* Source: SIE_STATUS.CRC_ERROR */
#define USBCTRL_REGS_INTS_ERROR_CRC				(1u << 9)
	/* Source: SIE_STATUS.BIT_STUFF_ERROR */
#define USBCTRL_REGS_INTS_ERROR_BIT_STUFF			(1u << 8)
	/* Source: SIE_STATUS.RX_OVERFLOW */
#define USBCTRL_REGS_INTS_ERROR_RX_OVERFLOW			(1u << 7)
	/* Source: SIE_STATUS.RX_TIMEOUT */
#define USBCTRL_REGS_INTS_ERROR_RX_TIMEOUT			(1u << 6)
	/* Source: SIE_STATUS.DATA_SEQ_ERROR */
#define USBCTRL_REGS_INTS_ERROR_DATA_SEQ			(1u << 5)
	/* Raised when any bit in BUFF_STATUS is set. */
#define USBCTRL_REGS_INTS_BUFF_STATUS				(1u << 4)
	/* Raised every time SIE_STATUS.TRANS_COMPLETE is set. */
#define USBCTRL_REGS_INTS_TRANS_COMPLETE			(1u << 3)
	/* Host: raised every time the host sends a SOF (Start of Frame). */
#define USBCTRL_REGS_INTS_HOST_SOF				(1u << 2)
	/* Host: raised when a device wakes up the host. */
#define USBCTRL_REGS_INTS_HOST_RESUME				(1u << 1)
	/* Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). */
#define USBCTRL_REGS_INTS_HOST_CONN_DIS				(1u << 0)

};


#define PIO0 ((struct mcu_pio *)0x50200000)
#define PIO1 ((struct mcu_pio *)0x50300000)

struct mcu_pio {

	/* 0x00: PIO control register */
	uint32_t volatile CTRL;
	/* Restart a state machine's clock divider from an initial phase of 0. Clock dividers are free-running, so once started, their output (including fractional jitter) is completely determined by the integer/fractional divisor configured in SMx_CLKDIV. */
#define PIO0_CTRL_CLKDIV_RESTART_Msk				(0xFu << 8)
#define PIO0_CTRL_CLKDIV_RESTART_Pos				8u
	/* Write 1 to instantly clear internal SM state which may be otherwise difficult to access and will affect future execution. */
#define PIO0_CTRL_SM_RESTART_Msk				(0xFu << 4)
#define PIO0_CTRL_SM_RESTART_Pos				4u
	/* Enable/disable each of the four state machines by writing 1/0 to each of these four bits. */
#define PIO0_CTRL_SM_ENABLE_Msk					(0xFu << 0)
#define PIO0_CTRL_SM_ENABLE_Pos					0u

	/* 0x04: FIFO status register */
	uint32_t volatile FSTAT;
	/* State machine TX FIFO is empty */
#define PIO0_FSTAT_TXEMPTY_Msk					(0xFu << 24)
#define PIO0_FSTAT_TXEMPTY_Pos					24u
	/* State machine TX FIFO is full */
#define PIO0_FSTAT_TXFULL_Msk					(0xFu << 16)
#define PIO0_FSTAT_TXFULL_Pos					16u
	/* State machine RX FIFO is empty */
#define PIO0_FSTAT_RXEMPTY_Msk					(0xFu << 8)
#define PIO0_FSTAT_RXEMPTY_Pos					8u
	/* State machine RX FIFO is full */
#define PIO0_FSTAT_RXFULL_Msk					(0xFu << 0)
#define PIO0_FSTAT_RXFULL_Pos					0u

	/* 0x08: FIFO debug register */
	uint32_t volatile FDEBUG;
	/* State machine has stalled on empty TX FIFO during a blocking PULL, or an OUT with autopull enabled. */
#define PIO0_FDEBUG_TXSTALL_Msk					(0xFu << 24)
#define PIO0_FDEBUG_TXSTALL_Pos					24u
	/* TX FIFO overflow (i.e. write-on-full by the system) has occurred. */
#define PIO0_FDEBUG_TXOVER_Msk					(0xFu << 16)
#define PIO0_FDEBUG_TXOVER_Pos					16u
	/* RX FIFO underflow (i.e. read-on-empty by the system) has occurred. */
#define PIO0_FDEBUG_RXUNDER_Msk					(0xFu << 8)
#define PIO0_FDEBUG_RXUNDER_Pos					8u
	/* State machine has stalled on full RX FIFO during a blocking PUSH, or an IN with autopush enabled. */
#define PIO0_FDEBUG_RXSTALL_Msk					(0xFu << 0)
#define PIO0_FDEBUG_RXSTALL_Pos					0u

	/* 0x0C: FIFO levels */
	uint32_t volatile FLEVEL;
	/*  */
#define PIO0_FLEVEL_RX3_Msk					(0xFu << 28)
#define PIO0_FLEVEL_RX3_Pos					28u
	/*  */
#define PIO0_FLEVEL_TX3_Msk					(0xFu << 24)
#define PIO0_FLEVEL_TX3_Pos					24u
	/*  */
#define PIO0_FLEVEL_RX2_Msk					(0xFu << 20)
#define PIO0_FLEVEL_RX2_Pos					20u
	/*  */
#define PIO0_FLEVEL_TX2_Msk					(0xFu << 16)
#define PIO0_FLEVEL_TX2_Pos					16u
	/*  */
#define PIO0_FLEVEL_RX1_Msk					(0xFu << 12)
#define PIO0_FLEVEL_RX1_Pos					12u
	/*  */
#define PIO0_FLEVEL_TX1_Msk					(0xFu << 8)
#define PIO0_FLEVEL_TX1_Pos					8u
	/*  */
#define PIO0_FLEVEL_RX0_Msk					(0xFu << 4)
#define PIO0_FLEVEL_RX0_Pos					4u
	/*  */
#define PIO0_FLEVEL_TX0_Msk					(0xFu << 0)
#define PIO0_FLEVEL_TX0_Pos					0u

	/* 0x10: Direct write access to the TX FIFO for this state machine. */
	uint32_t volatile TXF0;

	/* 0x14: Direct write access to the TX FIFO for this state machine. */
	uint32_t volatile TXF1;

	/* 0x18: Direct write access to the TX FIFO for this state machine. */
	uint32_t volatile TXF2;

	/* 0x1C: Direct write access to the TX FIFO for this state machine. */
	uint32_t volatile TXF3;

	/* 0x20: Direct read access to the RX FIFO for this state machine. */
	uint32_t volatile RXF0;

	/* 0x24: Direct read access to the RX FIFO for this state machine. */
	uint32_t volatile RXF1;

	/* 0x28: Direct read access to the RX FIFO for this state machine. */
	uint32_t volatile RXF2;

	/* 0x2C: Direct read access to the RX FIFO for this state machine. */
	uint32_t volatile RXF3;

	/* 0x30: State machine IRQ flags register. */
	uint32_t volatile IRQ;
	/*  */
#define PIO0_IRQ_IRQ_Msk					(0xFFu << 0)
#define PIO0_IRQ_IRQ_Pos					0u

	/* 0x34: Writing a 1 to each of these bits will forcibly assert the corresponding IRQ. */
	uint32_t volatile IRQ_FORCE;
	/*  */
#define PIO0_IRQ_FORCE_IRQ_FORCE_Msk				(0xFFu << 0)
#define PIO0_IRQ_FORCE_IRQ_FORCE_Pos				0u

	/* 0x38: There is a 2-flipflop synchronizer on each GPIO input, which protects PIO logic from metastabilities. This increases input delay, and for fast synchronous IO (e.g. SPI) these synchronizers may need to be bypassed. */
	uint32_t volatile INPUT_SYNC_BYPASS;

	/* 0x3C: Read to sample the pad output values PIO is currently driving to the GPIOs. */
	uint32_t volatile DBG_PADOUT;

	/* 0x40: Read to sample the pad output enables (direction) PIO is currently driving to the GPIOs. */
	uint32_t volatile DBG_PADOE;

	/* 0x44: The PIO hardware has some free parameters that may vary between chip products. */
	uint32_t volatile DBG_CFGINFO;
	/* The size of the instruction memory, measured in units of one instruction */
#define PIO0_DBG_CFGINFO_IMEM_SIZE_Msk				(0x3Fu << 16)
#define PIO0_DBG_CFGINFO_IMEM_SIZE_Pos				16u
	/* The number of state machines this PIO instance is equipped with. */
#define PIO0_DBG_CFGINFO_SM_COUNT_Msk				(0xFu << 8)
#define PIO0_DBG_CFGINFO_SM_COUNT_Pos				8u
	/* The depth of the state machine TX/RX FIFOs, measured in words. */
#define PIO0_DBG_CFGINFO_FIFO_DEPTH_Msk				(0x3Fu << 0)
#define PIO0_DBG_CFGINFO_FIFO_DEPTH_Pos				0u

	/* 0x48: Write-only access to instruction memory location 0 */
	uint32_t volatile INSTR_MEM0;
	/*  */
#define PIO0_INSTR_MEM0_INSTR_MEM0_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM0_INSTR_MEM0_Pos				0u

	/* 0x4C: Write-only access to instruction memory location 1 */
	uint32_t volatile INSTR_MEM1;
	/*  */
#define PIO0_INSTR_MEM1_INSTR_MEM1_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM1_INSTR_MEM1_Pos				0u

	/* 0x50: Write-only access to instruction memory location 2 */
	uint32_t volatile INSTR_MEM2;
	/*  */
#define PIO0_INSTR_MEM2_INSTR_MEM2_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM2_INSTR_MEM2_Pos				0u

	/* 0x54: Write-only access to instruction memory location 3 */
	uint32_t volatile INSTR_MEM3;
	/*  */
#define PIO0_INSTR_MEM3_INSTR_MEM3_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM3_INSTR_MEM3_Pos				0u

	/* 0x58: Write-only access to instruction memory location 4 */
	uint32_t volatile INSTR_MEM4;
	/*  */
#define PIO0_INSTR_MEM4_INSTR_MEM4_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM4_INSTR_MEM4_Pos				0u

	/* 0x5C: Write-only access to instruction memory location 5 */
	uint32_t volatile INSTR_MEM5;
	/*  */
#define PIO0_INSTR_MEM5_INSTR_MEM5_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM5_INSTR_MEM5_Pos				0u

	/* 0x60: Write-only access to instruction memory location 6 */
	uint32_t volatile INSTR_MEM6;
	/*  */
#define PIO0_INSTR_MEM6_INSTR_MEM6_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM6_INSTR_MEM6_Pos				0u

	/* 0x64: Write-only access to instruction memory location 7 */
	uint32_t volatile INSTR_MEM7;
	/*  */
#define PIO0_INSTR_MEM7_INSTR_MEM7_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM7_INSTR_MEM7_Pos				0u

	/* 0x68: Write-only access to instruction memory location 8 */
	uint32_t volatile INSTR_MEM8;
	/*  */
#define PIO0_INSTR_MEM8_INSTR_MEM8_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM8_INSTR_MEM8_Pos				0u

	/* 0x6C: Write-only access to instruction memory location 9 */
	uint32_t volatile INSTR_MEM9;
	/*  */
#define PIO0_INSTR_MEM9_INSTR_MEM9_Msk				(0xFFFFu << 0)
#define PIO0_INSTR_MEM9_INSTR_MEM9_Pos				0u

	/* 0x70: Write-only access to instruction memory location 10 */
	uint32_t volatile INSTR_MEM10;
	/*  */
#define PIO0_INSTR_MEM10_INSTR_MEM10_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM10_INSTR_MEM10_Pos			0u

	/* 0x74: Write-only access to instruction memory location 11 */
	uint32_t volatile INSTR_MEM11;
	/*  */
#define PIO0_INSTR_MEM11_INSTR_MEM11_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM11_INSTR_MEM11_Pos			0u

	/* 0x78: Write-only access to instruction memory location 12 */
	uint32_t volatile INSTR_MEM12;
	/*  */
#define PIO0_INSTR_MEM12_INSTR_MEM12_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM12_INSTR_MEM12_Pos			0u

	/* 0x7C: Write-only access to instruction memory location 13 */
	uint32_t volatile INSTR_MEM13;
	/*  */
#define PIO0_INSTR_MEM13_INSTR_MEM13_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM13_INSTR_MEM13_Pos			0u

	/* 0x80: Write-only access to instruction memory location 14 */
	uint32_t volatile INSTR_MEM14;
	/*  */
#define PIO0_INSTR_MEM14_INSTR_MEM14_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM14_INSTR_MEM14_Pos			0u

	/* 0x84: Write-only access to instruction memory location 15 */
	uint32_t volatile INSTR_MEM15;
	/*  */
#define PIO0_INSTR_MEM15_INSTR_MEM15_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM15_INSTR_MEM15_Pos			0u

	/* 0x88: Write-only access to instruction memory location 16 */
	uint32_t volatile INSTR_MEM16;
	/*  */
#define PIO0_INSTR_MEM16_INSTR_MEM16_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM16_INSTR_MEM16_Pos			0u

	/* 0x8C: Write-only access to instruction memory location 17 */
	uint32_t volatile INSTR_MEM17;
	/*  */
#define PIO0_INSTR_MEM17_INSTR_MEM17_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM17_INSTR_MEM17_Pos			0u

	/* 0x90: Write-only access to instruction memory location 18 */
	uint32_t volatile INSTR_MEM18;
	/*  */
#define PIO0_INSTR_MEM18_INSTR_MEM18_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM18_INSTR_MEM18_Pos			0u

	/* 0x94: Write-only access to instruction memory location 19 */
	uint32_t volatile INSTR_MEM19;
	/*  */
#define PIO0_INSTR_MEM19_INSTR_MEM19_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM19_INSTR_MEM19_Pos			0u

	/* 0x98: Write-only access to instruction memory location 20 */
	uint32_t volatile INSTR_MEM20;
	/*  */
#define PIO0_INSTR_MEM20_INSTR_MEM20_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM20_INSTR_MEM20_Pos			0u

	/* 0x9C: Write-only access to instruction memory location 21 */
	uint32_t volatile INSTR_MEM21;
	/*  */
#define PIO0_INSTR_MEM21_INSTR_MEM21_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM21_INSTR_MEM21_Pos			0u

	/* 0xA0: Write-only access to instruction memory location 22 */
	uint32_t volatile INSTR_MEM22;
	/*  */
#define PIO0_INSTR_MEM22_INSTR_MEM22_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM22_INSTR_MEM22_Pos			0u

	/* 0xA4: Write-only access to instruction memory location 23 */
	uint32_t volatile INSTR_MEM23;
	/*  */
#define PIO0_INSTR_MEM23_INSTR_MEM23_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM23_INSTR_MEM23_Pos			0u

	/* 0xA8: Write-only access to instruction memory location 24 */
	uint32_t volatile INSTR_MEM24;
	/*  */
#define PIO0_INSTR_MEM24_INSTR_MEM24_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM24_INSTR_MEM24_Pos			0u

	/* 0xAC: Write-only access to instruction memory location 25 */
	uint32_t volatile INSTR_MEM25;
	/*  */
#define PIO0_INSTR_MEM25_INSTR_MEM25_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM25_INSTR_MEM25_Pos			0u

	/* 0xB0: Write-only access to instruction memory location 26 */
	uint32_t volatile INSTR_MEM26;
	/*  */
#define PIO0_INSTR_MEM26_INSTR_MEM26_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM26_INSTR_MEM26_Pos			0u

	/* 0xB4: Write-only access to instruction memory location 27 */
	uint32_t volatile INSTR_MEM27;
	/*  */
#define PIO0_INSTR_MEM27_INSTR_MEM27_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM27_INSTR_MEM27_Pos			0u

	/* 0xB8: Write-only access to instruction memory location 28 */
	uint32_t volatile INSTR_MEM28;
	/*  */
#define PIO0_INSTR_MEM28_INSTR_MEM28_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM28_INSTR_MEM28_Pos			0u

	/* 0xBC: Write-only access to instruction memory location 29 */
	uint32_t volatile INSTR_MEM29;
	/*  */
#define PIO0_INSTR_MEM29_INSTR_MEM29_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM29_INSTR_MEM29_Pos			0u

	/* 0xC0: Write-only access to instruction memory location 30 */
	uint32_t volatile INSTR_MEM30;
	/*  */
#define PIO0_INSTR_MEM30_INSTR_MEM30_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM30_INSTR_MEM30_Pos			0u

	/* 0xC4: Write-only access to instruction memory location 31 */
	uint32_t volatile INSTR_MEM31;
	/*  */
#define PIO0_INSTR_MEM31_INSTR_MEM31_Msk			(0xFFFFu << 0)
#define PIO0_INSTR_MEM31_INSTR_MEM31_Pos			0u

	/* 0xC8: Clock divisor register for state machine 0 */
	uint32_t volatile SM0_CLKDIV;
	/* Effective frequency is sysclk/(int + frac/256). */
#define PIO0_SM0_CLKDIV_INT_Msk					(0xFFFFu << 16)
#define PIO0_SM0_CLKDIV_INT_Pos					16u
	/* Fractional part of clock divisor */
#define PIO0_SM0_CLKDIV_FRAC_Msk				(0xFFu << 8)
#define PIO0_SM0_CLKDIV_FRAC_Pos				8u

	/* 0xCC: Execution/behavioural settings for state machine 0 */
	uint32_t volatile SM0_EXECCTRL;
	/* If 1, an instruction written to SMx_INSTR is stalled, and latched by the state machine. */
#define PIO0_SM0_EXECCTRL_EXEC_STALLED				(1u << 31)
	/* If 1, the MSB of the Delay/Side-set instruction field is used as side-set enable, rather than a side-set data bit. */
#define PIO0_SM0_EXECCTRL_SIDE_EN				(1u << 30)
	/* If 1, side-set data is asserted to pin directions, instead of pin values */
#define PIO0_SM0_EXECCTRL_SIDE_PINDIR				(1u << 29)
	/* The GPIO number to use as condition for JMP PIN. */
#define PIO0_SM0_EXECCTRL_JMP_PIN_Msk				(0x1Fu << 24)
#define PIO0_SM0_EXECCTRL_JMP_PIN_Pos				24u
	/* Which data bit to use for inline OUT enable */
#define PIO0_SM0_EXECCTRL_OUT_EN_SEL_Msk			(0x1Fu << 19)
#define PIO0_SM0_EXECCTRL_OUT_EN_SEL_Pos			19u
	/* If 1, use a bit of OUT data as an auxiliary write enable */
#define PIO0_SM0_EXECCTRL_INLINE_OUT_EN				(1u << 18)
	/* Continuously assert the most recent OUT/SET to the pins */
#define PIO0_SM0_EXECCTRL_OUT_STICKY				(1u << 17)
	/* After reaching this address, execution is wrapped to wrap_bottom. */
#define PIO0_SM0_EXECCTRL_WRAP_TOP_Msk				(0x1Fu << 12)
#define PIO0_SM0_EXECCTRL_WRAP_TOP_Pos				12u
	/* After reaching wrap_top, execution is wrapped to this address. */
#define PIO0_SM0_EXECCTRL_WRAP_BOTTOM_Msk			(0x1Fu << 7)
#define PIO0_SM0_EXECCTRL_WRAP_BOTTOM_Pos			7u
	/* Comparison used for the MOV x, STATUS instruction. */
#define PIO0_SM0_EXECCTRL_STATUS_SEL				(1u << 4)
#define PIO0_SM0_EXECCTRL_STATUS_SEL_TXLEVEL			(0x0u << 4)
#define PIO0_SM0_EXECCTRL_STATUS_SEL_RXLEVEL			(0x1u << 4)
	/* Comparison level for the MOV x, STATUS instruction */
#define PIO0_SM0_EXECCTRL_STATUS_N_Msk				(0xFu << 0)
#define PIO0_SM0_EXECCTRL_STATUS_N_Pos				0u

	/* 0xD0: Control behaviour of the input/output shift registers for state machine 0 */
	uint32_t volatile SM0_SHIFTCTRL;
	/* When 1, RX FIFO steals the TX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM0_SHIFTCTRL_FJOIN_RX				(1u << 31)
	/* When 1, TX FIFO steals the RX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM0_SHIFTCTRL_FJOIN_TX				(1u << 30)
	/* Number of bits shifted out of OSR before autopull, or conditional pull (PULL IFEMPTY), will take place. */
#define PIO0_SM0_SHIFTCTRL_PULL_THRESH_Msk			(0x1Fu << 25)
#define PIO0_SM0_SHIFTCTRL_PULL_THRESH_Pos			25u
	/* Number of bits shifted into ISR before autopush, or conditional push (PUSH IFFULL), will take place. */
#define PIO0_SM0_SHIFTCTRL_PUSH_THRESH_Msk			(0x1Fu << 20)
#define PIO0_SM0_SHIFTCTRL_PUSH_THRESH_Pos			20u
	/* 1 = shift out of output shift register to right. */
#define PIO0_SM0_SHIFTCTRL_OUT_SHIFTDIR				(1u << 19)
	/* 1 = shift input shift register to right (data enters from left). */
#define PIO0_SM0_SHIFTCTRL_IN_SHIFTDIR				(1u << 18)
	/* Pull automatically when the output shift register is emptied, i.e. */
#define PIO0_SM0_SHIFTCTRL_AUTOPULL				(1u << 17)
	/* Push automatically when the input shift register is filled, i.e. */
#define PIO0_SM0_SHIFTCTRL_AUTOPUSH				(1u << 16)

	/* 0xD4: Current instruction address of state machine 0 */
	uint32_t volatile SM0_ADDR;
	/*  */
#define PIO0_SM0_ADDR_SM0_ADDR_Msk				(0x1Fu << 0)
#define PIO0_SM0_ADDR_SM0_ADDR_Pos				0u

	/* 0xD8: Read to see the instruction currently addressed by state machine 0's program counter */
	uint32_t volatile SM0_INSTR;
	/*  */
#define PIO0_SM0_INSTR_SM0_INSTR_Msk				(0xFFFFu << 0)
#define PIO0_SM0_INSTR_SM0_INSTR_Pos				0u

	/* 0xDC: State machine pin control */
	uint32_t volatile SM0_PINCTRL;
	/* The number of MSBs of the Delay/Side-set instruction field which are used for side-set. Inclusive of the enable bit, if present. Minimum of 0 (all delay bits, no side-set) and maximum of 5 (all side-set, no delay). */
#define PIO0_SM0_PINCTRL_SIDESET_COUNT_Msk			(0x7u << 29)
#define PIO0_SM0_PINCTRL_SIDESET_COUNT_Pos			29u
	/* The number of pins asserted by a SET. */
#define PIO0_SM0_PINCTRL_SET_COUNT_Msk				(0x7u << 26)
#define PIO0_SM0_PINCTRL_SET_COUNT_Pos				26u
	/* The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM0_PINCTRL_OUT_COUNT_Msk				(0x3Fu << 20)
#define PIO0_SM0_PINCTRL_OUT_COUNT_Pos				20u
	/* The pin which is mapped to the least-significant bit of a state machine's IN data bus. */
#define PIO0_SM0_PINCTRL_IN_BASE_Msk				(0x1Fu << 15)
#define PIO0_SM0_PINCTRL_IN_BASE_Pos				15u
	/* The lowest-numbered pin that will be affected by a side-set operation. The MSBs of an instruction's side-set/delay field (up to 5, determined by SIDESET_COUNT) are used for side-set data, with the remaining LSBs used for delay. */
#define PIO0_SM0_PINCTRL_SIDESET_BASE_Msk			(0x1Fu << 10)
#define PIO0_SM0_PINCTRL_SIDESET_BASE_Pos			10u
	/* The lowest-numbered pin that will be affected by a SET PINS or SET PINDIRS instruction. */
#define PIO0_SM0_PINCTRL_SET_BASE_Msk				(0x1Fu << 5)
#define PIO0_SM0_PINCTRL_SET_BASE_Pos				5u
	/* The lowest-numbered pin that will be affected by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM0_PINCTRL_OUT_BASE_Msk				(0x1Fu << 0)
#define PIO0_SM0_PINCTRL_OUT_BASE_Pos				0u

	/* 0xE0: Clock divisor register for state machine 1 */
	uint32_t volatile SM1_CLKDIV;
	/* Effective frequency is sysclk/(int + frac/256). */
#define PIO0_SM1_CLKDIV_INT_Msk					(0xFFFFu << 16)
#define PIO0_SM1_CLKDIV_INT_Pos					16u
	/* Fractional part of clock divisor */
#define PIO0_SM1_CLKDIV_FRAC_Msk				(0xFFu << 8)
#define PIO0_SM1_CLKDIV_FRAC_Pos				8u

	/* 0xE4: Execution/behavioural settings for state machine 1 */
	uint32_t volatile SM1_EXECCTRL;
	/* If 1, an instruction written to SMx_INSTR is stalled, and latched by the state machine. */
#define PIO0_SM1_EXECCTRL_EXEC_STALLED				(1u << 31)
	/* If 1, the MSB of the Delay/Side-set instruction field is used as side-set enable, rather than a side-set data bit. */
#define PIO0_SM1_EXECCTRL_SIDE_EN				(1u << 30)
	/* If 1, side-set data is asserted to pin directions, instead of pin values */
#define PIO0_SM1_EXECCTRL_SIDE_PINDIR				(1u << 29)
	/* The GPIO number to use as condition for JMP PIN. */
#define PIO0_SM1_EXECCTRL_JMP_PIN_Msk				(0x1Fu << 24)
#define PIO0_SM1_EXECCTRL_JMP_PIN_Pos				24u
	/* Which data bit to use for inline OUT enable */
#define PIO0_SM1_EXECCTRL_OUT_EN_SEL_Msk			(0x1Fu << 19)
#define PIO0_SM1_EXECCTRL_OUT_EN_SEL_Pos			19u
	/* If 1, use a bit of OUT data as an auxiliary write enable */
#define PIO0_SM1_EXECCTRL_INLINE_OUT_EN				(1u << 18)
	/* Continuously assert the most recent OUT/SET to the pins */
#define PIO0_SM1_EXECCTRL_OUT_STICKY				(1u << 17)
	/* After reaching this address, execution is wrapped to wrap_bottom. */
#define PIO0_SM1_EXECCTRL_WRAP_TOP_Msk				(0x1Fu << 12)
#define PIO0_SM1_EXECCTRL_WRAP_TOP_Pos				12u
	/* After reaching wrap_top, execution is wrapped to this address. */
#define PIO0_SM1_EXECCTRL_WRAP_BOTTOM_Msk			(0x1Fu << 7)
#define PIO0_SM1_EXECCTRL_WRAP_BOTTOM_Pos			7u
	/* Comparison used for the MOV x, STATUS instruction. */
#define PIO0_SM1_EXECCTRL_STATUS_SEL				(1u << 4)
#define PIO0_SM1_EXECCTRL_STATUS_SEL_TXLEVEL			(0x0u << 4)
#define PIO0_SM1_EXECCTRL_STATUS_SEL_RXLEVEL			(0x1u << 4)
	/* Comparison level for the MOV x, STATUS instruction */
#define PIO0_SM1_EXECCTRL_STATUS_N_Msk				(0xFu << 0)
#define PIO0_SM1_EXECCTRL_STATUS_N_Pos				0u

	/* 0xE8: Control behaviour of the input/output shift registers for state machine 1 */
	uint32_t volatile SM1_SHIFTCTRL;
	/* When 1, RX FIFO steals the TX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM1_SHIFTCTRL_FJOIN_RX				(1u << 31)
	/* When 1, TX FIFO steals the RX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM1_SHIFTCTRL_FJOIN_TX				(1u << 30)
	/* Number of bits shifted out of OSR before autopull, or conditional pull (PULL IFEMPTY), will take place. */
#define PIO0_SM1_SHIFTCTRL_PULL_THRESH_Msk			(0x1Fu << 25)
#define PIO0_SM1_SHIFTCTRL_PULL_THRESH_Pos			25u
	/* Number of bits shifted into ISR before autopush, or conditional push (PUSH IFFULL), will take place. */
#define PIO0_SM1_SHIFTCTRL_PUSH_THRESH_Msk			(0x1Fu << 20)
#define PIO0_SM1_SHIFTCTRL_PUSH_THRESH_Pos			20u
	/* 1 = shift out of output shift register to right. */
#define PIO0_SM1_SHIFTCTRL_OUT_SHIFTDIR				(1u << 19)
	/* 1 = shift input shift register to right (data enters from left). */
#define PIO0_SM1_SHIFTCTRL_IN_SHIFTDIR				(1u << 18)
	/* Pull automatically when the output shift register is emptied, i.e. */
#define PIO0_SM1_SHIFTCTRL_AUTOPULL				(1u << 17)
	/* Push automatically when the input shift register is filled, i.e. */
#define PIO0_SM1_SHIFTCTRL_AUTOPUSH				(1u << 16)

	/* 0xEC: Current instruction address of state machine 1 */
	uint32_t volatile SM1_ADDR;
	/*  */
#define PIO0_SM1_ADDR_SM1_ADDR_Msk				(0x1Fu << 0)
#define PIO0_SM1_ADDR_SM1_ADDR_Pos				0u

	/* 0xF0: Read to see the instruction currently addressed by state machine 1's program counter */
	uint32_t volatile SM1_INSTR;
	/*  */
#define PIO0_SM1_INSTR_SM1_INSTR_Msk				(0xFFFFu << 0)
#define PIO0_SM1_INSTR_SM1_INSTR_Pos				0u

	/* 0xF4: State machine pin control */
	uint32_t volatile SM1_PINCTRL;
	/* The number of MSBs of the Delay/Side-set instruction field which are used for side-set. Inclusive of the enable bit, if present. Minimum of 0 (all delay bits, no side-set) and maximum of 5 (all side-set, no delay). */
#define PIO0_SM1_PINCTRL_SIDESET_COUNT_Msk			(0x7u << 29)
#define PIO0_SM1_PINCTRL_SIDESET_COUNT_Pos			29u
	/* The number of pins asserted by a SET. */
#define PIO0_SM1_PINCTRL_SET_COUNT_Msk				(0x7u << 26)
#define PIO0_SM1_PINCTRL_SET_COUNT_Pos				26u
	/* The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM1_PINCTRL_OUT_COUNT_Msk				(0x3Fu << 20)
#define PIO0_SM1_PINCTRL_OUT_COUNT_Pos				20u
	/* The pin which is mapped to the least-significant bit of a state machine's IN data bus. */
#define PIO0_SM1_PINCTRL_IN_BASE_Msk				(0x1Fu << 15)
#define PIO0_SM1_PINCTRL_IN_BASE_Pos				15u
	/* The lowest-numbered pin that will be affected by a side-set operation. The MSBs of an instruction's side-set/delay field (up to 5, determined by SIDESET_COUNT) are used for side-set data, with the remaining LSBs used for delay. */
#define PIO0_SM1_PINCTRL_SIDESET_BASE_Msk			(0x1Fu << 10)
#define PIO0_SM1_PINCTRL_SIDESET_BASE_Pos			10u
	/* The lowest-numbered pin that will be affected by a SET PINS or SET PINDIRS instruction. */
#define PIO0_SM1_PINCTRL_SET_BASE_Msk				(0x1Fu << 5)
#define PIO0_SM1_PINCTRL_SET_BASE_Pos				5u
	/* The lowest-numbered pin that will be affected by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM1_PINCTRL_OUT_BASE_Msk				(0x1Fu << 0)
#define PIO0_SM1_PINCTRL_OUT_BASE_Pos				0u

	/* 0xF8: Clock divisor register for state machine 2 */
	uint32_t volatile SM2_CLKDIV;
	/* Effective frequency is sysclk/(int + frac/256). */
#define PIO0_SM2_CLKDIV_INT_Msk					(0xFFFFu << 16)
#define PIO0_SM2_CLKDIV_INT_Pos					16u
	/* Fractional part of clock divisor */
#define PIO0_SM2_CLKDIV_FRAC_Msk				(0xFFu << 8)
#define PIO0_SM2_CLKDIV_FRAC_Pos				8u

	/* 0xFC: Execution/behavioural settings for state machine 2 */
	uint32_t volatile SM2_EXECCTRL;
	/* If 1, an instruction written to SMx_INSTR is stalled, and latched by the state machine. */
#define PIO0_SM2_EXECCTRL_EXEC_STALLED				(1u << 31)
	/* If 1, the MSB of the Delay/Side-set instruction field is used as side-set enable, rather than a side-set data bit. */
#define PIO0_SM2_EXECCTRL_SIDE_EN				(1u << 30)
	/* If 1, side-set data is asserted to pin directions, instead of pin values */
#define PIO0_SM2_EXECCTRL_SIDE_PINDIR				(1u << 29)
	/* The GPIO number to use as condition for JMP PIN. */
#define PIO0_SM2_EXECCTRL_JMP_PIN_Msk				(0x1Fu << 24)
#define PIO0_SM2_EXECCTRL_JMP_PIN_Pos				24u
	/* Which data bit to use for inline OUT enable */
#define PIO0_SM2_EXECCTRL_OUT_EN_SEL_Msk			(0x1Fu << 19)
#define PIO0_SM2_EXECCTRL_OUT_EN_SEL_Pos			19u
	/* If 1, use a bit of OUT data as an auxiliary write enable */
#define PIO0_SM2_EXECCTRL_INLINE_OUT_EN				(1u << 18)
	/* Continuously assert the most recent OUT/SET to the pins */
#define PIO0_SM2_EXECCTRL_OUT_STICKY				(1u << 17)
	/* After reaching this address, execution is wrapped to wrap_bottom. */
#define PIO0_SM2_EXECCTRL_WRAP_TOP_Msk				(0x1Fu << 12)
#define PIO0_SM2_EXECCTRL_WRAP_TOP_Pos				12u
	/* After reaching wrap_top, execution is wrapped to this address. */
#define PIO0_SM2_EXECCTRL_WRAP_BOTTOM_Msk			(0x1Fu << 7)
#define PIO0_SM2_EXECCTRL_WRAP_BOTTOM_Pos			7u
	/* Comparison used for the MOV x, STATUS instruction. */
#define PIO0_SM2_EXECCTRL_STATUS_SEL				(1u << 4)
#define PIO0_SM2_EXECCTRL_STATUS_SEL_TXLEVEL			(0x0u << 4)
#define PIO0_SM2_EXECCTRL_STATUS_SEL_RXLEVEL			(0x1u << 4)
	/* Comparison level for the MOV x, STATUS instruction */
#define PIO0_SM2_EXECCTRL_STATUS_N_Msk				(0xFu << 0)
#define PIO0_SM2_EXECCTRL_STATUS_N_Pos				0u

	/* 0x100: Control behaviour of the input/output shift registers for state machine 2 */
	uint32_t volatile SM2_SHIFTCTRL;
	/* When 1, RX FIFO steals the TX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM2_SHIFTCTRL_FJOIN_RX				(1u << 31)
	/* When 1, TX FIFO steals the RX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM2_SHIFTCTRL_FJOIN_TX				(1u << 30)
	/* Number of bits shifted out of OSR before autopull, or conditional pull (PULL IFEMPTY), will take place. */
#define PIO0_SM2_SHIFTCTRL_PULL_THRESH_Msk			(0x1Fu << 25)
#define PIO0_SM2_SHIFTCTRL_PULL_THRESH_Pos			25u
	/* Number of bits shifted into ISR before autopush, or conditional push (PUSH IFFULL), will take place. */
#define PIO0_SM2_SHIFTCTRL_PUSH_THRESH_Msk			(0x1Fu << 20)
#define PIO0_SM2_SHIFTCTRL_PUSH_THRESH_Pos			20u
	/* 1 = shift out of output shift register to right. */
#define PIO0_SM2_SHIFTCTRL_OUT_SHIFTDIR				(1u << 19)
	/* 1 = shift input shift register to right (data enters from left). */
#define PIO0_SM2_SHIFTCTRL_IN_SHIFTDIR				(1u << 18)
	/* Pull automatically when the output shift register is emptied, i.e. */
#define PIO0_SM2_SHIFTCTRL_AUTOPULL				(1u << 17)
	/* Push automatically when the input shift register is filled, i.e. */
#define PIO0_SM2_SHIFTCTRL_AUTOPUSH				(1u << 16)

	/* 0x104: Current instruction address of state machine 2 */
	uint32_t volatile SM2_ADDR;
	/*  */
#define PIO0_SM2_ADDR_SM2_ADDR_Msk				(0x1Fu << 0)
#define PIO0_SM2_ADDR_SM2_ADDR_Pos				0u

	/* 0x108: Read to see the instruction currently addressed by state machine 2's program counter */
	uint32_t volatile SM2_INSTR;
	/*  */
#define PIO0_SM2_INSTR_SM2_INSTR_Msk				(0xFFFFu << 0)
#define PIO0_SM2_INSTR_SM2_INSTR_Pos				0u

	/* 0x10C: State machine pin control */
	uint32_t volatile SM2_PINCTRL;
	/* The number of MSBs of the Delay/Side-set instruction field which are used for side-set. Inclusive of the enable bit, if present. Minimum of 0 (all delay bits, no side-set) and maximum of 5 (all side-set, no delay). */
#define PIO0_SM2_PINCTRL_SIDESET_COUNT_Msk			(0x7u << 29)
#define PIO0_SM2_PINCTRL_SIDESET_COUNT_Pos			29u
	/* The number of pins asserted by a SET. */
#define PIO0_SM2_PINCTRL_SET_COUNT_Msk				(0x7u << 26)
#define PIO0_SM2_PINCTRL_SET_COUNT_Pos				26u
	/* The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM2_PINCTRL_OUT_COUNT_Msk				(0x3Fu << 20)
#define PIO0_SM2_PINCTRL_OUT_COUNT_Pos				20u
	/* The pin which is mapped to the least-significant bit of a state machine's IN data bus. */
#define PIO0_SM2_PINCTRL_IN_BASE_Msk				(0x1Fu << 15)
#define PIO0_SM2_PINCTRL_IN_BASE_Pos				15u
	/* The lowest-numbered pin that will be affected by a side-set operation. The MSBs of an instruction's side-set/delay field (up to 5, determined by SIDESET_COUNT) are used for side-set data, with the remaining LSBs used for delay. */
#define PIO0_SM2_PINCTRL_SIDESET_BASE_Msk			(0x1Fu << 10)
#define PIO0_SM2_PINCTRL_SIDESET_BASE_Pos			10u
	/* The lowest-numbered pin that will be affected by a SET PINS or SET PINDIRS instruction. */
#define PIO0_SM2_PINCTRL_SET_BASE_Msk				(0x1Fu << 5)
#define PIO0_SM2_PINCTRL_SET_BASE_Pos				5u
	/* The lowest-numbered pin that will be affected by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM2_PINCTRL_OUT_BASE_Msk				(0x1Fu << 0)
#define PIO0_SM2_PINCTRL_OUT_BASE_Pos				0u

	/* 0x110: Clock divisor register for state machine 3 */
	uint32_t volatile SM3_CLKDIV;
	/* Effective frequency is sysclk/(int + frac/256). */
#define PIO0_SM3_CLKDIV_INT_Msk					(0xFFFFu << 16)
#define PIO0_SM3_CLKDIV_INT_Pos					16u
	/* Fractional part of clock divisor */
#define PIO0_SM3_CLKDIV_FRAC_Msk				(0xFFu << 8)
#define PIO0_SM3_CLKDIV_FRAC_Pos				8u

	/* 0x114: Execution/behavioural settings for state machine 3 */
	uint32_t volatile SM3_EXECCTRL;
	/* If 1, an instruction written to SMx_INSTR is stalled, and latched by the state machine. */
#define PIO0_SM3_EXECCTRL_EXEC_STALLED				(1u << 31)
	/* If 1, the MSB of the Delay/Side-set instruction field is used as side-set enable, rather than a side-set data bit. */
#define PIO0_SM3_EXECCTRL_SIDE_EN				(1u << 30)
	/* If 1, side-set data is asserted to pin directions, instead of pin values */
#define PIO0_SM3_EXECCTRL_SIDE_PINDIR				(1u << 29)
	/* The GPIO number to use as condition for JMP PIN. */
#define PIO0_SM3_EXECCTRL_JMP_PIN_Msk				(0x1Fu << 24)
#define PIO0_SM3_EXECCTRL_JMP_PIN_Pos				24u
	/* Which data bit to use for inline OUT enable */
#define PIO0_SM3_EXECCTRL_OUT_EN_SEL_Msk			(0x1Fu << 19)
#define PIO0_SM3_EXECCTRL_OUT_EN_SEL_Pos			19u
	/* If 1, use a bit of OUT data as an auxiliary write enable */
#define PIO0_SM3_EXECCTRL_INLINE_OUT_EN				(1u << 18)
	/* Continuously assert the most recent OUT/SET to the pins */
#define PIO0_SM3_EXECCTRL_OUT_STICKY				(1u << 17)
	/* After reaching this address, execution is wrapped to wrap_bottom. */
#define PIO0_SM3_EXECCTRL_WRAP_TOP_Msk				(0x1Fu << 12)
#define PIO0_SM3_EXECCTRL_WRAP_TOP_Pos				12u
	/* After reaching wrap_top, execution is wrapped to this address. */
#define PIO0_SM3_EXECCTRL_WRAP_BOTTOM_Msk			(0x1Fu << 7)
#define PIO0_SM3_EXECCTRL_WRAP_BOTTOM_Pos			7u
	/* Comparison used for the MOV x, STATUS instruction. */
#define PIO0_SM3_EXECCTRL_STATUS_SEL				(1u << 4)
#define PIO0_SM3_EXECCTRL_STATUS_SEL_TXLEVEL			(0x0u << 4)
#define PIO0_SM3_EXECCTRL_STATUS_SEL_RXLEVEL			(0x1u << 4)
	/* Comparison level for the MOV x, STATUS instruction */
#define PIO0_SM3_EXECCTRL_STATUS_N_Msk				(0xFu << 0)
#define PIO0_SM3_EXECCTRL_STATUS_N_Pos				0u

	/* 0x118: Control behaviour of the input/output shift registers for state machine 3 */
	uint32_t volatile SM3_SHIFTCTRL;
	/* When 1, RX FIFO steals the TX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM3_SHIFTCTRL_FJOIN_RX				(1u << 31)
	/* When 1, TX FIFO steals the RX FIFO's storage, and becomes twice as deep. */
#define PIO0_SM3_SHIFTCTRL_FJOIN_TX				(1u << 30)
	/* Number of bits shifted out of OSR before autopull, or conditional pull (PULL IFEMPTY), will take place. */
#define PIO0_SM3_SHIFTCTRL_PULL_THRESH_Msk			(0x1Fu << 25)
#define PIO0_SM3_SHIFTCTRL_PULL_THRESH_Pos			25u
	/* Number of bits shifted into ISR before autopush, or conditional push (PUSH IFFULL), will take place. */
#define PIO0_SM3_SHIFTCTRL_PUSH_THRESH_Msk			(0x1Fu << 20)
#define PIO0_SM3_SHIFTCTRL_PUSH_THRESH_Pos			20u
	/* 1 = shift out of output shift register to right. */
#define PIO0_SM3_SHIFTCTRL_OUT_SHIFTDIR				(1u << 19)
	/* 1 = shift input shift register to right (data enters from left). */
#define PIO0_SM3_SHIFTCTRL_IN_SHIFTDIR				(1u << 18)
	/* Pull automatically when the output shift register is emptied, i.e. */
#define PIO0_SM3_SHIFTCTRL_AUTOPULL				(1u << 17)
	/* Push automatically when the input shift register is filled, i.e. */
#define PIO0_SM3_SHIFTCTRL_AUTOPUSH				(1u << 16)

	/* 0x11C: Current instruction address of state machine 3 */
	uint32_t volatile SM3_ADDR;
	/*  */
#define PIO0_SM3_ADDR_SM3_ADDR_Msk				(0x1Fu << 0)
#define PIO0_SM3_ADDR_SM3_ADDR_Pos				0u

	/* 0x120: Read to see the instruction currently addressed by state machine 3's program counter */
	uint32_t volatile SM3_INSTR;
	/*  */
#define PIO0_SM3_INSTR_SM3_INSTR_Msk				(0xFFFFu << 0)
#define PIO0_SM3_INSTR_SM3_INSTR_Pos				0u

	/* 0x124: State machine pin control */
	uint32_t volatile SM3_PINCTRL;
	/* The number of MSBs of the Delay/Side-set instruction field which are used for side-set. Inclusive of the enable bit, if present. Minimum of 0 (all delay bits, no side-set) and maximum of 5 (all side-set, no delay). */
#define PIO0_SM3_PINCTRL_SIDESET_COUNT_Msk			(0x7u << 29)
#define PIO0_SM3_PINCTRL_SIDESET_COUNT_Pos			29u
	/* The number of pins asserted by a SET. */
#define PIO0_SM3_PINCTRL_SET_COUNT_Msk				(0x7u << 26)
#define PIO0_SM3_PINCTRL_SET_COUNT_Pos				26u
	/* The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM3_PINCTRL_OUT_COUNT_Msk				(0x3Fu << 20)
#define PIO0_SM3_PINCTRL_OUT_COUNT_Pos				20u
	/* The pin which is mapped to the least-significant bit of a state machine's IN data bus. */
#define PIO0_SM3_PINCTRL_IN_BASE_Msk				(0x1Fu << 15)
#define PIO0_SM3_PINCTRL_IN_BASE_Pos				15u
	/* The lowest-numbered pin that will be affected by a side-set operation. The MSBs of an instruction's side-set/delay field (up to 5, determined by SIDESET_COUNT) are used for side-set data, with the remaining LSBs used for delay. */
#define PIO0_SM3_PINCTRL_SIDESET_BASE_Msk			(0x1Fu << 10)
#define PIO0_SM3_PINCTRL_SIDESET_BASE_Pos			10u
	/* The lowest-numbered pin that will be affected by a SET PINS or SET PINDIRS instruction. */
#define PIO0_SM3_PINCTRL_SET_BASE_Msk				(0x1Fu << 5)
#define PIO0_SM3_PINCTRL_SET_BASE_Pos				5u
	/* The lowest-numbered pin that will be affected by an OUT PINS, OUT PINDIRS or MOV PINS instruction. */
#define PIO0_SM3_PINCTRL_OUT_BASE_Msk				(0x1Fu << 0)
#define PIO0_SM3_PINCTRL_OUT_BASE_Pos				0u

	/* 0x128: Raw Interrupts */
	uint32_t volatile INTR;
	/*  */
#define PIO0_INTR_SM3						(1u << 11)
	/*  */
#define PIO0_INTR_SM2						(1u << 10)
	/*  */
#define PIO0_INTR_SM1						(1u << 9)
	/*  */
#define PIO0_INTR_SM0						(1u << 8)
	/*  */
#define PIO0_INTR_SM3_TXNFULL					(1u << 7)
	/*  */
#define PIO0_INTR_SM2_TXNFULL					(1u << 6)
	/*  */
#define PIO0_INTR_SM1_TXNFULL					(1u << 5)
	/*  */
#define PIO0_INTR_SM0_TXNFULL					(1u << 4)
	/*  */
#define PIO0_INTR_SM3_RXNEMPTY					(1u << 3)
	/*  */
#define PIO0_INTR_SM2_RXNEMPTY					(1u << 2)
	/*  */
#define PIO0_INTR_SM1_RXNEMPTY					(1u << 1)
	/*  */
#define PIO0_INTR_SM0_RXNEMPTY					(1u << 0)

	/* 0x12C: Interrupt Enable for irq0 */
	uint32_t volatile IRQ0_INTE;
	/*  */
#define PIO0_IRQ0_INTE_SM3					(1u << 11)
	/*  */
#define PIO0_IRQ0_INTE_SM2					(1u << 10)
	/*  */
#define PIO0_IRQ0_INTE_SM1					(1u << 9)
	/*  */
#define PIO0_IRQ0_INTE_SM0					(1u << 8)
	/*  */
#define PIO0_IRQ0_INTE_SM3_TXNFULL				(1u << 7)
	/*  */
#define PIO0_IRQ0_INTE_SM2_TXNFULL				(1u << 6)
	/*  */
#define PIO0_IRQ0_INTE_SM1_TXNFULL				(1u << 5)
	/*  */
#define PIO0_IRQ0_INTE_SM0_TXNFULL				(1u << 4)
	/*  */
#define PIO0_IRQ0_INTE_SM3_RXNEMPTY				(1u << 3)
	/*  */
#define PIO0_IRQ0_INTE_SM2_RXNEMPTY				(1u << 2)
	/*  */
#define PIO0_IRQ0_INTE_SM1_RXNEMPTY				(1u << 1)
	/*  */
#define PIO0_IRQ0_INTE_SM0_RXNEMPTY				(1u << 0)

	/* 0x130: Interrupt Force for irq0 */
	uint32_t volatile IRQ0_INTF;
	/*  */
#define PIO0_IRQ0_INTF_SM3					(1u << 11)
	/*  */
#define PIO0_IRQ0_INTF_SM2					(1u << 10)
	/*  */
#define PIO0_IRQ0_INTF_SM1					(1u << 9)
	/*  */
#define PIO0_IRQ0_INTF_SM0					(1u << 8)
	/*  */
#define PIO0_IRQ0_INTF_SM3_TXNFULL				(1u << 7)
	/*  */
#define PIO0_IRQ0_INTF_SM2_TXNFULL				(1u << 6)
	/*  */
#define PIO0_IRQ0_INTF_SM1_TXNFULL				(1u << 5)
	/*  */
#define PIO0_IRQ0_INTF_SM0_TXNFULL				(1u << 4)
	/*  */
#define PIO0_IRQ0_INTF_SM3_RXNEMPTY				(1u << 3)
	/*  */
#define PIO0_IRQ0_INTF_SM2_RXNEMPTY				(1u << 2)
	/*  */
#define PIO0_IRQ0_INTF_SM1_RXNEMPTY				(1u << 1)
	/*  */
#define PIO0_IRQ0_INTF_SM0_RXNEMPTY				(1u << 0)

	/* 0x134: Interrupt status after masking & forcing for irq0 */
	uint32_t volatile IRQ0_INTS;
	/*  */
#define PIO0_IRQ0_INTS_SM3					(1u << 11)
	/*  */
#define PIO0_IRQ0_INTS_SM2					(1u << 10)
	/*  */
#define PIO0_IRQ0_INTS_SM1					(1u << 9)
	/*  */
#define PIO0_IRQ0_INTS_SM0					(1u << 8)
	/*  */
#define PIO0_IRQ0_INTS_SM3_TXNFULL				(1u << 7)
	/*  */
#define PIO0_IRQ0_INTS_SM2_TXNFULL				(1u << 6)
	/*  */
#define PIO0_IRQ0_INTS_SM1_TXNFULL				(1u << 5)
	/*  */
#define PIO0_IRQ0_INTS_SM0_TXNFULL				(1u << 4)
	/*  */
#define PIO0_IRQ0_INTS_SM3_RXNEMPTY				(1u << 3)
	/*  */
#define PIO0_IRQ0_INTS_SM2_RXNEMPTY				(1u << 2)
	/*  */
#define PIO0_IRQ0_INTS_SM1_RXNEMPTY				(1u << 1)
	/*  */
#define PIO0_IRQ0_INTS_SM0_RXNEMPTY				(1u << 0)

	/* 0x138: Interrupt Enable for irq1 */
	uint32_t volatile IRQ1_INTE;
	/*  */
#define PIO0_IRQ1_INTE_SM3					(1u << 11)
	/*  */
#define PIO0_IRQ1_INTE_SM2					(1u << 10)
	/*  */
#define PIO0_IRQ1_INTE_SM1					(1u << 9)
	/*  */
#define PIO0_IRQ1_INTE_SM0					(1u << 8)
	/*  */
#define PIO0_IRQ1_INTE_SM3_TXNFULL				(1u << 7)
	/*  */
#define PIO0_IRQ1_INTE_SM2_TXNFULL				(1u << 6)
	/*  */
#define PIO0_IRQ1_INTE_SM1_TXNFULL				(1u << 5)
	/*  */
#define PIO0_IRQ1_INTE_SM0_TXNFULL				(1u << 4)
	/*  */
#define PIO0_IRQ1_INTE_SM3_RXNEMPTY				(1u << 3)
	/*  */
#define PIO0_IRQ1_INTE_SM2_RXNEMPTY				(1u << 2)
	/*  */
#define PIO0_IRQ1_INTE_SM1_RXNEMPTY				(1u << 1)
	/*  */
#define PIO0_IRQ1_INTE_SM0_RXNEMPTY				(1u << 0)

	/* 0x13C: Interrupt Force for irq1 */
	uint32_t volatile IRQ1_INTF;
	/*  */
#define PIO0_IRQ1_INTF_SM3					(1u << 11)
	/*  */
#define PIO0_IRQ1_INTF_SM2					(1u << 10)
	/*  */
#define PIO0_IRQ1_INTF_SM1					(1u << 9)
	/*  */
#define PIO0_IRQ1_INTF_SM0					(1u << 8)
	/*  */
#define PIO0_IRQ1_INTF_SM3_TXNFULL				(1u << 7)
	/*  */
#define PIO0_IRQ1_INTF_SM2_TXNFULL				(1u << 6)
	/*  */
#define PIO0_IRQ1_INTF_SM1_TXNFULL				(1u << 5)
	/*  */
#define PIO0_IRQ1_INTF_SM0_TXNFULL				(1u << 4)
	/*  */
#define PIO0_IRQ1_INTF_SM3_RXNEMPTY				(1u << 3)
	/*  */
#define PIO0_IRQ1_INTF_SM2_RXNEMPTY				(1u << 2)
	/*  */
#define PIO0_IRQ1_INTF_SM1_RXNEMPTY				(1u << 1)
	/*  */
#define PIO0_IRQ1_INTF_SM0_RXNEMPTY				(1u << 0)

	/* 0x140: Interrupt status after masking & forcing for irq1 */
	uint32_t volatile IRQ1_INTS;
	/*  */
#define PIO0_IRQ1_INTS_SM3					(1u << 11)
	/*  */
#define PIO0_IRQ1_INTS_SM2					(1u << 10)
	/*  */
#define PIO0_IRQ1_INTS_SM1					(1u << 9)
	/*  */
#define PIO0_IRQ1_INTS_SM0					(1u << 8)
	/*  */
#define PIO0_IRQ1_INTS_SM3_TXNFULL				(1u << 7)
	/*  */
#define PIO0_IRQ1_INTS_SM2_TXNFULL				(1u << 6)
	/*  */
#define PIO0_IRQ1_INTS_SM1_TXNFULL				(1u << 5)
	/*  */
#define PIO0_IRQ1_INTS_SM0_TXNFULL				(1u << 4)
	/*  */
#define PIO0_IRQ1_INTS_SM3_RXNEMPTY				(1u << 3)
	/*  */
#define PIO0_IRQ1_INTS_SM2_RXNEMPTY				(1u << 2)
	/*  */
#define PIO0_IRQ1_INTS_SM1_RXNEMPTY				(1u << 1)
	/*  */
#define PIO0_IRQ1_INTS_SM0_RXNEMPTY				(1u << 0)

};


#define SIO ((struct mcu_sio *)0xD0000000)

struct mcu_sio {

	/* 0x00: Processor core identifier */
	uint32_t volatile CPUID;

	/* 0x04: Input value for GPIO pins */
	uint32_t volatile GPIO_IN;
	/* Input value for GPIO0...29 */
#define SIO_GPIO_IN_GPIO_IN_Msk					(0x3FFFFFFFu << 0)
#define SIO_GPIO_IN_GPIO_IN_Pos					0u

	/* 0x08: Input value for QSPI pins */
	uint32_t volatile GPIO_HI_IN;
	/* Input value on QSPI IO in order 0..5: SCLK, SSn, SD0, SD1, SD2, SD3 */
#define SIO_GPIO_HI_IN_GPIO_HI_IN_Msk				(0x3Fu << 0)
#define SIO_GPIO_HI_IN_GPIO_HI_IN_Pos				0u

	/* 0x0C */
	uint8_t RESERVED0[0x10u-0x0Cu];

	/* 0x10: GPIO output value */
	uint32_t volatile GPIO_OUT;
	/* Set output level (1/0 -> high/low) for GPIO0...29. */
#define SIO_GPIO_OUT_GPIO_OUT_Msk				(0x3FFFFFFFu << 0)
#define SIO_GPIO_OUT_GPIO_OUT_Pos				0u

	/* 0x14: GPIO output value set */
	uint32_t volatile GPIO_OUT_SET;
	/* Perform an atomic bit-set on GPIO_OUT, i.e. */
#define SIO_GPIO_OUT_SET_GPIO_OUT_SET_Msk			(0x3FFFFFFFu << 0)
#define SIO_GPIO_OUT_SET_GPIO_OUT_SET_Pos			0u

	/* 0x18: GPIO output value clear */
	uint32_t volatile GPIO_OUT_CLR;
	/* Perform an atomic bit-clear on GPIO_OUT, i.e. */
#define SIO_GPIO_OUT_CLR_GPIO_OUT_CLR_Msk			(0x3FFFFFFFu << 0)
#define SIO_GPIO_OUT_CLR_GPIO_OUT_CLR_Pos			0u

	/* 0x1C: GPIO output value XOR */
	uint32_t volatile GPIO_OUT_XOR;
	/* Perform an atomic bitwise XOR on GPIO_OUT, i.e. */
#define SIO_GPIO_OUT_XOR_GPIO_OUT_XOR_Msk			(0x3FFFFFFFu << 0)
#define SIO_GPIO_OUT_XOR_GPIO_OUT_XOR_Pos			0u

	/* 0x20: GPIO output enable */
	uint32_t volatile GPIO_OE;
	/* Set output enable (1/0 -> output/input) for GPIO0...29. */
#define SIO_GPIO_OE_GPIO_OE_Msk					(0x3FFFFFFFu << 0)
#define SIO_GPIO_OE_GPIO_OE_Pos					0u

	/* 0x24: GPIO output enable set */
	uint32_t volatile GPIO_OE_SET;
	/* Perform an atomic bit-set on GPIO_OE, i.e. */
#define SIO_GPIO_OE_SET_GPIO_OE_SET_Msk				(0x3FFFFFFFu << 0)
#define SIO_GPIO_OE_SET_GPIO_OE_SET_Pos				0u

	/* 0x28: GPIO output enable clear */
	uint32_t volatile GPIO_OE_CLR;
	/* Perform an atomic bit-clear on GPIO_OE, i.e. */
#define SIO_GPIO_OE_CLR_GPIO_OE_CLR_Msk				(0x3FFFFFFFu << 0)
#define SIO_GPIO_OE_CLR_GPIO_OE_CLR_Pos				0u

	/* 0x2C: GPIO output enable XOR */
	uint32_t volatile GPIO_OE_XOR;
	/* Perform an atomic bitwise XOR on GPIO_OE, i.e. */
#define SIO_GPIO_OE_XOR_GPIO_OE_XOR_Msk				(0x3FFFFFFFu << 0)
#define SIO_GPIO_OE_XOR_GPIO_OE_XOR_Pos				0u

	/* 0x30: QSPI output value */
	uint32_t volatile GPIO_HI_OUT;
	/* Set output level (1/0 -> high/low) for QSPI IO0...5. */
#define SIO_GPIO_HI_OUT_GPIO_HI_OUT_Msk				(0x3Fu << 0)
#define SIO_GPIO_HI_OUT_GPIO_HI_OUT_Pos				0u

	/* 0x34: QSPI output value set */
	uint32_t volatile GPIO_HI_OUT_SET;
	/* Perform an atomic bit-set on GPIO_HI_OUT, i.e. */
#define SIO_GPIO_HI_OUT_SET_GPIO_HI_OUT_SET_Msk			(0x3Fu << 0)
#define SIO_GPIO_HI_OUT_SET_GPIO_HI_OUT_SET_Pos			0u

	/* 0x38: QSPI output value clear */
	uint32_t volatile GPIO_HI_OUT_CLR;
	/* Perform an atomic bit-clear on GPIO_HI_OUT, i.e. */
#define SIO_GPIO_HI_OUT_CLR_GPIO_HI_OUT_CLR_Msk			(0x3Fu << 0)
#define SIO_GPIO_HI_OUT_CLR_GPIO_HI_OUT_CLR_Pos			0u

	/* 0x3C: QSPI output value XOR */
	uint32_t volatile GPIO_HI_OUT_XOR;
	/* Perform an atomic bitwise XOR on GPIO_HI_OUT, i.e. */
#define SIO_GPIO_HI_OUT_XOR_GPIO_HI_OUT_XOR_Msk			(0x3Fu << 0)
#define SIO_GPIO_HI_OUT_XOR_GPIO_HI_OUT_XOR_Pos			0u

	/* 0x40: QSPI output enable */
	uint32_t volatile GPIO_HI_OE;
	/* Set output enable (1/0 -> output/input) for QSPI IO0...5. */
#define SIO_GPIO_HI_OE_GPIO_HI_OE_Msk				(0x3Fu << 0)
#define SIO_GPIO_HI_OE_GPIO_HI_OE_Pos				0u

	/* 0x44: QSPI output enable set */
	uint32_t volatile GPIO_HI_OE_SET;
	/* Perform an atomic bit-set on GPIO_HI_OE, i.e. */
#define SIO_GPIO_HI_OE_SET_GPIO_HI_OE_SET_Msk			(0x3Fu << 0)
#define SIO_GPIO_HI_OE_SET_GPIO_HI_OE_SET_Pos			0u

	/* 0x48: QSPI output enable clear */
	uint32_t volatile GPIO_HI_OE_CLR;
	/* Perform an atomic bit-clear on GPIO_HI_OE, i.e. */
#define SIO_GPIO_HI_OE_CLR_GPIO_HI_OE_CLR_Msk			(0x3Fu << 0)
#define SIO_GPIO_HI_OE_CLR_GPIO_HI_OE_CLR_Pos			0u

	/* 0x4C: QSPI output enable XOR */
	uint32_t volatile GPIO_HI_OE_XOR;
	/* Perform an atomic bitwise XOR on GPIO_HI_OE, i.e. */
#define SIO_GPIO_HI_OE_XOR_GPIO_HI_OE_XOR_Msk			(0x3Fu << 0)
#define SIO_GPIO_HI_OE_XOR_GPIO_HI_OE_XOR_Pos			0u

	/* 0x50: Status register for inter-core FIFOs (mailboxes). */
	uint32_t volatile FIFO_ST;
	/* Sticky flag indicating the RX FIFO was read when empty. */
#define SIO_FIFO_ST_ROE						(1u << 3)
	/* Sticky flag indicating the TX FIFO was written when full. */
#define SIO_FIFO_ST_WOF						(1u << 2)
	/* Value is 1 if this core's TX FIFO is not full (i.e. if FIFO_WR is ready for more data) */
#define SIO_FIFO_ST_RDY						(1u << 1)
	/* Value is 1 if this core's RX FIFO is not empty (i.e. if FIFO_RD is valid) */
#define SIO_FIFO_ST_VLD						(1u << 0)

	/* 0x54: Write access to this core's TX FIFO */
	uint32_t volatile FIFO_WR;

	/* 0x58: Read access to this core's RX FIFO */
	uint32_t volatile FIFO_RD;

	/* 0x5C: Spinlock state */
	uint32_t volatile SPINLOCK_ST;

	/* 0x60: Divider unsigned dividend */
	uint32_t volatile DIV_UDIVIDEND;

	/* 0x64: Divider unsigned divisor */
	uint32_t volatile DIV_UDIVISOR;

	/* 0x68: Divider signed dividend */
	uint32_t volatile DIV_SDIVIDEND;

	/* 0x6C: Divider signed divisor */
	uint32_t volatile DIV_SDIVISOR;

	/* 0x70: Divider result quotient */
	uint32_t volatile DIV_QUOTIENT;

	/* 0x74: Divider result remainder */
	uint32_t volatile DIV_REMAINDER;

	/* 0x78: Control and status register for divider. */
	uint32_t volatile DIV_CSR;
	/* Changes to 1 when any register is written, and back to 0 when QUOTIENT is read. */
#define SIO_DIV_CSR_DIRTY					(1u << 1)
	/* Reads as 0 when a calculation is in progress, 1 otherwise. */
#define SIO_DIV_CSR_READY					(1u << 0)

	/* 0x7C */
	uint8_t RESERVED1[0x80u-0x7Cu];

	/* 0x80: Read/write access to accumulator 0 */
	uint32_t volatile INTERP0_ACCUM0;

	/* 0x84: Read/write access to accumulator 1 */
	uint32_t volatile INTERP0_ACCUM1;

	/* 0x88: Read/write access to BASE0 register. */
	uint32_t volatile INTERP0_BASE0;

	/* 0x8C: Read/write access to BASE1 register. */
	uint32_t volatile INTERP0_BASE1;

	/* 0x90: Read/write access to BASE2 register. */
	uint32_t volatile INTERP0_BASE2;

	/* 0x94: Read LANE0 result, and simultaneously write lane results to both accumulators (POP). */
	uint32_t volatile INTERP0_POP_LANE0;

	/* 0x98: Read LANE1 result, and simultaneously write lane results to both accumulators (POP). */
	uint32_t volatile INTERP0_POP_LANE1;

	/* 0x9C: Read FULL result, and simultaneously write lane results to both accumulators (POP). */
	uint32_t volatile INTERP0_POP_FULL;

	/* 0xA0: Read LANE0 result, without altering any internal state (PEEK). */
	uint32_t volatile INTERP0_PEEK_LANE0;

	/* 0xA4: Read LANE1 result, without altering any internal state (PEEK). */
	uint32_t volatile INTERP0_PEEK_LANE1;

	/* 0xA8: Read FULL result, without altering any internal state (PEEK). */
	uint32_t volatile INTERP0_PEEK_FULL;

	/* 0xAC: Control register for lane 0 */
	uint32_t volatile INTERP0_CTRL_LANE0;
	/* Set if either OVERF0 or OVERF1 is set. */
#define SIO_INTERP0_CTRL_LANE0_OVERF				(1u << 25)
	/* Indicates if any masked-off MSBs in ACCUM1 are set. */
#define SIO_INTERP0_CTRL_LANE0_OVERF1				(1u << 24)
	/* Indicates if any masked-off MSBs in ACCUM0 are set. */
#define SIO_INTERP0_CTRL_LANE0_OVERF0				(1u << 23)
	/* Only present on INTERP0 on each core. */
#define SIO_INTERP0_CTRL_LANE0_BLEND				(1u << 21)
	/* ORed into bits 29:28 of the lane result presented to the processor on the bus. */
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_Msk			(0x3u << 19)
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_Pos			19u
	/* If 1, mask + shift is bypassed for LANE0 result. */
#define SIO_INTERP0_CTRL_LANE0_ADD_RAW				(1u << 18)
	/* If 1, feed the opposite lane's result into this lane's accumulator on POP. */
#define SIO_INTERP0_CTRL_LANE0_CROSS_RESULT			(1u << 17)
	/* If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware. */
#define SIO_INTERP0_CTRL_LANE0_CROSS_INPUT			(1u << 16)
	/* If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits */
#define SIO_INTERP0_CTRL_LANE0_SIGNED				(1u << 15)
	/* The most-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_Msk			(0x1Fu << 10)
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_Pos			10u
	/* The least-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_Msk			(0x1Fu << 5)
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_Pos			5u
	/* Logical right-shift applied to accumulator before masking */
#define SIO_INTERP0_CTRL_LANE0_SHIFT_Msk			(0x1Fu << 0)
#define SIO_INTERP0_CTRL_LANE0_SHIFT_Pos			0u

	/* 0xB0: Control register for lane 1 */
	uint32_t volatile INTERP0_CTRL_LANE1;
	/* ORed into bits 29:28 of the lane result presented to the processor on the bus. */
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_Msk			(0x3u << 19)
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_Pos			19u
	/* If 1, mask + shift is bypassed for LANE1 result. */
#define SIO_INTERP0_CTRL_LANE1_ADD_RAW				(1u << 18)
	/* If 1, feed the opposite lane's result into this lane's accumulator on POP. */
#define SIO_INTERP0_CTRL_LANE1_CROSS_RESULT			(1u << 17)
	/* If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware. */
#define SIO_INTERP0_CTRL_LANE1_CROSS_INPUT			(1u << 16)
	/* If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits */
#define SIO_INTERP0_CTRL_LANE1_SIGNED				(1u << 15)
	/* The most-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_Msk			(0x1Fu << 10)
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_Pos			10u
	/* The least-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_Msk			(0x1Fu << 5)
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_Pos			5u
	/* Logical right-shift applied to accumulator before masking */
#define SIO_INTERP0_CTRL_LANE1_SHIFT_Msk			(0x1Fu << 0)
#define SIO_INTERP0_CTRL_LANE1_SHIFT_Pos			0u

	/* 0xB4: Values written here are atomically added to ACCUM0 */
	uint32_t volatile INTERP0_ACCUM0_ADD;
	/*  */
#define SIO_INTERP0_ACCUM0_ADD_INTERP0_ACCUM0_ADD_Msk		(0xFFFFFFu << 0)
#define SIO_INTERP0_ACCUM0_ADD_INTERP0_ACCUM0_ADD_Pos		0u

	/* 0xB8: Values written here are atomically added to ACCUM1 */
	uint32_t volatile INTERP0_ACCUM1_ADD;
	/*  */
#define SIO_INTERP0_ACCUM1_ADD_INTERP0_ACCUM1_ADD_Msk		(0xFFFFFFu << 0)
#define SIO_INTERP0_ACCUM1_ADD_INTERP0_ACCUM1_ADD_Pos		0u

	/* 0xBC: On write, the lower 16 bits go to BASE0, upper bits to BASE1 simultaneously. */
	uint32_t volatile INTERP0_BASE_1AND0;

	/* 0xC0: Read/write access to accumulator 0 */
	uint32_t volatile INTERP1_ACCUM0;

	/* 0xC4: Read/write access to accumulator 1 */
	uint32_t volatile INTERP1_ACCUM1;

	/* 0xC8: Read/write access to BASE0 register. */
	uint32_t volatile INTERP1_BASE0;

	/* 0xCC: Read/write access to BASE1 register. */
	uint32_t volatile INTERP1_BASE1;

	/* 0xD0: Read/write access to BASE2 register. */
	uint32_t volatile INTERP1_BASE2;

	/* 0xD4: Read LANE0 result, and simultaneously write lane results to both accumulators (POP). */
	uint32_t volatile INTERP1_POP_LANE0;

	/* 0xD8: Read LANE1 result, and simultaneously write lane results to both accumulators (POP). */
	uint32_t volatile INTERP1_POP_LANE1;

	/* 0xDC: Read FULL result, and simultaneously write lane results to both accumulators (POP). */
	uint32_t volatile INTERP1_POP_FULL;

	/* 0xE0: Read LANE0 result, without altering any internal state (PEEK). */
	uint32_t volatile INTERP1_PEEK_LANE0;

	/* 0xE4: Read LANE1 result, without altering any internal state (PEEK). */
	uint32_t volatile INTERP1_PEEK_LANE1;

	/* 0xE8: Read FULL result, without altering any internal state (PEEK). */
	uint32_t volatile INTERP1_PEEK_FULL;

	/* 0xEC: Control register for lane 0 */
	uint32_t volatile INTERP1_CTRL_LANE0;
	/* Set if either OVERF0 or OVERF1 is set. */
#define SIO_INTERP1_CTRL_LANE0_OVERF				(1u << 25)
	/* Indicates if any masked-off MSBs in ACCUM1 are set. */
#define SIO_INTERP1_CTRL_LANE0_OVERF1				(1u << 24)
	/* Indicates if any masked-off MSBs in ACCUM0 are set. */
#define SIO_INTERP1_CTRL_LANE0_OVERF0				(1u << 23)
	/* Only present on INTERP1 on each core. */
#define SIO_INTERP1_CTRL_LANE0_CLAMP				(1u << 22)
	/* ORed into bits 29:28 of the lane result presented to the processor on the bus. */
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_Msk			(0x3u << 19)
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_Pos			19u
	/* If 1, mask + shift is bypassed for LANE0 result. */
#define SIO_INTERP1_CTRL_LANE0_ADD_RAW				(1u << 18)
	/* If 1, feed the opposite lane's result into this lane's accumulator on POP. */
#define SIO_INTERP1_CTRL_LANE0_CROSS_RESULT			(1u << 17)
	/* If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware. */
#define SIO_INTERP1_CTRL_LANE0_CROSS_INPUT			(1u << 16)
	/* If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits */
#define SIO_INTERP1_CTRL_LANE0_SIGNED				(1u << 15)
	/* The most-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_Msk			(0x1Fu << 10)
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_Pos			10u
	/* The least-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_Msk			(0x1Fu << 5)
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_Pos			5u
	/* Logical right-shift applied to accumulator before masking */
#define SIO_INTERP1_CTRL_LANE0_SHIFT_Msk			(0x1Fu << 0)
#define SIO_INTERP1_CTRL_LANE0_SHIFT_Pos			0u

	/* 0xF0: Control register for lane 1 */
	uint32_t volatile INTERP1_CTRL_LANE1;
	/* ORed into bits 29:28 of the lane result presented to the processor on the bus. */
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_Msk			(0x3u << 19)
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_Pos			19u
	/* If 1, mask + shift is bypassed for LANE1 result. */
#define SIO_INTERP1_CTRL_LANE1_ADD_RAW				(1u << 18)
	/* If 1, feed the opposite lane's result into this lane's accumulator on POP. */
#define SIO_INTERP1_CTRL_LANE1_CROSS_RESULT			(1u << 17)
	/* If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware. */
#define SIO_INTERP1_CTRL_LANE1_CROSS_INPUT			(1u << 16)
	/* If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits */
#define SIO_INTERP1_CTRL_LANE1_SIGNED				(1u << 15)
	/* The most-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_Msk			(0x1Fu << 10)
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_Pos			10u
	/* The least-significant bit allowed to pass by the mask (inclusive) */
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_Msk			(0x1Fu << 5)
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_Pos			5u
	/* Logical right-shift applied to accumulator before masking */
#define SIO_INTERP1_CTRL_LANE1_SHIFT_Msk			(0x1Fu << 0)
#define SIO_INTERP1_CTRL_LANE1_SHIFT_Pos			0u

	/* 0xF4: Values written here are atomically added to ACCUM0 */
	uint32_t volatile INTERP1_ACCUM0_ADD;
	/*  */
#define SIO_INTERP1_ACCUM0_ADD_INTERP1_ACCUM0_ADD_Msk		(0xFFFFFFu << 0)
#define SIO_INTERP1_ACCUM0_ADD_INTERP1_ACCUM0_ADD_Pos		0u

	/* 0xF8: Values written here are atomically added to ACCUM1 */
	uint32_t volatile INTERP1_ACCUM1_ADD;
	/*  */
#define SIO_INTERP1_ACCUM1_ADD_INTERP1_ACCUM1_ADD_Msk		(0xFFFFFFu << 0)
#define SIO_INTERP1_ACCUM1_ADD_INTERP1_ACCUM1_ADD_Pos		0u

	/* 0xFC: On write, the lower 16 bits go to BASE0, upper bits to BASE1 simultaneously. */
	uint32_t volatile INTERP1_BASE_1AND0;

	/* 0x100: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK0;

	/* 0x104: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK1;

	/* 0x108: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK2;

	/* 0x10C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK3;

	/* 0x110: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK4;

	/* 0x114: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK5;

	/* 0x118: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK6;

	/* 0x11C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK7;

	/* 0x120: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK8;

	/* 0x124: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK9;

	/* 0x128: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK10;

	/* 0x12C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK11;

	/* 0x130: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK12;

	/* 0x134: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK13;

	/* 0x138: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK14;

	/* 0x13C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK15;

	/* 0x140: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK16;

	/* 0x144: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK17;

	/* 0x148: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK18;

	/* 0x14C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK19;

	/* 0x150: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK20;

	/* 0x154: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK21;

	/* 0x158: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK22;

	/* 0x15C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK23;

	/* 0x160: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK24;

	/* 0x164: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK25;

	/* 0x168: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK26;

	/* 0x16C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK27;

	/* 0x170: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK28;

	/* 0x174: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK29;

	/* 0x178: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK30;

	/* 0x17C: Reading from a spinlock address will: */
	uint32_t volatile SPINLOCK31;

};


#define M0PLUS ((struct mcu_ppb *)0xE0000000)

struct mcu_ppb {

	/* 0x180 */
	uint8_t RESERVED0[0xE010u-0x180u];

	/* 0xE010: Use the SysTick Control and Status Register to enable the SysTick features. */
	uint32_t volatile SYST_CSR;
	/* Returns 1 if timer counted to 0 since last time this was read. */
#define M0PLUS_SYST_CSR_COUNTFLAG				(1u << 16)
	/* SysTick clock source. */
#define M0PLUS_SYST_CSR_CLKSOURCE				(1u << 2)
	/* Enables SysTick exception request: */
#define M0PLUS_SYST_CSR_TICKINT					(1u << 1)
	/* Enable SysTick counter: */
#define M0PLUS_SYST_CSR_ENABLE					(1u << 0)

	/* 0xE014: Use the SysTick Reload Value Register to specify the start value to load into the current value register when the counter reaches 0. */
	uint32_t volatile SYST_RVR;
	/* Value to load into the SysTick Current Value Register when the counter reaches 0. */
#define M0PLUS_SYST_RVR_RELOAD_Msk				(0xFFFFFFu << 0)
#define M0PLUS_SYST_RVR_RELOAD_Pos				0u

	/* 0xE018: Use the SysTick Current Value Register to find the current value in the register. */
	uint32_t volatile SYST_CVR;
	/* Reads return the current value of the SysTick counter. */
#define M0PLUS_SYST_CVR_CURRENT_Msk				(0xFFFFFFu << 0)
#define M0PLUS_SYST_CVR_CURRENT_Pos				0u

	/* 0xE01C: Use the SysTick Calibration Value Register to enable software to scale to any required speed using divide and multiply. */
	uint32_t volatile SYST_CALIB;
	/* If reads as 1, the Reference clock is not provided - the CLKSOURCE bit of the SysTick Control and Status register will be forced to 1 and cannot be cleared to 0. */
#define M0PLUS_SYST_CALIB_NOREF					(1u << 31)
	/* If reads as 1, the calibration value for 10ms is inexact (due to clock frequency). */
#define M0PLUS_SYST_CALIB_SKEW					(1u << 30)
	/* An optional Reload value to be used for 10ms (100Hz) timing, subject to system clock skew errors. */
#define M0PLUS_SYST_CALIB_TENMS_Msk				(0xFFFFFFu << 0)
#define M0PLUS_SYST_CALIB_TENMS_Pos				0u

	/* 0xE020 */
	uint8_t RESERVED1[0xE100u-0xE020u];

	/* 0xE100: Use the Interrupt Set-Enable Register to enable interrupts and determine which interrupts are currently enabled. */
	uint32_t volatile NVIC_ISER;
	/* Interrupt set-enable bits. */
#define M0PLUS_NVIC_ISER_SETENA_Msk				(0xFFFFFFFFu << 0)
#define M0PLUS_NVIC_ISER_SETENA_Pos				0u

	/* 0xE104 */
	uint8_t RESERVED2[0xE180u-0xE104u];

	/* 0xE180: Use the Interrupt Clear-Enable Registers to disable interrupts and determine which interrupts are currently enabled. */
	uint32_t volatile NVIC_ICER;
	/* Interrupt clear-enable bits. */
#define M0PLUS_NVIC_ICER_CLRENA_Msk				(0xFFFFFFFFu << 0)
#define M0PLUS_NVIC_ICER_CLRENA_Pos				0u

	/* 0xE184 */
	uint8_t RESERVED3[0xE200u-0xE184u];

	/* 0xE200: The NVIC_ISPR forces interrupts into the pending state, and shows which interrupts are pending. */
	uint32_t volatile NVIC_ISPR;
	/* Interrupt set-pending bits. */
#define M0PLUS_NVIC_ISPR_SETPEND_Msk				(0xFFFFFFFFu << 0)
#define M0PLUS_NVIC_ISPR_SETPEND_Pos				0u

	/* 0xE204 */
	uint8_t RESERVED4[0xE280u-0xE204u];

	/* 0xE280: Use the Interrupt Clear-Pending Register to clear pending interrupts and determine which interrupts are currently pending. */
	uint32_t volatile NVIC_ICPR;
	/* Interrupt clear-pending bits. */
#define M0PLUS_NVIC_ICPR_CLRPEND_Msk				(0xFFFFFFFFu << 0)
#define M0PLUS_NVIC_ICPR_CLRPEND_Pos				0u

	/* 0xE284 */
	uint8_t RESERVED5[0xE400u-0xE284u];

	/* 0xE400: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR0;
	/* Priority of interrupt 3 */
#define M0PLUS_NVIC_IPR0_IP_3_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR0_IP_3_Pos				30u
	/* Priority of interrupt 2 */
#define M0PLUS_NVIC_IPR0_IP_2_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR0_IP_2_Pos				22u
	/* Priority of interrupt 1 */
#define M0PLUS_NVIC_IPR0_IP_1_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR0_IP_1_Pos				14u
	/* Priority of interrupt 0 */
#define M0PLUS_NVIC_IPR0_IP_0_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR0_IP_0_Pos				6u

	/* 0xE404: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR1;
	/* Priority of interrupt 7 */
#define M0PLUS_NVIC_IPR1_IP_7_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR1_IP_7_Pos				30u
	/* Priority of interrupt 6 */
#define M0PLUS_NVIC_IPR1_IP_6_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR1_IP_6_Pos				22u
	/* Priority of interrupt 5 */
#define M0PLUS_NVIC_IPR1_IP_5_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR1_IP_5_Pos				14u
	/* Priority of interrupt 4 */
#define M0PLUS_NVIC_IPR1_IP_4_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR1_IP_4_Pos				6u

	/* 0xE408: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR2;
	/* Priority of interrupt 11 */
#define M0PLUS_NVIC_IPR2_IP_11_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR2_IP_11_Pos				30u
	/* Priority of interrupt 10 */
#define M0PLUS_NVIC_IPR2_IP_10_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR2_IP_10_Pos				22u
	/* Priority of interrupt 9 */
#define M0PLUS_NVIC_IPR2_IP_9_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR2_IP_9_Pos				14u
	/* Priority of interrupt 8 */
#define M0PLUS_NVIC_IPR2_IP_8_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR2_IP_8_Pos				6u

	/* 0xE40C: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR3;
	/* Priority of interrupt 15 */
#define M0PLUS_NVIC_IPR3_IP_15_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR3_IP_15_Pos				30u
	/* Priority of interrupt 14 */
#define M0PLUS_NVIC_IPR3_IP_14_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR3_IP_14_Pos				22u
	/* Priority of interrupt 13 */
#define M0PLUS_NVIC_IPR3_IP_13_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR3_IP_13_Pos				14u
	/* Priority of interrupt 12 */
#define M0PLUS_NVIC_IPR3_IP_12_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR3_IP_12_Pos				6u

	/* 0xE410: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR4;
	/* Priority of interrupt 19 */
#define M0PLUS_NVIC_IPR4_IP_19_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR4_IP_19_Pos				30u
	/* Priority of interrupt 18 */
#define M0PLUS_NVIC_IPR4_IP_18_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR4_IP_18_Pos				22u
	/* Priority of interrupt 17 */
#define M0PLUS_NVIC_IPR4_IP_17_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR4_IP_17_Pos				14u
	/* Priority of interrupt 16 */
#define M0PLUS_NVIC_IPR4_IP_16_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR4_IP_16_Pos				6u

	/* 0xE414: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR5;
	/* Priority of interrupt 23 */
#define M0PLUS_NVIC_IPR5_IP_23_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR5_IP_23_Pos				30u
	/* Priority of interrupt 22 */
#define M0PLUS_NVIC_IPR5_IP_22_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR5_IP_22_Pos				22u
	/* Priority of interrupt 21 */
#define M0PLUS_NVIC_IPR5_IP_21_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR5_IP_21_Pos				14u
	/* Priority of interrupt 20 */
#define M0PLUS_NVIC_IPR5_IP_20_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR5_IP_20_Pos				6u

	/* 0xE418: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR6;
	/* Priority of interrupt 27 */
#define M0PLUS_NVIC_IPR6_IP_27_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR6_IP_27_Pos				30u
	/* Priority of interrupt 26 */
#define M0PLUS_NVIC_IPR6_IP_26_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR6_IP_26_Pos				22u
	/* Priority of interrupt 25 */
#define M0PLUS_NVIC_IPR6_IP_25_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR6_IP_25_Pos				14u
	/* Priority of interrupt 24 */
#define M0PLUS_NVIC_IPR6_IP_24_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR6_IP_24_Pos				6u

	/* 0xE41C: Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. */
	uint32_t volatile NVIC_IPR7;
	/* Priority of interrupt 31 */
#define M0PLUS_NVIC_IPR7_IP_31_Msk				(0x3u << 30)
#define M0PLUS_NVIC_IPR7_IP_31_Pos				30u
	/* Priority of interrupt 30 */
#define M0PLUS_NVIC_IPR7_IP_30_Msk				(0x3u << 22)
#define M0PLUS_NVIC_IPR7_IP_30_Pos				22u
	/* Priority of interrupt 29 */
#define M0PLUS_NVIC_IPR7_IP_29_Msk				(0x3u << 14)
#define M0PLUS_NVIC_IPR7_IP_29_Pos				14u
	/* Priority of interrupt 28 */
#define M0PLUS_NVIC_IPR7_IP_28_Msk				(0x3u << 6)
#define M0PLUS_NVIC_IPR7_IP_28_Pos				6u

	/* 0xE420 */
	uint8_t RESERVED6[0xED00u-0xE420u];

	/* 0xED00: Read the CPU ID Base Register to determine: the ID number of the processor core, the version number of the processor core, the implementation details of the processor core. */
	uint32_t volatile CPUID;
	/* Implementor code: 0x41 = ARM */
#define M0PLUS_CPUID_IMPLEMENTER_Msk				(0xFFu << 24)
#define M0PLUS_CPUID_IMPLEMENTER_Pos				24u
	/* Major revision number n in the rnpm revision status: */
#define M0PLUS_CPUID_VARIANT_Msk				(0xFu << 20)
#define M0PLUS_CPUID_VARIANT_Pos				20u
	/* Constant that defines the architecture of the processor: */
#define M0PLUS_CPUID_ARCHITECTURE_Msk				(0xFu << 16)
#define M0PLUS_CPUID_ARCHITECTURE_Pos				16u
	/* Number of processor within family: 0xC60 = Cortex-M0+ */
#define M0PLUS_CPUID_PARTNO_Msk					(0xFFFu << 4)
#define M0PLUS_CPUID_PARTNO_Pos					4u
	/* Minor revision number m in the rnpm revision status: */
#define M0PLUS_CPUID_REVISION_Msk				(0xFu << 0)
#define M0PLUS_CPUID_REVISION_Pos				0u

	/* 0xED04: Use the Interrupt Control State Register to set a pending Non-Maskable Interrupt (NMI), set or clear a pending PendSV, set or clear a pending SysTick, check for pending exceptions, check the vector number of the highest priority pended exception, check the vector number of the active exception. */
	uint32_t volatile ICSR;
	/* Setting this bit will activate an NMI. */
#define M0PLUS_ICSR_NMIPENDSET					(1u << 31)
	/* PendSV set-pending bit. */
#define M0PLUS_ICSR_PENDSVSET					(1u << 28)
	/* PendSV clear-pending bit. */
#define M0PLUS_ICSR_PENDSVCLR					(1u << 27)
	/* SysTick exception set-pending bit. */
#define M0PLUS_ICSR_PENDSTSET					(1u << 26)
	/* SysTick exception clear-pending bit. */
#define M0PLUS_ICSR_PENDSTCLR					(1u << 25)
	/* The system can only access this bit when the core is halted. */
#define M0PLUS_ICSR_ISRPREEMPT					(1u << 23)
	/* External interrupt pending flag */
#define M0PLUS_ICSR_ISRPENDING					(1u << 22)
	/* Indicates the exception number for the highest priority pending exception: 0 = no pending exceptions. */
#define M0PLUS_ICSR_VECTPENDING_Msk				(0x1FFu << 12)
#define M0PLUS_ICSR_VECTPENDING_Pos				12u
	/* Active exception number field. */
#define M0PLUS_ICSR_VECTACTIVE_Msk				(0x1FFu << 0)
#define M0PLUS_ICSR_VECTACTIVE_Pos				0u

	/* 0xED08: The VTOR holds the vector table offset address. */
	uint32_t volatile VTOR;
	/* Bits [31:8] of the indicate the vector table offset address. */
#define M0PLUS_VTOR_TBLOFF_Msk					(0xFFFFFFu << 8)
#define M0PLUS_VTOR_TBLOFF_Pos					8u

	/* 0xED0C: Use the Application Interrupt and Reset Control Register to: determine data endianness, clear all active state information from debug halt mode, request a system reset. */
	uint32_t volatile AIRCR;
	/* Register key: */
#define M0PLUS_AIRCR_VECTKEY_Msk				(0xFFFFu << 16)
#define M0PLUS_AIRCR_VECTKEY_Pos				16u
	/* Data endianness implemented: */
#define M0PLUS_AIRCR_ENDIANESS					(1u << 15)
	/* Writing 1 to this bit causes the SYSRESETREQ signal to the outer system to be asserted to request a reset. */
#define M0PLUS_AIRCR_SYSRESETREQ				(1u << 2)
	/* Clears all active state information for fixed and configurable exceptions. */
#define M0PLUS_AIRCR_VECTCLRACTIVE				(1u << 1)

	/* 0xED10: System Control Register. */
	uint32_t volatile SCR;
	/* Send Event on Pending bit: */
#define M0PLUS_SCR_SEVONPEND					(1u << 4)
	/* Controls whether the processor uses sleep or deep sleep as its low power mode: */
#define M0PLUS_SCR_SLEEPDEEP					(1u << 2)
	/* Indicates sleep-on-exit when returning from Handler mode to Thread mode: */
#define M0PLUS_SCR_SLEEPONEXIT					(1u << 1)

	/* 0xED14: The Configuration and Control Register permanently enables stack alignment and causes unaligned accesses to result in a Hard Fault. */
	uint32_t volatile CCR;
	/* Always reads as one, indicates 8-byte stack alignment on exception entry. */
#define M0PLUS_CCR_STKALIGN					(1u << 9)
	/* Always reads as one, indicates that all unaligned accesses generate a HardFault. */
#define M0PLUS_CCR_UNALIGN_TRP					(1u << 3)

	/* 0xED18 */
	uint8_t RESERVED7[0xED1Cu-0xED18u];

	/* 0xED1C: System handlers are a special class of exception handler that can have their priority set to any of the priority levels. */
	uint32_t volatile SHPR2;
	/* Priority of system handler 11, SVCall */
#define M0PLUS_SHPR2_PRI_11_Msk					(0x3u << 30)
#define M0PLUS_SHPR2_PRI_11_Pos					30u

	/* 0xED20: System handlers are a special class of exception handler that can have their priority set to any of the priority levels. */
	uint32_t volatile SHPR3;
	/* Priority of system handler 15, SysTick */
#define M0PLUS_SHPR3_PRI_15_Msk					(0x3u << 30)
#define M0PLUS_SHPR3_PRI_15_Pos					30u
	/* Priority of system handler 14, PendSV */
#define M0PLUS_SHPR3_PRI_14_Msk					(0x3u << 22)
#define M0PLUS_SHPR3_PRI_14_Pos					22u

	/* 0xED24: Use the System Handler Control and State Register to determine or clear the pending status of SVCall. */
	uint32_t volatile SHCSR;
	/* Reads as 1 if SVCall is Pending. */
#define M0PLUS_SHCSR_SVCALLPENDED				(1u << 15)

	/* 0xED28 */
	uint8_t RESERVED8[0xED90u-0xED28u];

	/* 0xED90: Read the MPU Type Register to determine if the processor implements an MPU, and how many regions the MPU supports. */
	uint32_t volatile MPU_TYPE;
	/* Instruction region. */
#define M0PLUS_MPU_TYPE_IREGION_Msk				(0xFFu << 16)
#define M0PLUS_MPU_TYPE_IREGION_Pos				16u
	/* Number of regions supported by the MPU. */
#define M0PLUS_MPU_TYPE_DREGION_Msk				(0xFFu << 8)
#define M0PLUS_MPU_TYPE_DREGION_Pos				8u
	/* Indicates support for separate instruction and data address maps. */
#define M0PLUS_MPU_TYPE_SEPARATE				(1u << 0)

	/* 0xED94: Use the MPU Control Register to enable and disable the MPU, and to control whether the default memory map is enabled as a background region for privileged accesses, and whether the MPU is enabled for HardFaults and NMIs. */
	uint32_t volatile MPU_CTRL;
	/* Controls whether the default memory map is enabled as a background region for privileged accesses. */
#define M0PLUS_MPU_CTRL_PRIVDEFENA				(1u << 2)
	/* Controls the use of the MPU for HardFaults and NMIs. */
#define M0PLUS_MPU_CTRL_HFNMIENA				(1u << 1)
	/* Enables the MPU. */
#define M0PLUS_MPU_CTRL_ENABLE					(1u << 0)

	/* 0xED98: Use the MPU Region Number Register to select the region currently accessed by MPU_RBAR and MPU_RASR. */
	uint32_t volatile MPU_RNR;
	/* Indicates the MPU region referenced by the MPU_RBAR and MPU_RASR registers. */
#define M0PLUS_MPU_RNR_REGION_Msk				(0xFu << 0)
#define M0PLUS_MPU_RNR_REGION_Pos				0u

	/* 0xED9C: Read the MPU Region Base Address Register to determine the base address of the region identified by MPU_RNR. */
	uint32_t volatile MPU_RBAR;
	/* Base address of the region. */
#define M0PLUS_MPU_RBAR_ADDR_Msk				(0xFFFFFFu << 8)
#define M0PLUS_MPU_RBAR_ADDR_Pos				8u
	/* On writes, indicates whether the write must update the base address of the region identified by the REGION field, updating the MPU_RNR to indicate this new region. */
#define M0PLUS_MPU_RBAR_VALID					(1u << 4)
	/* On writes, specifies the number of the region whose base address to update provided VALID is set written as 1. */
#define M0PLUS_MPU_RBAR_REGION_Msk				(0xFu << 0)
#define M0PLUS_MPU_RBAR_REGION_Pos				0u

	/* 0xEDA0: Use the MPU Region Attribute and Size Register to define the size, access behaviour and memory type of the region identified by MPU_RNR, and enable that region. */
	uint32_t volatile MPU_RASR;
	/* The MPU Region Attribute field. */
#define M0PLUS_MPU_RASR_ATTRS_Msk				(0xFFFFu << 16)
#define M0PLUS_MPU_RASR_ATTRS_Pos				16u
	/* Subregion Disable. */
#define M0PLUS_MPU_RASR_SRD_Msk					(0xFFu << 8)
#define M0PLUS_MPU_RASR_SRD_Pos					8u
	/* Indicates the region size. Region size in bytes = 2^(SIZE+1). The minimum permitted value is 7 (b00111) = 256Bytes */
#define M0PLUS_MPU_RASR_SIZE_Msk				(0x1Fu << 1)
#define M0PLUS_MPU_RASR_SIZE_Pos				1u
	/* Enables the region. */
#define M0PLUS_MPU_RASR_ENABLE					(1u << 0)

};


/* MACROS */

#define FIELD(reg, fld)		(((reg) & fld##_Msk) >> fld##_Pos)

extern void __stop_program(void);


/* CLOCKS */

#define CLK_SYS_HZ 125000000
#define CLK_PERI_HZ CLK_SYS_HZ


/* GPIO */

extern void gpio_init(void);
extern void gpio_set_mode_output(uint8_t pin);
extern void gpio_set_pin(uint8_t pin);
extern void gpio_clear_pin(uint8_t pin);


/* SPI */

/* submit a write, then processed by the SPI interrupts */
extern void spi_interrupt(struct mcu_spi *spi);

/* the clock speed might not be exact due to integer division */
extern void spi_init(struct mcu_spi *spi, uint8_t clock_divider,
	uint8_t pin_sck, uint8_t pin_csn, uint8_t pin_rx, uint8_t pin_tx);

/* interrupt handler for SPI events */
extern void spi_io_callback(struct mcu_spi *spi, uint8_t rx, uint8_t volatile *tx);

/* set SPI interrupts on or off */
extern void spi_enable_interrupts(struct mcu_spi *spi);
extern void spi_disable_interrupts(struct mcu_spi *spi);


#endif
