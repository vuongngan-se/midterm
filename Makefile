CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
OBJS = ls.o print.o cmp.o
TARGET = ls

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

ls.o: ls.c ls.h print.h
	$(CC) $(CFLAGS) -c ls.c

print.o: print.c print.h ls.h
	$(CC) $(CFLAGS) -c print.c

cmp.o: cmp.c ls.h
	$(CC) $(CFLAGS) -c cmp.c

clean:
	rm -f $(OBJS) $(TARGET)
