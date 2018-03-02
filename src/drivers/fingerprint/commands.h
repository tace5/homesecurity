//
// Created by Linus on 2018-03-01.
//

#ifndef HOMESECURITY_COMMANDS_H
#define HOMESECURITY_COMMANDS_H


// INSTRUCTION CODES
#define IC_SCAN_PRINT       0x01
#define IC_IMAGE_TO_BUFFER  0x02
#define IC_MATCH_IN_BUFFER  0x03
#define IC_SEARCH_MATCH     0x04
#define IC_REG_MODEL        0x05
#define IC_STORE_PRINT      0x06
#define IC_LOAD_PRINT       0x07
#define IC_DELETE_PRINT     0x0C
#define IC_DROP_PRINTS      0x0D
#define IC_SET_SYS_PARAM    0x0E
#define IC_READ_SYS_PARAM   0x0F
#define IC_SET_ADDRESS      0x15
#define IC_WRITE_NOTEPAD    0x18
#define IC_READ_NOTEPAD     0x19
#define IC_LED_ON           0x50
#define IC_LED_OFF          0x51
#define IC_HANDSHAKE        0x53
#define IC_AUTO_LOGIN       0x54
#define IC_AUTO_SEARCH      0x55

// PACKAGE IDENTIFIERS
#define PKG_COMMAND     0x01
#define PKG_DATA        0x02
#define PKG_ACKNOWLEDGE 0x07
#define PKG_DATA_END    0x08

// SETTINGS
#define PRINT_PAGE_ID       0x0001
#define CHAR_BUFFER_1       0x1
#define CHAR_BUFFER_2       0x2
#define PRINT_REPEAT_NR     0x3
#define PRINT_SCAN_TIME     0x1F
#define REPEATED_PRINTS     0x0
#define MODULE_ADDRESS      0x0
#define PRINT_SEARCH_NUMBER 0x0001

// RESPONSE CODES
#define RES_SUCCESS         0x00
#define RES_RECEIVE_FAIL    0x01
#define RES_NO_FINGER       0x02
#define RES_ENROLLMENT_FAIL 0x03
#define RES_DISTORTED_IMAGE 0x06
#define RES_WEAK_PRINT_FAIL 0x07
#define RES_MATCH_FAIL      0x08
#define RES_NO_MATCH_FOUND  0x09
#define RES_COMBINE_FAIL    0x0A
#define RES_PAGE_ID_OOB     0x0B
#define RES_TEMPLATE_ERROR  0x0C
#define RES_RECEIVE_ERROR   0x0E
#define RES_TEMP_DEL_FAIL   0x10
#define RES_DROP_FAIL       0x11
#define RES_GEN_IMAGE_FAIL  0x15
#define RES_FLASH_W_FAIL    0x18
#define RES_INVALID_PARAM   0x1A
#define RES_PRINT_EXISTS    0x24
#define PS_AUTOLOGIN_OK1    0x56
#define PS_AUTOLOGIN_OK2    0x57


// COMMAND FUNCTIONS - MOST FUNCTIONS RETURN THE CONFORMATION CODE RESPONSE FROM THE SENSOR

uint8_t scan_print(void);

uint8_t image_to_buffer(uint8_t buffer_id);

uint8_t match_buffers(uint8_t * match_score);

uint8_t search_for_match(uint8_t * match_score);

uint8_t generate_print_model(void);

uint8_t save_print_to_flash(uint8_t buffer_id);

uint8_t load_print_from_flash(uint8_t buffer_id);

uint8_t delete_print_in_flash(int page_id);

uint8_t drop_prints_in_flash(void);

uint8_t set_sys_param(uint8_t param, uint8_t value);

uint8_t * get_sys_params(void);

uint8_t set_address(int adr);

uint8_t write_to_notepad(uint8_t page, uint8_t * content);

uint8_t * read_notepad_page(uint8_t page);

uint8_t change_led(uint8_t on);

uint8_t force_handshake();

uint8_t run_auto_login(void);

uint8_t run_auto_search(uint8_t * match_score);

#include "commands.c"

#endif //HOMESECURITY_COMMANDS_H
