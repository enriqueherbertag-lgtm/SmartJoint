#ifndef DRV8320_H
#define DRV8320_H

#include <stdint.h>

void drv8320_init(void);
void drv8320_enable(uint8_t enable);
void drv8320_set_duty(float duty);  // -1.0 a 1.0
float drv8320_get_current(void);    // Pendiente

#endif
