#include "spi.h"

#if SPI_DATASIZE > 16
#error "SPI_DATASIZE invalid"
#elif SPI_DATASIZE < 4
#error "SPI_DATASIZE invalid"
#endif

#include <stdlib.h>

static uint8_t transmit_byte(uint8_t byte, SPI_TypeDef *SPI) {
	while (!(SPI->SR & (1 << 1))); // Poll TXE
	*(volatile uint8_t *)(&SPI->DR) = byte;

	while (!(SPI->SR & (1 << 0))); // Poll RXNE
	return *(volatile uint8_t *)(&SPI->DR);
}

static void cs_low() {
	GPIOA->BSRR |= (1 << 20); // Reset output for PA4
}

static void cs_high() {
	GPIOA->BSRR |= (1 << 4); // Set output for PA4
}

static int spi1_init(void) {
	RCC->AHB2ENR |= (1 << GPIOA_BIT);
	RCC->AHB2RSTR |= (1 << GPIOA_BIT); // Set
	RCC->AHB2RSTR &= ~(1 << GPIOA_BIT); // Clear

	/* Configure PA4 as CS */
	GPIOA->MODER &= ~(3 << PA4); // Clear mode
	GPIOA->MODER |= (1 << PA4); // Set output mode
	//GPIOA->OSPEEDR |= (3 << PA4); // Set very high speed output mode

	/* Configure PA5 as SCLK */
	GPIOA->MODER &= ~(3 << PA5); // Clear mode
	GPIOA->MODER |= (2 << PA5); // Set alternate function mode
	GPIOA->AFRL &= ~(15 << PA5*2); // Clear alternate function
	GPIOA->AFRL |= (5 << PA5*2); // Set alternate function 5

	/* Configure PA6 as MISO */
	GPIOA->MODER &= ~(3 << PA6); // Clear mode
	GPIOA->MODER |= (2 << PA6); // Set alternate function mode
	GPIOA->AFRL &= ~(15 << PA6*2); // Clear alternate function
	GPIOA->AFRL |= (5 << PA6*2); // Set alternate function 5

	/* Configure PA7 as MOSI */
	GPIOA->MODER &= ~(3 << PA7); // Clear mode
	GPIOA->MODER |= (2 << PA7); // Set alternate function mode
	GPIOA->AFRL &= ~(15 << PA7*2); // Clear alternate function
	GPIOA->AFRL |= (5 << PA7*2); // Set alternate function 5

	/* Enable SPI1 clock and reset SPI1 */
	RCC->APB2ENR |= (1 << SPI1_BIT);
	RCC->APB2RSTR |= (1 << SPI1_BIT); // Set
	RCC->APB2RSTR &= ~(1 << SPI1_BIT); // Clear

	cs_high();

	SPI1->CR2 = ((SPI_DATASIZE-1) << 8) // DS[2:0] = 0111 (8-bit Data Size)
			  | (1 << 7)
			  | (1 << 6)
			  | (1 << 12); // Set FIFO reception threshold to 8-bit (ensures an RXNE event after one byte is received)

	/* Configure SPI1 */
	SPI1->CR1 = (spi1.br_div << 3) // Baud-rate
			  | (1 << 2) // Master Configuration
			  | (1 << 8) // Software Slave Management
			  | (1 << 9) // Internal Slave Select
			  | (spi1.mode << 0) // Mode
			  | (1 << 6); // Enable

	if (!(RCC->APB2ENR & (1 << SPI1_BIT)))
		return -ENOCLK;

	if (!(SPI1->CR1 & (1 << 6)))
		return -ENOTACT;

	spi1.initialized = 1;

	return ENONE;
}

static int spi_transmit(SPI spi) {
	if (!spi.initialized)
		return -ENOTRDY;

	cs_low();

	for (uint32_t i = 0; i < spi.buffer_len; i++)
		spi.rx_buffer[i] = transmit_byte(spi.tx_buffer[i], spi.reg_addr);

	cs_high();

	while (!(spi.reg_addr->SR & (1 << 1))); // Poll TXE

	return ENONE;
}

static int spi1_transmit(void) {
	return spi_transmit(spi1);
}

SPI spi1 = {
	.reg_addr = SPI1,
	.initialized = 0,
	.br_div = div_8,
	.buffer_len = 0,
	.tx_buffer = 0,
	.rx_buffer = 0,
	.mode = 0,
    .transmit = spi1_transmit,
	.init = spi1_init,
};
