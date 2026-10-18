#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <termios.h>

#include "device_common.h"
#include <libevdev/libevdev.h>

#define CROW_BAUDRATE B115200

#define CROW_CLOCK_TICK "^^change(1,1)"
#define CROW_CLOCK_TICK_LEN (sizeof(CROW_CLOCK_TICK) - 1)

struct dev_crow {
    struct dev_common base;
    int fd;
    struct termios oldtio, newtio;
    char line[256];
    // tail of the previous read, so a clock tick split across reads is still found
    char clock_carry[CROW_CLOCK_TICK_LEN - 1];
    size_t clock_carry_len;
};

extern int dev_crow_init(void *self);
extern void *dev_crow_start(void *self);
extern void dev_crow_deinit(void *self);

extern void dev_crow_send(struct dev_crow *d, const char *line);
