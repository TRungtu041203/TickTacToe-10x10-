// File: Game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Bot.h"
using namespace std;

class Game {
private:
    vector<vector<char>> board;
    bool isGameOver;
    string player1Name;
    Bot* bot;

public:
    Game(string p1, Bot* b = nullptr);
    void displayBoard();
    vector<string> startGameWithBot();

private:
    bool placeMove(int x, int y, char symbol);
    bool checkWin(char symbol);
    void announceWinner(char symbol);
    void endGameWithResult(bool playerWon, bool isDraw);
};

#endif // GAME_H