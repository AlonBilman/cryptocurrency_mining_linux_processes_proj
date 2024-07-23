#include "miner.h"


Miner::Miner(int id_,int server_pipe_,const char* path): id(id_),server_pipe(server_pipe_) {
     
     std::string my_pipe_name = path;
     my_pipe_name.append("miner_pipe_"+id);
     if(mkfifo(my_pipe_name.c_str(),0666))
     {
        //fail
     } 
     my_pipe=open(my_pipe_name.c_str(),O_RDONLY);
     check_fd(my_pipe);
     //--------------------------------------------------------------------------------- 
     //making the connection message.
     message_connect connect_req;
     connect_req.my_pipe = my_pipe_name;
     wrap_message(CONNECT_REQ,(void*)(&connect_req));
     check_fd(write(server_pipe,&to_send,sizeof(to_send)));
     

     //making the named pipe  
     //errorCheck(my_pipe);
    //send the server your pipe name 
    //wait for the response of the first block.
    //start mining.
}

void Miner::update_target_parameters(Block new_block) {
    //if we read something, update. else return.
    
    difficulty_target = new_block.get_difficulty();
    height_target = new_block.get_height() + 1;
    last_hash = new_block.get_hash();
    nonce = 0; //init nonce
}

unsigned int Miner::calculate_hash_code() {
    timestamp = std::time(nullptr); //take the current time since 1970 (unix epoch)
        std::string data_to_hash = std::to_string(height_target) + std::to_string(nonce) + std::to_string(timestamp) +
                                   std::to_string(last_hash) + std::to_string(id);
    uLong crc_res = 0;
    crc_res = crc32(crc_res, reinterpret_cast<const Bytef *>(data_to_hash.c_str()), data_to_hash.size());
    //reinterpret cast is used to cast the pointer.
    return crc_res;
}

void Miner::start_mining() {
    while (true) {
        update_target_parameters();

        unsigned int crc_res = calculate_hash_code(); //this also updates the timestamp
        //if the miner hits the right hash:
        if ((crc_res >> (32 - difficulty_target)) == 0) //update the server "socket" or "mail-box"
        {
            //change cout to the log file.
            std::cout << "Miner #" << id
                    << " mined a new Block #" << std::dec << height_target
                    << ", With the hash 0x" << std::hex << crc_res << std::endl;

          
            //update and send block to server
            auto new_block = Block(last_hash, height_target, difficulty_target, nonce, crc_res, id,
                                   static_cast<int>(timestamp));
            //write this block to the server pipe. 
        }
        //the miners mine all the time, therefor while sending
        //the new block to the server it will increase the nonce
        //to try different nonce
        ++nonce;
    }
}

void Miner::wrap_message(int type, void* message)
{
   to_send.id=id;
   to_send.type= type;

   if(type==CONNECT_REQ)
   {
        to_send.connect = *static_cast<message_connect*>(message); 
   }
   else if(type==NEW_BLOCK)
   {
        to_send.block_mined=*static_cast<message_block*>(message);
   }
   //else dont do nothing, return.

}