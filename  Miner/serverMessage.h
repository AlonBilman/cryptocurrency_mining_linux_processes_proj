#include "block.h"

#define NEW_BLOCK 1
#define CONNECT_REQ 2

class serverMessage {
private:
    int type; //type of message
    int id;
    std::string my_pipe={};
    Block data=Block();
public:
   serverMessage(int type, int id):type(type),id(id){};
   void set_pipe_name(std::string path){
    my_pipe=path;
    }
   void set_block_data(Block &block){
    data=block;
    }
};

