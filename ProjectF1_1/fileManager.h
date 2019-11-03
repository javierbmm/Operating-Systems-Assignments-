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

FileData getFileData (const char * filename);


#endif //PROJECTF1_1_FILEMANAGER_H
