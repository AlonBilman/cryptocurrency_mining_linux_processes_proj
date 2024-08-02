#pragma once
#include <iostream>
#include "block.h"
#include <zlib.h>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>
#include "serverMessage.h"
#include "global.h"

enum 
{
    SERVER_PIPE,
    MY_PIPE,
    LOG_FILE,
    SIZE
};

class Miner {
private:
    //Data members
    int id;
    int difficulty_target = 0;
    unsigned int last_hash = 0;
    int height_target = 1;
    int nonce = 0;
    int timestamp;
    int fd[SIZE]={-1}; // fd arr
    Block block; //sends by the server. 

public:
    //constructor
    Miner(int id,int server_pipe);
    //functions
    void update_target_parameters();
    void start_mining();
    unsigned int calculate_hash_code();
    void print_block_params();
};
