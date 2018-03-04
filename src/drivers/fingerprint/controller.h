//
// Created by Linus on 2018-02-26.
//

#ifndef HOMESECURITY_CONTROLLER_H
#define HOMESECURITY_CONTROLLER_H

#define HEADER 0xEF01  // Header value for data package
#define ADDR 0xFFFFFFFF  // Default adder value for data package

#define FINGER_TOUCH_INT 0x800

/* Declare serial buffer for storing output from sensor */
extern char serial_buffer[10][9];

// CORE FUNCTIONS

int check_for_errors();

int get_total_package_length(int data_length);

void handle_interrupt();

uint8_t listen_for_acknowledgement(uint8_t *data_storage);

void transmit_package(uint8_t *package, int package_len);

void pack(uint8_t pid, int data_length, uint8_t *data, int adder, uint8_t *storage);

int unpack(int package);

// CONTROLLER FUNCTIONS

void enroll_print_1st();

void enroll_print_2nd();

uint8_t auth_chain(uint8_t * match_score);

void authenticate();

void arm_alarm();

void disarm();

#include "controller_core.c"
#include "controller_functions.c"

#endif //HOMESECURITY_CONTROLLER_H
