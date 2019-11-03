#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#define FALSE 0
#define TRUE 1
#define BUFF_SIZE 101
typedef struct Step{
    int id;
    char *description;
    int time;
    int prevTask;
    int isFinished;
}step;
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

int getId(int file){
    char* line = calloc(0,0);
    readUntilLimit(file, line, '-');
    int id = atoi(&line[1]);

    return id;
}
char* getDesc(int file){
    char* line = calloc(0,0);
    readUntilLimit(file, line, '-');

    return line;
}
int getTime(int file){
    char* line = calloc(0,0);
    readUntilLimit(file, line, '-');
    int time = atoi(line);

    return time;
}

int getPrevTask(int file){
    char* line = calloc(0,0);
    int prevTask;
    if(readUntilLimit(file, line, '\n') > 0)
        prevTask = atoi(&line[1]);
    else
        prevTask = -1;

    return prevTask;
}

int getData(int file, step *newStep){
    newStep = realloc(newStep, sizeof(step)*1);
    char *aux = malloc(2);
    int endOfLinePosition = readUntilLimit(file, aux, EOF);
    if(endOfLinePosition <= 1)
        return -1;

    lseek(file, -endOfLinePosition-1, SEEK_CUR);
    // initialazing
    newStep->isFinished = FALSE;
    newStep->id = getId(file);
    skipDelimiter(file, '-');
    char *auxDesc = getDesc(file);
    newStep->description = auxDesc;
    skipDelimiter(file, '-');
    newStep->time = getTime(file);
    skipDelimiter(file, '-');
    newStep->prevTask = getPrevTask(file);
    skipDelimiter(file, '\n');

    return 1;
}

 void* th_func ( void *vargp){
     char buffer[BUFF_SIZE];
     step *newStep = vargp;
     sprintf(buffer, "Starting: %s \n",newStep->description);
     write(1, buffer, strlen(buffer));

     sleep(newStep->time);
     newStep->isFinished = TRUE;

     sprintf(buffer, "Finished: %s \n",newStep->description);
     write(1, buffer, strlen(buffer));

     return NULL;
 }

int strcpyexcept(char* src, char* dest, char except, char substitute){
    int size = strlen(src);
    char* cpysrc = (char*)malloc(sizeof(char)*size);
    strcpy(cpysrc, src);

    int i;
    for(i=0; i<size; i++){
        if(cpysrc[i] == except)
            cpysrc[i] = substitute;
    }

    strcpy(dest, cpysrc);

    free(cpysrc);
    cpysrc = NULL;

    return size;
};
int main() {
    char buffer[BUFF_SIZE];
    // Asking for file
    int file;
    char filename[BUFF_SIZE];
    while(1) {
        sprintf(buffer, "Enter plate to cook:\n");
        write(1, buffer, strlen(buffer));
        read(1, buffer, 30);
        strcpyexcept(buffer, filename, '\n', '\0');
        strcat(filename, ".txt");
        fflush(stdout);
        file = open(filename, O_RDONLY);
        if (file == -1) {
            sprintf(buffer, "Unknown dish. Try again.\n");
            write(1, buffer, strlen(buffer));
        } else
            break;
    }


    // Getting steps
    step *steps = calloc(0, 0); /* fill this */
    step *newStep = calloc(0,0);
    int numSteps = 0;

    while(getData(file, newStep) != -1){
        printf("aja\n");
        numSteps++;
        steps = realloc(steps, sizeof(step) * numSteps);
        steps[numSteps-1] = *newStep;
    }

    pthread_t thread_id[numSteps];

    // Stepping with threads
    int i = 0, numFinishedSteps = 0;
    while(numFinishedSteps <= numSteps){
        if(steps[i].prevTask >= 0){
            if(steps[steps[i].prevTask].isFinished){
                pthread_create(&thread_id[i], NULL, th_func, (void*)&steps[i]);
                numFinishedSteps++;
            }
        }
    }

    for(i=0; i<numSteps; i++){
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}