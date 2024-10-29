CC = gcc
CFLAGS = -Wall -I./include
LDFLAGS =

SRC = src/main.c src/keyboard.c src/screen.c src/timer.c
OBJ = $(SRC:.c=.o)
TARGET = snake_game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)