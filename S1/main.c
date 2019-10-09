#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define CERTIFICATE "------ Certificate of loser ------\n\n"
#define LOST "You have lost a total of "
#define LOST2 " seconds!\n\n"
#define SIGNATURE "Alice and Bob\n"
int totalTime = -1;
int numAttempts = 0;
int shouldExit = 0;

void ksighandler(int signum)
{
    switch (signum)
    {
        char* msg1;
        char* msg2;
        char* msg3;
        char* msg4;
        char* msg5;
        char* msg6;
        char* msg7;
        char* msg8;
        char* msg9;
        char* msg10;
        char* msg11;
        char* msg12;
        char* msg13;
        char* msg14;

        case SIGINT:
            msg1 = "\nI  have  received  a  SIGINT,  but  that  will  not  end  the program! ";
            write(1, msg1, strlen(msg1) );
            break;
        case SIGQUIT:
            msg14 = "\nI  have  received  a  SIGQUIT,  but  that  will  not  end  the program! ";
            write(1, msg14, strlen(msg14) );
            break;
        case SIGHUP:
            msg2 = "\nI  have  received  a  SIGHUP,  but  that  will  not  end  the program! ";
            write(1, msg2, strlen(msg2) );
            break;
        case SIGILL:
            msg3 = "\nI  have  received  a  SIGILL,  but  that  will  not  end  the program! ";
            write(1, msg3, strlen(msg3) );
            break;
        case SIGTRAP:
            msg4 = "\nI  have  received  a  SIGTRAP,  but  that  will  not  end  the program! ";
            write(1, msg4, strlen(msg4) );
            break;
        case SIGABRT:
            msg5 = "\nI  have  received  a  SIGABRT,  but  that  will  not  end  the program! ";
            write(1, msg5, strlen(msg5) );
            break;
        case SIGBUS:
            msg6 = "\nI  have  received  a  SIGBUS,  but  that  will  not  end  the program! ";
            write(1, msg6, strlen(msg6) );
            break;
        case SIGFPE:
            msg7 = "\nI  have  received  a  SIGFPE,  but  that  will  not  end  the program! ";
            write(1, msg7, strlen(msg7) );
            break;
        case SIGUSR1:
            msg8 = "\nI  have  received  a  SIGUSR1,  but  that  will  not  end  the program! ";
            write(1, msg8, strlen(msg8) );
            break;
        case SIGSEGV:
            msg9 = "\nI  have  received  a  SIGSEGV,  but  that  will  not  end  the program! ";
            write(1, msg9, strlen(msg9) );
            break;
        case SIGPIPE:
            msg10 = "\nI  have  received  a  SIGPIPE,  but  that  will  not  end  the program! ";
            write(1, msg10, strlen(msg10) );
            break;
        case SIGTERM:
            msg11 = "\nI  have  received  a  SIGTERM,  but  that  will  not  end  the program! ";
            write(1, msg11, strlen(msg11) );
            break;
        case SIGCHLD:
            msg12 = "\nI  have  received  a  SIGCHLD,  but  that  will  not  end  the program! ",
                    write(1, msg12, strlen(msg12) );
            break;
        case SIGCONT:
            msg13 = "\nI  have  received  a  SIGCONT,  but  that  will  not  end  the program! ";
            write(1, msg13, strlen(msg13) );
            break;
    };
    numAttempts++;
}
void myWrite () {
    int f = open("Certificate.prank", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    write(f, CERTIFICATE, strlen(CERTIFICATE)  );
    write (f, LOST, strlen(LOST));
    char time [10] = "\0";
    sprintf(time, "%d" , totalTime);
    write (f, time, strlen(time));
    write (f, LOST2, strlen(LOST2));
    write (f, SIGNATURE, strlen(SIGNATURE));
    close(f);
}
void sigusrhandler(){
    char* msg1 = "\nI received a SIGUSR2, you were lucky, you found it after ";
    char* msg2 = " attempts... Finishing the program!\nYou have won a lost time certificate! It has been stored as Certificate.prank :)\n";

    write(1, msg1, strlen(msg1));
    char buffer[10];
    sprintf(buffer,"%d", numAttempts);
    write(1, buffer, strlen(buffer));
    write(1, msg2, strlen(msg2));
    shouldExit = 1;
}

void alarm_handler(){
    totalTime++;
    char* msg1 = "\nYou have lost ";
    char* msg2 = " seconds.";
    write(1, msg1, strlen(msg1));
    char buffer[10];
    sprintf(buffer,"%d", totalTime);
    write(1, buffer, strlen(buffer));
    write(1, msg2, strlen(msg2));

    alarm(1);
}

int main() {
    int i;

    /* doing 'kill -l' at the shell, we can see there are 64 different signals...
     * we will reprogram all of them in order to execute the ksighandler method
     */
    for (i = 1; i <= 64; i++)
    {
        signal(i, ksighandler);
    }

    signal(SIGALRM, alarm_handler);
    signal(SIGUSR2, sigusrhandler);
    /* Program an alarm in order to receive a SIGALRM (14) after 30 seconds.
     */
    alarm(1);

    /* We're doing an infinite loop in order to see our process PID,
     * so we can send him any signal we want.
     */
    //pause in a loop

    while(shouldExit == 0){
        pause();
    }

    myWrite();

    return 0;
}