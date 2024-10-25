#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN() system("cls");
#define GETCH() _getch();
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

#define CLEAR_SCREEN() system("clear")
#define GETCH() unix_getch()
#define NEWLINE '\n'

#endif

#endif