#include <stdlib.h>
#include "wavegenerator.h"

uint16_t timer;
uint16_t rcount;

void initWaveGenerator(uint8_t wave)
{
    rcount = 12 * wave;
}

uint8_t updateWaveGenerator(Enemy enemies[], uint8_t wave)
{
    if(rcount == 0)
    {
        return 0;
    }

    timer++;

    if(timer == 24)
    {
        timer = 0;
        uint8_t enemyIndex = (rand() % (wave * 100)) / 100;
        addEnemy(enemies, 16, 16, 1, &enemyTypes[enemyIndex]);
        rcount--;
    }
    return 1;
}