#pragma once
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


 extern const char* MAIN_PATH;
 extern const char* SERVER_PIPE_NAME;
 extern const char* CONF_NAME;
 extern const char* BASE_PIPE_NAME;
 extern const char* LOG_NAME;
 extern const char* LOG_PATH;

void check_fd(int fd, int my_log, int my_pipe);

struct msg{
    int type;
    int id;
    int size;
};