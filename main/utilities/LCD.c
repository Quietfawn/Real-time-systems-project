#include <stdio.h>
#include <driver/gpio.h>
#include <utilities/LCD.h>
#include <esp_err.h>

void spi_init (void){

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, config, SPI_DMA_CH_AUTO));

}
