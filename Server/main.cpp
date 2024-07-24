#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include "server.h"



int main(int argc, char *argv[]) {

    


}








/*

void processArguments(int number_of_arguments, char *the_arguments[]) {
    try {
        if (number_of_arguments < 2) {
            //We did not get the difficulty
            throw std::string("No argument provided***\nPlease run the program again with difficulty number.\n");
        }

        int difficulty = std::stoi(the_arguments[1]);

        if (difficulty <= 0) {
            throw std::string(
                "Difficulty has to be positive!***\nPlease run the program again with difficulty number.\n");
        }
    } catch (const std::string &error) {
        std::cout << "Error!!!:\n ***" << error << std::endl;
        throw; // Rethrow the exception to be caught in the calling context
    }
}


*/