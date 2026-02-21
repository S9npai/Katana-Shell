#ifndef SIGNALS_H
#define SIGNALS_H


void sigchld_handler(int);

void blockSIGCHLD(sigset_t &prev);
void restoreSIGCHLD(sigset_t &prev);

void setupParentSignals();
void setupChildSignals();

#endif