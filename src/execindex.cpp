#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include "include/commands.h"
#include "include/types.hpp"


std::unordered_map<std::string, std::function<void(const Command&)>> builtins = {
    {"pwd", [](const Command& cmd){ currWorkingDir(); }},
    {"hostname", [](const Command&) {  get_host(); }},
    {"whoami", [](const Command& cmd){ get_user(); }},
    {"clear", [](const Command&) {  clearScreen(); }},
    {"cd", [](const Command&) {  changeCurrDir(); }},
    {"ls", [](const Command&) {  displayDirContents(); }},
    {"touch", [](const Command&) {  createFile(); }},
    {"mv", [](const Command&) {  moveFile(); }},
    {"rm", [](const Command&) {  removeFile(); }},
    {"mkdir", [](const Command&) {  createDir(); }},
    {"mvdir", [](const Command&) {  moveDir(); }},
    {"ls", [](const Command&) {  removeDir(); }},
    {"cp", [](const Command&) {  copy(); }},
    {"ls", [](const Command&) {  ; }},
    {"ls", [](const Command&) {  ; }},
    {"ls", [](const Command&) {  ; }}
};


