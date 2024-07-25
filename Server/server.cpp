#include "server.h"
#define NO_FD -1

Server::Server()
{  
     std::string my_log_name= THIS_PATH;
     my_log_name.append(LOG_NAME);

     my_log = open(my_log_name.c_str(),O_RDWR | O_CREAT, 0644); //only I need to write
     check_fd(my_log,NO_FD,NO_FD); //sending -1, there is no fd to close...

     
     //redirect stdout and stderr to the log file...
    if (dup2(my_log, STDOUT_FILENO) == -1 || dup2(my_log, STDERR_FILENO) == -1)
    {
        std::cerr << "Error on redirecting STDOUT or STDERR" << std::endl;
        close(my_log); 
    }


     set_difficulty(); //getting the difficulty from the conf file and 
                        //setting up the difficulty lvl.
    
    next_block.set_difficulty(difficulty_target);
    block_chain.push_front(next_block);
    
    
     //opening my pipe.
     std::string my_pipe_name = THIS_PATH;
     my_pipe_name.append(SERVER_PIPE_NAME);
     check_fd(mkfifo(my_pipe_name.c_str(),0666),my_log,NO_FD);
     my_pipe = open(my_pipe_name.c_str(),O_RDWR);
     check_fd(my_pipe,my_log,NO_FD);

     std::cout<<"init finished"<<std::endl;
}


void Server::print_last_block_(Block &block_added) {
    std::cout << "Server: New block added by Miner #" << std::dec << block_added.get_relayed_by()
            << ", height(" << std::dec << block_added.get_height() << "), timestamp(" << block_added.get_timestamp()
            << "), hash(0x" << std::hex << block_added.get_hash() << std::dec << "), prev_hash(0x"
            << std::hex << block_added.get_prev_hash() << std::dec << "), nonce("
            << block_added.get_nonce() << ")" << std::endl;
}

bool Server::verify_proof_of_work_(Block &block_to_check) {

    if (block_to_check.get_difficulty() != difficulty_target) {
        std::cout << "The Difficulty is wrong, Miner #" << block_to_check.get_relayed_by() << std::endl;
        return false;
    } else if (block_to_check.get_height() != number_of_blocks + 1) {
        std::cout << "Server: The Height is wrong, Miner #" << block_to_check.get_relayed_by() << std::endl;
        return false;
    } else if (block_to_check.get_prev_hash() != block_chain.front().get_hash()) {
        std::cout << "Server: The prev_hash is wrong, Miner #" << block_to_check.get_relayed_by() << std::endl;
        return false;
    }

    unsigned int hash_test = //this calculates the hash
            hash(block_to_check.get_height(), block_to_check.get_nonce(), (block_to_check.get_timestamp()),
                 block_to_check.get_prev_hash(), block_to_check.get_relayed_by());

    if (hash_test != block_to_check.get_hash()) {
        std::cout << "Server: The Hash is wrong, Miner #" << block_to_check.get_relayed_by() << std::endl;
        return false;
    } else if ((hash_test >> (32 - difficulty_target)) != 0) {
        std::cout << "Server: The Hash is wrong, Miner #" << block_to_check.get_relayed_by() << std::endl;
        return false;
    }
    return true; //if we survived all the checks.
}

void Server::add_block_(Block &block_to_add) //adding to block_chain. making sure that its secure
{
    block_chain.push_front(block_to_add);
    ++number_of_blocks;
    //calling the print function 
    print_last_block_(block_to_add);
    if (block_chain.size() == MAX_CHAIN_SIZE)
        block_chain.pop_back(); //deleting the first block
}

void Server::start() {
    //reading buffers
    char data_name[256];
    std::cout<<"listening on "<<THIS_PATH<<SERVER_PIPE_NAME<<std::endl;
 
    while (true) 
    {
        //wait on pipe. start listening...check_fd(fcntl(fd[MY_PIPE], F_SETFL, O_RDONLY|O_NONBLOCK),fd,SIZE);
        msg read_m; 
        read(my_pipe,(void*)&read_m,sizeof(read_m)); // size of 3 ints.
        switch (read_m.type)
        {
        case CONNECT_REQ:
            read(my_pipe,(void*)&data_name,read_m.size);
            std::cout<<"Recieved connection request from miner #"<<read_m.id<<"pipe name: "<<data_name<<std::endl;
            update_miners_pipes(data_name); //this will open the file to read
            //writing the miner pipe the curr block. 
            write(miners_pipes[read_m.id-1],&block_chain.front(),sizeof(Block));
            break;

        case NEW_BLOCK:
            read(my_pipe,&next_block,read_m.size);
            if (verify_proof_of_work_(next_block))
            {
                add_block_(next_block);
                for(int i=0;i<miners_pipes.size();++i)
                    write(miners_pipes[i],&next_block,sizeof(Block));
            }
            break;
        default:
            std::cout<<"Could not identify the message..."<<std::endl;
            exit(-1);
            break;
        }
    }
}

//Block data getters
int Server::get_latest_block_height() {
    auto res = block_chain.front().get_height();
    return res;
}

unsigned int Server::get_latest_block_hash() {
    auto res = block_chain.front().get_hash();
    return res;
}

int Server::get_latest_block_difficulty() {
    auto res = block_chain.front().get_difficulty();
    return res;
}

unsigned int hash(int height, int nonce, time_t timestamp, unsigned int last_hash, int id) {
    std::string data_to_hash = std::to_string(height) + std::to_string(nonce) + std::to_string(timestamp) +
                               std::to_string(last_hash) + std::to_string(id);
    uLong crc_res = 0;
    crc_res = crc32(crc_res, reinterpret_cast<const Bytef *>(data_to_hash.c_str()), data_to_hash.size());
    //reinterpret cast is used to cast the pointer.
    return crc_res;
}

void Server::set_difficulty()
{
    int difficulty=0;
    std::string conf_file_name = THIS_PATH;
    conf_file_name.append(CONF_NAME);

    std::ifstream file(conf_file_name); 
    std::string line_read; //what Ill read from the file.
    if (file.is_open())
    {
        while (std::getline(file, line_read))
        {
            if (line_read.find("DIFFICULTY=") == 0) 
            {
                difficulty = std::stoi(line_read.substr(11)); //DIFFICULTY= -> 10 chars
                break; //stop
            }
        }
        file.close(); //close the file
    } 
    else {
        //this will be written inside the log file
        std::cout << "Error opening config file..."<<std::endl;
        std::cout<<"difficulty set to 8 by default..."<<std::endl;
        difficulty_target = 8;
    }

    difficulty_target = difficulty;
    std::cout<<"Difficulty set to "<<difficulty<<std::endl;
}

void Server::update_miners_pipes(std::string path)
{
    int add_fd = open(path.c_str(),O_WRONLY | O_NONBLOCK); 
    if(add_fd==-1)
        std::cout<<"Error on opening fd from miner"<<std::endl;
    else
        miners_pipes.push_back(add_fd); //update the pipes vector.
}

unsigned int Server::hash(int height, int nonce, time_t timestamp, unsigned int last_hash, int id) 
{
    std::string data_to_hash = std::to_string(height) + std::to_string(nonce) + std::to_string(timestamp) +
                               std::to_string(last_hash) + std::to_string(id);
    uLong crc_res = 0;
    crc_res = crc32(crc_res, reinterpret_cast<const Bytef *>(data_to_hash.c_str()), data_to_hash.size());
    //reinterpret cast is used to cast the pointer.
    return crc_res;
}