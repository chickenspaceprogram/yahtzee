#ifndef ESCAPE_CODES_H
#define ESCAPE_CODES_H


// windows actually supports ANSI escape codes! good job microsoft, it only took you until 2016

#define HIDE_CURSOR()					printf("\x1B[?25l") // Hides the cursor
#define SHOW_CURSOR()					printf("\x1B[?25h") // Shows the cursor
#define RESET_COLORS()					printf("\x1B[0m") // Resets colors (also resets things like bold text)
#define INVERT_COLORS()					printf("\x1B[47m\x1B[30m") // Inverts colors. Makes background white and text black.
#define BOLD_TEXT()						printf("\x1B[1m") // Makes text bold
#define SAVE_CURSOR()					printf("\x1B 7") // Saves the cursor's position
#define LOAD_CURSOR()					printf("\x1B 8") // Loads the cursor from the saved position in memory
#define CURSOR_TO_POSITION(row, col)	printf("\x1B[%d;%dH", row, col) // Moves cursor to position (row, col).
#define CURSOR_TO_COL(col)              printf("\x1B[%dG", col) // Moves cursor to column `col`.
#define CURSOR_UP(rows)                 printf("\x1B[%dA", rows) // Moves cursor up by `rows` lines.
#define CURSOR_DOWN(rows)               printf("\x1B[%dB", rows) // Moves cursor down by `rows` lines.

#define DRAW_MODE						"\x1B(0" // Puts the terminal into draw mode, where line-drawing characters are drawn instead of ASCII characters
#define ASCII_MODE						"\x1B(B" // Takes the terminal out of line-drawing mode and puts it back in ASCII mode.

// the last two are string literals since that was less messy

#endif