#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <execution>
#include <sys/wait.h>
#include <format>
#include "include/types.hpp"
#include "include/execindex.hpp"
#include "include/executor.hpp"
#include "signals.h"


void executeInternal(Command &cmd) {
    if (cmd.name.empty()) return;

    auto it = builtins.find(cmd.name);
    if (it != builtins.end()) {
        it->second(cmd);
    }

    else {
        executeExternal(cmd);
    }
}

void executeExternal(Command &cmd) {
    auto args = cmd.argv();

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

        if (execvp(args[0], args.data()) == -1) {
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



