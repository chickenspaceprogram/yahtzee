#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include "syscalls.h"
#include "escape_codes.h"

#define ESC         0x1B
#define UP_ARROW    0x141
#define DOWN_ARROW  0x142
#define RIGHT_ARROW 0x143
#define LEFT_ARROW  0x144

#define ARRAY_SIZE 256

typedef struct option option;

struct option {
    char msg[256];
    unsigned char selection_char;
    int is_valid;
};

/**
 * Function name: menu
 * Date created: 10/22/2024
 * Date last modified: 10/22/2024
 * Description: Displays a pretty menu and allows the user to select an option.
 *              Returns -1 if there are no valid options.
 * Inputs:
 * `options` : An array of option structs that contain the messages to be printed for each option
 * `end_string` : A string to be printed at the end of the menu
 * `` :
 * `` :
 * Outputs: The option that was selected
 */
int menu(option *options, char *end_string, int num_options);

/**
* Function name: handle_escape_sequences
* Date created: 10/22/2024
* Date last modified: 10/22/2024
* Description:  Handles any escape sequences that the user has entered, currently just the arrow keys.
*               Assumes that the escape character has already been gotten from stdin.
* Inputs: none
* Outputs:  A value representing the escape character entered.
*           If a valid escape sequence isn't recognized, ESC is returned and any characters this function grabs are pushed back onto stdin.
*/
int handle_escape_sequences(void);

#endif