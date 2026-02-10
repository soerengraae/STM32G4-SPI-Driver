# STM32G4 SPI Driver

A bare-metal SPI master driver for STM32G4 (ARM Cortex-M4) microcontrollers. Provides an object-style C interface for SPI communication with support for both polling and interrupt-driven modes.

## Features

- **SPI1 and SPI2** peripheral support
- **Polling and interrupt** transmission modes
- Configurable baud rate (div/2 through div/256)
- Configurable data size and SPI mode
- Automatic chip select (CS) control
- No HAL dependency

## Pin Configuration

| Function | SPI1 (GPIOA) | SPI2 (GPIOB) |
|----------|--------------|--------------|
| CS       | PA4          | PB12         |
| SCLK     | PA5          | PB13         |
| MISO     | PA6          | PB14         |
| MOSI     | PA7          | PB15         |

## Usage
Simply include the files in your project. See main.c for a transmission example.

## Configuration

Default settings on the `spi1` and `spi2` objects:

| Parameter    | Default  | Options                                          |
|--------------|----------|--------------------------------------------------|
| `br_div`     | `div_8`  | `div_2`, `div_4`, `div_8`, … `div_256`           |
| `ds`         | `8`      | Data size in bits                                |
| `mode`       | `0`      | SPI mode (CPOL/CPHA)                             |
| `interrupts` | `0`      | `0` = polling, `1` = interrupt-driven            |
