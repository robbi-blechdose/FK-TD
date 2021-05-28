#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} Point;

void copyPoint(Point* dst, Point* src);

#endif