#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} vec2i;

typedef struct {
    float x;
    float y;
} vec2;

void vec2i_copy(vec2i* dst, vec2i* src);
uint8_t vec2i_distance(vec2i* va, vec2i* vb);
bool vec2i_withinRadius(vec2i* va, vec2i* vb, uint8_t radius);

uint8_t lerp(uint8_t a, uint8_t b, float f);

#endif