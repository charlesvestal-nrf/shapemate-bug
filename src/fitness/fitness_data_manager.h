#ifndef SHAPEMATE_FITNESS_DATA_MANAGER_H
#define SHAPEMATE_FITNESS_DATA_MANAGER_H

#include <stdint.h>

struct fitness_sample {
	uint32_t timestamp;
	uint16_t heart_rate;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	uint32_t steps;
};

void fitness_data_manager_init(void);
void fitness_read_sensors(struct fitness_sample *sample);
int write_fitness_data_to_flash(const struct fitness_sample *sample);

#endif
