#include "wavegenerator.h"

uint16_t timer;

void updateWaveGenerator(Enemy enemies[])
{
    timer++;

    if(timer == 50)
    {
        timer = 0;
        addEnemy(enemies, 16, 16, 1, &enemyTypes[0]);
    }
}