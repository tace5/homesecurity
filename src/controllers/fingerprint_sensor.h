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

void handle_interrupt();


// CONTROLLER FUNCTIONS

void enroll_print_1st();

void enroll_print_2nd();

uint8_t auth_chain(uint8_t * match_score);

void authenticate();

void arm_alarm();

void disarm();

#include "fingerprint_core.c"
#include "fingerprint_sensor.c"

#endif //HOMESECURITY_FINGERPRINT_SENSOR_H_H
