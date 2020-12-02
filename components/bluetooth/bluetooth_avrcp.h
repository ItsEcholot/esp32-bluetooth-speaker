#ifndef BLUETOOTH_AVRCP_H
#define BLUETOOTH_AVRCP_H

#include <esp_log.h>
#include <esp_avrc_api.h>

#define BLUETOOTH_AVRCP_TAG "BT AVRCP"

esp_err_t bt_avrcp_setup(void);
esp_err_t bt_avrcp_request_metadata(void);

#endif