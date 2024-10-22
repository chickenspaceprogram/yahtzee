#include "yahtzee.h"

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

	for (int i = 1; i < 14; ++i) {
		start_turn(&player1, i, "Player 1");
		play_yahtzee_turn(&player1);
		start_turn(&player2, i, "Player 2");
		play_yahtzee_turn(&player2);
		init_dice(&(player1.player_dice), 5);
		init_dice(&(player2.player_dice), 5);
	}
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
	print_dice_combinations(player->scores, player->player_dice.frequencies);
	selection = select_dice_combination(player->scores);
	player->scores[selection] = get_dice_score(player->player_dice.frequencies, (score_combinations) selection);
	printf("Your score is now %d. Press any key to continue . . . ", sum_array(player->scores, START_SCORE_ARRAY, LEN_SCORE_ARRAY));
	HIDE_CURSOR();
	GETCH();
	SHOW_CURSOR();
}

void start_turn(player_info *player, int num_turns, char *player_name) {
	CLEAR_SCREEN();
	printf("Hi %s! It's currently turn %d.\n", player_name, num_turns);
	printf("Your current score is: %d\n\nPress any key to continue . . .", sum_array(player->scores, START_SCORE_ARRAY, LEN_SCORE_ARRAY));
	HIDE_CURSOR();
	GETCH();
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