CC=gcc-7
CFLAGS= -g -pthread -Wall -Wextra -I.
DEPS = protocol.h connections.h fileManager.h parsingInputs.h commandsActions.h list.h
OBJ = main.o connections.o fileManager.o parsingInputs.o commandsActions.o list.o protocol.o

%.o: %.c $(DEPS)
	@echo "Compiling project"
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	@echo "Working on main"
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Done!"

.PHONY: clean

clean:
	@echo "Cleaning up"
	rm -f *.o
