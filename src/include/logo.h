#ifndef LOGO_H
#define LOGO_H
#include <iostream>
#include <string>
#include <vector>


struct palette {
    inline static std::string magenta = "\033[35m";
    inline static std::string cyan = "\033[36m";
};

void drawLogo() {
    std::vector <std::string> logo = {
        "  __          __ __      __                         _____ __         ____     ",
        "  \\ \\        / //_/___ _/ /_____ _____  ____ _     / ___// /_  ___  / / /     ",
        "   \\ \\      / ,< / __ `/ __/ __ `/ __ \\/ __ `/_____\\__ \\/ __ \\/ _ \\/ / / ",
        "   / /     / /| / /_/ / /_/ /_/ / / / / /_/ /_____/__/ / / / /  __/ / /       ",
        "  /_/     /_/ |_\\__,_/\\__/\\__,_/_/ /_/\\__,_/     /____/_/ /_/\\___/_/_/   ",
        "                                                                              "
    };

    for (const auto& line : logo) {
        std::cout << line << std::endl;
    }
}

void showPrompt() {
    std::cout << palette::cyan << "Katana ニヿ ▶ " << std::endl;
}

#endif

