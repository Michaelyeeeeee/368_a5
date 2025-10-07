CC = gcc
CFLAGS = -Wall -g -s
SRCS = a5.c coordinates.c  dimensions.c post_order.c tree.c
OBJS = $(SRCS:.c=.o)
TARGET = a5

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)