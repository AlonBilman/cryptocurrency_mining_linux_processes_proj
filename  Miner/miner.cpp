#include "miner.h"
#include "serverMessage.h"

Miner::Miner(int id_,int server_pipe_,const char* path): id(id_),server_pipe(server_pipe_) {
     
     std::string my_pipe_name = path;
     my_pipe_name.append("miner_pipe_"+id);

     check_fd(mkfifo(my_pipe_name.c_str(),0666));
     
     my_pipe=open(my_pipe_name.c_str(),O_RDONLY);
     check_fd(my_pipe);
     //making the connection message.
     serverMessage connect_req(CONNECT_REQ,id);

     connect_req.set_pipe_name(my_pipe_name);

     std::string my_log_name= path;
     my_log_name.append("mtacoin.log");
     my_log=open(my_log_name.c_str(),O_RDWR | O_CREAT, 0644); //only I need to write
     check_fd(my_log);

     //redirect stdout to the log file.
     if(dup2(my_log, STDOUT_FILENO)==-1)
     {
        //write an error.
        exit(1);
     }

     check_fd(write(server_pipe,&connect_req,sizeof(serverMessage)),CLOSE);
    //this will be written in the log file.
     std::cout<<"Miner #"<<id<<" sent connect request on"<<my_pipe_name<<std::endl;

    //this will block him untill recieving a block
     check_fd(read(my_pipe,block,sizeof(Block)),CLOSE);

     //update
     std::cout<<"Miner #"<<id<<"received first block: ";
     update_target_parameters();

     //now I want it to be nonblocking, update the pipe mode to readonly + nonblocking
     check_fd(fcntl(my_pipe, F_SETFL, O_RDONLY | O_NONBLOCK),CLOSE);
     
    //thats it for init miner.
}

void Miner::update_target_parameters() {
    
    difficulty_target = block->get_difficulty();
    height_target = block->get_height() + 1;
    last_hash = block->get_hash();
    nonce = 0; //init nonce
    print_block_params();
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

void Miner::print_block_params()
{
    std::cout << "relayed_by(" << std::dec << block->get_relayed_by()
            << "), height(" << std::dec << block->get_height() << "), timestamp(" << block->get_timestamp()
            << "), hash(0x" << std::hex << block->get_hash() << std::dec << "), prev_hash(0x"
            << std::hex << block->get_prev_hash() << std::dec << "), nonce("
            << block->get_nonce() << ")" << std::endl;
   
}

void Miner::start_mining() {

    while (true) {
        //update if there is a new block.
        if(read(my_pipe,block,sizeof(Block))!=-1)
        {
            std::cout<<"Miner #"<<id<<"received block: ";
            update_target_parameters();
        }
        unsigned int crc_res = calculate_hash_code(); //this also updates the timestamp
        //if the miner hits the right hash:
        if ((crc_res >> (32 - difficulty_target)) == 0) //update the server "socket" or "mail-box"
        {
            //change cout to the log file.
            std::cout << "Miner #" << id
                    << " mined a new Block #" << std::dec << height_target
                    << ", With the hash 0x" << std::hex << crc_res 
                    << ", difficulty "<<difficulty_target<<std::endl;

            //update and send block to server
            auto new_block = Block(last_hash, height_target, difficulty_target, nonce, crc_res, id,
                                   static_cast<int>(timestamp));

            //write this block to the server pipe.
            serverMessage message(NEW_BLOCK,id);
            message.set_block_data(new_block);
            //we dont need to check, if there was an error, the miner keep going + its non blocking.
            write(server_pipe,&message,sizeof(serverMessage)); 
        }
       //increase the nonce
        ++nonce;
    }
}


