CC=gcc
CFLAGS=-Wall
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC=exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(EXEC) $(OBJ)
