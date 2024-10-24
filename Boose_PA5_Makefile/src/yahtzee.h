#ifndef YAHTZEE_H
#define YAHTZEE_H

#include <stdio.h>
#include "dice.h"
#include "ui.h"
#include "ascii-dice.h"
#include "syscalls.h"

#define NUM_DICE			5
#define START_SCORE_ARRAY	1
#define LEN_SCORE_ARRAY		14

typedef struct player_info player_info;

struct player_info {
	int scores[14]; // i miss Fortran's arbitrary-start array indexing, so convenient
	dice player_dice; // opted for nested structs for more clarity, player_info.dice.values is more readable than player_info.values
};

typedef enum score_combinations {
	SUM_1 = 1,
	SUM_2,
	SUM_3,
	SUM_4,
	SUM_5,
	SUM_6,
	THREE_KIND,
	FOUR_KIND,
	FULL_HOUSE,
	SMALL_STRAIGHT,
	LARGE_STRAIGHT,
	YAHTZEE,
	CHANCE
} score_combinations;

/**
* Function name: init_player_info
* Date created: 10/16/2024
* Date last modified: 10/18/2024
* Description: Initializes a player_info struct with the default values.
* Inputs:
* `info` : A pointer to the struct to be initialized
* Outputs: none
*/
void init_player_info(player_info *info);

/**
* Function name: play_yahtzee_game
* Date created: 10/18/2024
* Date last modified: 10/18/2024
* Description: Plays through a 2-player game of Yahtzee.
* Inputs: none
* Outputs: none
*/
void play_yahtzee_game(void);

/**
* Function name: play_yahtzee_turn
* Date created: 10/16/2024
* Date last modified: 10/18/2024
* Description: Plays through a turn of Yahtzee
* Inputs: 
* Outputs: 
*/
void play_yahtzee_turn(player_info *player);

/**
* Function name: start_turn
* Date created: 10/16/2024
* Date last modified: 10/18/2024
* Description:	Displays the player's score and prompts them to start their turn.
* Inputs: 
* Outputs: 
*/
void start_turn(player_info *player, int num_turns, char *player_name);

/**
* Function name: get_dice_score
* Date created: 10/12/2024
* Date last modified: 10/12/2024
* Description: 
* Inputs: 
* Outputs: 
*/
int get_dice_score(int *dice_freqs, score_combinations selection);

/**
* Function name: 
* Date created: 10/12/2024
* Date last modified: 10/12/2024
* Description: 
* Inputs: 
* Outputs: 
*/
int get_straight_length(int *dice_freqs);

/**
* Function name: find_max_freq
* Date created: 10/12/2024
* Date last modified: 10/12/2024
* Description: 
* Inputs: 
* Outputs: 
*/
int find_max_freq(int *dice_freqs);

/**
* Function name: sum_dice
* Date created: 10/15/2024
* Date last modified: 10/15/2024
* Description: 
* Inputs: 
* Outputs: 
*/
int sum_dice(int *dice_freqs);

/**
* Function name: sum_array
* Date created: 10/16/2024
* Date last modified: 10/18/2024
* Description: Sums the values in the array from `start` to `end` that are not equal to -1.
* Inputs: 
* Outputs: 
*/
int sum_array(int *array, int start, int end);

int find_full_house(int *dice_freqs);

#endif