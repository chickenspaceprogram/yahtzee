#include "ascii-dice.h"

void print_dice(int *dice, int num_dice) {
	printf("\n");
	print_dice_nums(num_dice);
	printf("\n");
	print_die_faces(dice, num_dice);
}

void print_die_faces(int *dice, int num_dice) {

	// looping through the rows, printing the necessary one for each die, as well as a bit of padding space and a newline
	for (int row = 0; row < NUM_ROWS; ++row) {
		for (int die_index = 1; die_index < num_dice + 1; ++die_index) {
			printf("   ");
			print_row(dice[die_index], row);
		}
		printf("\n");
	}
}

void print_row(int roll, int row_num) {

	/*
	The first switch decides which row we're in, since some rows are top/bottom/empty rows for padding and those are easy to take care of.
	The nested switches decide which row type to print based on the roll of the die.
	Every die from 1-6 can be constructed from some combination of rows with 2 dots, rows with 1 dot in the left, right, or center, and empty rows.
	*/
	switch (row_num) {
	case 0: printf(TOP_ROW);
		break;
	case 1:
		switch (roll) {
		case 1: printf(EMPTY_ROW);
			break;
		case 2: case 3: printf(RIGHT_ROW);
			break;
		case 4: case 5: case 6: printf(DOUBLE_ROW);
			break;
		}
		break;
	case 2:
		switch (roll) {
		case 1: case 3: case 5: printf(CENTER_ROW);
			break;
		case 2: case 4: printf(EMPTY_ROW);
			break;
		case 6: printf(DOUBLE_ROW);
			break;
		}
		break;
	case 3:
		switch (roll) {
		case 1: printf(EMPTY_ROW);
			break;
		case 2: case 3: printf(LEFT_ROW);
			break;
		case 4: case 5: case 6: printf(DOUBLE_ROW);
			break;
		}
		break;
	case 4: printf(BOTTOM_ROW);
		break;
	}
}

void print_dice_nums(int num_dice) {
	for (int i = 1; i < num_dice + 1; ++i) {
		BOLD_TEXT();
		printf("     < %d >  ", i); // This would kinda break for i >= 10, but it should never go that high.
		RESET_COLORS();
	}
	printf("\n");
}