#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include "../include/cmdheaders/sysinfo.hpp"


void clearScreen() {
    printf("\033[H\033[2J");
    fflush(stdout);
}

void get_user() {
    struct passwd *user = getpwuid(getuid());
    if (user != nullptr) std::cout<<user->pw_name<< std::endl;
    else std::cout<<"Unknown user !"<< std::endl;
}

void get_host() {
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    printf("%s\n", hostname);
}

int main() {
    clearScreen();
    get_host();
    get_user();
}


