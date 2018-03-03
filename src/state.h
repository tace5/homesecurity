//
// Created by Linus Bein Fahlander on 2018-03-03.
//

#ifndef HOMESECURITY_STATE_H
#define HOMESECURITY_STATE_H

#define DEFAULT_STATE   0x0
#define CONFIG_MODE     0x1
#define ALARM_ARMED     0x2
#define ALARM_TRIGGERED 0x3
#define FINGER_OFF_INT  0x4

uint8_t CURRENT_STATE = 0x0;

#endif //HOMESECURITY_STATE_H
