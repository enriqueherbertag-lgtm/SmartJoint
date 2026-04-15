#ifndef AS5715R_H
#define AS5715R_H

#include <stdint.h>

void as5715r_init(void);
float as5715r_get_angle(void);
float as5715r_get_velocity(void);  // Pendiente

#endif
