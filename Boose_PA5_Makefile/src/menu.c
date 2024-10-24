#include "menu.h"

// functions are declared as static in the .c file to make them private

/**
 * Function name: find_item
 * Date created: 10/22/2024
 * Date last modified: 
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static int find_item(option *options, int num_options, char item_character, int current_selection);

/**
 * Function name: clear_row
 * Date created: 10/22/2024
 * Date last modified: 
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void clear_row(option *options, int row_to_print, int option_to_print);

/**
 * Function name: print_row
 * Date created: 10/22/2024
 * Date last modified: 
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void print_row(option *options, int row_to_print, int option_to_print);

/**
 * Function name: up_row
 * Date created: 10/22/2024
 * Date last modified: 
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static int up_row(option *options, int current_selection);

/**
 * Function name: down_row
 * Date created: 10/22/2024
 * Date last modified: 
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static int down_row(option *options, int num_options, int current_selection);

/**
 * Function name: print_rows
 * Date created: 10/24/2024
 * Date last modified: 
 * Description: 
 * Inputs: 
 * `options` : An array of structs containing the various printable options and information about them.
 * `option_row_nums` : An output array containing the associated row on which each option was printed.
 * `num_options` : The number of options to print
 * `start_row` : The row on which to start printing the options
 * Outputs: none
 */
static void print_rows(option *options, int *option_row_nums, int num_options, int start_row);


/* Public functions: */


int menu(option *options, int num_options, int menu_start_row) {
    int keypress = 0;
    int selection = down_row(options, num_options, -1), temp; // finding first valid option
    int option_rows[ARRAY_SIZE] = {0};
    
    if (selection == -1) { // in this case, there are no valid options
        return selection;
    }

    // printing all the valid messages
    print_rows(options, option_rows, num_options, menu_start_row);
    
    while (keypress != NEWLINE && keypress != EOF) {
        keypress = GETCH();
        if (keypress == '\x1B') { // if keypress is an escape char, the user has pressed an arrow key
            keypress = handle_escape_sequences();
        }
        switch (keypress) {
            case UP_ARROW: case LEFT_ARROW:
                // clearing row, finding the row to move to, and reprinting the new row
                clear_row(options, option_rows[selection], selection);
                selection = up_row(options, selection);
                print_row(options, option_rows[selection], selection);
                break;
            case DOWN_ARROW: case RIGHT_ARROW:
                clear_row(options, option_rows[selection], selection);
                selection = down_row(options, num_options, selection);
                print_row(options, option_rows[selection], selection);
                break;
            default:
                if ((temp = find_item(options, num_options, keypress, selection)) != selection) {
                    clear_row(options, option_rows[selection], selection);
                    selection = temp;
                    print_row(options, option_rows[selection], selection);
                }
                break;
        }
    }

    return selection;
}

int handle_escape_sequences(void) {
    int first_char = GETCH(), second_char;
    if (first_char != '[') {
        ungetc(first_char, stdin);
        return ESC;
    }
    switch (second_char = GETCH()) {
        case 'A':
            return UP_ARROW;
            break;
        case 'B':
            return DOWN_ARROW;
            break;
        case 'C':
            return RIGHT_ARROW;
            break;
        case 'D':
            return LEFT_ARROW;
            break;
        default:
            ungetc(second_char, stdin);
            ungetc(first_char, stdin);
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

int count_newlines(char *string) {
    int i = 0;
    int num_newlines = 0;
    while (string[i] != '\0') {
        if (string[i] == '\n') {
            ++num_newlines;
        }
        ++i;
    }

    return num_newlines;
}

/* Private functions: */


void clear_row(option *options, int row_to_print, int option_to_print) {
    CURSOR_TO_POSITION(row_to_print, 1);
    printf("  %s", options[option_to_print].msg);
}

void print_row(option *options, int row_to_print, int option_to_print) {
    CURSOR_TO_POSITION(row_to_print, 1);
    printf("> %s", options[option_to_print].msg);
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

static void print_rows(option *options, int *option_row_nums, int num_options, int start_row) {
    int current_row = start_row;
    for (int i = 0; i < num_options; ++i) {
        if (options[i].is_valid) {
            clear_row(options, current_row++, i); // function is misleadingly named, sorry. this just prints a row without a > at the start.
        }
    }
}