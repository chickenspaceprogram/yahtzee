.PHONY: all clean objects


ALL_SRCS := $(wildcard src/*.c) # gets a space separated list of every source file in src/

# replaces src/ with target/obj/ and .c with .o for each thing in ALL_SRCS
ALL_OBJS := $(patsubst src/%.c, target/obj/%.o, $(ALL_SRCS)) # peak readability
all: $(ALL_OBJS)
	$(CC) $^ -o yahtzee

target/obj/%.o: src/%.c target/obj
	$(CC) -Wall -c -Isrc $< -o $@

# Making output paths
target: 
	mkdir target

target/obj: target
	mkdir target/obj

#