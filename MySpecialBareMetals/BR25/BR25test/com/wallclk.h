#ifndef _WALLCLK_H
#define _WALLCLK_H

#include <stdint.h>

#define USLEEP_1SEC	1000000

void wallclk_init();

uint64_t micros();
void usleep(uint32_t us);

uint32_t millis();
void delay(uint32_t ms);

#endif
