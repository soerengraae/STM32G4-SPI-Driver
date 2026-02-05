#ifndef SPI_H_
#define SPI_H_

// SPI_DATASIZE defines the Data Size of the SPI data packets - default is 8-bit; 4- to 16-bit is possible.
#define SPI_DATASIZE 8

#include <stdint.h>

#define RCC_BASE 0x40021000
typedef struct {
	volatile uint32_t CR; // Offset 0x00
	volatile uint32_t ICSCR; // Offset 0x04
	volatile uint32_t CFGR; // Offset 0x08
	volatile uint32_t PLLCFGR; // Offset 0x0C
	volatile uint32_t RES0; // Offset 0x10
	volatile uint32_t RES1; // Offset 0x14
	volatile uint32_t CIER; // Offset 0x18
	volatile uint32_t CIFR; // Offset 0x1C
	volatile uint32_t CICR; // Offset 0x20
	volatile uint32_t RES2; // Offset 0x24
	volatile uint32_t AHB1RSTR; // Offset 0x28
	volatile uint32_t AHB2RSTR; // Offset 0x2C
	volatile uint32_t AHB3RSTR; // Offset 0x30
	volatile uint32_t RES3; // Offset 0x34
	volatile uint32_t APB1RSTR1; // Offset 0x38
	volatile uint32_t APB1RSTR2; // Offset 0x3C
	volatile uint32_t APB2RSTR; // Offset 0x40
	volatile uint32_t RES4; // Offset 0x44
	volatile uint32_t RCC_AHB1ENR; // Offset 0x48
	volatile uint32_t AHB2ENR; // Offset 0x4C
	volatile uint32_t AHB3ENR; // Offset 0x50
	volatile uint32_t RES5; // Offset 0x54
	volatile uint32_t APB1ENR1; // Offset 0x58
	volatile uint32_t APB1ENR2; // Offset 0x5C
	volatile uint32_t APB2ENR; // Offset 0x60
	volatile uint32_t RES6; // Offset 0x64
	volatile uint32_t AHB1SMENR; // Offset 0x68
	volatile uint32_t AHB2SMENR; // Offset 0x6C
	volatile uint32_t AHB3SMENR; // Offset 0x70
	volatile uint32_t RES7; // Offset 0x74
	volatile uint32_t APB1SMENR1; // Offset 0x78
	volatile uint32_t APB1SMENR2; // Offset 0x7C
	volatile uint32_t APB2SMENR; // Offset 0x80
	volatile uint32_t RES8; // Offset 0x84
	volatile uint32_t CCIPR; // Offset 0x88
	volatile uint32_t RES9; // Offset 0x8C
	volatile uint32_t BDCR; // Offset 0x90
	volatile uint32_t RCC_CSR; // Offset 0x94
	volatile uint32_t CRRCR; // Offset 0x98
	volatile uint32_t CCIPR2; // Offset 0x9C
} RCC_TypeDef;
#define RCC ((RCC_TypeDef *)RCC_BASE)
#define GPIOA_BIT 0
#define SPI1_BIT 12

#define GPIOA_BASE 0x48000000
typedef struct {
	volatile uint32_t MODER; // Offset 0x00
	volatile uint32_t OTYPER; // Offset 0x04
	volatile uint32_t OSPEEDR; // Offset 0x08
	volatile uint32_t PUPDR; // Offset 0x0C
	volatile uint32_t IDR; // Offset 0x10
	volatile uint32_t ODR; // Offset 0x14
	volatile uint32_t BSRR; // Offset 0x18
	volatile uint32_t LCKR; // Offset 0x1C
	volatile uint32_t AFRL; // Offset 0x20
	volatile uint32_t AFRH; // Offset 0x24
	volatile uint32_t BRR; // Offset 0x28
} GPIO_TypeDef;
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define PA4 8
#define PA5 10
#define PA6 12
#define PA7 14

#define SPI1_BASE 0x40013000
typedef struct {
	volatile uint32_t CR1; // Offset 0x00
	volatile uint32_t CR2; // Offset 0x04
	volatile uint32_t SR; // Offset 0x08
	volatile uint32_t DR; // Offset 0x0C
	volatile uint32_t CRCPR; // Offset 0x10
	volatile uint32_t RXCRCR; // Offset 0x14
	volatile uint32_t TXCRCR; // Offset 0x18
	volatile uint32_t I2SCFGR; // Offset 0x1C
	volatile uint32_t I2SPR; // Offset 0x20
} SPI_TypeDef;
#define SPI1 ((SPI_TypeDef *)SPI1_BASE)

/**
 * @brief Provides pre-defined values for selecting the SPI baud-rate divisor.
 * If using the default 16MHz high-speed internal clock, these are the resulting baud-rates:
 * div_2 -> 8MHz
 * div_4 -> 4MHz
 * div_8 -> 2MHz
 * div_16 -> 1MHz
 * div_32 -> 500kHz
 * div_64 -> 250kHz
 * div_128 -> 125kHz
 * div_256 -> 62.5kHz
 * */
typedef enum {
	div_2,
	div_4,
	div_8,
	div_16,
	div_32,
	div_64,
	div_128,
	div_256
} SPI_Baudrate_Divisor;

typedef enum {
	ENONE,
	ENOCLK,
	ENOTACT
} SPI_Error_Code;

/**
 * @brief Transmits the data in the given @p tx_buffer of length @p len, and stores the responses in @p rx_buffer.
 * @return 0 if successful, negative error code on failure.
 * */
int spi1_transmit(uint8_t *tx_buffer, uint8_t *rx_buffer, uint32_t len);

int spi1_init_master_mode0(SPI_Baudrate_Divisor);
int spi1_init_master_mode1(SPI_Baudrate_Divisor);
int spi1_init_master_mode2(SPI_Baudrate_Divisor);
int spi1_init_master_mode3(SPI_Baudrate_Divisor);


#endif /* SPI_H_ */
