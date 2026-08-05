CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude -g -O2

SRC=src/arena.c
TARGET=test_arena

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
