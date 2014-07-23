#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "defaults.h"

#define check_error(condition, error_message) \
    do { \
        if((condition)) { \
            fprintf(stderr, error_message ": %s\n", strerror(errno)); \
            exit(1); \
        } \
    } while(0)

#define abs(i) ((i) < 0 ? (-(i)) : (i))

void handle_arguments(int argc, char **argv) {
    if(!smooth)
        max_steps = 1;
    sleep_length /= max_steps;
}

int read_value(char *name) {
    FILE *fp;
    int value;
    fp = fopen(name, "r");
    check_error(fp == NULL, "Failed to read value");
    check_error(fscanf(fp, "%d", &value) != 1,
                "Failed to read value");
    fclose(fp);
    return value;
}

int read_light_value(char *name) {
    FILE *fp;
    int value;
    fp = fopen(name, "r");
    check_error(fp == NULL, "Failed to read value");
    check_error(fscanf(fp, "(%d", &value) != 1,
                "Failed to read value");
    fclose(fp);
    return value;
}

void write_value(char *name, int new) {
    FILE *fp;
    if(!pretend) {
        fp = fopen(name, "w");
        check_error(fp == NULL, "Failed to write value");
        check_error(fprintf(fp, "%d", new) < 1,
                    "Failed to write value");
        fclose(fp);
    }
}

int build_value(float min_x, float max_x, float min_y,
                  float max_y, float current) {
    if(current <= min_x)
        return min_y;
    if(current >= max_x)
        return max_y;
    return min_y + (max_y - min_y) / (max_x - min_x) * (current  - min_x);
}

void main_loop() {
    struct timespec sleep_time;
    int current_light;
    float current_backlight, new_backlight;
    float current_keyboard_light, new_keyboard_light;
    float backlight_step, keyboard_step;
    int i;
    current_backlight = new_backlight = 0;
    current_keyboard_light = new_keyboard_light = 0;
    backlight_step = keyboard_step = 0;
    current_light = read_light_value(light_sensor);
#ifdef DEBUG
    printf("Current light: %d\n", current_light);
#endif
    if(autobacklight) {
        current_backlight = read_value(screen_backlight);
        new_backlight = build_value(dark_light_value,
                                    bright_light_value,
                                    dark_backlight_value,
                                    bright_backlight_value,
                                    current_light);
#ifdef DEBUG
        printf("Target backlight: %f\n", new_backlight);
#endif
        backlight_step = (new_backlight - current_backlight) / max_steps;
    }
    if(autokeyboard) {
        current_keyboard_light = read_value(keyboard_backlight);
        new_keyboard_light = build_value(dark_light_value,
                                         bright_light_value,
                                         dark_keyboard_value,
                                         bright_keyboard_value,
                                         current_light);
        keyboard_step = (new_keyboard_light - current_keyboard_light) / max_steps;
#ifdef DEBUG
        printf("Target keyboard light: %f\n", new_keyboard_light);
#endif
    }
    for(i = 0; i < max_steps; i++) {
        if(autobacklight) {
            current_backlight += backlight_step;
#ifdef DEBUG
            printf("Setting current light to %f.\n", current_backlight);
#endif
            write_value(screen_backlight, (int)current_backlight);
        }
        if(autokeyboard) {
            current_keyboard_light += keyboard_step;
#ifdef DEBUG
            printf("Setting current keyboard light to %f.\n", current_keyboard_light);
#endif
            write_value(keyboard_backlight, (int)current_keyboard_light);
        }
        sleep_time.tv_sec = sleep_length / 1000;
        sleep_time.tv_nsec = sleep_length % 1000 * 1000000;
        if(nanosleep(&sleep_time, NULL)) {
            oneshot = 1;
            return;
        }
    }
}

int main(int argc, char **argv) {
    pid_t child_pid;
    handle_arguments(argc, argv);
    if(daemonize) {
        child_pid = fork();
        check_error(child_pid < 0, "Failed to fork child.");
        /* is this the parent */
        if(child_pid > 0)
            return 0;
    }
    do
        main_loop();
    while(!oneshot);
#ifdef DEBUG
    printf("Exiting.\n");
#endif
}
