#ifndef AUTOBACKLIGHT_DEFAULTS_H
#define AUTOBACKLIGHT_DEFAULTS_H

#include "config.h"

/* run as daemon */
int daemonize = 0;

/* run only once */
int oneshot = 0;

/* wait between scans in ms */
int sleep_length = INTERVAL * 1000;

/* is the backlight smooth */
int smooth = SMOOTH;

/* how many steps to smooth */
int max_steps = 5;

/* pretend = 1: do not write changes */
int pretend = 0;

/* enable automatic backlight */
int autobacklight = AUTOMATIC_BACKLIGHT_ENABLED;
char *screen_backlight = "/sys/class/backlight/mba6x_backlight/brightness";
char *max_screen_backlight = "/sys/class/backlight/mba6x_backlight/max_brightness";
/* enable automatic keyboard light */
int autokeyboard = AUTOMATIC_KEYBOARD_LIGHT_ENABLED;
char *keyboard_backlight = "/sys/class/leds/smc::kbd_backlight/brightness";
char *max_keyboard_backlight = "/sys/class/leds/smc::kbd_backlight/max_brightness";
char *light_sensor = "/sys/devices/platform/applesmc.768/light";

int dark_light_value = DARK_LIGHT_SENSOR_VALUE;
int dark_backlight_value = DARK_BACKLIGHT_VALUE;
int dark_keyboard_value = DARK_KEYBOARD_LIGHT_VALUE;
int bright_light_value = BRIGHT_LIGHT_SENSOR_VALUE;
int bright_backlight_value = BRIGHT_BACKLIGHT_VALUE;
int bright_keyboard_value = BRIGHT_KEYBOARD_LIGHT_VALUE;

#endif
