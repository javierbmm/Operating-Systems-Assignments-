//
// Created by Olívia Rey Pellicer on 22/10/2019.
//

#ifndef PROJECTF1_1_FILEMANAGER_H

#define PROJECTF1_1_FILEMANAGER_H
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef struct  {
char * user_name;
char * audio_folder;
char * ip;
char * port;
char * web_ip;
char * init_port;
char * final_port;
} FileData;

int getSizeOfLine(int file, char charLimit);
int readUntilLimit(int file, char** line, char limit);
void skipDelimiter(int file, char delimiter);
FileData getFileData (const int file);


#endif //PROJECTF1_1_FILEMANAGER_H
