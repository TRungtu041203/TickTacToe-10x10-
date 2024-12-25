#include "Bot.h"
#include <set>
#include <unordered_map>
#include <iostream>

// Transposition Table
unordered_map<string, int> transpositionTable;

pair<int, int> Bot::getMove(vector<vector<char>>& board, char playerSymbol) {
    // Clear transposition table for each game
    transpositionTable.clear();

    if (level == EASY) {
        return easyMove(board);
    }
    else if (level == NORMAL) {
        return iterativeDeepening(board, playerSymbol, 10); // Depth 3
    }
    else {
        return iterativeDeepening(board, playerSymbol, 15); // Depth 10 for hard mode
    }
}

vector<pair<int, int>> Bot::getPlayableMoves(const vector<vector<char>>& board, const set<pair<int, int>>& activeMoves) {
    set<pair<int, int>> playableMoves;
    for (const auto& move : activeMoves) {
        int x = move.first;
        int y = move.second;
        for (int i = max(0, x - 1); i <= min((int)board.size() - 1, x + 1); i++) {
            for (int j = max(0, y - 1); j <= min((int)board[0].size() - 1, y + 1); j++) {
                if (board[i][j] == ' ') {
                    playableMoves.insert({ i, j });
                }
            }
        }
    }
    return vector<pair<int, int>>(playableMoves.begin(), playableMoves.end());
}
pair<int, int> Bot::easyMove(vector<vector<char>>& board) {
    vector<pair<int, int>> possibleMoves;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == ' ') {
                possibleMoves.push_back({ i, j });
            }
        }
    }
    if (!possibleMoves.empty()) {
        return possibleMoves[rand() % possibleMoves.size()];
    }
    return { -1, -1 };
}

pair<int, int> Bot::iterativeDeepening(vector<vector<char>>& board, char playerSymbol, int maxDepth) {
    pair<int, int> bestMove = { -1, -1 };
    for (int depth = 3; depth <= maxDepth; depth++) {
        bestMove = minimaxMoveAlphaBeta(board, playerSymbol, depth, -10000, 10000, true);
    }
    return bestMove;
}

pair<int, int> Bot::minimaxMoveAlphaBeta(vector<vector<char>>& board, char playerSymbol, int depth, int alpha, int beta, bool maximizing) {
    set<pair<int, int>> activeMoves;

    // Update active moves dynamically
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != ' ') {
                activeMoves.insert({ i, j });
            }
        }
    }

    vector<pair<int, int>> possibleMoves = getPlayableMoves(board, activeMoves);
    if (possibleMoves.empty()) {
        // If no adjacent moves are available, consider the entire board
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == ' ') {
                    possibleMoves.push_back({ i, j });
                }
            }
        }
    }

    prioritizeMoves(possibleMoves, board, playerSymbol);

    char opponent = (playerSymbol == 'X') ? 'O' : 'X';
    int bestScore = maximizing ? -10000 : 10000;
    pair<int, int> bestMove = { -1, -1 };

    for (const auto& move : possibleMoves) {
        int i = move.first, j = move.second;
        board[i][j] = maximizing ? playerSymbol : opponent;

        string boardState = serializeBoard(board);
        int score;

        if (transpositionTable.find(boardState) != transpositionTable.end()) {
            score = transpositionTable[boardState];
        }
        else {
            score = minimaxAlphaBeta(board, depth - 1, alpha, beta, !maximizing, playerSymbol);
            transpositionTable[boardState] = score;
        }

        board[i][j] = ' ';

        if (maximizing) {
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
            alpha = max(alpha, score);
        }
        else {
            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
            beta = min(beta, score);
        }
        if (beta <= alpha) break;
    }
    return bestMove;
}

