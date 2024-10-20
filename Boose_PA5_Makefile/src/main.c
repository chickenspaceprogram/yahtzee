#include "ui.h"
#include "ascii-dice.h"
#include "yahtzee.h"
#include "syscalls.h"
#include <stdio.h>

int main(void) {
	// i do not know why this needs an empty line to not break but it does ;-;
	seed_rand();
	play_yahtzee_game();
}