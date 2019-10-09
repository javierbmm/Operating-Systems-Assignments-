//
// Created by Olívia Rey Pellicer on 03/10/2019.
//

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
void kctrlc(int signum)
{
    printf("I've received a cntrl + c (%d). I should abort.\n", signum);
}

void ksigalrm(int signum)
{
    printf("I've received a sigalrm (%d).\n", signum);
}

void kgeneric(int signum)
{
    switch
    printf("I've received an unknown signal (%d)\n", signum);
}*/

/* This method is used to handle different types of signals, and execute a given
 * method depending on which one has received
 */




