#ifndef AUTOBACKLIGHT_CONFIG_H
#define AUTOBACKLIGHT_CONFIG_H

//todo config

#define DEBUG

int smooth = 0;
int daemonize = 0;
int oneshot = 0;
int sleep_length = 3000;
char *run_dir = "/var/run/";
char *screen_backlight = "/sys/class/backlight/mba6x_backlight/brightness";
char *max_screen_backlight = "/sys/class/backlight/mba6x_backlight/max_brightness";
char *keyboard_backlight = "/sys/class/leds/smc::kbd_backlight/brightness";
char *max_keyboard_backlight = "/sys/class/leds/smc::kbd_backlight/max_brightness";
char *light_sensor = "/sys/devices/platform/applesmc.768/light";
int max_light_value = 100;
int min_backlight_percentage = 25;
int max_backlight_percentage = 100;
int min_keyboard_percentage = 0;
int max_keyboard_percentage = 10;

#endif
