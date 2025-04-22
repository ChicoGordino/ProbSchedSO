CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./src
LDFLAGS = -lm

SRC = $(wildcard src/*.c) $(wildcard src/scheduler/*.c)
OBJ = $(SRC:.c=.o)
EXEC = probsched

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
