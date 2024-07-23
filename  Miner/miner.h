#pragma once
#include <iostream>
#include "block.h"
#include "server.h"
#include <zlib.h>
#include <ctime>
#include "global.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <string>

class Miner {
private:
    //Data members
    int id;
    int difficulty_target = 0;
    unsigned int last_hash = 0;
    int height_target = 1;
    int nonce = 0;
    int timestamp;
    int miner_pipe;
    std::string my_path = "/tmp/miner_pipe_";

public:

    //constructor
    Miner(int id);

    //functions
    void update_target_parameters();

    virtual void start_mining();
    unsigned int calculate_hash_code();
};