int Bot::minimaxAlphaBeta(vector<vector<char>>& board, int depth, int alpha, int beta, bool maximizing, char playerSymbol) {
    char opponent = (playerSymbol == 'X') ? 'O' : 'X';
    int evaluation = evaluate(board, playerSymbol);
    if (depth == 0 || evaluation == 100 || evaluation == -100) {
        return evaluation;
    }

    vector<pair<int, int>> possibleMoves;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == ' ') {
                possibleMoves.push_back({ i, j });
            }
        }
    }

    if (possibleMoves.empty()) {
        return 0; // Draw condition
    }

    int bestScore = maximizing ? -10000 : 10000;
    for (const auto& move : possibleMoves) {
        int i = move.first, j = move.second;
        board[i][j] = maximizing ? playerSymbol : opponent;
        int score = minimaxAlphaBeta(board, depth - 1, alpha, beta, !maximizing, playerSymbol);
        board[i][j] = ' ';

        if (maximizing) {
            bestScore = max(bestScore, score);
            alpha = max(alpha, score);
        }
        else {
            bestScore = min(bestScore, score);
            beta = min(beta, score);
        }
        if (beta <= alpha) break;
    }
    return bestScore;
}

int Bot::evaluate(vector<vector<char>>& board, char playerSymbol) {
    char opponent = (playerSymbol == 'X') ? 'O' : 'X';
    int score = 0;

    // Scoring patterns
    const int WIN_SCORE = 100;
    const int FOUR_IN_ROW = 50;
    const int THREE_IN_ROW = 20;
    const int TWO_IN_ROW = 10;
    const int CENTER_BONUS = 15; // Increased center bonus for early moves

    // Check rows
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size() - 4; j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i][j + k] == playerSymbol) playerCount++;
                if (board[i][j + k] == opponent) opponentCount++;
            }
            score += calculateScore(playerCount, opponentCount);
        }
    }

    // Check columns
    for (int i = 0; i < board.size() - 4; i++) {
        for (int j = 0; j < board[i].size(); j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j] == playerSymbol) playerCount++;
                if (board[i + k][j] == opponent) opponentCount++;
            }
            score += calculateScore(playerCount, opponentCount);
        }
    }

    // Check diagonals
    for (int i = 0; i < board.size() - 4; i++) {
        for (int j = 0; j < board[i].size() - 4; j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i + k][j + k] == playerSymbol) playerCount++;
                if (board[i + k][j + k] == opponent) opponentCount++;
            }
            score += calculateScore(playerCount, opponentCount);
        }
    }

    // Check anti-diagonals
    for (int i = 4; i < board.size(); i++) {
        for (int j = 0; j < board[i].size() - 4; j++) {
            int playerCount = 0, opponentCount = 0;
            for (int k = 0; k < 5; k++) {
                if (board[i - k][j + k] == playerSymbol) playerCount++;
                if (board[i - k][j + k] == opponent) opponentCount++;
            }
            score += calculateScore(playerCount, opponentCount);
        }
    }

    // Bonus for central positions
    for (int i = 3; i < board.size() - 3; i++) {
        for (int j = 3; j < board[i].size() - 3; j++) {
            if (board[i][j] == playerSymbol) score += CENTER_BONUS;
            if (board[i][j] == opponent) score -= CENTER_BONUS;
        }
    }

    return score;
}

int Bot::calculateScore(int playerCount, int opponentCount) {
    if (playerCount > 0 && opponentCount > 0) return 0; // Mixed line, no score
    if (playerCount == 5) return 100;
    if (opponentCount == 5) return -100;
    if (playerCount == 4) return 50;
    if (opponentCount == 4) return -50;
    if (playerCount == 3) return 20;
    if (opponentCount == 3) return -20;
    if (playerCount == 2) return 10;
    if (opponentCount == 2) return -10;
    return 0;
}

void Bot::prioritizeMoves(vector<pair<int, int>>& moves, const vector<vector<char>>& board, char playerSymbol) {
    vector<vector<char>> tempBoard = board; // Create a temporary copy
    sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
        tempBoard[a.first][a.second] = playerSymbol;
        int scoreA = evaluate(tempBoard, playerSymbol);
        tempBoard[a.first][a.second] = ' ';

        tempBoard[b.first][b.second] = playerSymbol;
        int scoreB = evaluate(tempBoard, playerSymbol);
        tempBoard[b.first][b.second] = ' ';

        return scoreA > scoreB;
        });
}

string Bot::serializeBoard(const vector<vector<char>>& board) {
    string result;
    for (const auto& row :
		board) { // Serialize the board state into a string for transposition table
		for (char cell : row) {
			result += cell;
		}
	}
	return result;
}