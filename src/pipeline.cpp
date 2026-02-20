#include <iostream>
#include <string>
#include <unistd.h>
#include "include/pipeline.hpp"
#include <sys/wait.h>


void pipelineHandler(pipeline &ppn) {
    int prev_read = -1;
    std::vector<pid_t> pids;

    for (std::size_t i = 0; i < ppn.commands.size(); i++) {
        bool last = (i == ppn.commands.size() - 1);

        int fd[2];
        if (!last) pipe(fd);

        pid_t pid = fork();

        if (pid == 0) {
            if (prev_read != -1) {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }

            if (!last) {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                close(fd[0]);
            }

            Command &cmd = ppn.commands[i];
            std::vector<char*> args;
            args.push_back(const_cast<char*>(cmd.name.c_str()));
            for (auto &a : cmd.rawArgs) args.push_back(const_cast<char*>(a.c_str()));
            args.push_back(nullptr);

            execvp(args[0], args.data());
            perror("Katana");
            _exit(EXIT_FAILURE);
        }

        pids.push_back(pid);

        if (prev_read != -1) close(prev_read);
        if (!last) close(fd[1]);
        prev_read = last? -1 : fd[0];
    }

    for (auto &p: pids) {
        int status;
        waitpid(p, &status,0);
    }
}


