#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "include/execindex.hpp"


std::unordered_map<std::string, std::function<void(const Command&)>> builtins = {
    {"hostname", [](const Command&) { get_host(); }},
    {"whoami", [](const Command& cmd){ get_user(); }},
    {"clear", [](const Command&) { clearScreen(); }},
    {"pwd", [](const Command& cmd){ currWorkingDir(); }},
    {"ls", [](const Command&) {  displayDirContents(); }}/*
    {"cd", [](const Command&) {  changeCurrDir(); }},
    {"mkdir", [](const Command&) {  createDir(); }},
    {"mvdir", [](const Command&) {  moveDir(); }},
    {"rmdir", [](const Command&) {  removeDir(); }},
    {"touch", [](const Command&) {  createFile(); }},
    {"mv", [](const Command&) {  moveFile(); }},
    {"rm", [](const Command&) {  removeFile(); }},
    {"cp", [](const Command&) {  copy(); }},*/

};

