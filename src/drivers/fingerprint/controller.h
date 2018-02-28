//
// Created by Linus on 2018-02-26.
//

#ifndef HOMESECURITY_CONTROLLER_H
#define HOMESECURITY_CONTROLLER_H

#define HEADER 0xEF01  // Header value for data package
#define ADDR 0xFFFFFFFF  // Default adder value for data package

//  Package identifier codes
#define PACKAGE_COMMAND 0x1
#define PACKAGE_DATA 0x2
#define PACKAGE_ACKNOWLEDGEMENT 0x7
#define PACKAGE_END 0x8

/* Declare serial buffer for storing output from sensor */
extern char serial_buffer[10][9];

void handle_sensor_output();
int check_for_errors();
int get_total_package_length(int data_length);
void transmit_package(uint8_t * package, int package_len);
void pack(int pid, int data_length, int * data, int adder, uint8_t * storage);
int unpack(int package);

#include "controller_functions.c"

#endif //HOMESECURITY_CONTROLLER_H
