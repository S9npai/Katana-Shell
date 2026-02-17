#include <iostream>
#include <string>
#include "include/commands.h"
#include "include/executor.hpp"
#include "include/parser.hpp"
#include "include/types.hpp"
#include "include/logo.h"
#include <csignal>


int main() {
    signal(SIGINT, SIG_IGN);

    drawLogo();

    while (true) {
        showPrompt();

        std::string input;
        if (!std::getline(std::cin, input) || input == "exit") {
            break;
        }

        if (input.empty()) {
            continue;
        }

        Command cmd = parseCommand(input);

        executeInternal(cmd);
    }

    return 0;
}

