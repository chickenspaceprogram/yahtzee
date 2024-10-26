#include "yahtzee.h"

/* Private function declarations */

/**
 * Function name: get_straight_length
 * Date created: 10/12/2024
 * Date last modified: 10/12/2024
 * Description: Finds the length of the longest straight that the user rolled.
 * Inputs: 
 * `dice_freqs` : An array containing the frequency with which each die was rolled.
 * Outputs: The length of the longest straight that the user rolled.
 */
static int get_straight_length(int *dice_freqs);

/**
 * Function name: find_max_freq
 * Date created: 10/12/2024
 * Date last modified: 10/12/2024
 * Description: Finds the number of times that the most-frequently-rolled die was rolled.
 * Inputs: 
 * `dice_freqs` : An array containing the frequency with which each die was rolled.
 * Outputs: The maximum roll frequency.
 */
static int find_max_freq(int *dice_freqs);

/**
 * Function name: sum_dice
 * Date created: 10/15/2024
 * Date last modified: 10/15/2024
 * Description: Finds the sum of the face values of all the dice.
 * Inputs: 
 * `dice_freqs` : An array containing the frequency with which each die was rolled.
 * Outputs: The sum of the face values of all the dice.
 */
static int sum_dice(int *dice_freqs);

/**
 * Function name: sum_array
 * Date created: 10/16/2024
 * Date last modified: 10/18/2024
 * Description: Sums the values in the array from `start` to `end` that are not equal to -1.
 * Inputs: 
 * `array` : The array to be summed.
 * `start` : The index to start summing at (inclusive).
 * `end` : The index to end at (exclusive.)
 * Outputs: The sum of the values in the array
 */
static int sum_array(int *array, int start, int end);

/**
 * Function name: find_full_house
 * Date created: 10/15/2024
 * Date last modified: 10/15/2024
 * Description: Checks whether the user has a full house.
 * Inputs: 
 * `dice_freqs` : An array containing the frequency with which each die was rolled.
 * Outputs: 1 if the user has a full house, 0 otherwise
 */
static int find_full_house(int *dice_freqs);


/* Public functions */


void init_player_info(player_info *player) {
	for (int i = START_SCORE_ARRAY; i < LEN_SCORE_ARRAY; ++i) {
		player->scores[i] = -1;
	}
	init_dice(&(player->player_dice), 5);
}

void play_yahtzee_game(void) {
	player_info player1;
	player_info player2;
	init_player_info(&player1);
	init_player_info(&player2);
	int player1_score = 0, player2_score = 0;

	for (int i = 1; i < 14; ++i) {
		start_turn(&player1, i, "Player 1");
		play_yahtzee_turn(&player1);
		start_turn(&player2, i, "Player 2");
		play_yahtzee_turn(&player2);
		init_dice(&(player1.player_dice), 5);
		init_dice(&(player2.player_dice), 5);
	}

	player1_score = sum_array(player1.scores, START_SCORE_ARRAY, LEN_SCORE_ARRAY);
	player2_score = sum_array(player2.scores, START_SCORE_ARRAY, LEN_SCORE_ARRAY);
	CLEAR_SCREEN();
	HIDE_CURSOR();
	printf("\nThe game has ended!\n\n");
	if (player1_score > player2_score) {
		printf("Player 1 won the game!\n\n");
	}
	else if (player1_score == player2_score) {
		printf("Both players tied!\n\n");
	}
	else {
		printf("Player 2 won the game!\n\n");
	}
	printf("Player 1's score was: %d\nPlayer 2's score was: %d\n\n\n", player1_score, player2_score);
	printf("Press any key to continue . . . ");
	PAUSE();
}

