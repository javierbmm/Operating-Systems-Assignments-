//
// Created by Olívia Rey Pellicer on 22/10/2019.
//


#include "fileManager.h"

FileData getFileData (const char * filename) {
    FileData data;
    int f, i = 0, j = 0;
    char aux;
    char* word;
    word [0] = '\0';
    f = open (filename, O_RDONLY);
 /*   while (read(f, &aux, 1) >= 0) {
        if (aux != '\n') {
            word[i] = aux;
            i++;
            word[i] = '\0';
        } else {
            i = 0;
            switch (j) {
                case 0:
                    data.user_name = word;
                    break;
                case 1:

                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
            }
            memset(word, '\0', strlen(word));
        }
    }*/
    while (read(f, &aux, 1) >= 0) { // 0 reached end of fie?
        switch (i) {
            case 0:
                data.user_name = word;
                break;
            case 1:
                data.audio_folder = word;
                break;
            case 2:
                data.ip = word;
                break;
            case 3:
                data.port = word;
                break;
            case 4:
                data.web_ip = word;
                break;
            case 5:
                data.init_port = word;
                break;
            case 6:
                data.final_port = word;
                break;
        }
        i++;
    }
    return data;
}
