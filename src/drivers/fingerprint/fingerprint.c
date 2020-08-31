//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../../controllers/fingerprint_sensor.h"
#include "setup.h"
#include "fingerprint.h"

void fingerprint_main(){
    init();
    setup();
}

uint8_t listen_for_acknowledgement(uint8_t * data_storage){

    int i = 0;
    uint8_t padding_data[9];  // Storage for the first 9 bytes before package data is transmitted
    while (i < 9){
        while (!(U1STA & 0xF));  // Wait for Buffer Data available or Errors
        if(!check_for_errors()){
            padding_data[i] = U1RXREG;
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
        while (!(U1STA & 0xF));  // Wait for Buffer Data available or Errors
        if(!check_for_errors()){
            package_data[i] = U1RXREG;
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
        while(U1STA & (1 << 9));  // Wait until last transmit has finished (TRMT) ( || !(U1STA & (1 << 8))) and transmit buffer is empty (UTXBF)
        U1TXREG = package[i];  // Set transmit buffer to current package byte
        i++;
    }
}

void pack(uint8_t pid, int data_length, uint8_t * data, int adder, uint8_t * storage) {
    int len = data_length + 2; // Add 2 bytes to len count for checksum
    int package_len = (2 + 4 + 1 + 2 +
                       len);  // Calculate the total package length (HEADER + ADDER + PID + LENGTH + DATA(len + SUM)) bytes

    //Set HEADER
    storage[0] = (HEADER & 0xFF00) >> 8;
    storage[1] = HEADER & 0xFF;

    //Set ADDR
    if (adder == 0) {
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
    int datasum = 0;
    for (i = 0; i < data_length; ++i) {
        datasum += data[i];
    }
    int checksum = (pid + len + datasum) & 0xFFFF;
    storage[9 + i] = (checksum & 0xFF00) >> 8;
    storage[10 + i] = checksum & 0xFF;

}
