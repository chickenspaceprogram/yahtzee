#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include "terminal.h"
#include "escape-codes.h"

#define ARRAY_SIZE  256

#ifdef _WIN32
#define ESC         0xE0 // The character that starts an arrow key sequence
#else
#define ESC         0x1B // The character that starts an arrow key sequence
#endif

typedef struct option option;

struct option {
    char msg[ARRAY_SIZE];
    unsigned char selection_char;
    int is_valid;
};

/**
 * Function name: menu
 * Date created: 10/22/2024
 * Date last modified: 10/22/2024
 * Description: Displays a pretty menu and allows the user to select an option.
 *              Returns -1 if there are no valid options.
 *              This function kinda sucks and needs a proper wrapper function to be usable.
 *              It does work, though.
 * Inputs:
 * `options` : An array of option structs that contain the messages to be printed for each option
 * `end_string` : A string to be printed at the end of the menu
 * `` :
 * `` :
 * Outputs: The option that was selected
 */
int menu(option *options, char *end_string, int num_options);

#endif