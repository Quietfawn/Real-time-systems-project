#include <stdio.h>
#include <driver/gpio.h>
#include <hal/spi_types.h>
#include "driver/spi_common.h"
#include "driver/spi_master.h"

#define ILI9481
#define CS GPIO_NUM_5
#define RESET GPIO_NUM_21
#define DC_RS GPIO_NUM_19
#define MOSI GPIO_NUM_23
#define SCK GPIO_NUM_18
#define LED GPIO_NUM_22
#define MISO -1
#define T_CLK GPIO_NUM_17
#define T_CS GPIO_NUM_16
#define T_DIN GPIO_NUM_15
#define T_DO GPIO_NUM_14
#define T_IRQ GPIO_NUM_33


spi_bus_config_t config = {
.mosi_io_num = MOSI,
.data0_io_num = -1,
.miso_io_num = MISO,
.sclk_io_num = SCK,
.max_transfer_sz = 0,
};

spi_device_interface_config_t dev_config = {
    .command_bits = 8,
    .address_bits = 8,
    .mode = 0,
    .clock_source = SPI2_HOST,
    .spics_io_num = CS,

};

spi_device_handle_t handle;


void spi_init (void);

