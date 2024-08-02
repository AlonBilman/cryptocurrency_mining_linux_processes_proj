#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "block.h"
#include <zlib.h>
#include <fstream>
#include "global.h"
#include <signal.h>


#define MAX_CHAIN_SIZE 100
#define NEW_BLOCK 1
#define CONNECT_REQ 2


class Server {
private:
    //Data members
    int number_of_blocks = 1;
    int difficulty_target;
    std::list<Block> block_chain;
    std::vector<int> miners_pipes;
    int my_pipe;
    int my_log;
    Block next_block;

private: //Private functions

    bool verify_proof_of_work_(Block &block_to_check);

    void add_block_(Block &block_to_add);

    void print_last_block_(Block &block_added);

public:
    // Constructor
    Server();

    //Member functions
    void start();

    void update_miners_pipes(std::string path);

    //Block data getters
    int get_latest_block_height();

    unsigned int get_latest_block_hash();

    int get_latest_block_difficulty();

    unsigned int hash(int height, int nonce, time_t timestamp, unsigned int last_hash, int id);

    void set_difficulty();
};
