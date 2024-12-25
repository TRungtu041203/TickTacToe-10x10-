#pragma once
// PlayerManager.h
#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include <vector>
#include <string>

class PlayerManager {
public:
    // Load all players from a history file
    void loadPlayersFromFile(const std::string& filename);

    // Save all players back to the file
    void savePlayersToFile(const std::string& playerName, int result) const;

    // Search for a player by name and print their details
    void searchPlayerByName(const std::string& name) const;

    void updatePlayerRecord(const std::string& name, bool isWin, bool isDraw);

    // Find the closest level match for a player
    const Player* findClosestLevelPlayer(const Player& target) const;


private:
    std::vector<Player> players;
};

#endif
#pragma once
