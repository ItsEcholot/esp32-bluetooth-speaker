#ifndef BLUETOOTH_A2DP_H
#define BLUETOOTH_A2DP_H

#include <string.h>
#include <esp_log.h>
#include <esp_a2dp_api.h>

#include "bluetooth_service_t.h"

#define BLUETOOTH_A2DP_TAG "BT A2DP"

extern bluetooth_service_t *g_bt_service;
extern void (* bt_a2d_sink_cb_ptr)(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *p_param); // Added to esp-adf/components/../bluetooth_service.c
extern void (* bt_a2d_sink_data_cb_ptr)(const uint8_t *data, uint32_t len);                // Added to esp-adf/components/../bluetooth_service.c

esp_err_t bt_a2dp_setup(void);

#endif