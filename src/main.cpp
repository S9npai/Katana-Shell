#include <iostream>
#include <string>
#include "include/logo.h"
#include "include/parser.hpp"
#include "include/executor.hpp"


int main() {
    drawLogo();
    while (true) {
        showPrompt();
        std::string input;
        if (!getline(std::cin, input) || input == "exit")
            break;

        if (input.empty()) continue;

        Command cmd = parseCommand(input);

        executeInternal(cmd);
    }
    return 0;
}

