#include "bluetooth_a2dp.h"

/*static void bt_a2dp_callback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
static void bt_a2dp_callback_connection_state_handler(struct a2d_conn_stat_param* param);
static void bt_a2dp_callback_audio_state_handler(struct a2d_audio_stat_param* param);
static void bt_a2dp_sink_data_callback(const uint8_t* data, uint32_t len);
static uint32_t s_pkt_cnt = 0;*/

esp_err_t bt_a2dp_setup(void) {
    esp_err_t err;
    if ((err = esp_a2d_register_callback(bt_a2d_sink_cb_ptr)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_A2DP_TAG, "Register callback failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_a2d_sink_register_data_callback(bt_a2d_sink_data_cb_ptr)) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_A2DP_TAG, "Register sink data callback failed: %s", esp_err_to_name(err));
        return err;
    }
    if ((err = esp_a2d_sink_init()) != ESP_OK) {
        ESP_LOGE(BLUETOOTH_A2DP_TAG, "Sink init failed: %s", esp_err_to_name(err));
        return err;
    }

    g_bt_service->stream_type = AUDIO_STREAM_READER;

    ESP_LOGI(BLUETOOTH_A2DP_TAG, "Setup done");
    return ESP_OK;
}

/*static void bt_a2dp_callback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {
    const char* tag = "BT A2DP CALLBACK";
    switch (event)
    {
    case ESP_A2D_CONNECTION_STATE_EVT:
        bt_a2dp_callback_connection_state_handler(&(param->conn_stat));
        break;
    case ESP_A2D_AUDIO_STATE_EVT:
        bt_a2dp_callback_audio_state_handler(&(param->audio_stat));
        break;
    default:
        ESP_LOGI(tag, "Unhandled event %i", event);
        break;
    }
}

static void bt_a2dp_callback_connection_state_handler(struct a2d_conn_stat_param* param) {
    const char* tag = "BT A2DP CALLBACK CON STATE HANDLER";
    char conn_state[5];
    switch (param->state)
    {
    case ESP_A2D_CONNECTION_STATE_DISCONNECTED:
        strncpy(conn_state, "DISC", 5);
        break;
    case ESP_A2D_CONNECTION_STATE_CONNECTING:
        strncpy(conn_state, "CONI", 5);
        break;
    case ESP_A2D_CONNECTION_STATE_CONNECTED:
        strncpy(conn_state, "COND", 5);
        break;
    case ESP_A2D_CONNECTION_STATE_DISCONNECTING:
        strncpy(conn_state, "DISI", 5);
        break;
    default:
        break;
    }
    ESP_LOGI(tag, "Connection state %s", conn_state);
}

static void bt_a2dp_callback_audio_state_handler(struct a2d_audio_stat_param* param) {
    const char* tag = "BT A2DP CALLBACK AUDIO STATE HANDLER";
    char conn_state[8];
    switch (param->state)
    {
    case ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND:
        strncpy(conn_state, "REMSUSP", 8);
        break;
    case ESP_A2D_AUDIO_STATE_STOPPED:
        strncpy(conn_state, "STOPPED", 8);
        break;
    case ESP_A2D_AUDIO_STATE_STARTED:
        strncpy(conn_state, "STARTED", 8);
        break;
    default:
        break;
    }
    ESP_LOGI(tag, "Connection state %s", conn_state);
}

static void bt_a2dp_sink_data_callback(const uint8_t* data, uint32_t len) {
    if (++s_pkt_cnt % 100 == 0) {
        ESP_LOGI("a2dp sink data callback", "Audio packet count %u", s_pkt_cnt);
    }
}*/