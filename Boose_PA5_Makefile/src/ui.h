#ifndef UI
#define UI

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "yahtzee.h"
#include "ascii-dice.h"
#include "escape_codes.h"
#include "syscalls.h"
#include "menu.h"

#define PAGE_SIZE		4096

// cursed
#define ROLL_INFO_ROW	11
#define COL_SIZE		12
#define SHIFT_AMT		-8

#define SCORE_POS       41
#define NUM_OPTIONS     14


/*
Please note that some of the functions in this file were originally written for PA 4.
*/

/**
* Function name: print_file
* Date created: 09/25/2024
* Date last modified: 10/10/2024
* Description:	Prints the contents of a file to stdout.
*				This is used to print the rules and the main menu because a bunch of printf() statements would've been extremely ugly
* Inputs:
* `filename` : The name of the file.
* `clear_screen` : Whether to clear the screen before displaying the file.
* Outputs: none
*/
void print_file(char *filename, int clear_screen);

/**
* Function name: select_from_menu
* Date created: 10/12/2024
* Date last modified: 10/24/2024
* Description: Displays a menu with all the options that haven't yet been selected by the user.
* Inputs: 
* `scores` : An array containing the user's score for each dice combination (or -1, if the combination has not been selected yet)
* `dice_freqs` : An array containing the frequency of each die roll.
* Outputs: The user's selection.
*/
int select_from_menu(int *scores, int *dice_freqs);

/**
* Function name: select_dice_combination
* Date created: 10/12/2024
* Date last modified: 10/18/2024
* Description:	Allows the user to enter a dice combination they would like to use their roll for.
*				Prevents the user from entering an invalid dice combination.
* Inputs: An array containing 1 for each valid dice combination, and 0 if that combination is invalid
* Outputs: The combination the user chose.
*/
int select_dice_combination(int *scores);

/**
* Function name: roll_selector
* Date created: 10/12/2024
* Date last modified: 10/18/2024
* Description: 
* Inputs: 
* `dice` : An array containing the dice the user rolled. The first value in this array is ignored, and there are assumed to be 5 dice in this array. Therefore, the length of this array must be 6.
* `should_reroll` : The array containing whether to reroll each die.
* `turn_num` : The number of the turn the user is on.
* Outputs: Returns 1 if the user has not ended their turn, and 0 if they have. Sets the values in should_reroll to the ones the user entered.
*/
int roll_selector(int *dice, int *should_reroll, int turn_num);

/**
* Function name: get_keep_die_selection
* Date created: 10/12/2024
* Date last modified: 10/15/2024
* Description:	Waits for the user to press the '1', '2', '3', '4', '5', or [Enter] keys, and returns the value of the key they pressed.
*				NEWLINE is returned if the user presses [Enter], and the corresponding ASCII character for the digit is returned if the user presses 1-5.
* Inputs: none
* Outputs: An integer containing either the user's selection ('1'-'5'), or NEWLINE (either '\r' or '\n', depending on the user's OS.
*/
int get_keep_die_selection(void);

/**
* Function name: print_whether_roll
* Date created: 10/18/2024
* Date last modified: 10/18/2024
* Description:	If the corresponding element in should_reroll != 0, any past [NO ROLL] message is cleared.
*				Otherwise, a [NO ROLL] messge is printed in the right spot.'
* 
* Inputs: 
* `should_reroll` : The array containing whether to reroll each die
* `die_num` : Which die's reroll status is to be printed
* 
* Outputs: None to this program, but the [NO ROLL] message is displayed/cleared for the user.
*/
void print_whether_roll(int *should_reroll, int die_num);

/**
* Function name: print_no_roll
* Date created: 10/18/2024
* Date last modified: 10/18/2024
* Description: Prints a [NO ROLL] message below one of the dice.
* Inputs: 
* `die_num` : Which die the [NO ROLL] is to be printed below. Should be from 1-5.
* Outputs: none
*/
void print_no_roll(int die_num);

/**
* Function name: clear_no_roll
* Date created: 10/18/2024
* Date last modified: 10/18/2024
* Description: Clears the [NO ROLL] message printed by print_no_roll
* Inputs: 
* `die_num` : Which die the [NO ROLL] is to be printed below. Should be from 1-5.
* Outputs: none
*/
void clear_no_roll(int die_num);

#endif