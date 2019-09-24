//
// Created by javif on 9/23/2019.
//

#include <stringmanipulation.h>
#include <string.h>
#include <stdlib.h>

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
