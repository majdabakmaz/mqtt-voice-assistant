#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "projectconfig.h"

#define BROKER_URL CONFIG_MY_BROKER_URL

static const char *TAG = "MQTT";
esp_mqtt_client_handle_t client;
TaskHandle_t myTaskHandle = NULL;

void my_publish(int mode)
{
    int msg_id;
    switch (mode)
    {
    case 1:
        msg_id = esp_mqtt_client_publish(client, "fromLyraT", "palim", 0, 1, 0);
        break;
    case 0:
        msg_id = esp_mqtt_client_publish(client, "fromLyraT", "gasim", 0, 1, 0);
        break;
    case 2:
        msg_id = esp_mqtt_client_publish(client, "fromLyraT", "Say Hello", 0, 1, 0);
        break;
    case 3:
        msg_id = esp_mqtt_client_publish(client, "fromLyraT", "What time is it?", 0, 1, 0);
        break;
    default:
        break;
    }
}

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0)
    {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;

    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_publish(client, "fromLyraT", "boook", 0, 1, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "sunnyday", 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_publish(client, "fromLyraT", "Say Hello", 0, 1, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        // printf("PRIMLJENO = (%.*s) -> %.*s\r\n", event->topic_len, event->topic, event->data_len, event->data);
        printf("data\n");
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}

void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = BROKER_URL,
        .event_handle = mqtt_event_handler,
    };
    // esp_mqtt_client_handle_t
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

    // xTaskCreate(publish, "publish", 4096, NULL, 10, &myTaskHandle);
}

// void publish(void *pvParameters)
// {
//     int i = 0;
//     char mssg[50];
//     while (1)
//     {
//         vTaskDelay(pdMS_TO_TICKS(2000));
//         //       snprintf(mssg, sizeof(mssg), "boook(%d)", i);
//         // esp_mqtt_client_publish(client, "fromLyraT", mssg, 0, 1, 0);
//         i++;
//     }
// }