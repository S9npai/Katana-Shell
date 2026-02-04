#ifndef TYPES_HPP
#define TYPES_HPP
#include <vector>


struct Command {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<char> options;
    std::vector<std::string> longOptions;
    std::vector<std::string> quotes;
    std::string input_file;
    std::string output_file;

    Command() = default;
};


struct pipeline {
    std::vector<Command> commands;
};

#endif

