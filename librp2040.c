#include "libc.h"
#include "librp2040.h"


/// INIT ///


extern int main(void);
extern char __data_start, __data_end, __data_load_start;
extern char __bss_start, __bss_end, __stack_top;

void
__reset_handler(void)
{
	volatile char *dst, *src = &__data_load_start;

	for (dst = &__data_start; dst < &__data_end; *dst++ = *src++);
	for (dst = &__bss_start; dst < &__bss_end; *dst++ = 0);
	main();
	for (int volatile i = 0 ;; i++);
}

void
__isr_spi0(void)
{
	spi_interrupt(SPI0);
}

void
__isr_spi1(void)
{
	spi_interrupt(SPI1);
}

/* so that the debugger can immediately see which fault was triggered */
void __null_handler(void)		{ for (int volatile i = 0;; i++); }
void __isr_hard_fault(void)		{ for (int volatile i = 0;; i++); }
void __isr_memory_management(void)	{ for (int volatile i = 0;; i++); }
void __isr_non_maskable_interrupt(void)	{ for (int volatile i = 0;; i++); }
void __isr_bus_fault(void)		{ for (int volatile i = 0;; i++); }
void __isr_usage_fault(void)		{ for (int volatile i = 0;; i++); }
void __isr_secure_fault(void)		{ for (int volatile i = 0;; i++); }

/*
 * Boot stage 2 bootloader: padded and checksummed version of
 * pico-sdk/src/rp2_common/boot_stage2/bs2_default.bin
 * It is placed at the lowest address of the ROM by the linker script
 */
char __bootloader[] = {
	0x00, 0xb5, 0x32, 0x4b, 0x21, 0x20, 0x58, 0x60, 0x98, 0x68, 0x02, 0x21,
	0x88, 0x43, 0x98, 0x60, 0xd8, 0x60, 0x18, 0x61, 0x58, 0x61, 0x2e, 0x4b,
	0x00, 0x21, 0x99, 0x60, 0x02, 0x21, 0x59, 0x61, 0x01, 0x21, 0xf0, 0x22,
	0x99, 0x50, 0x2b, 0x49, 0x19, 0x60, 0x01, 0x21, 0x99, 0x60, 0x35, 0x20,
	0x00, 0xf0, 0x44, 0xf8, 0x02, 0x22, 0x90, 0x42, 0x14, 0xd0, 0x06, 0x21,
	0x19, 0x66, 0x00, 0xf0, 0x34, 0xf8, 0x19, 0x6e, 0x01, 0x21, 0x19, 0x66,
	0x00, 0x20, 0x18, 0x66, 0x1a, 0x66, 0x00, 0xf0, 0x2c, 0xf8, 0x19, 0x6e,
	0x19, 0x6e, 0x19, 0x6e, 0x05, 0x20, 0x00, 0xf0, 0x2f, 0xf8, 0x01, 0x21,
	0x08, 0x42, 0xf9, 0xd1, 0x00, 0x21, 0x99, 0x60, 0x1b, 0x49, 0x19, 0x60,
	0x00, 0x21, 0x59, 0x60, 0x1a, 0x49, 0x1b, 0x48, 0x01, 0x60, 0x01, 0x21,
	0x99, 0x60, 0xeb, 0x21, 0x19, 0x66, 0xa0, 0x21, 0x19, 0x66, 0x00, 0xf0,
	0x12, 0xf8, 0x00, 0x21, 0x99, 0x60, 0x16, 0x49, 0x14, 0x48, 0x01, 0x60,
	0x01, 0x21, 0x99, 0x60, 0x01, 0xbc, 0x00, 0x28, 0x00, 0xd0, 0x00, 0x47,
	0x12, 0x48, 0x13, 0x49, 0x08, 0x60, 0x03, 0xc8, 0x80, 0xf3, 0x08, 0x88,
	0x08, 0x47, 0x03, 0xb5, 0x99, 0x6a, 0x04, 0x20, 0x01, 0x42, 0xfb, 0xd0,
	0x01, 0x20, 0x01, 0x42, 0xf8, 0xd1, 0x03, 0xbd, 0x02, 0xb5, 0x18, 0x66,
	0x18, 0x66, 0xff, 0xf7, 0xf2, 0xff, 0x18, 0x6e, 0x18, 0x6e, 0x02, 0xbd,
	0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x03, 0x5f, 0x00, 0x21, 0x22, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x18,
	0x22, 0x20, 0x00, 0xa0, 0x00, 0x01, 0x00, 0x10, 0x08, 0xed, 0x00, 0xe0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x74, 0xb2, 0x4e, 0x7a,
};

