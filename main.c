#include <stdint.h>
#include "spi.h"

int main(void)
{
	uint32_t buffer_len = 6;
	uint8_t tx_buffer[] = {0x90, 0x02, 0x03, 0x04, 0x05, 0x06};
	uint8_t rx_buffer[buffer_len];

	spi2.interrupts = 1;
	spi2.init();
	spi2.tx_buffer = tx_buffer;
	spi2.rx_buffer = rx_buffer;
	spi2.buffer_len = buffer_len;
	spi2.transmit();

	for(uint8_t i = 0; i < 255; i++); // Short delay

	spi2.interrupts = 0;
	spi2.transmit();

    /* Loop forever */
	for(;;);
}
