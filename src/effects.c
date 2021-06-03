#include "effects.h"

Effect effects[255];

SDL_Surface* fireball;

void initEffects()
{
    fireball = loadPNG("res/effects/fireball.png");
}

void addEffect(EffectType t, Point* tower, Point* enemy, uint8_t radius)
{
    uint8_t i;
    for(i = 0; i < 255; i++)
    {
        if(effects[i].type == NONE)
        {
            effects[i].type = t;
            effects[i].timer = 5;
            effects[i].radius = radius * 16;
            effects[i].a.x = tower->x * 16 + 8;
            effects[i].a.y = tower->y * 16 + 8;
            effects[i].b.x = enemy->x + 8;
            effects[i].b.y = enemy->y + 8;
            effects[i].middle.x = effects[i].a.x + (effects[i].b.x - effects[i].a.x) / 2;
            effects[i].middle.y = effects[i].a.y + (effects[i].b.y - effects[i].a.y) / 2;
            break;
        }
    }
}

void drawEffects(SDL_Surface* screen)
{
    uint8_t i;
    for(i = 0; i < 255; i++)
    {
        switch(effects[i].type)
        {
            case ZAP:
            {
                uint8_t mx = effects[i].middle.x + (rand() % 16 - 8);
                uint8_t my = effects[i].middle.y + (rand() % 16 - 8);
                thickLineRGBA(screen, effects[i].a.x, effects[i].a.y, mx, my, 2, 0, 170, 255, 255);
                thickLineRGBA(screen, mx, my, effects[i].b.x, effects[i].b.y, 2, 0, 170, 255, 255);
                break;
            }
            case ICE:
            {
                circleRGBA(screen, effects[i].a.x, effects[i].a.y, effects[i].radius + (rand() % 8 - 4),
                            0, 255, 255, 255);
                circleRGBA(screen, effects[i].a.x, effects[i].a.y, effects[i].radius - 4 + (rand() % 8 - 4),
                            0, 200, 255, 255);
                break;
            }
            case FIRE:
            {
                SDL_Rect rect = {.x = 8 * (effects[i].timer % 2), .y = 0, .w = 8, .h = 8};
                float diff = effects[i].timer / 5.0f;
                SDL_Rect pos = {.x = lerp(effects[i].b.x, effects[i].a.x, diff) - 4,
                                .y = lerp(effects[i].b.y, effects[i].a.y, diff) - 4};
                SDL_BlitSurface(fireball, &rect, screen, &pos);
                break;
            }
            default:
            {
                break;
            }
        }

        if(effects[i].type)
        {
            effects[i].timer--;
            if(!effects[i].timer)
            {
                effects[i].type = NONE;
            }
        }
    }
}