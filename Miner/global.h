#pragma once
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define CLOSE true

extern const char* THIS_PATH;
extern const char* SERVER_PIPE_NAME;
extern const char* CONF_NAME;
extern const char* BASE_PIPE_NAME;
extern const char* LOG_NAME;


void check_fd(int fd,int* fds,int size);