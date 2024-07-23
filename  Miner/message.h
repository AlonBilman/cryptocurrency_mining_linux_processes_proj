#include "block.h"

#define NEW_BLOCK 1
#define CONNECT_REQ 2

struct message_connect {
    std::string my_pipe; 
};

struct message_block {
    Block data;
};

struct message_to_server {
    int type; // connection (CONNECT_REQ) or new block (NEW_BLOCK)
    int id; // miner's id
    union {
        message_connect connect;
        message_block block_mined;
    };
};
