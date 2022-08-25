#include "utils.h"
#include <SDL_image.h>

void copyPoint(Point* dst, Point* src)
{
    dst->x = src->x;
    dst->y = src->y;
}

bool hitPE(Point* enemy, Point* projectile, uint8_t radius)
{
    return sqrt(pow(enemy->x + 8 - projectile->x, 2) + pow(enemy->y + 8 - projectile->y, 2)) < radius;
}

uint8_t distanceTE(Point* enemy, Point* tower)
{
    Point temp;
    temp.x = enemy->x / 16;
    temp.y = enemy->y / 16;
    return sqrt(pow(temp.x - tower->x, 2) + pow(temp.y - tower->y, 2));
}

uint8_t lerp(uint8_t a, uint8_t b, float f)
{
    return a + f * (b - a);
}

SDL_Surface* loadPNG(const char* path)
{
    SDL_Surface* loaded = IMG_Load(path);
    if(loaded != NULL)
    {
        SDL_Surface* converted = SDL_DisplayFormatAlpha(loaded);
        SDL_FreeSurface(loaded);
        if(converted != NULL)
        {
            return converted;
        }
    }
    printf("PNG loading failed for \"%s\".\n", path);
    return NULL;
}