/*
 * ShapeMate Fitness Data Manager
 *
 * Collects sensor data (heart rate, accelerometer, gyroscope) and stores
 * it to flash in 5-minute intervals.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <string.h>

#include "fitness_data_manager.h"
#include "../storage/flash_fs.h"

LOG_MODULE_REGISTER(fitness, LOG_LEVEL_INF);

static uint32_t total_steps;

void fitness_data_manager_init(void)
{
	total_steps = 0;
	LOG_INF("Sensor array initialized (heart rate, accelerometer, gyroscope)");
}

void fitness_read_sensors(struct fitness_sample *sample)
{
	memset(sample, 0, sizeof(*sample));
	sample->timestamp = (uint32_t)(k_uptime_get() / 1000);
	/* In real firmware, these would read from I2C/SPI sensor peripherals */
	sample->heart_rate = 72;
	sample->steps = total_steps;

	LOG_INF("Collecting fitness data, 5-minute interval");
}

int write_fitness_data_to_flash(const struct fitness_sample *sample)
{
	LOG_DBG("Storing fitness metrics to flash memory, 5-minute block");

	int rc = flash_fs_write((const uint8_t *)sample, sizeof(*sample));
	if (rc == 0) {
		LOG_INF("Fitness data successfully written to flash");
	}

	return rc;
}
