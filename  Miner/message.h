#include <block.h>

typedef struct message_block
{
    char type;
    Block data;
    
}message_block;

typedef struct message_connect
{
    char type;
    std::string my_pipe;
}message_connect;

typedef struct new_block
{
    Block data;
}new_block;