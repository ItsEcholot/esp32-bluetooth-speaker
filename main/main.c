#include "main.h"

#include <esp_log.h>
#include <esp_ota_ops.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "nvs.h"
#include "bluetooth.h"

#include <audio_pipeline.h>
#include <esp_spp_api.h>

void vMonitor_activity() {
    //char report[2000];
    for (;;) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        //vTaskGetRunTimeStats(report);
        //ESP_LOGI(tag, "\n%s", report);
        /*if (bt_avrcp_request_metadata() != ESP_OK) {
            ESP_LOGE(tag, "Failed to request metadata");
        }*/
    }
}

void vHealth_confirm() {
    for (;;) {
        vTaskDelay(HEALTH_CHECK_OK_DELAY / portTICK_PERIOD_MS);
        if (esp_ota_mark_app_valid_cancel_rollback() == ESP_OK) {
            ESP_LOGI(MAIN_TAG, "OTA Health confirmed after %i seconds", HEALTH_CHECK_OK_DELAY/1000);
            vTaskDelete(NULL);
        } else {
            ESP_LOGE(MAIN_TAG, "Error while confirming health");
        }
    }
}

    uint32_t handle;
    const char *hello_text = BT_DEVICE_NAME" says hello :)\n";
    uint8_t *data;
    uint16_t len;
    esp_ota_handle_t *ota_handle;
    esp_partition_t *partition;
void bt_spp_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    esp_err_t err;
    switch (event)
    {
    case ESP_SPP_START_EVT:
        ESP_LOGI(MAIN_TAG, "Server start");
        break;
    case ESP_SPP_SRV_OPEN_EVT:
        ESP_LOGI(MAIN_TAG, "Server connection open");
        handle = param->srv_open.handle;
        //esp_spp_write(handle, strlen(hello_text)+1, (uint8_t*) hello_text);
        partition = esp_ota_get_next_update_partition(NULL);
        if (partition == NULL) {
            ESP_LOGE(MAIN_TAG, "Getting next partition failed");
            return;
        }
        if((err = esp_ota_begin(partition, OTA_SIZE_UNKNOWN, ota_handle)) != ESP_OK) {
            ESP_LOGE(MAIN_TAG, "Begin failed: %s", esp_err_to_name(err));
            return;
        }
        break;    
    case ESP_SPP_DATA_IND_EVT:
        data = param->data_ind.data;
        len = param->data_ind.len;
        ESP_LOGI(MAIN_TAG, "Received data %i", len);
        if((err = esp_ota_write(ota_handle, data, len)) != ESP_OK) {
            ESP_LOGE(MAIN_TAG, "Write failed: %s", esp_err_to_name(err));
            return;
        }
        break;
    case ESP_SPP_CLOSE_EVT:
        handle = param->close.handle;
        if((err = esp_ota_end(handle)) != ESP_OK) {
            ESP_LOGE(MAIN_TAG, "End failed: %s", esp_err_to_name(err));
            return;
        }
        if ((err = esp_ota_set_boot_partition(partition)) != ESP_OK) {
            ESP_LOGE(MAIN_TAG, "Set boot partition failed: %s", esp_err_to_name(err));
            return;
        }
        esp_restart();
        break;
    default:
        break;
    }
}

void app_main(void)
{
    ESP_LOGI(MAIN_TAG, "esp32-bluetooth-speaker v"VERSION_STRING" starting");
    bool ota_rollback_possible = esp_ota_check_rollback_is_possible();

    nvs_init();

    if(bt_controller_setup() != ESP_OK && ota_rollback_possible) esp_ota_mark_app_invalid_rollback_and_reboot();
    if(bt_bluedroid_setup(BT_DEVICE_NAME) != ESP_OK && ota_rollback_possible) esp_ota_mark_app_invalid_rollback_and_reboot();
    if(bt_a2dp_setup() != ESP_OK && ota_rollback_possible) esp_ota_mark_app_invalid_rollback_and_reboot();
    if(bt_avrcp_setup() != ESP_OK && ota_rollback_possible) esp_ota_mark_app_invalid_rollback_and_reboot();
    if(bt_gap_setup() != ESP_OK && ota_rollback_possible) esp_ota_mark_app_invalid_rollback_and_reboot();

    esp_err_t err;
    audio_pipeline_cfg_t pipeline_bt_i2s_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    audio_pipeline_handle_t pipeline_bt_i2s;
    if ((pipeline_bt_i2s = audio_pipeline_init(&pipeline_bt_i2s_cfg)) == NULL) {
        ESP_LOGE(MAIN_TAG, "Pipeline init failed");
        return;
    }
    audio_element_handle_t audio_el_bt = bluetooth_service_create_stream();
    audio_pipeline_register(pipeline_bt_i2s, audio_el_bt, "bt");
    //audio_pipeline_link()
    audio_pipeline_run(pipeline_bt_i2s);

    if ((err = esp_spp_register_callback(bt_spp_callback)) != ESP_OK) {
        ESP_LOGE(MAIN_TAG, "Register callback failed: %s", esp_err_to_name(err));
        return;
    }
    if ((err = esp_spp_init(ESP_SPP_MODE_CB)) != ESP_OK) {
        ESP_LOGE(MAIN_TAG, "Init failed: %s", esp_err_to_name(err));
        return;
    }
    if ((err = esp_spp_start_srv(ESP_SPP_SEC_NONE, ESP_SPP_ROLE_MASTER, 0, "serial")) != ESP_OK) {
        ESP_LOGE(MAIN_TAG, "Srv start failed: %s", esp_err_to_name(err));
        return;
    }

    xTaskCreatePinnedToCore(vMonitor_activity, "monitor_act", 4096, NULL, 1, NULL, 1);
    if (ota_rollback_possible) xTaskCreatePinnedToCore(vHealth_confirm, "health_conf", 512, NULL, 1, NULL, 1);

    ESP_LOGI(MAIN_TAG, "Done, on core %i", xPortGetCoreID());
}
