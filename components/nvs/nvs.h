#ifndef NVS_H
#define NVS_H

#include <esp_log.h>
#include <esp_bt_defs.h>
#include <nvs_flash.h>

#define NVS_COMPONENT_TAG "NVS"
#define NVS_BT_NAMESPACE "bt"

void nvs_init(void);

#endif