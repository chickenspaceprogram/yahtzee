#ifndef DICE
#define DICE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_DICE 5 // the number of dice in a game of Yahtzee

/*
Some of the code in this file was reused from PA 4.
*/

/**
* Struct name: dice
* Date created: 10/11/2024
* Date last modified: 10/11/2024
* Description: Contains the dice for a game of Yahtzee, whether to reroll them, and their frequencies.
*/
typedef struct dice dice;
struct dice {
	int values[NUM_DICE + 1];
	int should_reroll[NUM_DICE + 1];
	int frequencies[7];
};

/**
 * Function name: init_dice
 * Date created: 10/11/2024
 * Date last modified: 10/11/2024
 * Description: Resets the should_reroll value of every die to 1.
 * Inputs:
 * `the_dice` : A pointer to a `dice` struct containing information about the dice.
 * Outputs: none
 */
void init_dice(dice *the_dice);

/**
* Function name: seed_rand
* Date created: 09/25/2024
* Date last modified: 09/25/2024
* Description: Seeds the random number generator with the current time.
* Inputs: none
* Outputs: none
*/
void seed_rand(void);

/**
* Function name: roll_die
* Date created: 09/25/2024
* Date last modified: 09/25/2024
* Description: Finds a random number from 1-6.
* Inputs: none
* Outputs: A random number from 1-6.
*/
int roll_die(void);

/**
* Function name: roll_dice
* Date created: 10/11/2024
* Date last modified: 10/11/2024
* Description: Rerolls any dice in dice_array that have should_reroll flag set to 1.
* Inputs:
* `dice_array` : An array containing the dice. The first value is ignored.
* `should_reroll` : Each element in this array controls whether its corresponding element in dice_array should be rerolled.
*					If an element here is set to 0, the die isn't rerolled. Otherwise, it is.
* `num_dice` : The number of dice in `dice_array` and `should_reroll`. Should be one less than the length of these arrays (since the first element is ignored).
* Outputs: Values in `dice_array` are randomized if the corresponding flag in `should_reroll` is set.
*/
void roll_dice(int *dice_array, int *should_reroll, int num_dice);

/**
* Function name: calculate_frequencies
* Date created: 10/12/2024
* Date last modified: 10/12/2024
* Description: Finds the number of occurrrences of each die.
* Inputs:
* `dice_array` : An array containing the dice.
*				 The first element is ignored, so the length of this array should be num_dice + 1.
* `frequencies_array` : An array that is 7 items long. The frequencies of each die roll will be put in this array
*						The frequency of a roll of `1` is put at index 1, `2` is at index 2, and so on.
* `num_dice` : The number of dice in `dice_array`.
* Outputs: Sets each corresponding element in frequencies_array to the frequency of that roll in dice_array
*/
void calculate_frequencies(int *dice_array, int *frequencies_array, int num_dice);


/**
* Function name: process_roll
* Date created: 10/12/2024
* Date last modified: 10/12/2024
* Description: A wrapper function that processes a single roll of the dice in the game of Yahtzee.
* 
* Inputs: 
* `dice_info` : A struct containing the dice rolls, whether to reroll them, and space to put the frequencies of each die roll.
* Outputs: Rerolls any dice with their corresponding `should_reroll` flag set to any nonzero value.
*		   Resets `frequencies_array` to match the new dice frequencies.
*/
void process_roll(dice *dice_info);

#endif