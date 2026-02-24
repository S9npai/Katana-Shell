#ifndef TYPES_HPP
#define TYPES_HPP
#include <vector>
#include <string>


enum class RedirectMode {
    None,
    Input,
    Output,
    Append,
    Error
};

struct Redirect {
    std::string file;
    RedirectMode mode;
};

struct Command {
    std::string                 name;
    std::vector<std::string>    parameters;
    std::vector<char>           options;
    std::vector<std::string>    longOptions;
    std::vector<std::string>    rawArgs;
    std::vector<Redirect>       redirections;

    std::vector<char*> argv() {
        std::vector<char*> v;
        v.push_back(const_cast<char*>(name.c_str()));
        for (auto &a : rawArgs) v.push_back(const_cast<char*>(a.c_str()));
        v.push_back(nullptr);
        return v;
    }

    Command() = default;
};

struct pipeline {
    std::vector<Command> commands;
};

#endif

