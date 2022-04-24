#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    mkfifo("fifo", 0666);

    return 0;
}