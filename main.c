#include <stdint.h>
#include "spi.h"

int main(void)
{
	uint32_t buffer_len = 6;
	uint8_t tx_buffer[] = {0x90, 0x02, 0x03, 0x04, 0x05, 0x06};
	uint8_t rx_buffer[buffer_len];

	// Initialises the SPI2 peripheral as Master in mode 0 with baud-rate divisor 8.
	// To adjust initialisation parameters, the following could be un-commented and changed to preference (must be done before init()):
	//spi2.mode = 3;
	//spi2.master = 0;
	//spi2.br_div = div_16;
	spi2.init();
	spi2.interrupts = 1;
	spi2.tx_buffer = tx_buffer; // Set buffer pointers before transmit
	spi2.rx_buffer = rx_buffer;
	spi2.buffer_len = buffer_len; // Buffer length is also needed
	spi2.transmit(); // Go ahead and transmit your data

	for(volatile uint8_t i = 0; i < 255; i++); // Short delay

	// Interrupts can be enabled/disabled at any time between transmissions.
	spi2.interrupts = 0;
	spi2.transmit();

    /* Loop forever */
	for(;;);
}
