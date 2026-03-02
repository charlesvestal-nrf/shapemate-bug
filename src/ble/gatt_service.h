#ifndef SHAPEMATE_GATT_SERVICE_H
#define SHAPEMATE_GATT_SERVICE_H

#include <stdint.h>

typedef void (*ble_connected_cb_t)(uint16_t handle);
typedef void (*ble_disconnected_cb_t)(void);

void gatt_service_init(ble_connected_cb_t on_connect, ble_disconnected_cb_t on_disconnect);
void send_char_notify(uint16_t conn_handle);

#endif
