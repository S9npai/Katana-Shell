#include <string>
#include <deque>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <pwd.h>
#include <unistd.h>
#include "include/utils.h"


std::deque<std::string> command_history;
const size_t Max_history = 25;


// Resolves HOME at runtime — safe for any user on any machine
static std::string getHome() {
    const char* home = getenv("HOME");
    if (!home) home = getpwuid(getuid())->pw_dir;  // fallback if HOME unset
    return std::string(home);
}

// KATANA_DATA_SUFFIX and KATANA_HISTORY_SUFFIX are injected by CMake
// as plain relative strings like ".local/share/katana-shell"
static const std::string history_file = getHome() + "/" + KATANA_HISTORY_SUFFIX;
static const std::string data_dir     = getHome() + "/" + KATANA_DATA_SUFFIX;


void saveHistory() {
    std::ofstream ofs(history_file, std::ios::trunc);
    if (!ofs.is_open()) return;

    for (const auto& cmd : command_history)
        ofs << cmd << "\n";
}

void addToHistory(const std::string &cmd) {
    if (cmd.empty()) return;
    if (!command_history.empty() && command_history.back() == cmd) return;

    command_history.push_back(cmd);
    if (command_history.size() > Max_history)
        command_history.pop_front();
}

void showHistory() {
    if (command_history.empty()) {
        std::cout << "History is empty. Go do something memorable." << std::endl;
        return;
    }

    int index = 1;
    for (const auto& cmd : command_history)
        std::cout << " " << std::setw(3) << index++ << "  " << cmd << std::endl;
}

void loadHistory() {
    std::ifstream ifs(history_file);
    if (!ifs.is_open()) return;  // first run, file doesn't exist yet — that's fine

    std::string line;
    while (std::getline(ifs, line))
        if (!line.empty()) command_history.push_back(line);
}

void displayManual() {
    std::string manualPath = data_dir + "/Katana-Shell reference.txt";
    std::ifstream manual(manualPath);

    if (!manual.is_open()) {
        std::cerr << "Error: manual not found at " << manualPath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(manual, line))
        std::cout << line << std::endl;
}

