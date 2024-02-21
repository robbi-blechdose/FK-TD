#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

typedef struct {
    uint16_t wave;
    uint8_t waveActive;
    uint16_t money;
    uint8_t lives;
} Game;

SDL_Surface* loadPNG(const char* path);

#endif