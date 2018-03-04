
#ifndef US_SENSOR_H
#define US_SENSOR_H

#define TRIG  0x20
#define ECHO  0x40

void sensor_init(void);
void send_pulse(void);
int measure_dist(void);

#include "us_sensor.c"

#endif
