#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "include/types.hpp"
#include "include/parser.hpp"
#include "include/helpers.hpp"


Command parseCommand(const std::string& input) {
    Command cmd;
    std::stringstream ss(input);
    std::string token;
    ss >> cmd.name;

    while (ss >> std::ws && !ss.eof()) {
        char peek = ss.peek();
        if (ss.peek() == '"' || ss.peek() == '\'') {
            ss >> quoted(token, peek);
            if (peek == '"') token = expandEnvVars(token);
            cmd.parameters.push_back(token);
        }

        else {
            ss >> token;
            token = expandPath(token);
            token = expandEnvVars(token);

            if (token.substr(0,2) == "--") {
                cmd.longOptions.push_back(token.substr(2));
            }

            else if (token[0] == '-') {
                for (size_t i = 1; i < token.size(); i++) cmd.options.push_back(token[i]);
            }

            else cmd.parameters.push_back(token);
        }
        cmd.rawArgs.push_back(token);
    }

    return cmd;
}

pipeline parsePipeline(std::string &input) {
    pipeline ppn;
    std::string segment;
    std::stringstream ss(input);

    while (std::getline(ss, segment, '|')) {
        if (segment.find_first_not_of(" \t\n\r") == std::string::npos) continue;
        ppn.commands.push_back(parseCommand(segment));
    }

    return ppn;
}

