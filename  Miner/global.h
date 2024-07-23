#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "message.h"

#define CLOSE true
const char* THIS_PATH = "/home/alon/Desktop/Task3_mtaCoin/linux_processes_task3/";
const char* SERVER_PIPE_NAME = "server_pipe";
const char* CONF_NAME = "mtacoin.conf";
const char* MINERS_COUNT = "miners_count";

void check_fd(int fd);
void check_fd(int fd, bool close_);