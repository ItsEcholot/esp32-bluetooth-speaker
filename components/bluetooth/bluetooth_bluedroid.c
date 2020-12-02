#include "bluetooth_bluedroid.h"

esp_err_t bt_bluedroid_setup(const char* device_name) {
    esp_err_t err;
    if ((err = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_BLUEDROID_TAG, "Init failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_BLUEDROID_TAG, "Enable failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_bt_dev_set_device_name(device_name)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_BLUEDROID_TAG, "Set device name failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(BLUETOOTH_BLUEDROID_TAG, "Setup done");
    return ESP_OK;
}