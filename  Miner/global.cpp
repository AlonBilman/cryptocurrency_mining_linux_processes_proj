#include "global.h"

 const char* THIS_PATH = "/home/alon/Desktop/Task3_mtaCoin/linux_processes_task3/";
 const char* SERVER_PIPE_NAME = "server_pipe";
 const char* CONF_NAME = "mtacoin.conf";
 const char* BASE_PIPE_NAME = "miner_pipe_";
 const char* LOG_NAME = "mtacoin.log";

void check_fd(int fd, int* fd_s ,int size)
{
     if(fd==-1) {
        //will be written in the log-file.
        perror("Error with fd");
        if(fd_s!=nullptr){ //closing all the opened fds.
             for(int i=0;i<size;++i)
                {
                    if(fd_s[i]!=-1) // if we opend it. (init -1 when creating a miner)
                        close(fd_s[i]);
                }
        }
        //exit with an error flag.
        exit(EXIT_FAILURE);
    }
}