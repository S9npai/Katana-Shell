#include <string>
#include <deque>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "include/utils.h"
#include <filesystem>


std::deque<std::string> command_history;
const size_t Max_history = 25;
std::string history_file = "assets/history.txt";

void saveHistory() {
    std::ofstream ofs(history_file, std::ios::trunc);
    if (!ofs.is_open()) return;

    for (const auto& cmd : command_history) {
        ofs << cmd << "\n";
    }
    ofs.close();
}

void addToHistory(const std::string &cmd) {
    if (cmd.empty()) return;
    if (!command_history.empty() && command_history.back() == cmd) return;

    command_history.push_back(cmd);
    if (command_history.size() > Max_history) {
        command_history.pop_front();
    }
}

void showHistory() {
    if (command_history.empty()) {
        std::cout << "History is empty. Go do something memorable." << std::endl;
        return;
    }

    int index = 1;
    for (const auto& cmd : command_history) {
        std::cout << " " << std::setw(3) << index++ << "  " << cmd << std::endl;
    }
}

void loadHistory() {
    if (!std::filesystem::exists("assets")) {
        std::filesystem::create_directory("assets");
    }

    std::ifstream ifs(history_file);
    if (!ifs.is_open()) return;

    std::string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) command_history.push_back(line);
    }
}

void displayManual() {
    std::string manualPath = "Katana-Shell reference.txt";
    std::ifstream manual(manualPath);

    if (!manual.is_open()) {
        std::cerr << "Error: Command reference " << manualPath << " not found." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(manual, line)) {
        std::cout << line << std::endl;
    }

    manual.close();
}

