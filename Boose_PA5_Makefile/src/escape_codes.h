#ifndef ESCAPE_CODES_H
#define ESCAPE_CODES_H


// windows actually supports ANSI escape codes! good job microsoft, it only took you until 2016
#define HIDE_CURSOR()					printf("\x1B[?25l")
#define SHOW_CURSOR()					printf("\x1B[?25h")
#define RESET_COLORS()					printf("\x1B[0m")
#define INVERT_COLORS()					printf("\x1B[47m\x1B[30m")
#define BOLD_TEXT()						printf("\x1B[1m")
#define SAVE_CURSOR()					printf("\x1B 7")
#define LOAD_CURSOR()					printf("\x1B 8") // Loads the cursor from the saved position in memory
#define CURSOR_TO_POSITION(row, col)	printf("\x1B[%d;%dH", row, col) // Moves cursor to position (row, col).
#define CURSOR_TO_COL(col)              printf("\x1B[%dG", col) // Moves cursor to column `col`.
#define CURSOR_UP(rows)                 printf("\x1B[%dA", rows) // Moves cursor up by `rows` lines.
#define CURSOR_DOWN(rows)               printf("\x1B[%dB", rows) // Moves cursor down by `rows` lines.
#define DRAW_MODE						"\x1B(0" // C concatenates string literals, and I needed these to be concatenated with other stuff at compiletime for less headaches
#define ASCII_MODE						"\x1B(B"

#endif