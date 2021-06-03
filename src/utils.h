#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <math.h>
#include <SDL.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} Point;

void copyPoint(Point* dst, Point* src);
uint8_t distanceTE(Point* enemy, Point* tower);
uint8_t lerp(uint8_t a, uint8_t b, float f);
SDL_Surface* loadPNG(const char* path);

#endif