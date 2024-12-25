// ReplayManager.cpp
#include "ReplayManager.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <sstream>

void ReplayManager::saveReplay(const std::string& fileName, const std::vector<std::string>& moves) const {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to save replay to file " << fileName << "\n";
        return;
    }

    for (const auto& move : moves) {
        file << move << "\n";
    }

    file.close();
    std::cout << "Replay saved to " << fileName << "\n";
}

std::vector<std::string> ReplayManager::loadReplay(const std::string& fileName) const {
    std::vector<std::string> moves;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to load replay from file " << fileName << "\n";
        return moves;
    }

    std::string line;
    while (std::getline(file, line)) {
        moves.push_back(line);
    }

    file.close();
    return moves;
}

void ReplayManager::rewatchReplay(const std::string& fileName) const {
    std::vector<std::string> moves = loadReplay(fileName);
    if (moves.empty()) {
        std::cerr << "No replay data available to rewatch." << std::endl;
        return;
    }

    // Initialize an empty 10x10 board
    std::vector<std::vector<char>> board(10, std::vector<char>(10, ' '));

    std::cout << "Rewatching Replay: " << fileName << "\n";
    int moveCount = 0;
    for (const auto& move : moves) {
        // Parse the move
        std::istringstream iss(move);
        std::string player;
        int x, y;
        char colon, comma, paren;

        if (!(iss >> player >> paren >> x >> comma >> y >> paren)) {
            std::cerr << "Error parsing move: " << move << "\n";
            continue;
        }

        // Determine the symbol based on move count
        char symbol = (moveCount % 2 == 0) ? 'X' : 'O';
        moveCount++;

        // Place the move on the board
        board[x][y] = symbol;

        // Display the board
        system("CLS");
        std::cout << "    ";
        for (int i = 0; i < 10; ++i) std::cout << i << "   ";
        std::cout << "\n";

        std::cout << "   +";
        for (int i = 0; i < 10; ++i) std::cout << "---+";
        std::cout << "\n";

        for (int i = 0; i < 10; ++i) {
            std::cout << i << "  | ";
            for (int j = 0; j < 10; ++j) {
                std::cout << (board[i][j] == ' ' ? ' ' : board[i][j]) << " | ";
            }
            std::cout << "\n";
            std::cout << "   +";
            for (int j = 0; j < 10; ++j) std::cout << "---+";
            std::cout << "\n";
        }

        // Display the move and wait
        std::cout << "Move: " << move << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
