#include "block.h"
#include <cstring>
#define NEW_BLOCK 1
#define CONNECT_REQ 2

struct server_connect_message
{
    int type = CONNECT_REQ;
    int id;
    int data_size;
    char buffer[64];

    server_connect_message(int id):id(id){}
};

struct server_block_message
{
    int type = NEW_BLOCK; //type of message
    int id;
    int data_size;
    Block data;

    server_block_message(int id, int data_size,Block data):id(id),data_size(data_size),data(data){}
};