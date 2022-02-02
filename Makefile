
CC=gcc

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs compile

dirs: 
	mkdir -p ./$(BIN)

run: all
	$(BIN)/main

compile: $(OBJ)
	$(CC) -o $(BIN)/main $^


%.o: %.c
	$(CC) -o $@ -c $<


clean:
	rm -rf $(BIN) $(OBJ)
