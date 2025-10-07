CC = gcc
CFLAGS = -Wall -g -s
SRCS = a5.c tree.c post_order.c dimensions.c coordinates.c
OBJS = $(SRCS:.c=.o)
TARGET = a5

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)