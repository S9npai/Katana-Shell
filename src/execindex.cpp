#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "include/execindex.hpp"
#include "utils.h"


std::unordered_map<std::string, std::function<void(Command&)>> builtins = {
    {"exit", [](Command&) { std::exit(EXIT_SUCCESS); }},
    {"quit", [](Command&) { std::exit(EXIT_SUCCESS); }},
    {"hostname", [](Command&) { get_host(); }},
    {"whoami", [](Command&){ get_user(); }},
    {"clear", [](Command&) { clearScreen(); }},
    {"pwd", [](Command&){ currWorkingDir(); }},
    {"ls", [](Command& cmd)   { displayDirContents(cmd); }},
    {"cd", [](Command& cmd) { changeCurrDir(cmd); }},
    {"mkdir", [](Command& cmd) { createDir(cmd); }},
    {"mv", [](Command& cmd) { move(cmd); }},
    {"rmdir", [](Command& cmd) { removeDir(cmd); }},
    {"rm", [](Command& cmd) { removeFile(cmd); }},
    {"find", [](Command& cmd) { findFile(cmd); }},
    {"touch", [](Command& cmd) { createFile(cmd); }},
    {"cp", [](Command& cmd) { copyFile(cmd); }},
    {"history", [](Command&) { showHistory(); }},
    {"help", [](Command&) { displayManual(); }},
};

