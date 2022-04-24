#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){
    int fd_pipe = open("ex2", O_WRONLY);

    for(int i = 0; i < argc; i++){
        write(fd_pipe, argv[i], strlen(argv[i]));
        write(fd_pipe, " ", 1);
    }
    write(fd_pipe, "\n", 1);

    //sleep(10);
    close(fd_pipe);
    return 0;
}