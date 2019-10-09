//
// Created by javif on 9/22/2019.
//

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fileManager.h>

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

int readUntilLimit(int file, void* line, char limit){
    int endOfLinePosition = getSizeOfLine(file, limit);

    line = realloc(line,(endOfLinePosition)*sizeof(line));
    // Now we have to go back on the file using read and the same number of bytes from endOfLinePosition
    lseek(file, -endOfLinePosition-1, SEEK_CUR);
    read(file, line, endOfLinePosition);

    return endOfLinePosition;
}

int readLine(int file, void* line){
    char endOfLine = '/';

    return readUntilLimit(file, &*line, endOfLine);
}

int readPilotName(int file, void *line){
    char delimiter = '-';

    return readUntilLimit(file, line, delimiter);
}

/* readDelimiter: Reads all the incomming delimiters until it reaches one non-delimiter,
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
