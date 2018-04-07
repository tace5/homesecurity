//
// Created by Linus Bein Fahlander on 2018-03-05.
//

#ifndef HOMESECURITY_FINGERPRINT_SENSOR_H_H
#define HOMESECURITY_FINGERPRINT_SENSOR_H_H

#define HEADER 0xEF01  // Header value for data package
#define ADDR 0xFFFFFFFF  // Default adder value for data package

#define FINGER_TOUCH_INT 0x800

/* Declare serial buffer for storing output from sensor */
extern char serial_buffer[10][9];

// CORE FUNCTIONS

int check_for_errors();

char check_for_stored_print();

int get_total_package_length(int data_length);

void enable_fingerprint_interrupt(void);

void disable_fingerprint_interrupt(void);

void handle_finger_interrupt();


// CONTROLLER FUNCTIONS

uint8_t enroll_print_1st();

uint8_t enroll_print_2nd();

uint8_t enroll_finger();

uint8_t auth_chain(uint8_t * match_score);

uint8_t authenticate();

uint8_t arm_alarm();

uint8_t disarm();

#include "fingerprint_core.c"
#include "fingerprint_sensor.c"

#endif //HOMESECURITY_FINGERPRINT_SENSOR_H_H
