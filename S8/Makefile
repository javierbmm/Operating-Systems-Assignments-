CC=gcc-7
CFLAGS= -Wall -Wextra -I.
OBJ = receiver.o sender.o

all: $(OBJ)
	@echo "Working on main"
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Done!"

.PHONY: clean

clean:
	@echo "Cleaning up"
	rm -f *.o
