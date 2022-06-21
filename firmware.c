#include "libc.h"
#include "librp2040.h"

/* Send requests to a Wishbone B4 bus as master through SPI */

#define LED		25
#define TRIGGER		22

#define SPI_RX		16
#define SPI_CSN		17
#define SPI_SCK		18
#define SPI_TX		19

enum wb_state {
	WB_STATE_PUT_COMMAND,
	WB_STATE_PUT_ADDRESS,
	WB_STATE_PUT_DATA_0,
	WB_STATE_PUT_DATA_1,
	WB_STATE_PUT_DATA_2,
	WB_STATE_PUT_DATA_3,
	WB_STATE_WAIT_ACK,
	WB_STATE_GET_DATA_0,
	WB_STATE_GET_DATA_1,
	WB_STATE_GET_DATA_2,
	WB_STATE_GET_DATA_3,
	WB_STATE_IDLE,
};

struct {
	enum wb_state state;
	size_t skip;
	uint8_t wb_we_o;
	uint8_t wb_adr_o;
	uint8_t wb_sel_o;
	uint32_t wb_dat_o;
	uint32_t wb_dat_i;
	uint8_t done;
} wb = { .state = WB_STATE_IDLE };

void
wb_pack(uint8_t we, uint16_t addr, uint8_t size, uint32_t data)
{
	switch (size) {
	case 1:
		wb.wb_sel_o = (uint8_t)(0x1u << (addr & 0x3));
		break;
	case 2:
		wb.wb_sel_o = (uint8_t)(0x3u << (addr & 0x2));
		break;
	case 4:
		wb.wb_sel_o = (uint8_t)(0x7u);
		break;
	default:
		assert(!"invalid size given");
	}
	wb.wb_we_o = we;
	wb.wb_adr_o = (uint8_t)(addr >> 2);
	wb.wb_dat_o = data;
	wb.state = WB_STATE_PUT_COMMAND;

}

static inline void
wb_write(uint16_t addr, uint8_t size, uint32_t data)
{
	while (wb.state != WB_STATE_IDLE);
	wb_pack(1, addr, size, data);
	spi_io_callback(SPI0, 0x00, (uint8_t *)&SPI0->SSPDR);
	spi_enable_interrupts(SPI0);
}

void
wb_write_u8(uint16_t addr, uint8_t data)
{
	wb_write(addr, sizeof data, data);
}

void
wb_write_u16(uint16_t addr, uint16_t data)
{
	wb_write(addr, sizeof data, data);
}

void
wb_write_u32(uint16_t addr, uint32_t data)
{
	wb_write(addr, sizeof data, data);
}

static inline uint32_t
wb_read(uint16_t addr, uint8_t size)
{
	while (wb.state != WB_STATE_IDLE);
	wb_pack(0, addr, size, 0x00);
	spi_enable_interrupts(SPI0);
	return wb.wb_dat_i;
}

uint8_t
wb_read_u8(uint16_t addr)
{
	return (uint8_t)wb_read(addr, sizeof(uint8_t));
}

uint16_t
wb_read_u16(uint16_t addr)
{
	return (uint16_t)wb_read(addr, sizeof(uint16_t));
}

uint32_t
wb_read_u32(uint16_t addr)
{
	return wb_read(addr, sizeof(uint16_t));
}

void
spi_io_callback(struct mcu_spi *spi, uint8_t rx, uint8_t volatile *tx)
{
	assert(spi == SPI0);

	switch (wb.state) {
	case WB_STATE_PUT_COMMAND:
		*tx = (uint8_t)(wb.wb_we_o << 7) | wb.wb_sel_o;
		wb.state++;
		break;
	case WB_STATE_PUT_ADDRESS:
		*tx = wb.wb_adr_o;
		wb.state = wb.wb_we_o ? wb.state + 1 : WB_STATE_WAIT_ACK;
		break;
	case WB_STATE_PUT_DATA_0:
	case WB_STATE_PUT_DATA_1:
	case WB_STATE_PUT_DATA_2:
	case WB_STATE_PUT_DATA_3:
		*tx = (uint8_t)(wb.wb_dat_o >> 24);
		wb.wb_dat_o = (uint32_t)(wb.wb_dat_o << 8);
		wb.state++;
		break;
	case WB_STATE_WAIT_ACK:
		*tx = 0x00;
		if (rx == 0xFF)
			wb.state = wb.wb_we_o ? WB_STATE_IDLE : wb.state + 1;
		break;
	case WB_STATE_GET_DATA_0:
	case WB_STATE_GET_DATA_1:
	case WB_STATE_GET_DATA_2:
	case WB_STATE_GET_DATA_3:
		*tx = 0x00;
		wb.wb_dat_i = (uint32_t)(wb.wb_dat_i << 8) | rx;
		wb.state++;
		break;
	case WB_STATE_IDLE:
		spi_disable_interrupts(SPI0);
		break;
	default:
		assert(!"unreached");
		break;
	}
}

void
alert(void)
{
	static uint16_t i = 0;

	if (i++ < UINT16_MAX / 2)
		gpio_set_pin(LED);
	else
		gpio_clear_pin(LED);
}

int
main(void)
{
	gpio_init();
	gpio_set_mode_output(LED);
	gpio_set_mode_output(TRIGGER);
	spi_init(SPI0, 254, SPI_SCK, SPI_CSN, SPI_RX, SPI_TX);

	for (uint32_t i = 0; i < 0x10000; i++) gpio_clear_pin(LED);
	gpio_set_pin(LED);
	for (;;) wb_write_u32(0x0000, 0xF4F4F4F4);

	return 0;
}
