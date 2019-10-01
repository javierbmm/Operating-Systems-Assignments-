//
// Created by javif on 9/22/2019.
//

#ifndef FIRSTPRACTICE1_FILEMANAGER_H
#define FIRSTPRACTICE1_FILEMANAGER_H

int getSizeOfLine(int file, char charLimit);


int readUntilLimit(int file, void* line, char limit);


int readLine(int file, void* line);


int readPilotName(int file, void *line);


void skipDelimiter(int file, char delimiter);

#endif //FIRSTPRACTICE1_FILEMANAGER_H
