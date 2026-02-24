#ifndef EXECINDEX_HPP
#define EXECINDEX_HPP
#include <any>
#include <functional>
#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include "commands.h"
#include "types.hpp"


extern std::unordered_map<std::string, std::function<void(Command&)>> builtins;


#endif

