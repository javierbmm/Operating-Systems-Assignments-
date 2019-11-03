//
// Created by Olívia Rey Pellicer on 22/10/2019.
//


#include <fileManager.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 256


/* Read the file char by char until it reaches the character specified in charLimit
 *  ARGS: int file
 *  ARGS: char charLimit
 *
 *  @returns-> charPosition: Position (bytes) of the char specified in charLimit
 */
int getSizeOfLine(int file, char charLimit) {
    int charPosition = 0;
    char iteratorChar;  // We use char because it's 1 byte size, so we can count the exact number of bytes
    while(1){
        if(read(file, &iteratorChar, 1) == 0)
            return 0;
        if(iteratorChar == charLimit)
            break;
        charPosition++;
    };

    return charPosition;
}

int readUntilLimit(int file, char** line, char limit){
    int endOfLinePosition = getSizeOfLine(file, limit);  // Get the number of characters to read

    *line = (char*)realloc(*line,(endOfLinePosition+1)* sizeof(char)); // Assigning enough memory
    // Now we have to go back on the file using read and the same number of bytes from endOfLinePosition
    lseek(file, -endOfLinePosition-1, SEEK_CUR);
    read(file, *line, endOfLinePosition);
    (*line)[endOfLinePosition] = '\0';

    return endOfLinePosition;
}
/* skipDelimiter: Reads all the incomming delimiters until it reaches one non-delimiter,
 * then go back one byte
*/
void skipDelimiter(int file, char delimiter){
    char iteratorChar;

    while(read(file, &iteratorChar, 1) > 0){
        if(iteratorChar == delimiter) // if delimiter, keep going
            continue;
        else {                          // go back when isn't delimiter
            lseek(file, -1, SEEK_CUR);
            return;
        }
    }
}

FileData getFileData (const int file) {
    FileData data;
    int i = 0;
    char delimiter = '\n';
    char *word = malloc(1);
    int size_of_word = 1;

    while (size_of_word> 0) { // 0 reached end of fie?
        size_of_word = readUntilLimit(file, &word, delimiter) ;
        char *word_cpy = malloc(size_of_word+1);
        strcpy(word_cpy, word);

        switch (i) {
            case 0:
                data.user_name = word_cpy;
                break;
            case 1:
                data.audio_folder = word_cpy;
                break;
            case 2:
                data.ip = word_cpy;
                break;
            case 3:
                data.port = word_cpy;
                break;
            case 4:
                data.web_ip = word_cpy;
                break;
            case 5:
                data.init_port = word_cpy;
                break;
            case 6:
                data.final_port = word_cpy;
                break;
        };

        skipDelimiter(file, delimiter);
        i++;
        // Empty-ing the buffer
        memset(word,0,strlen(word));
        word[0] = '\0';

    }

    free(word);
    //close(f);

    return data;
}
