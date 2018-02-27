//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "controller.h"
#include "setup.h"
#include "fingerprint_main.h"

void fingerprint_main(){
    init();
    setup();
}
