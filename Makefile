
CC = gcc

CFLAGS = -std=c11 -g -D_POSIX_C_SOURCE
LDFLAGS = -g

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs compile

dirs: 
	mkdir -p ./$(BIN)

run: all
	$(BIN)/main

compile: $(OBJ)
	$(CC) -o $(BIN)/main $^ $(LDFLAGS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf $(BIN) $(OBJ)
