// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <sstream>

class Player {
private:
    std::string name;
    int wins;
    int losses;
    int draws;
    double level; // Calculated as (wins - losses) / total games

    void updateLevel() {
        int totalGames = wins + losses + draws;
        level = totalGames > 0 ? static_cast<double>(wins - losses) / totalGames : 0;
    }

public:
    Player(const std::string& name, int wins, int losses, int draws)
        : name(name), wins(wins), losses(losses), draws(draws) {
        updateLevel();
    }

    std::string getName() const { return name; }
    double getLevel() const { return level; }

    void printInfo() const {
        std::cout << "Name: " << name << "\nWins: " << wins
            << "\nLosses: " << losses << "\nDraws: " << draws
            << "\nRatio (Win vs Loss): " << level << "\n";
    }

    static Player fromString(const std::string& line) {
        std::istringstream iss(line);
        std::string name;
        int wins, losses, draws;
        iss >> name >> wins >> losses >> draws;
        return Player(name, wins, losses, draws);
    }

    static std::string serialize(const Player& player) {
        std::ostringstream oss;
        oss << player.name << " " << player.wins << " " << player.losses << " " << player.draws;
        return oss.str();
    }

    void addWin() {
        wins++;
        updateLevel();
    }

    void addLoss() {
        losses++;
        updateLevel();
    }

    void addDraw() {
        draws++;
        updateLevel();
    }
};

#endif
