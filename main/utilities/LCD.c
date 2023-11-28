#include <stdio.h>
#include <driver/gpio.h>
#include <utilities/LCD.h>
#include <esp_err.h>

spi_bus_config_t config = {
.mosi_io_num = MOSI,
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

void spi_init (void){

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &config, SPI_DMA_CH_AUTO));

}
