#include "bluetooth_controller.h"

static esp_err_t bt_controller_adf_init_service_var();

esp_err_t bt_controller_setup(void) {
    esp_err_t err;
    
    bt_controller_adf_init_service_var();
    esp_bt_controller_config_t bt_controller_config = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((err = esp_bt_controller_init(&bt_controller_config)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_CONTROLLER_TAG, "Init failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_bt_controller_enable(ESP_BT_MODE_BTDM)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_CONTROLLER_TAG, "Enable failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(BLUETOOTH_CONTROLLER_TAG, "Setup done");
    return ESP_OK;
}

static esp_err_t bt_controller_adf_init_service_var() {
    g_bt_service = calloc(1, sizeof(bluetooth_service_t));
    AUDIO_MEM_CHECK(BLUETOOTH_CONTROLLER_TAG, g_bt_service, return);
    if (g_bt_service != NULL)
        return ESP_OK;
    else
        return ESP_ERR_NO_MEM;
}