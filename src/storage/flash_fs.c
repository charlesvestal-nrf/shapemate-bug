/*
 * ShapeMate Flash Filesystem
 *
 * Simple flash storage layer for persisting fitness data between syncs.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <memfault/components.h>
#include <string.h>

#include "flash_fs.h"

LOG_MODULE_REGISTER(flash_fs, LOG_LEVEL_DBG);

#define FLASH_PARTITION_SIZE (1024 * 1024)  /* 1MB */
#define FLASH_BLOCK_SIZE     4096

static uint8_t flash_storage[FLASH_BLOCK_SIZE];
static size_t stored_len;

void flash_fs_init(void)
{
	stored_len = 0;
	memset(flash_storage, 0, sizeof(flash_storage));
	LOG_INF("Flash filesystem initialized");
}

int flash_fs_write(const uint8_t *data, size_t len)
{
	if (len > sizeof(flash_storage)) {
		len = sizeof(flash_storage);
	}

	memcpy(flash_storage, data, len);
	stored_len = len;

	LOG_DBG("Wrote %zu bytes to flash", len);
	return 0;
}

int flash_fs_read(uint8_t *buf, size_t len)
{
	MEMFAULT_ASSERT(buf != NULL);

	size_t read_len = MIN(len, stored_len);
	memcpy(buf, flash_storage, read_len);

	LOG_DBG("Read %zu bytes from flash", read_len);
	return 0;
}
