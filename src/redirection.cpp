#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "types.hpp"
#include "include/redirection.hpp"


void redirectionHandler(Command &cmd) {
    for (auto &redir: cmd.redirections) {
        int fd = -1;

        if (redir.mode == RedirectMode::Input) {
            fd = open(redir.file.c_str(), O_RDONLY);
            if (fd == -1) { perror("open input"); _exit(EXIT_FAILURE); }
            dup2(fd, STDIN_FILENO);
        }

        else if (redir.mode == RedirectMode::Output) {
            fd = open(redir.file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) { perror("open output"); _exit(EXIT_FAILURE); }
            dup2(fd, STDOUT_FILENO);
        }

        else if (redir.mode == RedirectMode::Append) {
            fd = open(redir.file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) { perror("open append"); _exit(EXIT_FAILURE); }
            dup2(fd, STDOUT_FILENO);
        }

        else if (redir.mode == RedirectMode::Error) {
            fd = open(redir.file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) perror("open input");
            dup2(fd, STDERR_FILENO);
        }

        if (fd != -1) {
            close(fd);
        }
    }
}