void *__stack_pointer = &__stack_top;	/* 0x00 */

void (*__vectors[])(void) = {
	&__reset_handler,		/* 0x04 -15 ARM Reset */
	&__isr_non_maskable_interrupt,	/* 0x08 -14 ARM NonMaskableInt */
	&__isr_hard_fault,		/* 0x0C -13 ARM HardFault */
	&__isr_memory_management,	/* 0x10 -12 ARM MemoryManagement */
	&__isr_bus_fault,		/* 0x14 -11 ARM BusFault */
	&__isr_usage_fault,		/* 0x18 -10 ARM UsageFault */
	&__isr_secure_fault,		/* 0x1C -9 ARM SecureFault */
	&__null_handler,		/* 0x20 -8 Reserved */
	&__null_handler,		/* 0x24 -7 Reserved */
	&__null_handler,		/* 0x28 -6 Reserved */
	&__null_handler,		/* 0x2C -5 ARM SVCall */
	&__null_handler,		/* 0x30 -4 ARM DebugMonitor */
	&__null_handler,		/* 0x34 -3 Reserved */
	&__null_handler,		/* 0x38 -2 ARM PendSV */
	&__null_handler,		/* 0x3C -1 ARM SysTick */
	&__null_handler,		/* 0x40 #0 TIMER_IRQ_0 */
	&__null_handler,		/* 0x44 #1 TIMER_IRQ_1 */
	&__null_handler,		/* 0x48 #2 TIMER_IRQ_2 */
	&__null_handler,		/* 0x4C #3 TIMER_IRQ_3 */
	&__null_handler,		/* 0x50 #4 PWM_IRQ_WRAP */
	&__null_handler,		/* 0x54 #5 USBCTRL_IRQ */
	&__null_handler,		/* 0x58 #6 XIP_IRQ */
	&__null_handler,		/* 0x5C #7 PIO0_IRQ_0 */
	&__null_handler,		/* 0x60 #8 PIO0_IRQ_1 */
	&__null_handler,		/* 0x64 #9 PIO1_IRQ_0 */
	&__null_handler,		/* 0x68 #10 PIO1_IRQ_1 */
	&__null_handler,		/* 0x6C #11 DMA_IRQ_0 */
	&__null_handler,		/* 0x70 #12 DMA_IRQ_1 */
	&__null_handler,		/* 0x74 #13 IO_IRQ_BANK0 */
	&__null_handler,		/* 0x78 #14 IO_IRQ_QSPI */
	&__null_handler,		/* 0x7C #15 SIO_IRQ_PROC0 */
	&__null_handler,		/* 0x80 #16 SIO_IRQ_PROC1 */
	&__null_handler,		/* 0x84 #17 CLOCKS_IRQ */
	&__isr_spi0,			/* 0x88 #18 SPI0_IRQ */
	&__isr_spi1,			/* 0x8C #19 SPI1_IRQ */
	&__null_handler,		/* 0x90 #20 UART0_IRQ */
	&__null_handler,		/* 0x94 #21 UART1_IRQ */
	&__null_handler,		/* 0x98 #22 ADC_IRQ_FIFO */
	&__null_handler,		/* 0x9C #23 I2C0_IRQ */
	&__null_handler,		/* 0xA0 #24 I2C1_IRQ */
	&__null_handler,		/* 0xA4 #25 RTC_IRQ */
};


/// GPIO ///


void
gpio_init(void)
{
	RESETS->RESET &= ~RESETS_RESET_IO_BANK0;
	RESETS->RESET &= ~RESETS_RESET_PADS_BANK0;
	while ((RESETS->RESET_DONE & RESETS_RESET_DONE_IO_BANK0) == 0);
	while ((RESETS->RESET_DONE & RESETS_RESET_DONE_PADS_BANK0) == 0);
}

void
gpio_set_mode_output(uint8_t pin)
{
	SIO->GPIO_OE_SET = 1u << pin;
	IO_BANK0->GPIO[pin].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_SIO;
}

void
gpio_set_pin(uint8_t pin)
{
	SIO->GPIO_OUT_SET = 1u << pin;
}

void
gpio_clear_pin(uint8_t pin)
{
	SIO->GPIO_OUT_CLR = 1u << pin;
}


