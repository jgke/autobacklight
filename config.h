#ifndef AUTOBACKLIGHT_CONFIG_H
#define AUTOBACKLIGHT_CONFIG_H

/* 0 = false, 1 = true */
#define AUTOMATIC_BACKLIGHT_ENABLED 1
#define AUTOMATIC_KEYBOARD_LIGHT_ENABLED 1

/* lower light value than DARK_LIGHT_SENSOR_VALUE:
 *   backlight = DARK_BACKLIGHT_VALUE,
 *   keyboard = DARK_KEYBOARD_LIGHT_VALUE
 */
#define DARK_LIGHT_SENSOR_VALUE 0
#define DARK_BACKLIGHT_VALUE 140
#define DARK_KEYBOARD_LIGHT_VALUE 20

/* higher light value than BRIGHT_LIGHT_SENSOR_VALUE:
 *   backlight = BRIGHT_BACKLIGHT_VALUE,
 *   keyboard = BRIGHT_KEYBOARD_LIGHT_VALUE
 */
#define BRIGHT_LIGHT_SENSOR_VALUE 200
#define BRIGHT_BACKLIGHT_VALUE 255
#define BRIGHT_KEYBOARD_LIGHT_VALUE 0

/* smooth changes, 0 = false, 1 = true */
#define SMOOTH 1

/* interval between scanning for changes in seconds */
#define INTERVAL 5

#endif
