#include "miner.h"


Miner::Miner(int id_): id(id_) {
     //update the name of the pipe
     //create the pipe
}

void Miner::update_target_parameters() {
    //if we read something, update. else return.


    difficulty_target = my_server->get_latest_block_difficulty();
    height_target = my_server->get_latest_block_height() + 1;
    last_hash = my_server->get_latest_block_hash();
    nonce = 0; //init nonce
}

unsigned int Miner::calculate_hash_code() {
    timestamp = std::time(nullptr); //take the current time since 1970 (unix epoch)
    return hash(height_target, nonce, timestamp, last_hash, id);
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
