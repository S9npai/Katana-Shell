#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <execution>
#include <sys/wait.h>
#include <format>
#include "include/types.hpp"
#include "include/execindex.hpp"
#include "include/executor.hpp"


void executeInternal(const Command & cmd) {
    auto it = builtins.find(cmd.name);
    if (it != builtins.end()) {
        it->second(cmd);
    }

    else {
        executeExternal(cmd);
    }
}

void executeExternal(const Command &cmd) {
    std::vector<char*>args;
    args.push_back(const_cast<char*>(cmd.name.c_str()));

    for (auto &g: cmd.rawArgs) {
        args.push_back(const_cast<char*>(g.c_str()));
    }
    args.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0) std::perror("Forking failed ! \n");

    else if (pid == 0) {
        setpgid(pid, 0);
        tcsetpgrp(STDIN_FILENO, getpgrp());
        signal(SIGINT, SIG_DFL);

        if (execvp(args[0], args.data()) == -1) {
            std::perror("Execution failed");
            _exit(EXIT_FAILURE);
        }

        _exit(1);
    }

    else {
        int status;
        setpgid(pid, pid);
        waitpid(pid, &status, 0);
        tcsetpgrp(STDIN_FILENO, getpgrp());
    }
}


