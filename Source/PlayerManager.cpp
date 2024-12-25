// PlayerManager.cpp
#include "PlayerManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "Utilities.h"
#include <cmath>

struct PlayerStats {
    std::string name;
    int wins;
    int losses;
    int draws;
};

void PlayerManager::loadPlayersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        Player player = Player::fromString(line);
        players.push_back(player);
    }

    file.close();
}

void PlayerManager::savePlayersToFile(const std::string& playerName, int result) const {
    // Check file existance
    std::string filename = "Player.txt";
    std::ifstream testFile(filename);
    if (!testFile.is_open()) {
        // File does not exist then create it
        std::ofstream createFile(filename);
        if (!createFile.is_open()) {
            std::cerr << "Error: Unable to create file " << filename << "\n";
            return;
        }
        createFile.close();
    }
    else {
        testFile.close();
    }

    std::ifstream playerFile(filename);

    if (!playerFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    std::vector<PlayerStats> players;
    std::string line;
    bool modified = false;

    while (std::getline(playerFile, line)) {
        std::istringstream iss(line);
        PlayerStats player;
        if (iss >> player.name >> player.wins >> player.losses >> player.draws) {
            if (player.name == playerName) {
                // Update the player's stats if the name matches
                player.wins += (result == 0) ? 1 : 0;
                player.losses += (result == 1) ? 1 : 0;
                player.draws += (result == 2) ? 1 : 0;
                modified = true;
            }
            players.push_back(player);
        }
    }
    playerFile.close();

    std::ofstream outputFile(filename, std::ios::trunc);
    if (!outputFile) {
        std::cerr << "Cannot open file to write.\n";
        return;
    }

    for (const auto& outputLine : players) {
        outputFile << outputLine.name << " " <<
            outputLine.wins << " " << 
            outputLine.losses << " " << 
            outputLine.draws << '\n';
    }

    if (!modified) {
        outputFile << playerName << " " <<
            ((result == 0) ? 1 : 0) << " " <<
            ((result == 1) ? 1 : 0) << " " <<
            ((result == 2) ? 1 : 0) << "\n";

    }

    outputFile.close();
    std::cout << "Player info saved.\n";

    outputFile.close();
}



void PlayerManager::searchPlayerByName(const std::string& name) const {
    system("CLS"); // Clear the screen before starting the search
    bool found = false;
    // Header for search results
    Textcolor(14); // Yellow
    std::cout << "\n*------- SEARCH RESULTS -------*\n";
    Textcolor(7); // Default color

    for (const auto& player : players) {
        if (player.getName() == name) {
            found = true;

            // Display player details
            Textcolor(10); // Green for success
            std::cout << "\nPlayer Found:\n";
            Textcolor(7); // Default color
            player.printInfo();

            // Suggest the closest level player
            const Player* closestMatch = findClosestLevelPlayer(player);
            if (closestMatch) {
                Textcolor(14); // Yellow for suggestions
                std::cout << "\nSuggested Match:\n";
                Textcolor(7); // Default color
                closestMatch->printInfo();
            }
            break; // Exit loop after finding the player
        }
    }

    if (!found) {
        Textcolor(12); // Red for not found
        std::cout << "\nPlayer not found!\n";
    }
    Textcolor(7); // Reset to default color
    system("pause"); // Pause to allow the user to read the output
}

const Player* PlayerManager::findClosestLevelPlayer(const Player& target) const {
    const Player* closest = nullptr;
    double minDifference = (std::numeric_limits<double>::max)();

    for (const auto& player : players) {
        if (player.getName() == target.getName()) continue; // Skip the same player

        double diff = std::abs(target.getLevel() - player.getLevel());
        if (diff < minDifference) {
            closest = &player;
            minDifference = diff;
        }
    }

    return closest;
}

void PlayerManager::updatePlayerRecord(const std::string& name, bool isWin, bool isDraw) {
    for (auto& player : players) {
        if (player.getName() == name) {
            if (isWin) {
                player.addWin();
            }
            else if (isDraw) {
                player.addDraw();
            }
            else {
                player.addLoss();
            }
            return;
        }
    }
    // If player not found, add as a new player
    players.emplace_back(name, isWin ? 1 : 0, isWin ? 0 : 1, isDraw ? 1 : 0);
}
