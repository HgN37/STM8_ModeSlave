#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "stm8s.h"

void randomInit(void);
void randomDeInit(void);
uint16_t randomGenerate(void);

#endif