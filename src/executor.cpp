#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <execution>
#include <sys/ipc.h>
#include <sys/wait.h>
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

    for (auto &p: cmd.parameters) {
        args.push_back(const_cast<char*>(p.c_str()));
    }
    args.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0) std::perror("Forking failed ! \n");
    else if (pid == 0) {
        if (execvp(args[0], args.data()) == -1) {
            std::perror("Execution failed");
            _exit(EXIT_FAILURE);
        }
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }
}


