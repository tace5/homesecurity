//
// Created by Linus on 2018-03-31.
//

#include "state_main.h"
#include "state_functions.h"
#include "../utils/utils.h"

void state_main(){
    StateFunc statefunc = led1_on;

    while (1){
        statefunc = (StateFunc)(*statefunc)();
        _delay(1000);
    }
}
