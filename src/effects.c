#include "effects.h"

#include "utils.h"

const uint8_t effectTimers[] = {
    0, 5, 5, 10
};

Effect effects[255];

SDL_Surface* explosion;

void initEffects()
{
    explosion = loadPNG("res/effects/explosion.png");
}

void quitEffects()
{
    //TODO
}

void addEffect(EffectType type, uint8_t x, uint8_t y, vec2i* enemy, uint8_t radius)
{
    for(uint8_t i = 0; i < 255; i++)
    {
        if(effects[i].type == EFT_NONE)
        {
            effects[i].type = type;
            effects[i].timer = effectTimers[type];
            effects[i].radius = radius * 16;
            effects[i].a.x = x;
            effects[i].a.y = y;
            effects[i].b.x = enemy->x;
            effects[i].b.y = enemy->y;
            effects[i].middle.x = effects[i].a.x + (effects[i].b.x - effects[i].a.x) / 2;
            effects[i].middle.y = effects[i].a.y + (effects[i].b.y - effects[i].a.y) / 2;
            break;
        }
    }
}

void drawEffects(SDL_Surface* screen)
{
    for(uint8_t i = 0; i < 255; i++)
    {
        switch(effects[i].type)
        {
            case EFT_ZAP:
            {
                uint8_t mx = effects[i].middle.x + (rand() % 16 - 8);
                uint8_t my = effects[i].middle.y + (rand() % 16 - 8);
                thickLineRGBA(screen, effects[i].a.x, effects[i].a.y, mx, my, 2, 0, 170, 255, 255);
                thickLineRGBA(screen, mx, my, effects[i].b.x, effects[i].b.y, 2, 0, 170, 255, 255);
                break;
            }
            case EFT_ICE:
            {
                circleRGBA(screen, effects[i].a.x, effects[i].a.y, effects[i].radius + (rand() % 8 - 4),
                            0, 255, 255, 255);
                circleRGBA(screen, effects[i].a.x, effects[i].a.y, effects[i].radius - 4 + (rand() % 8 - 4),
                            0, 200, 255, 255);
                break;
            }
            case EFT_EXPLOSION:
            {
                SDL_Rect rect = {.x = 32 * (effects[i].timer % 8), .y = 0, .w = 32, .h = 32};
                SDL_Rect pos = {.x = effects[i].a.x - 16, .y = effects[i].a.y - 16};
                SDL_BlitSurface(explosion, &rect, screen, &pos);
                break;
            }
            default:
            {
                break;
            }
        }

        if(effects[i].type != EFT_NONE)
        {
            effects[i].timer--;
            if(!effects[i].timer)
            {
                effects[i].type = EFT_NONE;
            }
        }
    }
}