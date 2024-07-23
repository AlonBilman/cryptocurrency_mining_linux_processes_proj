#include <iostream>
#include <cstring>
#include "miner.h"
#include "global.h"

int main(int argc, char *argv[]) {

    //get the server pipe path:
    std::string server_path = THIS_PATH; 
    server_path.append(SERVER_PIPE_NAME);
    std::string miners_count = THIS_PATH;
    miners_count.append(MINERS_COUNT);

    //open the server file to write
    int fd_server = open(server_path.c_str(),O_WRONLY);
    check_fd(fd_server);

    //open the miners count file in order to set id.
    int fd_miners_count = open(miners_count.c_str(),O_RDWR | O_NONBLOCK);
    check_fd(fd_miners_count);
    int id;
    check_fd(read(fd_miners_count,&id,sizeof(int)),CLOSE);
    ++id;
    check_fd(write(fd_miners_count,&id,sizeof(int)),CLOSE);

    close(fd_miners_count); //close the counter file.
    
    Miner miner(id,fd_server,THIS_PATH);
    miner.start_mining();
     
     return 0;
}
