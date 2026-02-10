#include <stdint.h>
#include "spi.h"

int main(void)
{
	uint32_t buffer_len = 6;
	uint8_t tx_buffer[] = {0x90, 0x02, 0x03, 0x04, 0x05, 0x06};
	uint8_t rx_buffer[buffer_len];

	spi1.init();
	spi1.tx_buffer = tx_buffer;
	spi1.rx_buffer = rx_buffer;
	spi1.buffer_len = buffer_len;
	spi1.transmit();

    /* Loop forever */
	for(;;);
}
