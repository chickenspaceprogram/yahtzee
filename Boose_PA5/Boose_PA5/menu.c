#include "menu.h"


// These values are returned by handle_escape_sequences if the user presses an arrow key.
#define UP_ARROW    0x141
#define DOWN_ARROW  0x142
#define RIGHT_ARROW 0x143
#define LEFT_ARROW  0x144

// *nix and Windows format arrow key escape sequences differently
#ifdef _WIN32
#define UP_CHAR     'H'
#define DOWN_CHAR   'P'
#define RIGHT_CHAR  'M'
#define LEFT_CHAR   'K'
#else
#define UP_CHAR     'A'
#define DOWN_CHAR   'B'
#define RIGHT_CHAR  'C'
#define LEFT_CHAR   'D'
#endif

/**
 * Function name: find_item
 * Date created: 10/22/2024
 * Date last modified: 10/22/2024
 * Description: 
 * Inputs: 
 * `options` : An array of `option` structs containing the various menu options.
 * `num_options` : The total number of options.
 * `item_character` : The character that the user selected.
 * `current_selection` : The user's current selection. 
 * Outputs: The index of the option which can be selected by pressing `item_character`, or `current_selection` if the charater is not associated with an option.
 */
static int find_item(option *options, int num_options, char item_character, int current_selection);

/**
 * Function name: clear_row
 * Date created: 10/22/2024
 * Date last modified: 10/22/2024
 * Description: Prints a row without a `>` marker at the current cursor position.
 * Inputs: 
 * `options` : An array of `option` structs containing the various menu options.
 * `option_to_print` : The index of the option to print.
 * Outputs: none
 */
static void clear_row(option *options, int option_to_print);

/**
 * Function name: print_row
 * Date created: 10/22/2024
 * Date last modified: 10/25/2024
 * Description: Prints a row with a `>` marker at the current cursor position.
 * Inputs: 
 * `options` : An array of `option` structs containing the various menu options.
 * `option_to_print` : The index of the option to print.
 * Outputs: none
 */
static void print_row(option *options, int option_to_print);

/**
 * Function name: up_row
 * Date created: 10/22/2024
 * Date last modified: 10/22/2024
 * Description: Returns the index of the option that is one row up from the current option.
 * Inputs: 
 * `options` : An array of `option` structs containing the various menu options.
 * `current_selection` : The index of the user's current selection.
 * Outputs: The index of the option that is one row up from the current option.
 */
static int up_row(option *options, int current_selection);

/**
 * Function name: down_row
 * Date created: 10/22/2024
 * Date last modified: 10/22/2024
 * Description: Returns the index of the option that is one row down from the current option.
 * Inputs: 
 * `options` : An array of `option` structs containing the various menu options.
 * `current_selection` : The index of the user's current selection.
 * Outputs: The index of the option that is one row down from the current option.
 */
static int down_row(option *options, int num_options, int current_selection);

/**
 * Function name: print_rows
 * Date created: 10/24/2024
 * Date last modified: 10/24/24
 * Description: Prints all the valid options, and returns how many valid options there were
 * Inputs: 
 * `options` : An array of structs containing the various printable options and information about them.
 * `option_row_nums` : An output array containing the associated row on which each option was printed.
 * `num_options` : The number of options to print
 * Outputs: The total number of rows printed
 */
static int print_rows(option *options, int *option_row_nums, int num_options);

/**
 * Function name: print_end_string
 * Date created: 10/24/24
 * Date last modified: 10/24/24
 * Description: Prints the string to go at the end of the menu, and returns the number of newlines in this string.
 * Inputs: 
 * `end_string` : The string to go at the end of the menu
 * Outputs: The number of newlines in the string
 */
static int print_end_string(char *end_string);

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
static int handle_escape_sequences(void);


/* Public functions: */


