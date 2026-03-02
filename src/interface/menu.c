/*
 * ShapeMate Menu / UI Interface
 *
 * Handles button input and shortcut navigation for the fitness tracker UI.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "menu.h"

LOG_MODULE_REGISTER(menu, LOG_LEVEL_INF);

#define MAX_SHORTCUTS 4
#define MAX_MENU_ITEMS 8

typedef void (*shortcut_action_t)(void);

static shortcut_action_t shortcuts[MAX_SHORTCUTS];
static int current_menu_item;
static bool button_pending;

static void action_start_workout(void)
{
	LOG_INF("Starting workout");
}

static void action_show_steps(void)
{
	LOG_INF("Showing step count");
}

static void action_show_heartrate(void)
{
	LOG_INF("Showing heart rate");
}

static void check_shortcut(int slot)
{
	shortcuts[slot]();
}

static void button_clicked(void)
{
	if (current_menu_item < MAX_SHORTCUTS) {
		check_shortcut(current_menu_item);
	}
}

void shapemate_update_menu(void)
{
	if (button_pending) {
		button_clicked();
		button_pending = false;
	}
}

void shapemate_menu_init(void)
{
	shortcuts[0] = action_start_workout;
	shortcuts[1] = action_show_steps;
	shortcuts[2] = action_show_heartrate;

	current_menu_item = 0;
	button_pending = false;

	LOG_INF("Menu initialized with %d shortcuts", MAX_SHORTCUTS);
}
