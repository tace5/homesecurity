//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "controller.h"
#include "../display/display_functions.h"

void handle_sensor_output(int *read_port) {
    // Template - Display sensor output on screen
    IFSCLR(1) = 0x200;
    display_debug(0, &U2RXREG);
}

int get_total_package_length(int data_length){
    return (2 + 4 + 1 + 2 + data_length + 2);
}

void pack(int pid, int data_length, int * data, int adder, uint8_t * storage) {
    len = data_length + 2; // Add 2 bytes to len count for checksum
    int package_len = (2 + 4 + 1 + 2 + len);  // Calculate the total package length (HEADER + ADDER + PID + LENGTH + DATA(len + SUM)) bytes

    //Set HEADER
    storage[0] = (0xEF01 & 0xFF00) >> 8;
    storage[1] = 0xEF01 & 0xFF;

    //Set ADDR
    if(adder == 0){
        adder = 0xFFFFFFFF;
    }
    storage[2] = (adder & 0xFF000000) >> (8 * 3);
    storage[3] = (adder & 0xFF0000) >> (8 * 2);
    storage[4] = (adder & 0xFF00) >> 8;
    storage[5] = (adder & 0xFF);

    //Set Package ID
    storage[6] = pid & 0xFF;

    //Set Package Length
    storage[7] = (len & 0xFF00) >> (1 * 8);
    storage[8] = len & 0xFF;

    //Set Package Data
    int i;
    char * data_byte = (char *) data;
    for (i = 0; i < len - 2; ++i) {
        printf("Adding data byte nr %d\n", i);
        storage[9 + i] = (*(data_byte + ((len - 3) - i)) & 0xFF);
    }

    //Set Package Checksum
    int checksum = (pid + len + *data) & 0xFFFF;
    storage[9 + i] = (checksum & 0xFF00) >> 8;
    storage[10 + i] = checksum & 0xFF;

}

int unpack(int package) {
    //TODO - Logic for unpacking the package contents depending on package type
    return 0;
}

