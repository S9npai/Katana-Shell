#include<iostream>
#include<vector>
#include<string>
#include<sys/types.h>
#include<pwd.h>
#include<unistd.h>
#include<fstream>
#include<iomanip>
#include<filesystem>
using namespace std;
using namespace filesystem;
namespace fs = filesystem;


void prev_working_tree() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s \n" ,cwd);
}

/*void list_dir_contents() {
    ;
}

void change_dir() {
    ;
}

void copy() {
    ;
}

void remove() {
    ;
}

void move() {
    ;
}*/

void prevContents() {
    string path = "/etc/yum.repos.d/terra.repo";
}

int main() {
    prev_working_tree();
}


