#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

int seconds = 0;
int count_ctrl = 0;
int should_exit = 0;

void shutdown_handler(int signum){
    printf("exiting...\n");
    exit(1);
}

void inc_second(int signum){
    seconds++;
    printf("ALRM\n");
    alarm(1);
}

void print_seconds(int signum){
    printf("CTRL+C. seconds: %d\n", seconds);
    count_ctrl++;
}

void sigquit_handler(int signum){
    printf("NUM DE VEZES CTRL : %d\n", count_ctrl);
    printf("exiting...\n");
    should_exit = 1;
}

int main(int argc, char* argv[]){
    
    if(signal(SIGALRM, inc_second)  == SIG_ERR){
        perror("error\n");
        return 1;
    }
    
    if(signal(SIGINT, print_seconds) == SIG_ERR){
        perror("error\n");
        return 1;
    }

    if(signal(SIGQUIT, sigquit_handler) == SIG_ERR){
        perror("error\n");
        return 1;
    }


    printf("getpid : %d\n", getpid());

    alarm(1);
    while(!should_exit){
        printf("exexecuting....\n");
        pause();
    }

    printf("seconds : %d\n", seconds);

    return 0;
}