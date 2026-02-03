#ifndef TYPES_HPP
#define TYPES_HPP

#include<iostream>
#include<vector>
using namespace std;


struct Command {
    string name;
    vector<string> parameters;
    vector<char> options;
    string input_file;
    string output_file;

    Command() {}

    Command(string input) {
        void parseCommand();
    }
};


struct pipeline {
    vector<Command> commands;
};

#endif
