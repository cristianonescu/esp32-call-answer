#include <stdio.h>
#include "esp_hf_client_api.h"
#include "esp_gap_bt_api.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "nvs_flash.h"
#include "sdkconfig.h"

#define TAG "HFP_BUTTON"

#define GPIO_ANSWER   12
#define GPIO_HANGUP   14

static esp_hf_client_connection_state_t hf_state = ESP_HF_CLIENT_CONNECTION_STATE_DISCONNECTED;
static int call_status = 0;  // 0=idle, 1=active

static void gap_event_handler(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);
static void hf_client_cb(esp_hf_client_cb_event_t event, esp_hf_client_cb_param_t *param);

static void gpio_init_buttons(void)
{
    gpio_config_t io = {
        .pin_bit_mask = (1ULL << GPIO_ANSWER) | (1ULL << GPIO_HANGUP),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io);
    ESP_LOGI(TAG, "Buttons GPIO %d(answer) %d(hangup)", GPIO_ANSWER, GPIO_HANGUP);
}

static void gap_event_handler(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    ESP_LOGI(TAG, "GAP event: %d", event);
}

static void hf_client_cb(esp_hf_client_cb_event_t event, esp_hf_client_cb_param_t *param)
{
    switch (event) {
    case ESP_HF_CLIENT_CONNECTION_STATE_EVT:
        hf_state = param->conn_stat.state;
        ESP_LOGI(TAG, "=== HFP STATE: %d ===", hf_state);
        break;

    case ESP_HF_CLIENT_CIND_CALL_EVT:
        call_status = param->call.status;
        ESP_LOGI(TAG, "=== CALL STATUS: %d ===", call_status);
        break;

    case ESP_HF_CLIENT_CIND_CALL_SETUP_EVT:
        ESP_LOGI(TAG, "=== CALL SETUP: %d ===", param->call_setup.status);
        break;

    case ESP_HF_CLIENT_RING_IND_EVT:
        ESP_LOGI(TAG, "📞 RINGING! Press ANSWER!");
        break;

    default:
        ESP_LOGD(TAG, "HFP event: %d", event);
        break;
    }
}

static void button_task(void *arg)
{
    int last_answer = 1, last_hangup = 1;

    while (1) {
        int a = gpio_get_level(GPIO_ANSWER);
        int h = gpio_get_level(GPIO_HANGUP);

        if (a == 0 && last_answer == 1) {
            ESP_LOGI(TAG, "🔊 ANSWER! hf=%d call=%d", hf_state, call_status);
            if (hf_state >= ESP_HF_CLIENT_CONNECTION_STATE_CONNECTED) {
                esp_err_t ret = esp_hf_client_answer_call();
                ESP_LOGI(TAG, "ATA: %s", ret == ESP_OK ? "OK" : "FAILED");
            }
        }

        if (h == 0 && last_hangup == 1) {
            ESP_LOGI(TAG, "📞 HANGUP! hf=%d call=%d", hf_state, call_status);
            if (hf_state >= ESP_HF_CLIENT_CONNECTION_STATE_CONNECTED) {
                esp_err_t ret = esp_hf_client_reject_call();
                ESP_LOGI(TAG, "CHUP: %s", ret == ESP_OK ? "OK" : "FAILED");
            }
        }

        last_answer = a;
        last_hangup = h;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32 HFP Call Buttons");

    // NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    // BT Controller
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT));

    // Bluedroid
    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    // GAP
    esp_bt_gap_register_callback(gap_event_handler);
    ESP_ERROR_CHECK(esp_bt_gap_set_device_name("ESP32 Call Buttons"));
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    // Buttons
    gpio_init_buttons();
    xTaskCreate(button_task, "buttons", 4096, NULL, 5, NULL);

    // HFP
    ESP_ERROR_CHECK(esp_hf_client_init());
    esp_hf_client_register_callback(hf_client_cb);

    ESP_LOGI(TAG, "✅ READY! Pair 'ESP32 Call Buttons'");
}
