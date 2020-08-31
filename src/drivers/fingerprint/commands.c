//
// Created by Linus on 2018-03-01.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../../controllers/fingerprint_sensor.h"
#include "commands.h"
#include "../display/display_functions.h"
#include "../../utils/utils.h"

uint8_t scan_print(void) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_SCAN_PRINT;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t image_to_buffer(uint8_t buffer_id) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[2];
    data[0] = IC_IMAGE_TO_BUFFER;
    if (buffer_id == CHAR_BUFFER_1) {
        data[1] = CHAR_BUFFER_1;
    } else {
        data[1] = CHAR_BUFFER_2;
    }
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t match_buffers(uint8_t *match_score) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_MATCH_IN_BUFFER;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t response = listen_for_acknowledgement(match_score);

    return response;
}


uint8_t search_for_match(uint8_t *match_score) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_SEARCH_MATCH;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t response = listen_for_acknowledgement(match_score);

    return response;
}


uint8_t generate_print_model(void) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_REG_MODEL;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t save_print_to_flash(uint8_t buffer_id) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[4];
    data[0] = IC_STORE_PRINT;
    data[2] = PRINT_PAGE_ID >> 8;
    data[3] = PRINT_PAGE_ID & 0xFF;
    if (buffer_id == CHAR_BUFFER_1) {
        data[1] = CHAR_BUFFER_1;
    } else {
        data[1] = CHAR_BUFFER_2;
    }
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t load_print_from_flash(uint8_t buffer_id) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[4];
    data[0] = IC_LOAD_PRINT;
    data[2] = PRINT_PAGE_ID >> 8;
    data[3] = PRINT_PAGE_ID & 0xFF;
    if (buffer_id == CHAR_BUFFER_1) {
        data[1] = CHAR_BUFFER_1;
    } else {
        data[1] = CHAR_BUFFER_2;
    }
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t delete_print_in_flash(int page_id) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[5];
    data[0] = IC_DELETE_PRINT;
    data[1] = (page_id & 0xFF00) >> 8;
    data[2] = page_id & 0xFF;
    data[3] = 0x00;
    data[4] = 0x01;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t drop_prints_in_flash(void) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_DROP_PRINTS;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t set_sys_param(uint8_t param, uint8_t value) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[3];
    data[0] = IC_SET_SYS_PARAM;
    data[1] = param;
    data[2] = value;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t *get_sys_params(void) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_READ_SYS_PARAM;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    uint8_t static storage[17];

    transmit_package(packet, packet_len);
    storage[0] = listen_for_acknowledgement(storage + 1);

    return storage;
}


uint8_t set_address(int adr) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[5];
    data[0] = IC_SET_ADDRESS;
    data[1] = (adr & 0xFF000000) >> 24;
    data[2] = (adr & 0xFF0000) >> 16;
    data[3] = (adr & 0xFF00) >> 8;
    data[4] = (adr & 0xFF);
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t write_to_notepad(uint8_t page, uint8_t *content) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[34];
    data[0] = IC_WRITE_NOTEPAD;
    data[1] = page;

    int i = 0;
    for (i; i < 32; ++i) {
        data[2 + i] = content[i];
    }
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t static * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t *read_notepad_page(uint8_t page) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[2];
    data[0] = IC_READ_NOTEPAD;
    data[1] = page;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    uint8_t static response[33];

    transmit_package(packet, packet_len);
    response[0] = listen_for_acknowledgement(response + 1);

    return response;
}


uint8_t change_led(uint8_t on) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    if(on){
        data[0] = IC_LED_ON;
    } else{
        data[0] = IC_LED_OFF;
    }
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t force_handshake() {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[1];
    data[0] = IC_HANDSHAKE;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    return response;
}


uint8_t run_auto_login(void) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[6];
    data[0] = IC_AUTO_LOGIN;
    data[1] = PRINT_SCAN_TIME;
    data[2] = PRINT_REPEAT_NR;
    data[3] = 0x0;  //TODO - What is "Stored Sequence number"?
    data[4] = 0x0;  //TODO - What is "Stored Sequence number"?
    data[5] = REPEATED_PRINTS;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    transmit_package(packet, packet_len);

    uint8_t * storage;
    uint8_t response = listen_for_acknowledgement(storage);

    //TODO - Handle PS_AUTOLOGIN_OK1 and 2

    return response;
}


uint8_t run_auto_search(uint8_t * match_score) {
    uint8_t pid = PKG_COMMAND;
    uint8_t data[6];
    data[0] = IC_AUTO_SEARCH;
    data[1] = PRINT_SCAN_TIME;
    data[2] = PRINT_PAGE_ID >> 8;
    data[3] = PRINT_PAGE_ID & 0xFF;
    data[2] = PRINT_SEARCH_NUMBER >> 8;
    data[3] = PRINT_SEARCH_NUMBER & 0xFF;
    int len = sizeof(data);  // Data length in bytes, excluding length of PID and checksum
    int packet_len = get_total_package_length(len);
    uint8_t packet[packet_len];

    pack(pid, len, data, MODULE_ADDRESS, packet);

    uint8_t static storage[4];

    transmit_package(packet, packet_len);
    uint8_t response = listen_for_acknowledgement(storage);

    // Get the match score from the response and place it in match_score
    match_score[0] = storage[2];
    match_score[1] = storage[3];

    return response;
}

