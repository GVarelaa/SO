#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    char buffer[1024];
    int fd = open("fifo", O_WRONLY);
    int nr_bytes = 0;

    while((nr_bytes = read(0, buffer, 1024)) > 0){
        write(fd, buffer, nr_bytes);
    }

    close(fd);
    return 0;
}