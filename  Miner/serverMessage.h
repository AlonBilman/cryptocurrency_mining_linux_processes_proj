#include "block.h"

#define NEW_BLOCK 1
#define CONNECT_REQ 2

struct server_connect_message
{
    int type = CONNECT_REQ;
    int id;
    int data_size;
    std::string my_pype={};

    server_connect_message(int id, int data_size,std::string data):id(id),data_size(data_size),my_pype(data){}
};

struct server_block_message
{
    int type = NEW_BLOCK; //type of message
    int id;
    int data_size;
    Block data;

    server_block_message(int id, int data_size,Block data):id(id),data_size(data_size),data(data){}
};

