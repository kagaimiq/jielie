#ifndef _WALLCLK_H
#define _WALLCLK_H

#include <stdint.h>

#define USLEEP_1SEC	1000000

void wallclk_init();

uint64_t micros();
void usleep(uint64_t us);

uint64_t millis();
void delay(uint64_t ms);

#endif
