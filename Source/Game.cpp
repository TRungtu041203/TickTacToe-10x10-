// File: Game.cpp
#include "Game.h"
#include "Utilities.h"
#include "PlayerManager.h"
#include <iostream>
#include <ReplayManager.h>
#include <windows.h>
using namespace std;

Game::Game(string p1, Bot* b) : player1Name(p1), bot(b), isGameOver(false) {
    board.resize(10, vector<char>(10, ' '));
}

void Game::displayBoard() {
    system("CLS");
    Textcolor(14); // Orange color for the entire board
    cout << "    ";
    for (int i = 0; i < board.size(); ++i) cout << i << "   ";
    cout << endl;

    cout << "   +";
    for (int i = 0; i < board.size(); ++i) cout << "---+";
    cout << endl;

    for (int i = 0; i < board.size(); ++i) {
        cout << i << "  | ";
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 'X') {
                Textcolor(12); // Red for player moves
            }
            else if (board[i][j] == 'O') {
                Textcolor(10); // Green for bot moves
            }
            else {
                Textcolor(14); // Orange for empty cells to match the board
            }
            cout << board[i][j];
            Textcolor(14); // Reset to orange board color
            cout << " | ";
        }
        cout << endl;

        cout << "   +";
        for (int j = 0; j < board[i].size(); ++j) cout << "---+";
        cout << endl;
    }
    Textcolor(7); // Reset to default
}

std::vector<std::string> Game::startGameWithBot() {
    PlayerManager playerManager;
    std::vector<std::string> moves; // Collect all moves
    int x, y;
    char currentPlayer = 'X';
    while (!isGameOver) {
        displayBoard();
        if (currentPlayer == 'X') {
            cout << "Player " << player1Name << "'s turn. Enter row and column: ";
            cin >> x >> y;
            if (placeMove(x, y, currentPlayer)) {
                moves.push_back(player1Name + ": (" + to_string(x) + ", " + to_string(y) + ")");
                if (checkWin(currentPlayer)) {
                    announceWinner(currentPlayer);
                    playerManager.savePlayersToFile(player1Name, 0);
                    return moves;
                }
                currentPlayer = 'O';
            }
            else {
                cout << "Invalid move. Try again." << endl;
            }
        }
        else {
            cout << "BOT's turn...\n";
            pair<int, int> move = bot->getMove(board, 'O');
            placeMove(move.first, move.second, 'O');
            moves.push_back("BOT: (" + to_string(move.first) + ", " + to_string(move.second) + ")");
            if (checkWin('O')) {
                announceWinner('O');
                playerManager.savePlayersToFile(player1Name, 1);
                return moves;
            }
            currentPlayer = 'X';
        }
    }
    return moves;
}


bool Game::placeMove(int x, int y, char symbol) {
    if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() && board[x][y] == ' ') {
        board[x][y] = symbol;
        return true;
    }
    return false;
}

bool Game::checkWin(char symbol) {
    // Check rows and columns
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size() - 4; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol && board[i][j + 3] == symbol && board[i][j + 4] == symbol)
                return true;
        }
    }
    for (int i = 0; i < board.size() - 4; i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol && board[i + 3][j] == symbol && board[i + 4][j] == symbol)
                return true;
        }
    }

    // Check diagonals
    for (int i = 0; i < board.size() - 4; i++) {
        for (int j = 0; j < board.size() - 4; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol && board[i + 4][j + 4] == symbol)
                return true;
        }
    }
    for (int i = 4; i < board.size(); i++) {
        for (int j = 0; j < board.size() - 4; j++) {
            if (board[i][j] == symbol && board[i - 1][j + 1] == symbol && board[i - 2][j + 2] == symbol && board[i - 3][j + 3] == symbol && board[i - 4][j + 4] == symbol)
                return true;
        }
    }

    return false;
}


void Game::announceWinner(char symbol) {
    displayBoard();

    cout << (symbol == 'X' ? player1Name : "BOT") << " wins!\n";
    isGameOver = true;
}
// File: Bot.cpp