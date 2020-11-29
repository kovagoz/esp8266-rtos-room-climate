#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_err.h>
#include <dht/dht.h>

#define DHT_GPIO 5 // D1 pin

void temperature_task(void *pvParameters)
{
    ESP_ERROR_CHECK(dht_init(DHT_GPIO, false));

    vTaskDelay(2 * configTICK_RATE_HZ);

    for (;;) {
        float humidity    = 0;
        float temperature = 0;

        if (dht_read_float_data(DHT_TYPE_DHT22, DHT_GPIO, &humidity, &temperature) == ESP_OK) {
            printf("Humidity: %.2f Temperature: %.2f\n", humidity, temperature);
        } else {
            printf("Fail to get dht temperature data\n");
        }

        vTaskDelay(5 * configTICK_RATE_HZ);
    }

    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(temperature_task, "Get current temperature", 2048, NULL, tskIDLE_PRIORITY, NULL);
}
