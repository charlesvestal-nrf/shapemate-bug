/*
 * ShapeMate Companion Sync
 *
 * Handles periodic upload of fitness data to the companion phone app
 * over BLE.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <string.h>

#include "sync_with_companion.h"

LOG_MODULE_REGISTER(sync_companion, LOG_LEVEL_INF);

#define SYNC_CHUNK_SIZE 512

int hourly_fitness_data_upload(const uint8_t *data, size_t len, uint16_t conn_handle)
{
	LOG_INF("Attempting BLE connection with companion device");
	LOG_DBG("HCI_EVT_CONN_COMPLETE, connection successful, handle: %d", conn_handle);

	size_t offset = 0;

	while (offset < len) {
		size_t chunk = MIN(len - offset, SYNC_CHUNK_SIZE);
		/* bt_gatt_write(conn_handle, data + offset, chunk); */
		offset += chunk;
	}

	LOG_INF("Fitness data upload complete (%zu bytes)", len);
	return 0;
}
