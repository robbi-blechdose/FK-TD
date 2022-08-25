#ifndef _WAVEGENERATOR_H
#define _WAVEGENERATOR_H

#include <stdbool.h>

#include "entities.h"
#include "utils.h"

void initWaveGenerator(uint8_t wave, Point sp);
bool updateWaveGenerator(Enemy enemies[], uint8_t wave);

#endif