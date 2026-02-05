#include <stdint.h>
#include "spi.h"

int main(void)
{
	uint8_t tx_buffer[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	uint8_t rx_buffer[6];

	spi1_init_master_mode0(div_8);
	spi1_transmit(tx_buffer, rx_buffer, 6);

    /* Loop forever */
	for(;;);
}
