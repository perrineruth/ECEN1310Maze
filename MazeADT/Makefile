# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -g
PROG = printMaze
SRC = $(PROG).c maze.c
HDR = maze.h
OBJ = $(SRC:.c=.o)

# Targets
$(PROG): $(OBJ)
$(OBJ): $(HDR)
TAGS: $(SRC) $(HDR)
	etags $^
.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJ)
