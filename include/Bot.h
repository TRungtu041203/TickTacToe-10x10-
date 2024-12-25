#ifndef BOT_H
#define BOT_H

#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

class Bot {
public:
    enum Difficulty { EASY, NORMAL, HARD };
    Difficulty level;

    Bot(Difficulty lvl) : level(lvl) {}

    // Public methods
    pair<int, int> getMove(vector<vector<char>>& board, char playerSymbol);

private:
    // Easy mode: Random move
    pair<int, int> easyMove(vector<vector<char>>& board);

    // Iterative deepening with alpha-beta pruning
    pair<int, int> iterativeDeepening(vector<vector<char>>& board, char playerSymbol, int maxDepth);

    // Minimax with Alpha-Beta pruning
    pair<int, int> minimaxMoveAlphaBeta(vector<vector<char>>& board, char playerSymbol, int depth, int alpha, int beta, bool maximizing);

    // Minimax and Alpha-Beta pruning methods
    int minimaxAlphaBeta(vector<vector<char>>& board, int depth, int alpha, int beta, bool maximizing, char playerSymbol);

    // Helper for move prioritization
    void prioritizeMoves(vector<pair<int, int>>& moves, const vector<vector<char>>& board, char playerSymbol);

    // Helper to get playable moves around active gameplay
    vector<pair<int, int>> getPlayableMoves(const vector<vector<char>>& board, const set<pair<int, int>>& activeMoves);

    // Evaluation function
    int evaluate(vector<vector<char>>& board, char playerSymbol);

    // Scoring helper function
    int calculateScore(int playerCount, int opponentCount);

    // Board state serialization for transposition table
    string serializeBoard(const vector<vector<char>>& board);
};

#endif // BOT_H
