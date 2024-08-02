#include "global.h"

 const char* MAIN_PATH = "/mnt/mta/";
 const char* SERVER_PIPE_NAME = "server_pipe";
 const char* CONF_NAME = "mtacoin.conf";
 const char* BASE_PIPE_NAME = "miner_pipe_";
 const char* LOG_NAME = "mtacoinServer.log";
 const char* LOG_PATH = "/var/log/";

void check_fd(int fd, int my_log, int my_pipe)
{
     if(fd==-1) {
        //will be written in the log-file.
       std::cout<<"an error on fd";
        if(my_log!=-1)
            close(my_log);
        if(my_pipe!=-1)
            close(my_pipe);
        
        //exit with an error flag.
          exit(EXIT_FAILURE);
     }
        
}

