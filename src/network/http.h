//
// Created by Linus Bein Fahlander on 2018-03-04.
//

#ifndef HOMESECURITY_HTTP_H
#define HOMESECURITY_HTTP_H

#define REQ_GET     0x0
#define REQ_POST    0x1
#define REQ_PATCH   0x2
#define REQ_DELETE  0x3

// CONSTANT HEADERS
static char ACCEPT_CONTROL_REQ[] = "Access-Control-Request-Method: GET, POST, PATCH, DELETE";
static char ACCEPT[] = "Accept: application/json";
static char SERVER[] = "Server: Home Security Device HTTP Response Service (For KTH-Kista)";
static char CONTENT_TYPE[] = "Content-Type: application/json; charset=UTF-8";
static char HOST[] = "Host: 192.168.20.200";
static char ORIGIN[] = "Origin: 192.168.20.1";


// VARIABLE HEADERS
static char CONTENT_LENGTH[] = "Content-Length: ";


static char HTTP_VER[] = "HTTP/1.1";
static char LINE_BREAK[] = "\r\n";
static char EMPTY_BODY[] = " ";

uint32_t construct_http_request_header(char *storage, char request_type[], int request_type_len, char path[], int path_len, char body[], int body_len);

uint32_t construct_http_response_header(char *storage, uint16_t res_code);

#include "http.c"

#endif //HOMESECURITY_HTTP_H
