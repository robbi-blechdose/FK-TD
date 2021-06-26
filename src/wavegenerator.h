#ifndef _WAVEGENERATOR_H
#define _WAVEGENERATOR_H

#include "entities.h"
#include "utils.h"

void initWaveGenerator(uint8_t wave, Point sp);
uint8_t updateWaveGenerator(Enemy enemies[], uint8_t wave);

#endif