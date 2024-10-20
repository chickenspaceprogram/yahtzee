#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include "conio.h"
#define CLEAR_SCREEN() system("cls");
#define GETCH() _getch();
#define NEWLINE '\r'
#else

/**
* Function name: 
* Date created: 
* Date last modified: 
* Description: 
* Inputs: 
* Outputs: 
*/
int unix_getch(void); // if the OS is *nix, we put the definition here to make it accessible to the rest of the program

#define CLEAR_SCREEN() system("clear");
#define GETCH() unix_getch();
#define NEWLINE '\n'

#endif

#endif