void play_yahtzee_turn(player_info *player) {
	int rolls = 0, continue_turn = 1, selection = 0;
	do {
		process_roll(&(player->player_dice));
		continue_turn = roll_selector(player->player_dice.values, player->player_dice.should_reroll, ++rolls);

	} while (rolls < 3 && continue_turn);

	printf("The dice you rolled are:\n\n");
	print_die_faces(player->player_dice.values, 5);
	printf("\n");
	selection = select_from_menu(player->scores, player->player_dice.frequencies);
	player->scores[selection] = get_dice_score(player->player_dice.frequencies, (score_combinations) selection);
	CLEAR_SCREEN();
	printf("Your score is now %d. Press any key to continue . . . ", sum_array(player->scores, START_SCORE_ARRAY, LEN_SCORE_ARRAY));
	HIDE_CURSOR();
	PAUSE();
	SHOW_CURSOR();
}

void start_turn(player_info *player, int num_turns, char *player_name) {
	CLEAR_SCREEN();
	printf("Hi %s! It's currently turn %d.\n", player_name, num_turns);
	printf("Your current score is: %d\n\nPress any key to continue . . .", sum_array(player->scores, START_SCORE_ARRAY, LEN_SCORE_ARRAY));
	HIDE_CURSOR();
	PAUSE();
	SHOW_CURSOR();
}

int get_dice_score(int *dice_freqs, score_combinations selection) {
	int total = 0, straight_len = 0;
	switch (selection) {
		case SUM_1: case SUM_2: case SUM_3: case SUM_4: case SUM_5: case SUM_6:
			total = dice_freqs[selection] * selection; // the fact that C enums are just numbers is quite convenient here
			break;
		case THREE_KIND:
			if (find_max_freq(dice_freqs) >= 3) {
				total = sum_dice(dice_freqs);
			}
			break;
		case FOUR_KIND:
			if (find_max_freq(dice_freqs) >= 4) {
				total = sum_dice(dice_freqs);
			}
			break;
		case FULL_HOUSE:
			if (find_full_house(dice_freqs)) {
				total = 25;
			}
			break;
		case SMALL_STRAIGHT: // bug
			straight_len = get_straight_length(dice_freqs);
			if (straight_len >= 4) {
				total = 30;
			}
			break;
		case LARGE_STRAIGHT: // bug
			straight_len = get_straight_length(dice_freqs);
			if (straight_len >= 5) {
				total = 40;
			}
			break;
		case YAHTZEE:
			if (find_max_freq(dice_freqs) >= 5) {
				total = 50;
			}
			break;
		case CHANCE:
			total = sum_dice(dice_freqs);
			break;
	}
	return total;
}


/* Private functions */


int get_straight_length(int *dice_freqs) {
	int longest_straight_len = 0, current_straight_len = 0;
	for (int i = 1; i < 7; ++i) {
		if (dice_freqs[i]) {
			++current_straight_len;
		}
		else {
			if (current_straight_len > longest_straight_len) {
				longest_straight_len = current_straight_len;
			}
			current_straight_len = 0;
		}
	}
	if (current_straight_len > longest_straight_len) {
		longest_straight_len = current_straight_len;
	}
	return longest_straight_len;
}

int find_max_freq(int *dice_freqs) {
	int max = 0;
	for (int i = 1; i < 7; ++i) {
		if (dice_freqs[i] > max) {
			max = dice_freqs[i];
		}
	}
	return max;
}

int sum_dice(int *dice_freqs) {
	int sum = 0;
	for (int i = 1; i < 7; ++i) {
		sum += i * dice_freqs[i];
	}
	return sum;
}

int sum_array(int *array, int start, int end) {
	int total = 0;
	for (int i = start; i < end; ++i) {
		if (array[i] != -1) {
			total += array[i];
		}
	}
	return total;
}

int find_full_house(int *dice_freqs) {
	for (int i = 1; i < 7; ++i) {
		if (dice_freqs[i] != 2 && dice_freqs[i] != 3 && dice_freqs[i] != 0) {
			return 0; // if we find any frequency that isn't a 2, 3, or 0, there can't be a full house, so we return.
		}
	}
	return 1; // if we only find frequencies of 2, 3, or 0, we have a full house
}