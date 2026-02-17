#ifndef FILESYS_HPP
#define FILESYS_HPP
#include "../types.hpp"


std::string currWorkingDir();

void displayDirContents(Command &cmd);

void changeCurrDir(Command &cmd);

void createDir(Command &cmd);

void createPath(Command &cmd);

void removeDir();

void moveDir();

/*void createFile();

void moveFile();

void removeFile();

void copy();*/

#endif


