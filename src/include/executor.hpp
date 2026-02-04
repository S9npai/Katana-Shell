#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include "types.hpp"

void executeInternal(const Command & cmd);
void executeExternal(const Command & cmd);

#endif