#include "global.h"

 const char* THIS_PATH = "/home/alon/Desktop/Task3_mtaCoin/linux_processes_task3/";
 const char* SERVER_PIPE_NAME = "server_pipe";
 const char* CONF_NAME = "mtacoin.conf";
 const char* MINERS_COUNT = "miners_count";

void check_fd(int fd)
{
    if(fd==-1) {
        perror("Error with fd");
        exit(EXIT_FAILURE);
    }
}
void check_fd(int fd, bool close_)
{
     if(fd==-1) {
        perror("Error with fd");
        close(fd);
        exit(EXIT_FAILURE);
    }
}