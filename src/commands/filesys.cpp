#include <iostream>
#include <vector>
#include <string>
#include <regex>
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
    return currDir;
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

void createPath(const std::string &path) {
    for (uint i = 1; i < path.size(); i++) {
        if (path[i] == '/') {
            if (mkdir(path.substr(0, i).c_str(), 0755) == -1 && errno != EEXIST) {
                perror(("mkdir: " + path.substr(0,i)).c_str());
                return;
            }
        }
    }

    if (mkdir(path.c_str(), 0755) == -1 && errno != EEXIST) {
        perror(("mkdir: " + path).c_str());
    }
}

void createDir(Command& cmd) {
    if (cmd.parameters.empty()) {
        std::cerr << "mkdir: missing operand" << std::endl;
    }

    bool parent = false;
    for (auto &op: cmd.options) {
        if (op == 'p') { parent = true; break; }
    }

    for (auto &param: cmd.parameters) {
        if (!parent) {
            if (mkdir(param.c_str(), 0755) == -1)
                perror(("mkdir: cannot create directory '" + param + "'").c_str());
        }

        else {
            createPath(param);
        }
    }
}

void changeCurrDir(Command &cmd) {
    std::string destDir;

    destDir = cmd.parameters.empty() ? getenv("HOME") : cmd.parameters[0];

    if (chdir(destDir.c_str()) != 0) {
        perror("Couldn't change directory");
    }

    currWorkingDir();
}

void removeFile(Command &cmd) {
    bool recursive = false;
    for (auto &o: cmd.options) {
        if (o == 'r' || o == 'R') recursive = true;
    }

    if (cmd.parameters.empty()) { std::cerr << "rm: missing operand" << std::endl; }

    for (auto& target: cmd.parameters) {
        try {
            if (recursive) fs::remove_all(target);
            else fs::remove(target);
        }

        catch (fs::filesystem_error &e) {
            std::cout << "rm: " << e.what() << " \n";
        }
    }
}

void removeDir(Command &cmd) {
    std::string destDir = cmd.parameters.empty() ? currWorkingDir() : cmd.parameters[0];

    if (rmdir(destDir.c_str()) != 0) {
        std::cout << "Couldn't remove directory at "<< destDir << "\n";
    }

    else {
        std::cout << "Directory removed" << std::endl;;
    }
}

void move(Command &cmd) {
    if (cmd.parameters.size() < 2) { std::cerr << "mv: missing parameters" << std::endl; return; }

    std::string source = cmd.parameters[0];
    std::string destination = cmd.parameters[1];

    try {
        if (fs::is_directory(destination)) {
            fs::path srcPath(source);
            fs::path destPath(destination);
            destPath = destPath/srcPath.filename();
            fs::rename(source, destPath);
        }

        else {
            fs::rename(source, destination);
        }
    }

    catch (fs::filesystem_error &fe) {
        std::cerr << "mv" << fe.what() << std::endl;
    }
}


void copyFile(Command &cmd) {
    if (cmd.parameters.size() < 2) { std::cerr << "cp: missing operands \n"; return; }

    std::string sourceDir = cmd.parameters[0];
    std::string destDir = cmd.parameters[1];

    bool recursive = false;
    for (auto &o: cmd.options) { if (o == 'r' || o == 'R') recursive = true; }

    fs::copy_options options = fs::copy_options::overwrite_existing;
    if (recursive) options = options | fs::copy_options::recursive ;

    try {
        fs::copy(sourceDir, destDir, options);
    }
    catch (fs::filesystem_error &e) {
        std::cout << "cp: " << e.what() << std::endl;
    }
}

void createFile(Command &cmd) {
    if (cmd.parameters.empty()) { std::cerr << "touch: missing operand" << std::endl; }

    for (auto &filename: cmd.parameters) {
        try {
            fs::path p(filename);

            if (!fs::exists(p)) { std::ofstream ofs(p); ofs.close(); }
            else { fs::last_write_time(p, fs::file_time_type::clock::now()); }

        }

        catch (filesystem_error &e) {
            std::cerr << "touch:" << e.what() << std::endl;
        }
    }
}

void findFile(Command &cmd) {
    if (cmd.parameters.size() < 1) { std::cerr << "Usage: find [path] [filename] | [regex pattern]" << std::endl; return; }
    std::string target = cmd.parameters[0];

    bool foundLiteral = false;
    for (auto &entry: fs::recursive_directory_iterator(".")) {
        if (entry.path().filename() == target) {
            std::cout << entry.path().string() << std::endl;
            foundLiteral = true;
        }
    }
    if (foundLiteral) return;


    size_t pos = 0;
    while ((pos = target.find('.', pos)) != std::string::npos) {
        target.replace(pos, 1, "\\.");
        pos += 2;
    }

    pos = 0;
    while ((pos = target.find('*', pos)) != std::string::npos) {
        target.replace(pos, 1, ".*");
        pos += 2;
    }

    try {
        std::regex pattern(target);
        for (auto &entry: fs::recursive_directory_iterator(".")) {
            if (std::regex_match(entry.path().filename().string(), pattern))
                std::cout << entry.path().string() << std::endl;
        }
    }

    catch (std::regex_error &e) {
        std::cerr << e.what() << std::endl;
    }
}
