#ifndef HELPERS_HPP
#define HELPERS_HPP
#include <string>


std::string expandPath(const std::string &path);

std::string expandEnvVars(std::string &token);

#endif