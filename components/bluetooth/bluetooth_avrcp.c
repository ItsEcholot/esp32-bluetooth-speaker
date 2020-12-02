#include "bluetooth_avrcp.h"

static void bt_avrcp_callback(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param);

esp_err_t bt_avrcp_setup(void) {
    esp_err_t err;
    if ((err = esp_avrc_ct_register_callback(bt_avrcp_callback)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_AVRCP_TAG, "Register callback failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_avrc_ct_init()) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_AVRCP_TAG, "Controller init failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Setup done");
    return ESP_OK;
}

esp_err_t bt_avrcp_request_metadata(void) {
    const uint8_t attr_mask = ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST | ESP_AVRC_MD_ATTR_ALBUM;
    return esp_avrc_ct_send_metadata_cmd(0, attr_mask);
}

static void bt_avrcp_callback(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param) {
    switch (event)
    {
    case ESP_AVRC_CT_CONNECTION_STATE_EVT:
        ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Connection state %s", param->conn_stat.connected ? "connected" : "disconnected");
        //param->conn_stat.remote_bda
        break;
    case ESP_AVRC_CT_METADATA_RSP_EVT:
        switch (param->meta_rsp.attr_id)
        {
        case ESP_AVRC_MD_ATTR_TITLE:
            ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Metadata Title %s", param->meta_rsp.attr_text);
            break;
        case ESP_AVRC_MD_ATTR_ARTIST:
            ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Metadata Artist %s", param->meta_rsp.attr_text);
            break;
        case ESP_AVRC_MD_ATTR_ALBUM:
            ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Metadata Album %s", param->meta_rsp.attr_text);
            break;
        default:
            ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Unknown attribute %i", param->meta_rsp.attr_id);
            break;
        }
        break;
    default:
        ESP_LOGI(BLUETOOTH_AVRCP_TAG, "Unhandled event %i", event);
        break;
    }
}