#pragma once
#include <iostream>
#include "block.h"
#include <zlib.h>
#include <ctime>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>
#include "serverMessage.h"
#include "global.h"

class Miner {
private:
    //Data members
    int id;
    int difficulty_target = 0;
    unsigned int last_hash = 0;
    int height_target = 1;
    int nonce = 0;
    int timestamp;
    int server_pipe; //fd
    int my_pipe; //fd
    int my_log;  //fd
    Block* block;

public:
    //constructor
    Miner(int id,int server_pipe,const char* path);
    //functions
    void update_target_parameters();
    void start_mining();
    unsigned int calculate_hash_code();
    void print_block_params();
};
