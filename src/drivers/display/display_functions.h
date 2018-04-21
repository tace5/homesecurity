/* display_functions.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#ifndef HOMESECURITY_DISPLAY_FUNCTIONS_H
#define HOMESECURITY_DISPLAY_FUNCTIONS_H

/* Declare display-related functions from mipslabfunc.c */
void display_init(void);

void display_string(int line, char *s);

void display_update(void);

uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char *itoaconv(int num);

void quicksleep(int cyc);

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug(int slot, volatile int *const addr);

void display_setup(void);

#include "display_functions.c"

//Default messages

void user_message(char * message, int len);

void clr_user_message();

void state_message(char * message, int len);

void clr_state_message();

void msg_request_err();

void msg_finger_on_sensor(char put_or_keep);

void msg_remove_finger();

void msg_try_again();

#include "display_default_messages.c"

#endif //HOMESECURITY_DISPLAY_FUNCTIONS_H
