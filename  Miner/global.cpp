#include "global.h"


void check_fd(int fd)
{
    if(fd==-1) {
        perror("Error with fd");
        exit(EXIT_FAILURE);
    }
}
void check_fd(int fd, bool close_)
{
     if(fd==-1) {
        perror("Error with fd");
        close(fd);
        exit(EXIT_FAILURE);
    }
}