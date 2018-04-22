//
// Created by Linus Bein Fahlander on 2018-04-05.
//

#include "display_functions.h"


void user_message(char * message, int len){
    if(len < 17){
        display_string(2, message);
        display_string(3, "");
    } else{
        int i;
        int j;
        char mes1[16];
        char mes2[16];
        for (i = 0; i < 16; ++i) {
            mes1[i] = message[i];
        }
        for (j = 16; j < len; ++j) {
            mes2[j - 16] = message[j];
        }
        display_string(2, mes1);
        display_string(3, mes2);
    }

    display_update();
}

void state_message(char * message, int len){
    if(len < 17){
        display_string(0, message);
        display_string(1, "");
    } else{
        int i;
        int j;
        char mes1[16];
        char mes2[16];
        for (i = 0; i < 16; ++i) {
            mes1[i] = message[i];
        }
        for (j = 16; j < len; ++j) {
            mes2[j - 16] = message[j];
        }
        display_string(0, mes1);
        display_string(1, mes2);
    }

    display_update();
}

void msg_request_err(){
    display_string(2, "Request error");
    display_string(3, "");
    display_update();
}

void msg_finger_on_sensor(char put_or_keep){
    if (put_or_keep){
        display_string(2, "Put finger");
    } else{
        display_string(2, "Keep finger");
    }
    display_string(3, "on sensor!");
    display_update();
}

void msg_remove_finger(){
    display_string(2, "Remove finger");
    display_string(3, "from sensor!");
    display_update();
}

void msg_try_again(){
    display_string(2, "Try again");
    display_string(3, "");
    display_update();
}