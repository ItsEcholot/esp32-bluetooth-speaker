#ifndef BLUETOOTH_CONTROLLER_H
#define BLUETOOTH_CONTROLLER_H

#include <esp_log.h>
#include <esp_bt.h>
#include <freertos/FreeRTOS.h>
#include <bluetooth_service.h>

#include "bluetooth_service_t.h"

#define BLUETOOTH_CONTROLLER_TAG "BT CONTROLLER ADF"

extern bluetooth_service_t *g_bt_service;

esp_err_t bt_controller_setup(void);

#endif