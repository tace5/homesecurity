//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "controller.h"
#include "../display/display_functions.h"
#include "../../utils/utils.h"


int check_for_errors(){
    if(U2STA & 0x8){
        display_string(1, "ERROR! Parity");
        display_update();
        _delay(1000);

        return 1;
    }

    if(U2STA & 0x4){
        display_string(1, "ERROR! Framing");
        display_update();
        _delay(1000);

        return 1;
    }

    if(U2STA & 0x2){
        display_string(1, "ERROR! Overflow");
        display_update();
        _delay(1000);

        return 1;
    }

    return 0;
}

int get_total_package_length(int data_length){
    return (2 + 4 + 1 + 2 + data_length + 2);
}

void handle_interrupt(){
    IFSCLR(0) = FINGER_TOUCH_INT;

    // TODO - Check for user settings and act accordingly

    // Is alarm active

    // Is the user trying to add a new print

    // Is the user activating the alarm


}

uint8_t listen_for_acknowledgement(uint8_t * data_storage){

    int i = 0;
    uint8_t padding_data[9];  // Storage for the first 9 bytes before package data is transmitted
    while (i < 9){
        while (!(U2STA & 0xF));  // Wait for Buffer Data available or Errors
        if(!check_for_errors()){
            padding_data[i] = U2RXREG;
            i++;
        }
        else{
            break;  // TODO - Handle failure
        }
    }

    //Calculate how big the storage for the received confirmation code + data + checksum has to be.
    int data_length = (padding_data[7] << 8) | padding_data[8];
    uint8_t package_data[data_length];
    i = 0;
    while(i < data_length){
        while (!(U2STA & 0xF));  // Wait for Buffer Data available or Errors
        if(!check_for_errors()){
            package_data[i] = U2RXREG;
            i++;
        }
        else{
            break;  // TODO - Handle failure
        }
    }

    // Read additional data if any, skip checksum at the end of the package
    if(data_length > 0x3){
        int j = 1;
        for (j; j < data_length - 2; ++j) {
            data_storage[j - 1] = package_data[j];
        }
    }

    // Return the confirmation code
    return *package_data;

}

void transmit_package(uint8_t * package, int package_len){
    int i = 0;
    while (i < package_len){
        while(U2STA & (1 << 9));  // Wait until last transmit has finished (TRMT) and transmit buffer is empty (UTXBF)
        U2TXREG = package[i];  // Set transmit buffer to current package byte
        i++;

        //DEBUG
        /*
        volatile unsigned snapshot = (*(volatile unsigned*)(0xA0003000 + (0xF44)));
        snapshot = package[i];
        char debug[16] = "T P nr ";
        itoa(i, (debug + 7));
        display_string(0, debug);
        //char value[8];
        //num32asc(value, (int) package[i]);
        //display_string(1, value);
        display_update();
        display_debug(1, &snapshot);
        _delay(500);*/
    }
}

void pack(uint8_t pid, int data_length, uint8_t * data, int adder, uint8_t * storage) {
    int len = data_length + 2; // Add 2 bytes to len count for checksum
    int package_len = (2 + 4 + 1 + 2 + len);  // Calculate the total package length (HEADER + ADDER + PID + LENGTH + DATA(len + SUM)) bytes

    //Set HEADER
    storage[0] = (HEADER & 0xFF00) >> 8;
    storage[1] = HEADER & 0xFF;

    //Set ADDR
    if(adder == 0){
        adder = ADDR;
    }
    storage[2] = (adder & 0xFF000000) >> (8 * 3);
    storage[3] = (adder & 0xFF0000) >> (8 * 2);
    storage[4] = (adder & 0xFF00) >> 8;
    storage[5] = (adder & 0xFF);

    //Set Package ID
    storage[6] = pid;

    //Set Package Length
    storage[7] = (len & 0xFF00) >> (1 * 8);
    storage[8] = len & 0xFF;

    //Set Package Data
    int i;
    for (i = 0; i < data_length; ++i) {
        storage[9 + i] = data[i];
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
