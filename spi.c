#include "spi.h"

#include <stdlib.h>

static uint8_t transmit_byte(uint8_t byte, SPI_TypeDef *SPI) {
	while (!(SPI->SR & (1 << 1))); // Poll TXE
	*(volatile uint8_t *)(&SPI->DR) = byte;

	while (!(SPI->SR & (1 << 0))); // Poll RXNE
	return *(volatile uint8_t *)(&SPI->DR);
}

static void cs_low(SPI spi) {
	if (spi.reg_addr == spi1.reg_addr)
		GPIOA->BSRR |= (1 << 20); // Reset output for PA4
	else if (spi.reg_addr == spi2.reg_addr)
		GPIOB->BSRR |= (1 << 28); // Reset output for PB12
}

static void cs_high(SPI spi) {
	if (spi.reg_addr == spi1.reg_addr)
		GPIOA->BSRR |= (1 << 4); // Set output for PA4
	else if (spi.reg_addr == spi2.reg_addr)
		GPIOB->BSRR |= (1 << 12); // Set output for PB12
}

static int spi1_init(void) {
	RCC->AHB2ENR |= (1 << GPIOA_BIT);
	RCC->AHB2RSTR |= (1 << GPIOA_BIT); // Set
	RCC->AHB2RSTR &= ~(1 << GPIOA_BIT); // Clear

	/* Configure PA4 as CS */
	GPIOA->MODER &= ~(3 << PA4); // Clear mode
	GPIOA->MODER |= (1 << PA4); // Set output mode

	/* Configure PA5 as SCLK */
	GPIOA->MODER &= ~(3 << PA5); // Clear mode
	GPIOA->MODER |= (2 << PA5); // Set alternate function mode
	GPIOA->AFRL &= ~(15 << PA5_AF); // Clear alternate function
	GPIOA->AFRL |= (5 << PA5_AF); // Set alternate function 5

	/* Configure PA6 as MISO */
	GPIOA->MODER &= ~(3 << PA6); // Clear mode
	GPIOA->MODER |= (2 << PA6); // Set alternate function mode
	GPIOA->AFRL &= ~(15 << PA6_AF); // Clear alternate function
	GPIOA->AFRL |= (5 << PA6_AF); // Set alternate function 5

	/* Configure PA7 as MOSI */
	GPIOA->MODER &= ~(3 << PA7); // Clear mode
	GPIOA->MODER |= (2 << PA7); // Set alternate function mode
	GPIOA->AFRL &= ~(15 << PA7_AF); // Clear alternate function
	GPIOA->AFRL |= (5 << PA7_AF); // Set alternate function 5

	/* Enable SPI1 clock and reset SPI1 */
	RCC->APB2ENR |= (1 << SPI1_BIT);
	RCC->APB2RSTR |= (1 << SPI1_BIT); // Set
	RCC->APB2RSTR &= ~(1 << SPI1_BIT); // Clear

	cs_high(spi1);

	SPI1->CR2 = ((spi1.ds-1) << 8) // DS[2:0] = 0111 (8-bit Data Size)
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

static int spi2_init(void) {
	RCC->AHB2ENR |= (1 << GPIOB_BIT);
	RCC->AHB2RSTR |= (1 << GPIOB_BIT); // Set
	RCC->AHB2RSTR &= ~(1 << GPIOB_BIT); // Clear

	/* Configure PB12 as CS */
	GPIOB->MODER &= ~(3 << PB12); // Clear mode
	GPIOB->MODER |= (1 << PB12); // Set output mode

	/* Configure PB13 as SCLK */
	GPIOB->MODER &= ~(3 << PB13); // Clear mode
	GPIOB->MODER |= (2 << PB13); // Set alternate function mode
	GPIOB->AFRH &= ~(15 << PB13_AF); // Clear alternate function
	GPIOB->AFRH |= (5 << PB13_AF); // Set alternate function 5

	/* Configure PB14 as MISO */
	GPIOB->MODER &= ~(3 << PB14); // Clear mode
	GPIOB->MODER |= (2 << PB14); // Set alternate function mode
	GPIOB->AFRH &= ~(15 << PB14_AF); // Clear alternate function
	GPIOB->AFRH |= (5 << PB14_AF); // Set alternate function 5

	/* Configure PB15 as MOSI */
	GPIOB->MODER &= ~(3 << PB15); // Clear mode
	GPIOB->MODER |= (2 << PB15); // Set alternate function mode
	GPIOB->AFRH &= ~(15 << PB15_AF); // Clear alternate function
	GPIOB->AFRH |= (5 << PB15_AF); // Set alternate function 5

	/* Enable SPI2 clock and reset SPI2 */
	RCC->APB1ENR1 |= (1 << SPI2_BIT);
	RCC->APB1RSTR1 |= (1 << SPI2_BIT); // Set
	RCC->APB1RSTR1 &= ~(1 << SPI2_BIT); // Clear

	cs_high(spi2);

	SPI2->CR2 = ((spi2.ds-1) << 8) // DS[2:0] = 0111 (8-bit Data Size)
			  | (1 << 7)
			  | (1 << 6)
			  | (1 << 12); // Set FIFO reception threshold to 8-bit (ensures an RXNE event after one byte is received)

	/* Configure SPI1 */
	SPI2->CR1 = (spi2.br_div << 3) // Baud-rate
			  | (1 << 2) // Master Configuration
			  | (1 << 8) // Software Slave Management
			  | (1 << 9) // Internal Slave Select
			  | (spi2.mode << 0) // Mode
			  | (1 << 6); // Enable

	if (!(RCC->APB1ENR1 & (1 << SPI2_BIT)))
		return -ENOCLK;

	if (!(SPI2->CR1 & (1 << 6)))
		return -ENOTACT;

	spi2.initialized = 1;

	return ENONE;
}

static int spi_transmit(SPI spi) {
	if (!spi.initialized)
		return -ENOTRDY;

	cs_low(spi);

	for (uint32_t i = 0; i < spi.buffer_len; i++)
		spi.rx_buffer[i] = transmit_byte(spi.tx_buffer[i], spi.reg_addr);

	cs_high(spi);

	while (!(spi.reg_addr->SR & (1 << 1))); // Poll TXE

	return ENONE;
}

static int spi1_transmit(void) {
	return spi_transmit(spi1);
}

static int spi2_transmit(void) {
	return spi_transmit(spi2);
}

SPI spi1 = {
	.reg_addr = SPI1,
	.initialized = 0,
	.br_div = div_8,
	.ds = 8,
	.mode = 0,
    .transmit = spi1_transmit,
	.init = spi1_init,
};

SPI spi2 = {
	.reg_addr = SPI2,
	.initialized = 0,
	.br_div = div_8,
	.ds = 8,
	.mode = 0,
    .transmit = spi2_transmit,
	.init = spi2_init,
};
