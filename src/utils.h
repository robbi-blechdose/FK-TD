#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} Point;

typedef struct {
    float x;
    float y;
} Pointf;

typedef struct {
    uint16_t wave;
    uint8_t waveActive;
    uint16_t money;
    uint8_t lives;
} Game;

void copyPoint(Point* dst, Point* src);
bool hitPE(Point* enemy, Point* projectile, uint8_t radius);
uint8_t distanceTE(Point* enemy, Point* tower);
uint8_t lerp(uint8_t a, uint8_t b, float f);
SDL_Surface* loadPNG(const char* path);

#endif