#include<iostream>
#include<vector>
#include<string>
#include<sys/types.h>
#include<pwd.h>
#include<unistd.h>
using namespace std;


void clearScreen() {
    printf("\033[H\033[2J");
    fflush(stdout);
}

void get_user() {
    struct passwd *user = getpwuid(getuid());
    if (user!=NULL) cout<<user->pw_name<<endl;
    else cout<<"Unknown user !"<<endl;
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


