#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "include/execindex.hpp"


std::unordered_map<std::string, std::function<void(Command&)>> builtins = {
    {"hostname", [](Command&) { get_host(); }},
    {"whoami", [](Command&){ get_user(); }},
    {"clear", [](Command&) { clearScreen(); }},
    {"pwd", [](Command&){ currWorkingDir(); }},
    {"ls", [](Command& cmd)   { displayDirContents(cmd); }},
    {"cd", [](Command& cmd) { changeCurrDir(cmd); }},
    {"mkdir", [](Command& cmd) { createDir(cmd); }},
    {"mv", [](Command& cmd) { move(cmd); }},
    {"rmdir", [](Command& cmd) { removeDir(cmd); }}/*,
    {"find", [](Command& cmd) { findFile(cmd); }},
    {"touch", [](const Command&) { createFile(); }},
    {"rm", [](const Command&) { removeFile(); }},
    {"cp", [](const Command&) { copy(); }},*/
};

