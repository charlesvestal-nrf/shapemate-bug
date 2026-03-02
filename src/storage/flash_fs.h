#ifndef SHAPEMATE_FLASH_FS_H
#define SHAPEMATE_FLASH_FS_H

#include <stdint.h>
#include <stddef.h>

void flash_fs_init(void);
int flash_fs_write(const uint8_t *data, size_t len);
int flash_fs_read(uint8_t *buf, size_t len);

#endif
