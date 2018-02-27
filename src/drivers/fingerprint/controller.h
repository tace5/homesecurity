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

void handle_sensor_output(int * read_port);
int pack(int oid, int len, int data, int adder);
int unpack(int package);

#include "controller_functions.c"

#endif //HOMESECURITY_CONTROLLER_H
