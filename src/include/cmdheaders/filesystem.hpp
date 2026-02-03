#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP
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


void currWorkingDir();

void list_dir_contents();

void change_dir();

void copy();

void remove();

void move();

void prevContents();

#endif

