# "we have Visual Studio at home"
# Description: A Makefile for automatically building simple C projects.
# Author: chickenspaceprogram

# To compile, run `make` or `make all`
# To run, run `make run`.
# To delete compiled filed, run `make clean`.
# To export the project as a .zip file, run `make zip`.
# To make a new project, run `make new`.


# comments are here since I will have to review this in 6 months and will wonder what it's doing

.PHONY: all clean objects run zip build new

TARGET := target
BIN := $(TARGET)#			binary directory
OBJ := $(TARGET)/obj#		object directory
SRC := src#					source directory
NAME := Boose_PA5#			project name

ALL_SRCS := $(wildcard $(SRC)/*.c) # gets a space separated list of every source file in src/

# replaces src/ with target/obj/ and .c with .o for each thing in ALL_SRCS
ALL_OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(ALL_SRCS)) # definitely readable 

# linking source files into a single executable
all: build $(BIN)
	@printf "\nBuild completed successfully!\n"


build: $(ALL_OBJS)
	$(CC) $^ -o $(BIN)/$(NAME)

# compiling source files
$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) -Wall -c -I$(SRC) $< -o $@

# Making target directories

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

clean: 
	rm -rf target
	rm -f $(NAME).zip

run: all
	./$(BIN)/$(NAME)

zip: clean
	mkdir $(NAME)
	cp -R $(SRC) $(NAME)
	cp Makefile $(NAME)
	zip -r $(NAME).zip $(NAME)
	rm -rf $(NAME)

new: 
	mkdir src
	printf ".DS_Store\ntarget\n$(NAME).zip" >> .gitignore