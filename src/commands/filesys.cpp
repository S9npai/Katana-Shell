#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
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
    }

    DIR *dir = opendir(path.c_str());
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        std::string fullPath = path + "/" + filename;
        fs::file_status s = fs::status(fullPath);
        fs::perms p = s.permissions();

        struct stat info{};
        if (stat(fullPath.c_str(), &info) == -1) continue;

        if (showAll != true && filename[0] == '.') continue;

        if (longOpt != true) {
            std::cout << filename <<std::endl;
        }

        else if (longOpt == true) {
            struct passwd *pw = getpwuid(info.st_uid);
            struct group *gr = getgrgid(info.st_gid);

            auto show = [&](char op, fs::perms perm) {
                std::cout << ((p & perm) != fs::perms::none ? op : '-');
            };

            std::cout << (S_ISDIR(info.st_mode) ? "d" : "-");
            show('r', perms::owner_read);
            show('w', perms::owner_write);
            show('x', perms::owner_exec);
            show('r', perms::group_read);
            show('w', perms::group_write);
            show('x', perms::group_exec);
            show('r', perms::others_read);
            show('w', perms::others_write);
            show('x', perms::others_exec);

            std::cout << " " << std::setw(2) << info.st_nlink
                      << " " << (pw ? pw->pw_name : std::to_string(info.st_uid))
                      << " " << (gr ? gr->gr_name : std::to_string(info.st_gid));

            std::cout << " " << std::setw(8) << (info.st_size/1024) << " KB ";

            char mfTime[96];
            struct tm *timeinfo = localtime(&info.st_mtime);
            strftime(mfTime, sizeof(mfTime), "%b %d %H:%M:%S", timeinfo);
            std::cout << " " << mfTime;

            std::cout << "  " << filename <<  std::endl;
        }
    }
    closedir(dir);
}

void createDir(Command& cmd) {
    bool parent = false;

    for (auto &op: cmd.options) {
        if (op == 'p') parent = true;
        break;
    }

    if (parent) {
        for ()
    }

    else if (!parent) {
        if (cmd.parameters.empty()) {
            std::string destDir = getenv("HOME");

            if (errno == EEXIST) {
                std::cout << "Directory already exists \n";
            }

            mkdir(destDir.c_str(), 0755);
        }

        else if (!cmd.parameters.empty()) {
            bool completePath = true;
            std::string destDir = cmd.parameters[0];

            if (errno == EEXIST) {
                std::cout << "No such file or directory \n";
            }
            mkdir(destDir.c_str(), 0755);
        }
    }
}

void createPath(Command& cmd) {
}

/*void createFile(Command& cmd) {
    std::string path = cmd.parameters.empty() ? currWorkingDir() : cmd.parameters[0];


}*/

void changeCurrDir(Command &cmd) {
    std::string destDir;
    //const char* homeDir = getenv("HOME");

    /*if (cmd.parameters.empty()) {
        if (homeDir != nullptr) {
            destDir = homeDir;
        }
        else {
            perror("Error: HOME environment variable not set");
        }
    }

    else if (!cmd.parameters.empty()) {
        destDir = cmd.parameters[0];
    }*/

    destDir = cmd.parameters.empty() ? getenv("HOME") : cmd.parameters[0];

    if (chdir(destDir.c_str()) != 0) {
        perror("Couldn't change directory");
    }

    currWorkingDir();
}

/*void copy() {
    ;
}

void remove() {
    ;
}

void move() {
    ;
}*/


