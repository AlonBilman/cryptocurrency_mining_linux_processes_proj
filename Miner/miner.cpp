#include "miner.h"


Miner::Miner(int id_,int server_pipe_): id(id_){

    fd[SERVER_PIPE] = server_pipe_;

     std::string my_log_name= LOG_PATH;
     my_log_name.append(LOG_NAME);
     my_log_name.append(std::to_string(id));
     fd[LOG_FILE] = open(my_log_name.c_str(),O_WRONLY | O_CREAT, 0644); //only I need to write
     check_fd(fd[LOG_FILE],fd,SIZE);

     //redirect stdout and stderr to the log file...
     if (dup2(fd[LOG_FILE], STDOUT_FILENO) == -1 || dup2(fd[LOG_FILE], STDERR_FILENO) == -1)
    {
        perror("Error on redirecting STDOUT or STDERR");
        close(fd[LOG_FILE]);   
        close(fd[SERVER_PIPE]); 
        exit(EXIT_FAILURE);               
    }
     //opening my pipe.
     std::string my_pipe_name = MAIN_PATH;
     my_pipe_name.append(BASE_PIPE_NAME);
     my_pipe_name.append(std::to_string(id));

     check_fd(mkfifo(my_pipe_name.c_str(),0666),fd,SIZE);
     
     fd[MY_PIPE]=open(my_pipe_name.c_str(),O_RDONLY| O_NONBLOCK);
     check_fd(fd[MY_PIPE],fd,SIZE);
    
     //making the connection message. 

     server_connect_message connect_req(id);
     strcpy(connect_req.buffer,my_pipe_name.c_str());
     connect_req.buffer[strlen(connect_req.buffer)]='\0';
     connect_req.data_size=sizeof(connect_req.buffer);
     std::cout<<"attempt to write"<<std::endl;
     check_fd(write(fd[SERVER_PIPE],&connect_req,sizeof(connect_req)),fd,SIZE);
    //this will be written in the log file.
     std::cout<<"Miner #"<<id<<" sent connect request on"<<my_pipe_name<<std::endl;

     //set mine's pipe to blocking mode temporarily to wait for the first block
     check_fd(fcntl(fd[MY_PIPE], F_SETFL, fcntl(fd[MY_PIPE], F_GETFL) & ~O_NONBLOCK), fd, SIZE);

     //read - > blocked untill recieving data
     check_fd(read(fd[MY_PIPE],&block,sizeof(Block)),fd,SIZE);

     //update
     std::cout<<"Miner #"<<id<<" received first block: ";
     update_target_parameters();

     //now I want it to be nonblocking, update the pipe mode to readonly + nonblocking
     check_fd(fcntl(fd[MY_PIPE], F_SETFL, fcntl(fd[MY_PIPE], F_GETFL) | O_NONBLOCK), fd, SIZE);
    //thats it for init miner.
}

void Miner::update_target_parameters() 
{
    difficulty_target = block.get_difficulty();
    height_target = block.get_height() + 1;
    last_hash = block.get_hash();
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
    std::cout << "relayed_by(" << std::dec << block.get_relayed_by()
            << "), height(" << std::dec << block.get_height() << "), timestamp(" << block.get_timestamp()
            << "), hash(0x" << std::hex << block.get_hash() << std::dec << "), prev_hash(0x"
            << std::hex << block.get_prev_hash() << std::dec << "), nonce("
            << block.get_nonce() << ")" << std::endl;
   
}

void Miner::start_mining() {

    while (true) {
        //update if there is a new block.
        int read_ = read(fd[MY_PIPE],&block,sizeof(Block));
        if(read_!=0 && read_!=-1)
        {
             std::cout<<"Miner #"<<id<<" received a new block: ";
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
                    << ", difficulty "<<std::dec<<difficulty_target<<std::endl;

            //update and send block to server
            auto new_block = Block(last_hash, height_target, difficulty_target, nonce, crc_res, id, static_cast<int>(timestamp));

            //write this block to the server pipe.
            server_block_message message(id,sizeof(new_block),new_block);

            //we dont need to check, if there was an error, the miner keep going + its non blocking.
            write(fd[SERVER_PIPE],&message,sizeof(message)); //return->log
        }
       //increase the nonce
        ++nonce;
    }
}


