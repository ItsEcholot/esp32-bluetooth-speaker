#include "nvs.h"

void nvs_init(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    ESP_LOGI(NVS_COMPONENT_TAG, "Setup done");
}

void nvs_save_last_connected_bd_addr(esp_bd_addr_t addr) {
    esp_err_t err;
    nvs_handle_t nvs_handle;
    if ((err = nvs_open(NVS_BT_NAMESPACE, NVS_READWRITE, &nvs_handle)) != ESP_OK) {
        ESP_LOGE(NVS_COMPONENT_TAG, "Failed to open nvs handle: %s", esp_err_to_name(err));
        return;
    }
    
}