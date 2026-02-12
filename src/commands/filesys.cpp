#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include <sys/stat.h>
#include "../include/cmdheaders/filesys.hpp"
#include "../include/types.hpp"
using namespace std::filesystem;
namespace fs = std::filesystem;
using fs::perms;


std::string currWorkingDir() {
    char cwd[1024];
    const char* currDir = getcwd(cwd, sizeof(cwd));
    //printf("%s \n" ,cwd);
    return static_cast<std::string>(currDir);
}

void displayDirContents(Command& cmd) {
    std::string path = cmd.parameters.empty() ? currWorkingDir() : cmd.parameters[0];

    bool longOpt = false, showAll = false;

    for (auto x: cmd.options) {
        if (x == 'l') longOpt = true;
        if (x == 'a') showAll = true;
        break;
    }

    DIR *dir = opendir(path.c_str());
    if (!dir) return;

    struct dirent *entry;

    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;

        if (showAll != true && filename[0] == '.') {
            continue;
        }

        if (longOpt != true) {
            std::cout << filename <<std::endl;
        }

        else if (longOpt == true) {
            fs::file_status s = fs::status(path.append("/").append(filename));
            fs::perms p = s.permissions();

            auto show = [&](char op, fs::perms perm) {
                std::cout << ((p & perm) != fs::perms::none ? op : '-');
            };

            show('r', perms::owner_read);
            show('w', perms::owner_write);
            show('x', perms::owner_exec);
            show('r', perms::group_read);
            show('w', perms::group_write);
            show('x', perms::group_exec);
            show('r', perms::others_read);
            show('w', perms::others_write);
            show('x', perms::others_exec);
            <<  <<  <<  <<  <<  <<  <<  <<  << entry->d_name <<  std::endl;
        }
    }
    closedir(dir);
}

/*void createDir(Command& cmd) {

}*/

/*void createFile(Command& cmd) {
    std::string path = cmd.parameters.empty() ? currWorkingDir() : cmd.parameters[0];


}*/

/*void change_dir() {
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



int main() {
    currWorkingDir();
}

