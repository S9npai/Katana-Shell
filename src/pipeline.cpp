#include <iostream>
#include <string>
#include <unistd.h>
#include "include/pipeline.hpp"


void pipelineHandler(const char* p1, const char* p2) {
    int fd[2];
    pipe(fd);

    if (fork() != 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);


    }
}

