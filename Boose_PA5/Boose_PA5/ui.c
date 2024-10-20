#include "ui.h"
#include "syscalls.h"

void print_file(char *filename, int clear_screen) {

	// opening file, ensuring it is non-null
	FILE* input = fopen(filename, "r");
	if (input == NULL) {
		printf("An error occurred while loading the file `%s`.\n\nPress any key to continue . . . ", filename);
		GETCH();
		return;
	}
	// using a buffer looked marginally nicer than using getc() and putc() character-by-character
	// allocating it on the stack is probably bad practice since the buffer's relatively large, but I'm lazy and this worked
	char buffer[PAGE_SIZE]; // This could be set to all zeroes but it's unnecessary and (probably) would be marginally slower
	int chars_read = 0;

	// if we want to clear the screen, do it now after everything's been allocated to minimize time where screen is blank
	if (clear_screen) {
		CLEAR_SCREEN(); // the option to not clear the screen is not used, but I want to make this function more general
	}

	do {
		// fread() returns the number of bytes read from the buffer
		chars_read = (int)fread(buffer, sizeof(char), PAGE_SIZE, input);

		// we can then use sizeof(char) and the number of chars read to tell fwrite() how much of the buffer we want to write to stdout
		fwrite(buffer, sizeof(char), chars_read, stdout);
	} while (!feof(input)); // keep looping until we reach EOF

	// closing file
	fclose(input);
}

void print_dice_combinations(int *scores, int *dice_freqs) {
	int roll_score = 0;

	// having an array of messages is a lot neater than a bunch of if statements
	const char *one_digit_option_messages[] = { // made const since it won't change
		"| Combinations:         | Score: |\n", // this is something instead of NULL since it was easy to make it line up nicely when writing
		"|  1 : Sum of 1s        |    %d   |\n",
		"|  2 : Sum of 2s        |    %d   |\n",
		"|  3 : Sum of 3s        |    %d   |\n",
		"|  4 : Sum of 4s        |    %d   |\n",
		"|  5 : Sum of 5s        |    %d   |\n",
		"|  6 : Sum of 6s        |    %d   |\n",
		"|  7 : Three-of-a-kind  |    %d   |\n",
		"|  8 : Four-of-a-kind   |    %d   |\n",
		"|  9 : Full House       |    %d   |\n",
		"| 10 : Small Straight   |    %d   |\n",
		"| 11 : Large Straight   |    %d   |\n",
		"| 12 : Yahtzee          |    %d   |\n",
		"| 13 : Chance           |    %d   |\n"
	};
	const char *two_digit_option_messages[] = { // made const since it won't change
		"",
		"", // you can't have a sum of 1s that is > 9, so we can save a few bytes
		"|  2 : Sum of 2s        |   %d   |\n",
		"|  3 : Sum of 3s        |   %d   |\n",
		"|  4 : Sum of 4s        |   %d   |\n",
		"|  5 : Sum of 5s        |   %d   |\n",
		"|  6 : Sum of 6s        |   %d   |\n",
		"|  7 : Three-of-a-kind  |   %d   |\n",
		"|  8 : Four-of-a-kind   |   %d   |\n",
		"|  9 : Full House       |   %d   |\n",
		"| 10 : Small Straight   |   %d   |\n",
		"| 11 : Large Straight   |   %d   |\n",
		"| 12 : Yahtzee          |   %d   |\n",
		"| 13 : Chance           |   %d   |\n"
	};
	printf("Please select your preferred option by entering the corresponding number:\n\n");
	printf("----------------------------------\n");
	printf(one_digit_option_messages[0]);
	printf("----------------------------------\n");
	// looping through and printing every valid combination
	for (int i = 1; i < 14; ++i) {
		if (scores[i] == -1) {
			roll_score = get_dice_score(dice_freqs, (score_combinations) i);
			if (roll_score >= 10) {
				printf(two_digit_option_messages[i], roll_score);
			}
			else {
				printf(one_digit_option_messages[i], roll_score);
			}
		}
	}
	printf("----------------------------------\n");
}

