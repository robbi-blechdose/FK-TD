#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

typedef struct {
    uint16_t wave;
    bool waveActive;
    uint16_t money;
    uint8_t lives;
} Game;

/**
 * Macro for centering text
 * X is the length of the text
 * Note: X * 8 / 2 = X * 4
 **/
#define CENTER(X) (240 / 2 - (X) * 4)

void initPNG();
void initFont();

SDL_Surface* loadPNG(const char* path);

#endif