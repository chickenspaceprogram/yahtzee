#include "dice.h"

void init_dice(dice *the_dice) {
	// setting should_reroll to 1 for every die
	for (int i = 1; i < (NUM_DICE + 1); ++i) {
		the_dice->should_reroll[i] = 1;
	}
}

void seed_rand(void) {
	srand((unsigned int) time(NULL));
}

int roll_die(void) {
	return (rand() % 6) + 1; // since rand % 6 returns values 0-5, add one to get 1-6
}

void roll_dice(int *dice_array, int *should_reroll, int num_dice) {

	// looping through all the dice
	for (int i = 1; i < (num_dice + 1); ++i) {
		// if we should reroll this die, then we reroll it
		if (should_reroll[i]) {
			dice_array[i] = roll_die();
		}
	}
}

void calculate_frequencies(int *dice_array, int *frequencies_array, int num_dice) {

	// clearing frequencies_array
	for (int i = 1; i < 7; ++i) {
		frequencies_array[i] = 0;
	}

	// adding one to the element in frequencies_array matching the value of each die
	for (int i = 1; i < (num_dice + 1); ++i) {
		++(frequencies_array[dice_array[i]]);
	}
}

void process_roll(dice *dice_info) {
	// a wrapper function was used here to make the underlying code as modular as possible while still providing an easy interface for the rest of the program.
	roll_dice(dice_info->values, dice_info->should_reroll, 5);
	calculate_frequencies(dice_info->values, dice_info->frequencies, 5);
}