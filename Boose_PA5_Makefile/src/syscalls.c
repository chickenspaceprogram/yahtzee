#include "syscalls.h"

#ifndef _WIN32

int unix_getch(void) {
	struct termios prev_settings, non_canon;
	tcgetattr(STDIN_FILENO, &prev_settings);
	non_canon = prev_settings;

	// setting both the bits at the ICANON place and the ECHO place to 1
	// ICANON controls whether terminal input is buffered by lines (meaning that, when set to 0, this program can read characters immediately on keypress without waiting for [Enter] to be pressed)
	// ECHO controls whether keypresses are echoed to the terminal; when set to 0, nothing gets displayed
	tcflag_t flags = ICANON | ECHO;

	// flipping the bits of `flags` and binary-ANDing it with the currently-set flags to force the ICANON and ECHO bits to 0 and leave all other bits unchanged
	non_canon.c_lflag &= (~(flags));

	// setting the terminal settings to our new settings
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &non_canon);

	// getting a character from stdin
	int char_gotten = getchar();

	// resetting terminal settings
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &prev_settings);

	return char_gotten;
}

#endif