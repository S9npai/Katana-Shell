#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <execution>
#include <sys/wait.h>
#include <format>
#include "include/types.hpp"
#include "include/execindex.hpp"
#include "include/executor.hpp"


void executeInternal(Command &cmd) {
    auto it = builtins.find(cmd.name);
    if (it != builtins.end()) {
        it->second(cmd);
    }

    else {
        executeExternal(cmd);
    }
}

void executeExternal(Command &cmd) {
    std::vector<char*> args;
    args.push_back(const_cast<char*>(cmd.name.c_str()));
    for (auto &g : cmd.rawArgs) args.push_back(const_cast<char*>(g.c_str()));
    args.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0) std::perror("Forking failed ! \n");

    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        if (execvp(args[0], args.data()) == -1) {
            std::perror("Katana-Shell");
            _exit(EXIT_FAILURE);
        }
    }

    else if (pid > 0) {
        int status;
        waitpid(pid, &status, WUNTRACED);
    }
}



