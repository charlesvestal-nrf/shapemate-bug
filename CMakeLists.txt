cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(shapemate)

target_sources(app PRIVATE
  src/main.c
  src/app/main.c
  src/ble/gatt_service.c
  src/ble/sync_prep.c
  src/storage/flash_fs.c
  src/sync/sync_with_companion.c
  src/fitness/fitness_data_manager.c
  src/interface/menu.c
)
