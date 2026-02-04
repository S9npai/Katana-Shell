#include <iostream>
#include <string>
#include "include/logo.h"
using namespace std;


int main() {
    drawLogo();
    while (true) {
        showPrompt();
        string input;
        getline(std::cin, input);
    }
}

