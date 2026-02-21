#include <iostream>
#include <string>
#include <unistd.h>
#include "include/pipeline.hpp"
#include <sys/wait.h>
#include "execindex.hpp"
#include "signals.h"


void pipelineHandler(pipeline &ppn) {
    int prev_read = -1;
    std::vector<pid_t> pids;

    for (std::size_t i = 0; i < ppn.commands.size(); i++) {
        bool last = (i == ppn.commands.size() - 1);

        int fd[2];
        if (!last) {
            if (pipe(fd) == -1) { perror("pipe"); break; }
        }

        sigset_t prev;
        blockSIGCHLD(prev);

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork:");
            restoreSIGCHLD(prev);
            if (!last) { close(fd[0]); close(fd[1]); }
            break;
        }

        if (pid == 0) {
            signal(SIGINT, SIG_DFL);
            restoreSIGCHLD(prev);

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

            auto it = builtins.find(cmd.name);

            if (it != builtins.end()) {
                it->second(cmd);
                _exit(EXIT_SUCCESS);
            }

            auto args = cmd.argv();
            execvp(args[0], args.data());
            perror("Katana");
            _exit(EXIT_FAILURE);
        }

        pids.push_back(pid);
        restoreSIGCHLD(prev);

        if (prev_read != -1) close(prev_read);
        if (!last) close(fd[1]);
        prev_read = last ? -1 : fd[0];
    }

    if (prev_read == -1) close(prev_read);

    for (auto &p: pids) {
        int status;
        waitpid(p, &status,0);
    }
}


