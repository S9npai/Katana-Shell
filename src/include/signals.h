#ifndef SIGNALS_H
#define SIGNALS_H


void sigchld_handler(int);

void setupParentSignals();
void setupChildSignals();

#endif