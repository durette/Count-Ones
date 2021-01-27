CC=gcc
CFLAGS=-Wall -Wextra -march=native -mtune=native -O2
all: countones

countones:
        $(CC) $(CFLAGS) countones.c -ocountones
clean:
        rm countones
