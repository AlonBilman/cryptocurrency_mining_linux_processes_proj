#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include "server.h"



int main(int argc, char *argv[]) {

    Server server;
    server.start();
}
