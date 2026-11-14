CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 
TARGET = grafbejaro

SRCS = main.c graf.c fileIo.c algoritmus.c menu.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
