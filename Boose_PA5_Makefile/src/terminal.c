#include "terminal.h"

#ifndef _WIN32

// credit goes to the manpage for termios for explaining how this stuff works
int unix_getch(void) {
	// declaring structs that contain the terminal information
	struct termios prev_settings, non_canon;

	// getting the settings of the current tty, setting both structs to that information
	tcgetattr(STDIN_FILENO, &prev_settings);
	non_canon = prev_settings;

	// setting both the bits at the ICANON place and the ECHO place to 1, then flipping all bits
	tcflag_t flags = ~(ICANON | ECHO);

	// binary AND-ing `flags` with the currently-set flags forces the bits at the ICANON and ECHO places to 0, and leaves all others unchanged
	non_canon.c_lflag = flags & non_canon.c_lflag;

	tcsetattr(STDIN_FILENO, TCSANOW, &non_canon);
	int char_gotten = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &prev_settings);

	return char_gotten;
}

#endif