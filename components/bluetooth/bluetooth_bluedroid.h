#ifndef BLUETOOTH_BLUEDROID_H
#define BLUETOOTH_BLUEDROID_H

#include <esp_log.h>
#include <esp_bt_main.h>
#include <esp_bt_device.h>

#define BLUETOOTH_BLUEDROID_TAG "BT BLUEDROID"

esp_err_t bt_bluedroid_setup(const char* device_name);

#endif