#include "ui.h"
#include "ascii-dice.h"
#include "yahtzee.h"
#include <stdio.h>


int main(void) {
	seed_rand();
	play_yahtzee_game();
}