#pragma once
#ifndef PLAYWITHPLAYER_H
#define PLAYWITHPLAYER_H

#include <vector>
#include <string>

class PlayWithPlayer {
public:
    // Start the game for two players
    std::vector<std::string> startGame();

private:
    // Display the current state of the board
    void displayBoard(const std::vector<std::vector<char>>& board) const;

    // Check if the current player has won the game
    bool checkWin(const std::vector<std::vector<char>>& board, char currentPlayer) const;
};

#endif
