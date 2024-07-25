#include "global.h"

 const char* THIS_PATH = "/home/alon/Desktop/mta_files/";
 const char* SERVER_PIPE_NAME = "server_pipe";
 const char* CONF_NAME = "mtacoin.conf";
 const char* BASE_PIPE_NAME = "miner_pipe_";
 const char* LOG_NAME = "mtacoinServer.log";

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
