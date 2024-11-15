#include "ui.h"
#include "menu.h"
#include "yahtzee.h"
#include <stdio.h>

typedef enum MainMenu {
	PRINT_RULES = 1,
	PLAY_GAME,
	EXIT
} MainMenu;

int main(void) {
	seed_rand();

	// initializing a struct containing the options for the main menu
	option main_menu_options[] = {
		{.is_valid = 0, .msg = "\0", .selection_char = '\0'},
		{.is_valid = 1, .msg = DRAW_MODE"x"ASCII_MODE"1 : Print gamerules         "DRAW_MODE"x"ASCII_MODE"\0", .selection_char = '1'},
		{.is_valid = 1, .msg = DRAW_MODE"x"ASCII_MODE"2 : Start a game of Yahtzee "DRAW_MODE"x"ASCII_MODE"\0", .selection_char = '2'},
		{.is_valid = 1, .msg = DRAW_MODE"x"ASCII_MODE"3 : Exit                    "DRAW_MODE"x"ASCII_MODE"\0", .selection_char = '3'}
	};

	// keep looping until
	while (1) {
		// displaying menu header
		CLEAR_SCREEN(); HIDE_CURSOR();
		printf("Please select an option by pressing the key next to it, using the arrow keys, or pressing k or j.\n\nThen, press [Enter] to save your selection.\n\n");
		printf("  "DRAW_MODE"lqqqqqqqqqqqqqqqqqqqqqqqqqqqqk\n"ASCII_MODE);
		printf("  "DRAW_MODE"x"ASCII_MODE" PA 5 - Yahtzee - Main Menu "DRAW_MODE"x\n"ASCII_MODE);
		printf("  "DRAW_MODE"tqqqqqqqqqqqqqqqqqqqqqqqqqqqqu\n"ASCII_MODE);

		// displaying menu, getting user selection
		MainMenu selection = (MainMenu) menu(main_menu_options, DRAW_MODE"  mqqqqqqqqqqqqqqqqqqqqqqqqqqqqj"ASCII_MODE, 4);
		CLEAR_SCREEN(); SHOW_CURSOR();

		// deciding what to do based on the user's selection
		switch(selection) {
			case PRINT_RULES:
			
#ifdef _WIN32 // if the program is compiled on Windows, just print the rules and wait for user input
				HIDE_CURSOR();
				print_file("rules.txt", 0);
				(void) GETCH(); // just used to pause prgm execution
				SHOW_CURSOR();
#else
				system("less rules.txt"); // `less` exists on Unix systems and is prettier than just printing and waiting for user input
#endif
				break;
			case PLAY_GAME:
				play_yahtzee_game();
				break;
			case EXIT:
				printf("Yahtzee exiting . . . \n");
				return 0;
				break;
		}
	}
}