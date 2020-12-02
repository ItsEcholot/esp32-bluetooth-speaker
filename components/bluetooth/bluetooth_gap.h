#ifndef BLUETOOTH_GAP_H
#define BLUETOOTH_GAP_H

#include <esp_log.h>
#include <esp_gap_bt_api.h>

#define BLUETOOTH_GAP_TAG "BT GAP"

esp_err_t bt_gap_setup(void);

#endif