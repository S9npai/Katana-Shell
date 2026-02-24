#include <iostream>
#include <string>
#include <unistd.h>
#include "include/executor.hpp"
#include "include/parser.hpp"
#include "include/types.hpp"
#include "include/logo.h"
#include "../include/pipeline.hpp"
#include "signals.h"
#include "utils.h"


int main() {
    setpgid(0, 0);
    tcsetpgrp(STDIN_FILENO, getpgrp());

    setupParentSignals();
    loadHistory();
    drawLogo();

    while (true) {
        showPrompt();

        std::string input;
        if (!std::getline(std::cin, input)) {
            if (std::cin.eof()) {
                std::cout << "\n";
                saveHistory();
                break;
            }
            std::cin.clear();
            std::cout << "\n";
            continue;
        }

        if (input.empty() || input.find_first_not_of(" \t\n\r") == std::string::npos ) continue;

        addToHistory(input);

        if (input.find('|') != std::string::npos) {
            pipeline ppn = parsePipeline(input);
            pipelineHandler(ppn);
        }

        else {
            Command cmd = parseCommand(input);
            executeInternal(cmd);
        }
    }

    saveHistory();
    return 0;
}

