#ifndef SHAPEMATE_SYNC_WITH_COMPANION_H
#define SHAPEMATE_SYNC_WITH_COMPANION_H

#include <stdint.h>
#include <stddef.h>

int hourly_fitness_data_upload(const uint8_t *data, size_t len, uint16_t conn_handle);

#endif
