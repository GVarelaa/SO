#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    mkfifo("ex2", 0640);

    int fd_pipe = open("ex2", O_RDONLY);
    int fd_log = open("log.txt", O_CREAT | O_WRONLY, 0640);
    
    while(1){
        int n_bytes = 0;
        char buffer[1024];
        while((n_bytes = read(fd_pipe, buffer, 1024)) > 0){
            write(fd_log, buffer, n_bytes);
        }
    }

    close(fd_pipe);
    close(fd_log);
    return 0;
}