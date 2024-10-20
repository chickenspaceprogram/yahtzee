#include "syscalls.h"

#ifndef _WIN32

int unix_getch(void) {

	// stty is a POSIX utility that sets terminal settings. Using it is probably slower and worse than manipulating the settings manually, but I was lazy.
	// credit for this goes to the manpage for stty, it explained things well enough for me to piece this together
	system("stty raw"); // makes the terminal not buffer input, so we get characters immediately as they are typed
	int return_char = getchar();
	system("stty cooked"); // resets the terminal to buffer input again like normal
	return return_char;
}

#endif