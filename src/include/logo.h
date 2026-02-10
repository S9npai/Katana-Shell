#ifndef LOGO_H
#define LOGO_H
#include <iostream>
#include <string>
#include <vector>


struct palette {
    inline static std::string cyan = "\033[38;5;81m";
    inline static std::string blue = "\033[38;5;105m";
    inline static std::string bold = "\033[1m";
    inline static std::string reset = "\033[0m";
};

void drawLogo() {
    std::vector <std::string> logo = {
        "__          __ __      __                         _____ __         ____     ",
        "\\ \\        / //_/___ _/ /_____ _____  ____ _     / ___// /_  ___  / / /     ",
        " \\ \\      / ,< / __ `/ __/ __ `/ __ \\/ __ `/_____\\__ \\/ __ \\/ _ \\/ / / ",
        " / /     / /| / /_/ / /_/ /_/ / / / / /_/ /_____/__/ / / / /  __/ / /       ",
        "/_/     /_/ |_\\__,_/\\__/\\__,_/_/ /_/\\__,_/     /____/_/ /_/\\___/_/_/   ",
        "                                                                              "
    };

    for (const auto& line : logo) {
        std::cout << palette::bold << palette::cyan << line << palette::reset << std::endl;
    }
}

void showPrompt() {
    std::cout << palette::bold << palette::cyan << palette::blue << "Katana ヿニ ▶ " << palette::reset << std::flush << std::endl;
}

#endif


