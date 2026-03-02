/*
 * ShapeMate Application Logic
 *
 * Top-level application update loop that drives the UI subsystem.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "main.h"
#include "../interface/menu.h"

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);

static uint32_t tick_count;

void shapemate_update(void)
{
	tick_count++;

	/* Update UI subsystems */
	shapemate_update_menu();

	/* Future: update display, LED status, haptic feedback, etc. */
}
