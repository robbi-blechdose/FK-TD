#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

#include <stdbool.h>

#include "engine/math.h"

#include "entities/enemies.h"

void initWaveGenerator(uint8_t wave, vec2i sp);
bool updateWaveGenerator(Enemy* enemies, uint16_t maxEnemies, uint8_t wave);

#endif