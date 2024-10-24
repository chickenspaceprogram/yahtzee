#include "ui.h"
#include "menu.h"
#include "yahtzee.h"
#include <stdio.h>


int main(void) {
	seed_rand();
	option main_menu_options[] = {
		{.is_valid = 0, .msg = "\0", .selection_char = '\0'},
		{.is_valid = 1, .msg = DRAW_MODE"x"ASCII_MODE"1 : Print gamerules         "DRAW_MODE"x"ASCII_MODE"\0", .selection_char = '1'},
		{.is_valid = 1, .msg = DRAW_MODE"x"ASCII_MODE"2 : Start a game of Yahtzee "DRAW_MODE"x"ASCII_MODE"\0", .selection_char = '2'},
		{.is_valid = 1, .msg = DRAW_MODE"x"ASCII_MODE"3 : Exit                    "DRAW_MODE"x"ASCII_MODE"\0", .selection_char = '3'}
	};
	while (1) {
		CLEAR_SCREEN();
		HIDE_CURSOR();
		printf("Please select your preferred option by entering the corresponding number or using the arrow keys:\n\n");
		printf("  "DRAW_MODE"lqqqqqqqqqqqqqqqqqqqqqqqqqqqqk\n"ASCII_MODE);
		printf("  "DRAW_MODE"x"ASCII_MODE" PA 5 - Yahtzee - Main Menu "DRAW_MODE"x\n"ASCII_MODE);
		printf("  "DRAW_MODE"tqqqqqqqqqqqqqqqqqqqqqqqqqqqqu\n"ASCII_MODE);
		int selection = menu(main_menu_options, DRAW_MODE"  mqqqqqqqqqqqqqqqqqqqqqqqqqqqqj"ASCII_MODE, 4);
		SHOW_CURSOR();
		CLEAR_SCREEN();
		switch(selection) {
			case 1:
				HIDE_CURSOR();
				print_file("rules.txt", 0);
				(void) GETCH(); // just used to pause prgm execution
				SHOW_CURSOR();
				break;
			case 2:
				play_yahtzee_game();
				break;
			case 3:
				printf("Yahtzee exiting . . . \n");
				return 0;
				break;
		}
	}
}