CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./src
LDFLAGS = -lm

SRC = $(wildcard src/*.c) $(wildcard src/scheduler/*.c)
OBJ = $(SRC:.c=.o)
EXEC = probsched
CONFIG = "data/config.txt"

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

run: clean all
	./$(EXEC) $(CONFIG)
