# PA 5 readme

To run this, either build the code using the provided Makefile (cd into Boose_PA5_Makefile, enter `make` to build, and ./Boose_PA5 to run) or build it with Microsoft Visual Studio. The code has been tested on both MacOS and Windows, and it should work fine on other *nix systems as well (although I haven't bothered to test it).

To select items in a menu, use the arrow keys or press the key that corresponds to the item. Once you have selected the desired item, press [Enter].

I could've/should've just used the `curses` library, but hey, this works, and I'm not going to bother rewriting it.

Most of the game code is in the yahtzee.c/h and dice.c/h files, and the main menu is in main.c. 
Some of the functions are declared as static in the .c files to make them inaccessible to other parts of the program (and to make the header files more readable).

A description is provided below of all files in this project, for reference:

| File           | Description                                                 |
| -------------- | ----------------------------------------------------------- |
| yahtzee.c/h    | Handles scoring dice and playing through a game of Yahtzee  |
| dice.c/h       | Handles rolling dice and finding the frequency of each roll |
| ascii-dice.c/h | Handles printing the ASCII-art dice                         |
| menu.c/h       | Handles displaying and selecting items from menus           |
| ui.c/h         | Handles the die reroll selection menu and general UI tasks  |
| escape_codes.h | Provides macros for ANSI escape sequences                   |
| terminal.c/h   | Provides macros for commonly-used terminal UI functions     |
| main.c         | Handles displaying the main menu and printing rules         |