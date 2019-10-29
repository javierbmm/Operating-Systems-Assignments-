all: project

project: main.o fileManager.o
    gcc main.o fileManager.o -o project

main.o: main.c
    gcc -c main.c

fileManager.o: fileManager.c
    gcc -c fileManager.c