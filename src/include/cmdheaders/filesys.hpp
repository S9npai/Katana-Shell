#ifndef FILESYS_HPP
#define FILESYS_HPP
#include "../types.hpp"


std::string currWorkingDir();

void displayDirContents(Command &cmd);

void changeCurrDir(Command &cmd);

void createDir(Command &cmd);

void removeDir(Command &cmd);

void move(Command &cmd);

/*void createFile();

void moveFile();

void removeFile();

void copy();*/

#endif


