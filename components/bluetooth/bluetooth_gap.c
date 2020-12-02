#include "bluetooth_gap.h"

static void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

esp_err_t bt_gap_setup(void) {
    esp_err_t err;
    if ((err = esp_bt_gap_register_callback(bt_gap_callback)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_GAP_TAG, "Register callback failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_GAP_TAG, "Set scan mode failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(BLUETOOTH_GAP_TAG, "Setup done");
    return ESP_OK;
}

static void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
    ESP_LOGI(BLUETOOTH_GAP_TAG, "Event id %i", event);
    switch (event)
    {
    case ESP_BT_GAP_AUTH_CMPL_EVT:
        ESP_LOGI(BLUETOOTH_GAP_TAG, "Auth complete with %s", param->auth_cmpl.device_name);
        break;
    default:
        ESP_LOGI(BLUETOOTH_GAP_TAG, "Unhandled event %i", event);
        break;
    }
}