#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>
#include <vector>


struct Command {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<char> options;
    std::string input_file;
    std::string output_file;

    Command() {}

    Command(std::string input) {
        void parseCommand();
    }
};


struct pipeline {
    std::vector<Command> commands;
};

#endif