/// SPI ///


void
spi_init(struct mcu_spi *spi, uint8_t clock_divider,
	uint8_t pin_sck, uint8_t pin_csn, uint8_t pin_rx, uint8_t pin_tx)
{
	uint8_t id = (spi == SPI1);

	/* enable the peripheral clock, used by the TX/RX logic */
	CLOCKS->CLK[CLK_PERI].CTRL = CLOCKS_CLK_PERI_CTRL_ENABLE;

	/* take I/O, and SPI out of reset */
	RESETS->RESET &= ~RESETS_RESET_IO_BANK0;
	RESETS->RESET &= ~RESETS_RESET_PADS_BANK0;
	RESETS->RESET &= ~(RESETS_RESET_SPI0 << id);
	while (~RESETS->RESET_DONE & RESETS_RESET_DONE_IO_BANK0);
	while (~RESETS->RESET_DONE & RESETS_RESET_DONE_PADS_BANK0);
	while (~RESETS->RESET_DONE & (RESETS_RESET_DONE_SPI0 << id));

	/* setup the ports function multiplexing */
	IO_BANK0->GPIO[pin_sck].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_SPI;
	IO_BANK0->GPIO[pin_csn].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_SPI;
	IO_BANK0->GPIO[pin_rx].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_SPI;
	IO_BANK0->GPIO[pin_tx].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_SPI;

	/* set the direction of pins to input or output */
	SIO->GPIO_OE_SET = 1u << pin_sck | 1u << pin_csn | 1u << pin_tx;
	SIO->GPIO_OE_CLR = 1u << pin_rx;

	/* assume an incoming SSPCLK clock derived from CLK_PERI at 125MHz */
	spi->SSPCR0 = 0
	/* set SPI mode */
	 | SPI_SSPCR0_FRF_MOTOROLA
	/* propagate signals on positive edge (posege) */
	 | SPI_SSPCR0_SPH
	/* set the number of bits per frames */
	 | (8 - 1) << SPI_SSPCR0_DSS_Pos;

	/* the result of the division is expected to be >1 */
	assert(clock_divider >= 2 && clock_divider <= 254);
	clock_divider &= 0xFE;
	spi->SSPCPSR = clock_divider;

	/* enable the SPI module *after* (#4.4.4) it was configured */
	spi->SSPCR1 = SPI_SSPCR1_SSE;

	/* enable interrupts */
	NVIC->ISER |= 1u << (18 + id);
}

void
spi_io_start(struct mcu_spi *spi)
{
	spi_io_callback(spi, 0, (uint8_t *)&spi->SSPDR);
	spi_enable_interrupts(spi);
}

void
spi_interrupt(struct mcu_spi *spi)
{
	/* on every byte, call the handler */
	if (spi->SSPSR & SPI_SSPSR_TNF) {
		/* let the programmer decide what to send in real-time */
		spi_io_callback(spi, (uint8_t)spi->SSPDR, (uint8_t *)&spi->SSPDR);
	}
}

void
spi_enable_interrupts(struct mcu_spi *spi)
{
	spi->SSPIMSC = SPI_SSPIMSC_TXIM;
}

void
spi_disable_interrupts(struct mcu_spi *spi)
{
	spi->SSPIMSC = 0x00;
}


/// UART ///


void
uart_init(struct mcu_uart *uart, uint8_t pin_rx, uint8_t pin_tx)
{
	RESETS->RESET &= ~RESETS_RESET_IO_BANK0; // TODO: realy needed?
	RESETS->RESET &= ~RESETS_RESET_PADS_BANK0; // TODO: really needed?
	while ((RESETS->RESET_DONE & RESETS_RESET_DONE_IO_BANK0) == 0);
	while ((RESETS->RESET_DONE & RESETS_RESET_DONE_PADS_BANK0) == 0);

	if (uart == UART0) {
		RESETS->RESET &= ~RESETS_RESET_UART0;
		while ((RESETS->RESET_DONE & RESETS_RESET_DONE_UART0) == 0);
		
	}
	if (uart == UART1) {
		RESETS->RESET &= ~RESETS_RESET_UART1;
		while ((RESETS->RESET_DONE & RESETS_RESET_DONE_UART1) == 0);
	}

	IO_BANK0->GPIO[pin_rx].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_UART;
	IO_BANK0->GPIO[pin_tx].CTRL = IO_BANK0_GPIO_CTRL_FUNCSEL_UART;

	;
}
