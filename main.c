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

void handle_arguments(int argc, char **argv) {}

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
    fp = fopen(name, "w");
    check_error(fp == NULL, "Failed to write value");
    check_error(fprintf(fp, "%d", new) < 1,
                "Failed to write value");
    fclose(fp);
}

int get_backlight() {
    int value;
    int max;
    value = read_value(screen_backlight);
    max = read_value(max_screen_backlight);
    return (value * 100) / max;
}

int get_keyboard_light() {
    int value;
    int max;
    value = read_value(keyboard_backlight);
    max = read_value(max_keyboard_backlight);
    return (value * 100) / max;
}

void set_backlight(int new) {
    int max;
#ifdef DEBUG
    printf("Settings new screen light value to %d.\n", new);
#endif
    max = read_value(max_screen_backlight);
    write_value(screen_backlight, (max * new) / 100);
}

void set_keyboard_light(int new) {
    int max;
#ifdef DEBUG
    printf("Settings new keyboard light value to %d.\n", new);
#endif
    max = read_value(max_keyboard_backlight);
    write_value(keyboard_backlight, (max * new) / 100);
}

int main(int argc, char **argv) {
    pid_t child_pid;
    struct timespec sleep_time;
    sleep_time.tv_sec = sleep_length / 1000;
    sleep_time.tv_nsec = sleep_length % 1000;
    if(daemonize) {
        child_pid = fork();
        check_error(child_pid < 0, "Failed to fork child.");
        /* is this the parent */
        if(child_pid > 0)
            return 0;
    }
    do {
        int current_light, new_light;
        current_light = read_light_value(light_sensor);
#ifdef DEBUG
        printf("Current light: %d\n", current_light);
#endif
        if(autobacklight) {
            new_light = current_light;
            if(new_light < min_backlight_percentage)
                new_light = min_backlight_percentage;
            if(new_light > max_backlight_percentage)
                new_light = max_backlight_percentage;
            if(oneshot || abs(new_light - get_backlight()) > 5)
                set_backlight(new_light);
#ifdef DEBUG
            else
                printf("Not setting new value; old too close. (%d, %d)\n",
                            get_backlight(), new_light);
#endif
        }
        if(autokeyboard) {
            if(current_light == 0)
                new_light = max_keyboard_percentage;
            else
                new_light = 1 / (current_light / 30.0);
            if(new_light < min_keyboard_percentage)
                new_light = min_keyboard_percentage;
            if(new_light > max_keyboard_percentage)
                new_light = max_keyboard_percentage;
            if(oneshot || abs(new_light - get_keyboard_light()) > 1)
                set_keyboard_light(new_light);
#ifdef DEBUG
            else
                printf("Not setting new value; old too close. (%d, %d)\n",
                            get_keyboard_light(), new_light);
#endif
        }
    } while(!oneshot && !nanosleep(&sleep_time, NULL));
#ifdef DEBUG
    printf("Exiting.\n");
#endif
}
