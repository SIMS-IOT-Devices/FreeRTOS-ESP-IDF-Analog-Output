// Generate analog output

#include <stdio.h>
#include "esp_event.h"
#include "driver/gpio.h"
#include <driver/dac.h>

#define pin25 25

void app_main(void)
{
    int voltage = 0;
    int delta = 10;
    
    gpio_pad_select_gpio(pin25);                    // Defines GPIO functionality for the pin
    gpio_set_direction(pin25, GPIO_MODE_OUTPUT);    // Pin input/output definition

    while (true)
    {
        dac_output_enable(DAC_CHANNEL_1);           // Enable analog output at pin 25
        dac_output_voltage(DAC_CHANNEL_1, voltage); // Set analog level
        
        // Generate variable voltage number between 0 to 255 (3.3V)
        voltage = voltage + delta;
        if (voltage>240 || voltage<10) {delta=(-1)*delta;}
        printf("%d\n", voltage);

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}