int menu(option *options, char *end_string, int num_options) {
    int keypress = 0;
    int selection = down_row(options, num_options, -1), temp = 0; // finding first valid option
    int option_rows[ARRAY_SIZE] = {0};
    
    if (selection == -1) { // in this case, there are no valid options
        return selection;
    }

    // printing all the valid messages
    temp = print_rows(options, option_rows, num_options);
    temp += print_end_string(end_string);

    CURSOR_UP(temp);
    CURSOR_TO_COL(1);
    print_row(options, selection); // reprinting the first row with the selector marker
    
    while (keypress != NEWLINE && keypress != EOF) {
        keypress = GETCH();
        if (keypress == ESC) { // if keypress is an escape char, the user has pressed an arrow key
            keypress = handle_escape_sequences();
        }
        switch (keypress) {
            case UP_ARROW: case LEFT_ARROW: case 'k':
                // clearing row, finding the row to move to, and reprinting the new row
                temp = up_row(options, selection);
                if (temp != selection) {
                    clear_row(options, selection);
                    selection = temp;
                    CURSOR_UP(1);
                    print_row(options, selection);
                }
                break;
            case DOWN_ARROW: case RIGHT_ARROW: case 'j':
                temp = down_row(options, num_options, selection);
                if (temp != selection) {
                    clear_row(options, selection);
                    selection = temp;
                    CURSOR_DOWN(1);
                    print_row(options, selection);
                }
                break;
            default:
                if ((temp = find_item(options, num_options, keypress, selection)) != selection) {
                    clear_row(options, selection);
                    if (option_rows[temp] > option_rows[selection]) {
                        CURSOR_DOWN(option_rows[temp] - option_rows[selection]);
                    }
                    else {
                        CURSOR_UP(option_rows[selection] - option_rows[temp]);
                    }
                    selection = temp;
                    print_row(options, selection);
                }
                break;
        }
    }
    return selection;
}

int handle_escape_sequences(void) {
    int second_char;
#ifndef _WIN32 // if we're on *nix, we need to get the `[` character from stdin.
    int first_char = GETCH();
    if (first_char != '[') {
        ungetc(first_char, stdin);
        return ESC;
    }
#endif
    switch (second_char = GETCH()) {
        case UP_CHAR:
            return UP_ARROW;
            break;
        case DOWN_CHAR:
            return DOWN_ARROW;
            break;
        case RIGHT_CHAR:
            return RIGHT_ARROW;
            break;
        case LEFT_CHAR:
            return LEFT_ARROW;
            break;
        default:
            ungetc(second_char, stdin);
#ifndef _WIN32 // only unget the first char if we actually got it in the first place
            ungetc(first_char, stdin);
#endif
            return ESC;
    }
}

int find_item(option *options, int num_options, char item_character, int current_selection) {
    for (int i = 0; i < num_options; ++i) {
        if (options[i].is_valid && options[i].selection_char == item_character) {
            return i;
        }
    }
    // if the user didn't enter a valid character, return whatever the current selection is
    return current_selection;
}

/* Private functions: */


void clear_row(option *options, int option_to_print) {
    printf("  %s  ", options[option_to_print].msg);
    CURSOR_TO_COL(1);
}

void print_row(option *options, int option_to_print) {
    printf("> ");
    INVERT_COLORS();
    printf("%s", options[option_to_print].msg);
    RESET_COLORS();
    printf(" <");
    CURSOR_TO_COL(1);
}

int up_row(option *options, int current_selection) {
    if (current_selection == 0) {
        return current_selection; // already at the beginning!
    }
    for (int i = current_selection - 1; i >= 0; --i) {
        if (options[i].is_valid) {
            return i; // if we find a valid option, stop and return it!
        }
    }
    return current_selection; // couldn't find an earlier valid selection
}

int down_row(option *options, int num_options, int current_selection) {
    if (current_selection == num_options - 1) {
        return current_selection; // already at the end!
    }
    for (int i = current_selection + 1; i < num_options; ++i) {
        if (options[i].is_valid) {
            return i; // if we find a valid option, stop and return it!
        }
    }

    return current_selection; // couldn't find an earlier valid selection
}

int print_rows(option *options, int *option_row_nums, int num_options) {
    int rows_printed = 0;
    for (int i = 0; i < num_options; ++i) {
        if (options[i].is_valid) {
            option_row_nums[i] = rows_printed;
            clear_row(options, i); // function is misleadingly named, sorry. this just prints a row without a > at the start.
            putchar('\n');
            ++rows_printed;
        }
    }
    return rows_printed;
}

int print_end_string(char *end_string) {
    int index = 0, num_newlines = 0;
    while (end_string[index] != '\0') {
        putchar(end_string[index]);
        if (end_string[index] == '\n') {
            ++num_newlines;
        }
        ++index;
    }
    return num_newlines;
}