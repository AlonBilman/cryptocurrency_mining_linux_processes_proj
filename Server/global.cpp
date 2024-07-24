#include "global.h"

 const char* THIS_PATH = "/home/alon/Desktop/Task3_mtaCoin/linux_processes_task3/";
 const char* SERVER_PIPE_NAME = "server_pipe";
 const char* CONF_NAME = "mtacoin.conf";
 const char* BASE_PIPE_NAME = "miner_pipe_";
 const char* LOG_NAME = "mtacoin.log";

void check_fd(int fd, int my_log, int my_pipe)
{
     if(fd==-1) {
        //will be written in the log-file.
        perror("Error with fd");
        if(my_log!=-1)
            close(my_log);
        if(my_pipe!=-1)
            close(my_pipe);
     }
        //exit with an error flag.
          exit(EXIT_FAILURE);
}
