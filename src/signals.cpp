#include <csignal>
#include <sys/wait.h>
#include "include/signals.h"


void sigchld_handler(int i) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

void sigint_handler(int) {
    write(STDOUT_FILENO, "\n", 1);
}

void setupParentSignals() {
    struct sigaction sa_chld, sa_ignore;
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;

    sigaction(SIGINT,  &sa_ignore, nullptr);
    sigaction(SIGQUIT, &sa_ignore, nullptr);
    sigaction(SIGTSTP, &sa_ignore, nullptr);
    sigaction(SIGTTIN, &sa_ignore, nullptr);
    sigaction(SIGTTOU, &sa_ignore, nullptr);

    sa_chld.sa_handler = sigchld_handler;
    sigemptyset(&sa_chld.sa_mask);
    sa_chld.sa_flags = SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa_chld, nullptr);
}

void setupChildSignals() {
    struct sigaction sa_default;
    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;

    sigaction(SIGINT,  &sa_default, nullptr);
    sigaction(SIGQUIT, &sa_default, nullptr);
    sigaction(SIGTSTP, &sa_default, nullptr);
    sigaction(SIGTTIN, &sa_default, nullptr);
    sigaction(SIGTTOU, &sa_default, nullptr);
    sigaction(SIGCHLD, &sa_default, nullptr);
}

void restoreSIGCHLD(sigset_t &prev) {
    sigprocmask(SIG_SETMASK, &prev, nullptr);
}

void blockSIGCHLD(sigset_t &prev) {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &mask, &prev);
}

