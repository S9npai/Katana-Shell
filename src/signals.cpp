#include <csignal>
#include <sys/wait.h>
#include "include/signals.h"


void sigchld_handler(int i) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

void setupParentSignals() {
    signal(SIGINT,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
}

void setupChildSignals() {
    signal(SIGINT,  SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
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

