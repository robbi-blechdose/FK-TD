#include "math.h"

#include <math.h>

void vec2i_copy(vec2i* dst, vec2i* src)
{
    dst->x = src->x;
    dst->y = src->y;
}

uint8_t vec2i_distance(vec2i* va, vec2i* vb)
{
    return sqrtf(powf(va->x - vb->x, 2) + powf(va->y - vb->y, 2));
}

bool vec2i_withinRadius(vec2i* va, vec2i* vb, uint8_t radius)
{
    return vec2i_distance(va, vb) < radius;
}

bool vec2_withinRadius(vec2 va, vec2 vb, float radius)
{
    return sqrtf(powf(va.x - vb.x, 2) + powf(va.y - vb.y, 2)) < radius;
}

uint8_t lerp(uint8_t a, uint8_t b, float f)
{
    return a + f * (b - a);
}

float lerpf(float a, float b, float f)
{
    return a + f * (b - a);
}