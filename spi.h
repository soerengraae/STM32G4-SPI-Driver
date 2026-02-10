#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

#define NVIC_ISER_BASE ((uint32_t *) 0xE000E100)
#define SPI1_NVIC_POS 35
#define SPI1_NVIC_ISER SPI1_NVIC_POS / 32
#define SPI1_NVIC_ISER_OFFSET SPI1_NVIC_POS - 32
#define SPI2_NVIC_POS 36
#define SPI2_NVIC_ISER SPI2_NVIC_POS / 32
#define SPI2_NVIC_ISER_OFFSET SPI2_NVIC_POS - 32
#define NVIC_IPR_BASE ((uint32_t *) 0xE000E400)
#define SPI1_NVIC_IPR SPI1_NVIC_POS / 32
#define SPI1_NVIC_IPR_OFFSET SPI1_NVIC_POS - 32
#define SPI2_NVIC_IPR SPI2_NVIC_POS / 32
#define SPI2_NVIC_IPR_OFFSET SPI2_NVIC_POS - 32

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
#define GPIOB_BIT 1
#define SPI1_BIT 12
#define SPI2_BIT 14
#define SPI3_BIT 15
#define SPI4_BIT 15

#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
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
#define PA5_AF PA5*2
#define PA6_AF PA6*2
#define PA7_AF PA7*2
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define PB12 24
#define PB13 26
#define PB14 28
#define PB15 30
#define PB13_AF 20
#define PB14_AF 24
#define PB15_AF 28

#define SPI1_BASE 0x40013000
#define SPI2_BASE 0x40003800
#define SPI3_BASE 0x40003C00
#define SPI4_BASE 0x40013C00
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
#define SPI2 ((SPI_TypeDef *)SPI2_BASE)
#define SPI3 ((SPI_TypeDef *)SPI3_BASE)
#define SPI4 ((SPI_TypeDef *)SPI4_BASE)

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
	ENOTACT,
	ENOTEQ,
	ENOTRDY
} SPI_Error_Code;

/**
 * @brief The SPI object has a default baud-rate divisor of 8 (div_8) and a default mode of 0 (mode = 0).
 * Firstly the object is initialised with init(), which will use @p br_div and @p mode to configure the SPI peripheral.
 * Transmit data with transmit(), but first set the TX- and RX-buffers; don't forget to update @p buffer_len as well.
 * */
typedef struct {
	void *(cs_low); // Function for setting Chip Select low
	void *(cs_high); // Function for setting Chip Select high
    int (*transmit)(void); // Function for transmitting the TX buffer
    int (*init)(void); // Function for initialising the SPI peripheral and the respective pins
    uint8_t tx_ready;
	SPI_TypeDef *peripheral_addr; // Stores the address of the SPI peripheral
	uint8_t initialized; // Flag for initialisation
	uint8_t interrupts; // Flag for enabling interrupts during initialisation
	SPI_Baudrate_Divisor br_div; // Baud-rate divisor : default is 8
	uint8_t ds; // Data size : default is 8
	uint8_t mode; // SPI mode : default is 0
	uint32_t buffer_len; // TX/RX buffer length
	uint8_t *tx_buffer; // Pointer to the TX buffer
	uint8_t *rx_buffer; // Pointer to the RX buffer
} SPI;

/**
 * @brief spi1 uses the following pins:
 * PA4 as CS
 * PA5 as SCLK
 * PA6 as MISO
 * PA7 as MOSI
 * */
extern SPI spi1;

/**
 * @brief spi2 uses the following pins:
 * PB12 as CS
 * PB13 as SCLK
 * PB14 as MISO
 * PB25 as MOSI
 * */
extern SPI spi2;

#endif /* SPI_H_ */
