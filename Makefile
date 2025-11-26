CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lncurses

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = build/scp

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(BIN)
