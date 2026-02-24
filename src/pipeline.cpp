#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include "include/pipeline.hpp"
#include "execindex.hpp"
#include "redirection.hpp"
#include "signals.h"


void pipelineHandler(pipeline &ppn) {
    int prev_read = -1;
    std::vector<pid_t> pids;
    pid_t pgid = 0;
    sigset_t prev;
    blockSIGCHLD(prev);

    for (std::size_t i = 0; i < ppn.commands.size(); i++) {
        bool last = (i == ppn.commands.size() - 1);

        int fd[2];
        if (!last && pipe(fd) == -1) { perror("pipe"); break; }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork:");
            if (!last) { close(fd[0]); close(fd[1]); }
            break;
        }

        if (pid == 0) {
            setupChildSignals();
            if (i == 0) pgid = getpid();
            setpgid(0, pgid);

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
            redirectionHandler(cmd);

            auto it = builtins.find(cmd.name);
            if (it != builtins.end()) { it->second(cmd); _exit(EXIT_SUCCESS); }

            auto args = cmd.argv();
            execvp(args[0], args.data());
            perror("Katana");
            _exit(EXIT_FAILURE);
        }

        if (i == 0) pgid = pid;
        setpgid(pid, pgid);
        tcsetpgrp(STDIN_FILENO, pgid);

        pids.push_back(pid);

        if (prev_read != -1) close(prev_read);
        if (!last) close(fd[1]);
        prev_read = last ? -1 : fd[0];
    }

    if (prev_read != -1) close(prev_read);

    restoreSIGCHLD(prev);

    for (auto &p : pids) {
        int status;
        if (waitpid(p, &status, WUNTRACED) < 0 && errno != ECHILD)
            perror("waitpid");
        if (WIFSIGNALED(status))
            write(STDOUT_FILENO, "\n", 1);
    }

    tcsetpgrp(STDIN_FILENO, getpgrp());
}


