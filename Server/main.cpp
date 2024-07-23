#include <iostream>
#include "server.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

int main(int argc, char *argv[]) {

    int server_pipe = mkfifo("server_pipe",0666);
    return 0;
}
