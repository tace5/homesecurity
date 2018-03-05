//
// Created by Linus Bein Fahlander on 2018-03-04.
//

#include <stdint.h>
#include "http.h"
#include "../drivers/ethernet/enc28j60_instructions.h"
#include "../utils/utils.h"
#include "../third_party/jsmn/jsmn.h"


int write_to_storage(char *storage, char data[], int data_len){
    int i;
    for (i = 0; i < data_len; ++i) {
        storage[i] = data[i];
    }

    return i;
}

/* Returns length of data */
uint32_t construct_http_request_header(char *storage, char request_type[], int request_type_len, char path[], int path_len, char body[], int body_len) {
    // Headers: User-Agent, Host, Accept, Accept-Charset
    // Access-Control-Request-Method, Access-Control-Request-Headers
    // Content-Length, Content-Type (POST/PUT), Origin

    uint32_t s_i = 0;  // Current storage index

    // REQUEST LINE
    s_i += write_to_storage(storage, request_type, request_type_len);
    storage[s_i++] = ' ';
    s_i += write_to_storage((storage + s_i), path, path_len);
    storage[s_i++] = ' ';
    s_i += write_to_storage((storage + s_i), HTTP_VER, sizeof(HTTP_VER));
    s_i += write_to_storage((storage + s_i), LINE_BREAK, sizeof(LINE_BREAK));

    // REQUEST HEADERS
    // Host
    s_i += write_to_storage((storage + s_i), HOST, sizeof(HOST));
    s_i += write_to_storage((storage + s_i), LINE_BREAK, sizeof(LINE_BREAK));
    // Accept
    s_i += write_to_storage((storage + s_i), ACCEPT, sizeof(ACCEPT));
    s_i += write_to_storage((storage + s_i), LINE_BREAK, sizeof(LINE_BREAK));
    // Content Type
    s_i += write_to_storage((storage + s_i), CONTENT_TYPE, sizeof(CONTENT_TYPE));
    s_i += write_to_storage((storage + s_i), LINE_BREAK, sizeof(LINE_BREAK));

    // Content Length
    // Only set content length if body is set
    if(*body != ' ') {
        char len_char[digits(body_len)];
        itoa(body_len, len_char);  // Get ascii representation of body length
        s_i += write_to_storage((storage + s_i), CONTENT_LENGTH, sizeof(CONTENT_LENGTH));
        s_i += write_to_storage((storage + s_i), len_char, sizeof(len_char));
    }

    // REQUEST BODY
    if(*body != ' ') {
        s_i += write_to_storage((storage + s_i), body, body_len);
    }

    return s_i;

}

/* Returns status code */
uint32_t deconstruct_http_response(uint8_t *storage) {
    uint8_t i = 0;
    while(i < 10){
        while (!(read_control_register(EIR) & PKTIF));
        i++;
    }
}
