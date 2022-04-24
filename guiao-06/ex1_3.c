#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    char buffer[1024];
    int fd = open("fifo", O_RDONLY);
    int nr_bytes = 0;

    while((nr_bytes = read(fd, buffer, 1024)) > 0){
        write(1, buffer, nr_bytes);
    }

    close(fd);
    return 0;
}