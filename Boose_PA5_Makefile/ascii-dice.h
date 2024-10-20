#ifndef ASCII_DICE
#define ASCII_DICE

#include <stdio.h>
#include "escape_codes.h"


/*
Please note that parts of the code in this file were reused from PA 4.
*/

// macros are used here instead of creating a function to display each row type since they make the code more readable
// although with the macros for escape sequences and the use of DEC line drawing mode this is decidely no longer readable
// I learned about DEC line drawing mode here: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#define TOP_ROW		DRAW_MODE"lqqqqqqqk"ASCII_MODE
#define BOTTOM_ROW	DRAW_MODE"mqqqqqqqj"ASCII_MODE
#define EMPTY_ROW	DRAW_MODE"x       x"ASCII_MODE
#define DOUBLE_ROW	DRAW_MODE"x"ASCII_MODE" o   o "DRAW_MODE"x"ASCII_MODE
#define CENTER_ROW	DRAW_MODE"x"ASCII_MODE"   o   "DRAW_MODE"x"ASCII_MODE
#define LEFT_ROW	DRAW_MODE"x"ASCII_MODE" o     "DRAW_MODE"x"ASCII_MODE
#define RIGHT_ROW	DRAW_MODE"x"ASCII_MODE"     o "DRAW_MODE"x"ASCII_MODE
#define NUM_ROWS	5

/*
Example die ASCII art:

				Row number:		Row type:

+-------+			0			SOLID_ROW
| o   o |			1			DOUBLE_ROW
|   o   |			2			CENTER_ROW
| o   o |			3			DOUBLE_ROW
+-------+			4			SOLID_ROW

*/

/**
* Function name: print_dice
* Date created: 10/11/2024
* Date last modified: 10/18/2024
* 
* Description:	Prints any number of dice, along with their associated number and reroll status.
*				This function should only be used to print 9 or fewer dice, else display issues could occur.
* 
* Inputs:
* `dice` : An array containing all the die rolls. The first element in this array is ignored and not displayed.
* `was_rerolled` :	An array containing whether or not each individual die is to be rerolled.
*					If the die should be rerolled, the corresponding element should be set to 1.
*					Otherwise, it should be set to zero.
*					The first element in this array is ignored and not displayed.
* `num_dice` : The number of dice contained in `dice`.
* Outputs: none
*/
void print_dice(int *dice, int num_dice);

/**
* Function name: print_die_faces
* Date created: 09/25/2024
* Date last modified: 10/11/2024
*
* Description: Prints the faces of any number of dice to stdout as ASCII art.
*
* Inputs:
* `dice` : An array containing all the die rolls. The first element in this array is ignored and not displayed.
* `num_dice` : The number of dice contained in `dice`.
* Outputs: none
*/
void print_die_faces(int *dice, int num_dice); // this was the old print_dice from PA 4. A refactor shuffled things around a bit.


/**
* Function name: print_row
* Date created: 09/25/2024
* Date last modified: 10/18/2024
*
* Description: Prints a single row of a die's ASCII art representation to stdout.
*
* Inputs:
* `roll` : The die roll. Should be an int from 1-6 (inclusive). The behavior of inputs outside this range is undefined.
* `row_num` : The zero-indexed row of text to be printed. There are 5 rows in my ASCII representation of the die, so the behavior of inputs outside the range 0-4 (inclusive) is undefined.
* Outputs: none
*
* Notes:
* Rows are printed one-at-a-time to allow two dice to be printed side-by-side.
*/
void print_row(int roll, int row_num);

/**
* Function name: print_dice_nums
* Date created: 10/11/2024
* Date last modified: 10/11/2024
* Description: Prints the number corresponding to each die, spaced such that it lines up neatly with each die.
* Inputs:
* `num_dice` : The number of dice rolled.
* Outputs: none
*/
void print_dice_nums(int num_dice);

#endif