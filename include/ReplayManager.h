// ReplayManager.h
#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class ReplayManager {
public:
    // Save a replay of the game moves to a file
    void saveReplay(const std::string& fileName, const std::vector<std::string>& moves) const;

    // Load a replay from a file and return the moves
    std::vector<std::string> loadReplay(const std::string& fileName) const;

    // Rewatch the game move by move
    void rewatchReplay(const std::string& fileName) const;
};

#endif