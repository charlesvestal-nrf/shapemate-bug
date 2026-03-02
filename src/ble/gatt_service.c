/*
 * ShapeMate BLE GATT Service
 *
 * Handles BLE GATT characteristic notifications for the ShapeMate
 * fitness tracker companion app protocol.
 */

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/logging/log.h>
#include <memfault/components.h>

LOG_MODULE_REGISTER(gatt_service, LOG_LEVEL_INF);

#define GATT_NOTIFY_MTU 20

static ble_connected_cb_t connected_cb;
static ble_disconnected_cb_t disconnected_cb;
static uint8_t pending_notify_data[256];
static size_t pending_notify_len;

static void gatt_send_next_pkt(uint16_t conn_handle, const uint8_t *data, size_t len)
{
	MEMFAULT_ASSERT(conn_handle != 0);

	size_t offset = 0;

	while (offset < len) {
		size_t chunk = MIN(len - offset, GATT_NOTIFY_MTU);
		/* bt_gatt_notify(conn, attr, data + offset, chunk); */
		offset += chunk;
	}
}

void send_char_notify(uint16_t conn_handle)
{
	if (pending_notify_len == 0) {
		return;
	}

	gatt_send_next_pkt(conn_handle, pending_notify_data, pending_notify_len);
	pending_notify_len = 0;
}

void gatt_service_init(ble_connected_cb_t on_connect, ble_disconnected_cb_t on_disconnect)
{
	connected_cb = on_connect;
	disconnected_cb = on_disconnect;
	pending_notify_len = 0;

	LOG_INF("GATT service initialized");
}
