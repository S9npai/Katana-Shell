#include <iostream>
#include <string>
#include <csignal>
#include "include/executor.hpp"
#include "include/parser.hpp"
#include "include/types.hpp"
#include "include/logo.h"
#include "pipeline.hpp"
#include "signals.h"


int main() {
    setupParentSignals();
    drawLogo();

    while (true) {
        showPrompt();

        std::string input;
        if (!std::getline(std::cin, input)) break;

        if (input.empty()) continue;

        if (input.find('|') != std::string::npos) {
            pipeline ppn = parsePipeline(input);
            pipelineHandler(ppn);
        }

        else {
            Command cmd = parseCommand(input);
            executeInternal(cmd);
        }
    }

    return 0;
}

