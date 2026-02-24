#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <execution>
#include <sys/wait.h>
#include <format>
#include "include/types.hpp"
#include "include/execindex.hpp"
#include "include/executor.hpp"
#include "redirection.hpp"
#include "signals.h"


void executeInternal(Command &cmd) {
    if (cmd.name.empty()) return;

    auto it = builtins.find(cmd.name);
    if (it != builtins.end()) {
        int save_in = dup(STDIN_FILENO);
        int save_out = dup(STDOUT_FILENO);

        redirectionHandler(cmd);

        it->second(cmd);

        dup2(save_in, STDIN_FILENO);
        dup2(save_out, STDOUT_FILENO);
        close(save_in);
        close(save_out);
    }

    else {
        executeExternal(cmd);
    }
}

void executeExternal(Command &cmd) {
    auto agv = cmd.argv();
    char** args = agv.data();

    sigset_t prev;
    blockSIGCHLD(prev);

    pid_t pid = fork();

    if (pid < 0) {
        std::perror("Forking failed ! \n");
        restoreSIGCHLD(prev);
        return;
    }

    if (pid == 0) {
        restoreSIGCHLD(prev);
        setupChildSignals();

        redirectionHandler(cmd);

        if (execvp(args[0], args) == -1) {
            std::perror("Katana-Shell");
            _exit(EXIT_FAILURE);
        }
    }

    else if (pid > 0) {
        int status;
        waitpid(pid, &status, WUNTRACED);
        restoreSIGCHLD(prev);
    }
}



