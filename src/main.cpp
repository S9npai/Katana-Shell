#include <iostream>
#include <string>
#include "include/logo.h"


int main() {
    drawLogo();
    while (true) {
        showPrompt();
        std::string input;
        std::getline(std::cin, input);
    }
}

