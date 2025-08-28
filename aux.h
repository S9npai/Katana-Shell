#ifdef AUX
#endif
#include<bits/stdc++.h>
#include<ncurses/curses.h>
// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define nl <<endl;
using namespace std;

// 256-color ANSI format: \033[38;5;COLORm for foreground
string ansiColor(int color) {
    return "\033[38;5;" + to_string(color) + "m";
}

void drawLogo() {
    // color gradient (using 256-color palette)
    vector<string> logoLines = {
        "░░███░░░░███░░░░░░█████░░░░░░███████████░░░░░░█████░░░░░░███░░░░███░░░░░░░█████░░░░░░░░░░░█████████░░░███░░░░███░░█████████░░███░░░░░░░░███░░░░░░░░░░░░███░░░░░░░",
        "░░███░░███░░░░░░░███████░░░░░░░░░███░░░░░░░░░███████░░░░░█████░░███░░░░░░███████░░░░░░░░░███░░░░░░░░░░███░░░░███░░███░░░░░░░░███░░░░░░░░███░░░░░░░░░░░░░███░░░░░░",
        "░░███████░░░░░░░███░░░███░░░░░░░░███░░░░░░░░███░░░███░░░░██████████░░░░░███░░░███░░░░░░░░░█████████░░░██████████░░█████████░░███░░░░░░░░███░░░░░░░░░░░░░░███░░░░░",
        "░░███░░███░░░░░███████████░░░░░░░███░░░░░░░███████████░░░███░░█████░░░░███████████░░░░░░░░░░░░░░░███░░███░░░░███░░███░░░░░░░░███░░░░░░░░███░░░░░░░░░░░░░███░░░░░░",
        "░░███░░░░███░░███░░░░░░░███░░░░░░███░░░░░░███░░░░░░░███░░███░░░░███░░░███░░░░░░░███░░░░░░░█████████░░░███░░░░███░░█████████░░█████████░░█████████░░░░░░███░░░░░░░"
    };

    // Color progression
    vector<int> colors = {129, 135, 141, 147, 153, 159};

    cout << BOLD;
    for (size_t i = 0; i < logoLines.size(); i++) {
        // Use different color for each line
        int colorIndex = (i * colors.size()) / logoLines.size();
        cout << ansiColor(colors[colorIndex]) << logoLines[i] << endl;
    }
    cout << RESET << endl;
}