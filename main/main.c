#include <stdio.h>
#include <utilities/LCD.h>
#include "freertos/task.h"




void app_main(void)
{
    printf("main\n");

    spi_init();
    printf("spi innit completed\n");

    while(1){

        initialize_lcd();
        // printf("lcd init completed\n");

        vTaskDelay(500);
    }
}