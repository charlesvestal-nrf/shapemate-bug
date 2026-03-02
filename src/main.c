/*
 * ShapeMate Fitness Tracker Firmware
 * Main entry point
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <memfault/components.h>

#include "app/main.h"
#include "ble/gatt_service.h"
#include "ble/sync_prep.h"
#include "fitness/fitness_data_manager.h"
#include "interface/menu.h"
#include "storage/flash_fs.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define FITNESS_DATA_INTERVAL_MS    (5 * 60 * 1000)  /* 5 minutes */
#define SYNC_INTERVAL_MS            (60 * 60 * 1000)  /* 1 hour */
#define UI_UPDATE_INTERVAL_MS       100               /* 100ms */

static struct {
	int64_t last_fitness_collect;
	int64_t last_sync;
	int64_t last_ui_update;
	bool ble_connected;
	uint16_t conn_handle;
} state;

static void on_ble_connected(uint16_t handle)
{
	state.ble_connected = true;
	state.conn_handle = handle;
	LOG_INF("BLE connected, handle: %d", handle);
}

static void on_ble_disconnected(void)
{
	state.ble_connected = false;
	state.conn_handle = 0;
	LOG_INF("BLE disconnected");
}

static void collect_fitness_data(void)
{
	struct fitness_sample sample;

	fitness_read_sensors(&sample);
	write_fitness_data_to_flash(&sample);

	LOG_DBG("Stored fitness data to flash");
}

static void sync_to_companion(void)
{
	if (!state.ble_connected) {
		LOG_DBG("Skipping sync, no BLE connection");
		return;
	}

	uint8_t *buf;
	size_t buf_len;

	prepare_for_sync(&buf, &buf_len);
	hourly_fitness_data_upload(buf, buf_len, state.conn_handle);
}

static void update_ui(void)
{
	shapemate_update();
}

void main(void)
{
	LOG_INF("ShapeMate is alive!");

	memfault_device_info_boot();
	flash_fs_init();
	gatt_service_init(on_ble_connected, on_ble_disconnected);
	fitness_data_manager_init();
	shapemate_menu_init();

	state.last_fitness_collect = k_uptime_get();
	state.last_sync = k_uptime_get();
	state.last_ui_update = k_uptime_get();

	while (1) {
		int64_t now = k_uptime_get();

		if ((now - state.last_fitness_collect) >= FITNESS_DATA_INTERVAL_MS) {
			collect_fitness_data();
			state.last_fitness_collect = now;
		}

		send_char_notify(state.conn_handle);

		if ((now - state.last_sync) >= SYNC_INTERVAL_MS) {
			sync_to_companion();
			state.last_sync = now;
		}

		if ((now - state.last_ui_update) >= UI_UPDATE_INTERVAL_MS) {
			update_ui();
			state.last_ui_update = now;
		}

		k_msleep(10);
	}
}
