#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>

/**
 * Macro name: CLEAR_SCREEN
 * Date created: 10/19/2024
 * Date last modified: 10/25/2024
 * Description: Clears the screen.
 * Inputs: none
 * Outputs: none
 */
#define CLEAR_SCREEN() system("cls")

/**
 * Macro name: GETCH
 * Date created: 10/19/2024
 * Date last modified: 10/25/2024
 * Description: Gets a single keypress from the user without waiting or echoing the inputs to the terminal.
 * Inputs: none
 * Outputs: The user's keypress
 */
#define GETCH() _getch()

#define NEWLINE '\r'
#else
#include <termios.h>
#include <unistd.h>
/**
 * Function name: unix_getch
 * Date created: 10/19/2024
 * Date last modified: 10/22/2024
 * Description: Gets a character directly from stdin without buffering or echoing it to the terminal.
 * Inputs: none
 * Outputs: The character that was entered.
 */
int unix_getch(void);

/**
 * Macro name: CLEAR_SCREEN
 * Date created: 10/19/2024
 * Date last modified: 10/19/2024
 * Description: Clears the screen.
 * Inputs: none
 * Outputs: none
 */
#define CLEAR_SCREEN() system("clear")

/**
 * Macro name: GETCH
 * Date created: 10/19/2024
 * Date last modified: 10/22/2024
 * Description: Gets a character directly from stdin without buffering or echoing it to the terminal.
 * Inputs: none
 * Outputs: The character that was entered.
 */
#define GETCH() unix_getch()

#define NEWLINE '\n'

#endif

/**
 * Macro name: PAUSE
 * Date created: 10/24/2024
 * Date last modified: 10/24/2024
 * Description: Pauses the program's execution until the user presses any key.
 * Inputs: none
 * Outputs: none, typecasts to void to make it clear that this is solely for pausing
 */
#define PAUSE() (void) GETCH()

#endif
