#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "include/execindex.hpp"


std::unordered_map<std::string, std::function<void(const Command&)>> builtins = {
    {"hostname", [](const Command&) { get_host(); }},
    {"whoami", [](const Command&){ get_user(); }},
    {"clear", [](const Command&) { clearScreen(); }},
    {"pwd", [](const Command&){ currWorkingDir(); }},
    {"ls", [](const Command& cmd) { displayDirContents(const_cast<Command&>(cmd)); }},
    {"cd", [](const Command& cmd) { changeCurrDir(const_cast<Command&>(cmd)); }},
    {"mkdir", [](const Command& cmd) { createDir(const_cast<Command&>(cmd)); }},/*
    {"mvdir", [](const Command&) { moveDir(); }},
    */{"rmdir", [](const Command& cmd) { removeDir(const_cast<Command&>(cmd)); }}/*,
    {"touch", [](const Command&) { createFile(); }},
    {"mv", [](const Command&) { moveFile(); }},
    {"rm", [](const Command&) { removeFile(); }},
    {"cp", [](const Command&) { copy(); }},*/

};

