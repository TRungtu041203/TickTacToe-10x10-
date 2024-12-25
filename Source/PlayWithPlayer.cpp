#include "PlayWithPlayer.h"
#include <iostream>
#include <vector>
#include <PlayerManager.h>
using namespace std;

std::vector<std::string> PlayWithPlayer::startGame() {
    PlayerManager playerManager;
    std::vector<std::string> moves; // Collect all moves
    string player1, player2;
    cout << "Enter Player 1's name: ";
    cin >> player1;
    cout << "Enter Player 2's name: ";
    cin >> player2;

    vector<vector<char>> board(10, vector<char>(10, ' '));
    char currentPlayer = 'X';
    bool gameWon = false;

    while (!gameWon) {
        system("CLS");
        displayBoard(board);

        int x, y;
        cout << (currentPlayer == 'X' ? player1 : player2) << "'s turn. Enter row and column: ";
        cin >> x >> y;

        if (x >= 0 && x < 10 && y >= 0 && y < 10 && board[x][y] == ' ') {
            board[x][y] = currentPlayer;
            moves.push_back((currentPlayer == 'X' ? player1 : player2) + ": (" + to_string(x) + ", " + to_string(y) + ")");

            if (checkWin(board, currentPlayer)) {
                system("CLS");
                displayBoard(board);
                cout << (currentPlayer == 'X' ? player1 : player2) << " wins!\n";
                playerManager.savePlayersToFile((currentPlayer == 'X' ? player1 : player2), 0);
                playerManager.savePlayersToFile((currentPlayer == 'X' ? player2 : player1), 1);
                break;
            }
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        else {
            cout << "Invalid move. Try again." << endl;
        }
    }
    return moves;
}


void PlayWithPlayer::displayBoard(const vector<vector<char>>& board) const {
    cout << "    ";
    for (int i = 0; i < 10; ++i) cout << i << "   ";
    cout << endl;
    cout << "   +";
    for (int i = 0; i < 10; ++i) cout << "---+";
    cout << endl;
    for (int i = 0; i < 10; ++i) {
        cout << i << "  | ";
        for (int j = 0; j < 10; ++j) {
            cout << board[i][j] << " | ";
        }
        cout << endl;
        cout << "   +";
        for (int j = 0; j < 10; ++j) cout << "---+";
        cout << endl;
    }
}

bool PlayWithPlayer::checkWin(const vector<vector<char>>& board, char currentPlayer) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j] == currentPlayer && board[i][j + 1] == currentPlayer &&
                board[i][j + 2] == currentPlayer && board[i][j + 3] == currentPlayer &&
                board[i][j + 4] == currentPlayer) {
                return true;
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == currentPlayer && board[i + 1][j] == currentPlayer &&
                board[i + 2][j] == currentPlayer && board[i + 3][j] == currentPlayer &&
                board[i + 4][j] == currentPlayer) {
                return true;
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j] == currentPlayer && board[i + 1][j + 1] == currentPlayer &&
                board[i + 2][j + 2] == currentPlayer && board[i + 3][j + 3] == currentPlayer &&
                board[i + 4][j + 4] == currentPlayer) {
                return true;
            }
        }
    }

    for (int i = 4; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j] == currentPlayer && board[i - 1][j + 1] == currentPlayer &&
                board[i - 2][j + 2] == currentPlayer && board[i - 3][j + 3] == currentPlayer &&
                board[i - 4][j + 4] == currentPlayer) {
                return true;
            }
        }
    }

    return false;
}

