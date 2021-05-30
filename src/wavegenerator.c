#include "wavegenerator.h"

uint16_t timer;
uint16_t rcount;

void initWaveGenerator(uint8_t wave)
{
    rcount = 12 * wave;
}

uint8_t updateWaveGenerator(Enemy enemies[])
{
    if(rcount == 0)
    {
        return 0;
    }

    timer++;

    if(timer == 24)
    {
        timer = 0;
        addEnemy(enemies, 16, 16, 1, &enemyTypes[0]);
        rcount--;
    }
    return 1;
}