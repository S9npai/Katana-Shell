#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "include/types.hpp"
#include "include/parser.hpp"


Command parseCommand(const std::string& input) {
    Command cmd;
    std::stringstream ss(input);
    ss >> cmd.name;

    std::string token;

    while (ss >> std::ws && !ss.eof()) {
        if (ss.peek() == '"') {
            ss >> quoted(token);
            cmd.parameters.push_back(token);
        }

        else {
            ss >> token;

            if (token.substr(0,2) == "--") {
                cmd.longOptions.push_back(token.substr(2));
            }

            else if (token[0] == '-') {
                for (size_t i = 1; i < token.size(); i++) {
                    cmd.options.push_back(token[i]);
                }
            }

            else {
                cmd.parameters.push_back(token);
            }
        }
    }

    std::cout<<"longOptions:"<< std::endl;
    for (auto &x : cmd.longOptions) {
        std::cout << x << std::endl;
    }

    std::cout<<"options:"<< std::endl;
    for (auto &x : cmd.options) {
        std::cout << x << std::endl;
    }

    std::cout<<"params:"<<std::endl;
    for (auto &x : cmd.parameters) {
        std::cout << x << std::endl;
    }

    return cmd;
}


int main() {
    std::string input;
    getline(std::cin, input);
    parseCommand(input);
}

