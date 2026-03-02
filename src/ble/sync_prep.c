/*
 * ShapeMate Sync Preparation
 *
 * Prepares buffered fitness data for upload to the companion app.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>

#include "sync_prep.h"
#include "../storage/flash_fs.h"

LOG_MODULE_REGISTER(sync_prep, LOG_LEVEL_INF);

#define SYNC_BUFFER_SIZE (512 * 1024)  /* 512KB */

void prepare_for_sync(uint8_t **buf, size_t *buf_len)
{
	LOG_INF("Ready for sync with companion app");

	*buf = malloc(SYNC_BUFFER_SIZE);
	*buf_len = SYNC_BUFFER_SIZE;

	if (*buf != NULL) {
		flash_fs_read(*buf, *buf_len);
	}

	LOG_DBG("Syncing data buffer (size: %zuKB) to companion (handle: ?, buffer: %p)",
		*buf_len / 1024, *buf);
}
