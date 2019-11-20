CC=gcc
CFLAGS= -Wall -Wextra -I.
DEPS = fileManager.h parsingInputs.h commandsActions.h
OBJ = main.o fileManager.o parsingInputs.o commandsActions.o

%.o: %.c $(DEPS)
	@echo "Compiling project"
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@echo "Working on main"
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Done!"

.PHONY: clean

clean:
	@echo "Cleaning up"
	rm -f *.o