int select_dice_combination(int *scores) {
	int selection = 0;

	// keep looping until the user enters a valid dice combination, at which point we return
	while (1) {
		printf("\nYour selection: ");
		(void) scanf("%d", &selection);
		if (selection >= 1 && selection <= 14) {
			if (scores[selection] == -1) {
				getchar(); // cleaning up trailing newline
				return selection;
			}
		}
		printf("Your selection was invalid. Please try again.\n");
	}
}

int roll_selector(int *dice, int *should_reroll, int turn_num) {
	// initializing variables, clearing screen
	int selection = 0;
	CLEAR_SCREEN();

	print_dice(dice, 5);


	// telling user what to do
	printf("\n\n\n\n\nCurrently on roll %d.\n\nPress the number corresponding to a die to toggle whether it is to be rolled.\nTo reroll dice, press [Space], and to end your turn, press [Enter].\n", turn_num);

	// saving position of and hiding cursor
	SAVE_CURSOR();
	HIDE_CURSOR();

	for (int i = 1; i < 6; ++i) {
		print_whether_roll(should_reroll, i);
	}

	// keep looping until this function returns
	while (1) {

		// waiting for the user to enter something valid, this function continues once they do
		selection = get_keep_die_selection(); // this function's name is atrocious, sorry

		if (selection == ' ') {

			// reloading the previous position of the cursor so we can pick up where we left off before this function moved the cursor around
			LOAD_CURSOR();
			SHOW_CURSOR();
			CLEAR_SCREEN();
			return 1;
		}
		else if (selection == NEWLINE) { // windows using \r\n for newlines is annoying
			// reloading the previous position of the cursor so we can pick up where we left off before this function moved the cursor around
			LOAD_CURSOR();
			SHOW_CURSOR();

			printf("\n\n\n\n\n\n\nRoll saved. Press any key to continue . . . "); // i shouldn't have to do this many newlines, but 
			GETCH();
			CLEAR_SCREEN();
			return 0;
		}

		// flipping the value of should_reroll since the user pressed the corresponding key
		should_reroll[selection - '0'] = !should_reroll[selection - '0'];
		
		print_whether_roll(should_reroll, selection - '0');
	}

}

int get_keep_die_selection(void) {

	// keep looping until we return
	while (1) {
		int selection = GETCH(); // gets the key the user pressed

		// if the key is one we want, return it. otherwise, keep going
		if ((selection >= '1' && selection <= '5') || selection == NEWLINE || selection == ' ') {
			return selection;
		}
	}
}

void print_whether_roll(int *should_reroll, int die_num) {
	if (!should_reroll[die_num]) {
		print_no_roll(die_num); // printing [NO ROLL] message
	}
	else {
		clear_no_roll(die_num); // clearing [NO ROLL] message
	}
}

void print_no_roll(int die_num) {
	// apologies, this is basically unreadable. it does work though, and i have packaged all the horrid code into a few functions instead of scattering it everywhere

	int column = COL_SIZE * die_num + SHIFT_AMT; // bit of a cursed way to get the column but hey it works
	
	CURSOR_TO_POSITION(ROLL_INFO_ROW - 1, column); // moving the cursor to the right position
	printf(DRAW_MODE"lqqqqqqqk"); // enabling draw mode, then printing the top part of the box in draw mode

	CURSOR_TO_POSITION(ROLL_INFO_ROW, column);
	printf("x"ASCII_MODE"NO ROLL"DRAW_MODE"x"); // printing left side of box, then disabling draw mode, printing NO ROLL, reenabling draw mode, and printing right side of box

	CURSOR_TO_POSITION(ROLL_INFO_ROW + 1, column);
	printf("mqqqqqqqj"ASCII_MODE); // printing bottom of box, then disabling draw mode
}

void clear_no_roll(int die_num) {
	// this is also basically unreadable

	int column = COL_SIZE * die_num + SHIFT_AMT;

	CURSOR_TO_POSITION(ROLL_INFO_ROW - 1, column);
	printf("         ");

	CURSOR_TO_POSITION(ROLL_INFO_ROW, column);
	printf("         ");

	CURSOR_TO_POSITION(ROLL_INFO_ROW + 1, column);
	printf("         ");
}
