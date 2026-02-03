#ifndef LOGO_H
#define LOGO_H
#include <iostream>
#include<string>
#include<vector>
using namespace std;


struct palette {
    inline static string magenta = "\033[35m";
    inline static string cyan = "\033[36m";
};

void drawlogo() {
    vector <string> logo = {
        "  __          __ __      __                         _____ __         ____     ",
        "  \\ \\        / //_/___ _/ /_____ _____  ____ _     / ___// /_  ___  / / /     ",
        "   \\ \\      / ,< / __ `/ __/ __ `/ __ \\/ __ `/_____\\__ \\/ __ \\/ _ \\/ / / ",
        "   / /     / /| / /_/ / /_/ /_/ / / / / /_/ /_____/__/ / / / /  __/ / /       ",
        "  /_/     /_/ |_\\__,_/\\__/\\__,_/_/ /_/\\__,_/     /____/_/ /_/\\___/_/_/   ",
        "                                                                              "
    };

    for (const auto& line : logo) {
        cout << line << endl;
    }
}

void show_prompt() {
    cout << palette::cyan << "Katana ニヿ ▶ " << endl;
}

#endif

