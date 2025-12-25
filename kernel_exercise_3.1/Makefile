# Makefile for Exercise 3.1 — simple shell

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2
TARGET  := simple_shell
SRC     := simple_shell.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
