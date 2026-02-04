#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <bits/chrono.h>
#include "../include/cmdheaders/filesys.hpp"
struct Command;
using namespace std::filesystem;
namespace fs = std::filesystem;


void currWorkingDir() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s \n" ,cwd);
}

void displayDirContents(Command& cmd) {

}

void createDir(Command& cmd) {

}

void createFile(Command& cmd) {

}

/*

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
}

*/

int main() {
    currWorkingDir();
}


