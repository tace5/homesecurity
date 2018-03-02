//
// Created by Linus Bein Fahlander on 2018-02-27.
//

#include "buzzer.h"
#include "../../utils/utils.h"
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */


void buzz(int duration) {
    int i = 0;
    uint8_t freq_break = 0;
    uint8_t freq = 0;

    while (i < (duration << 1)){
        if(freq_break == 0x32){
            freq = ~(freq | 0x1);
            freq_break = 0;
        }

        BUZZER_PORT_SET = BUZZER_BIT;
        if(freq){
            _delay(2);
        } else{
            _delay(1);
        }
        BUZZER_PORT_CLR = BUZZER_BIT;

        freq_break++;
        i++;
        if(!freq){
            i++;
        }
    }

    return 1;
}

