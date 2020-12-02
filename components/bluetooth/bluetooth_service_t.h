#ifndef BLUETOOTH_SERVICE_T_H
#define BLUETOOTH_SERVICE_T_H

#include <freertos/FreeRTOS.h>
#include <bluetooth_service.h>
#include <esp_a2dp_api.h>
#include "esp_gap_bt_api.h"

typedef enum {
    BT_SOURCE_STATE_IDLE,
    BT_SOURCE_STATE_DISCOVERING,
    BT_SOURCE_STATE_DISCOVERED,
    BT_SOURCE_STATE_UNCONNECTED,
    BT_SOURCE_STATE_CONNECTING,
    BT_SOURCE_STATE_CONNECTED,
    BT_SOURCE_STATE_DISCONNECTING,
} esp_a2d_source_state_t;

typedef uint8_t esp_peer_bdname_t[ESP_BT_GAP_MAX_BDNAME_LEN + 1];

typedef struct bluetooth_service {
    audio_element_handle_t stream;
    esp_periph_handle_t periph;
    audio_stream_type_t stream_type;
    esp_bd_addr_t remote_bda;
    esp_peer_bdname_t peer_bdname;
    esp_a2d_connection_state_t connection_state;
    esp_a2d_source_state_t source_a2d_state;
    esp_a2d_audio_state_t audio_state;
    uint64_t pos;
    uint8_t tl;
    bool avrc_connected;
} bluetooth_service_t;

#endif