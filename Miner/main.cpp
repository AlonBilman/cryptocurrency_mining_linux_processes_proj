#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include "miner.h"
#include "global.h"

int create_miner_id();


int main(int argc, char *argv[]) {
    //get the server pipe path:
    std::string server_path = MAIN_PATH;
    server_path.append(SERVER_PIPE_NAME);
    //open the server file to write
    int fd_server = open(server_path.c_str(),O_WRONLY);
    check_fd(fd_server,nullptr,0);
    int id = create_miner_id();
    
    Miner miner(id,fd_server);
    miner.start_mining();
     
     return 0;
}


//find the max id, return id+1


int create_miner_id() 
{
    int new_id =0; 
    for(auto& name : std::filesystem::directory_iterator(MAIN_PATH))
    {
        if(name.is_fifo())
        {
            std::string get_name = name.path().filename().string(); //get the name and convert it to a string.
            //check if the filename start with "miner_pipe_" and extract the number with sscanf
            int number=0;
            if (std::sscanf(get_name.c_str(),"miner_pipe_%d",&number) == 1) 
            {
                if (number > new_id) 
                    new_id = number;
            }
        }
    }
    //if nothing was found, return 1. 
    return ++new_id;
}
