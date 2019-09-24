CC=gcc
CFLAGS= -Wall -Wextra -I.
DEPS = fileManager.h driversManager.h
OBJ = main.o fileManager.o driversManager.o

%.o: %.c $(DEPS)
    @echo "Compiling project"
    $(CC) -o $@ $< $(CFLAGS)

main: $(OBJ)
    @echo "Working on main"
    $(CC) -o $@ $^ $(CFLAGS)
    @echo "Done!"

.PHONY: clean

clean:
    @echo "Cleaning up"
    rm -f *.o