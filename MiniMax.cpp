/* 
 * Minimax Implementation for ConnectR
 * Felipe Spinolo
 * CS4523 Artificial Intelligence
 * Dr. Michael Franklin
 * Project 2
 */

#include "Minimax.h"
#include <algorithm>

const size_t MiniMax::alphaBeta(tree& root) {

    /* Return the index of the best move we can find */

    int v = maximize( // currently looking 3 rounds (6 moves) ahead
        root, 6, std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    // find the child that has score v
    for (size_t i = 0; i < root.children.size(); ++i) {
        if (root.children[i].score == v) {
            return i;
        }
    }
    // if all else fails, pick the middle
    return root.children.size() / 2;

}

const int MiniMax::maximize(tree& current, size_t depth, int alpha, int beta) {

    /* Return the highest heuristic value from the moves available to us */

    if (winningMove(current.board, true)) { // Ouch.  Game over.
        current.score = std::numeric_limits<int>::min();
        return current.score;
    }

    if (depth == 0) { // Base case.  Run the heuristic.
        current.score = scoreBoard(current.board);
        return current.score;
    }
    // Recursive case.  Take the max of the mins.
    int v = std::numeric_limits<int>::min();
    size_t numChildren = current.children.size();
    for (size_t i = 0; i < numChildren; ++i) {
        std::vector<std::string> childBoard = makeMove(current.board, i, true);
        current.children[i] = tree(numChildren, childBoard);
        v = std::max(v, minimize(current.children[i], --depth, alpha, beta));
        if (v >= beta) { // ***PRUNE***
            return v;
        }
        alpha = std::max(alpha, v);
    }
    // We didn't prune.
    return v;

}

const int MiniMax::minimize(tree& current, size_t depth, int alpha, int beta) {

    /* Return the lowest heuristic value from the moves available to the
     * opponent */

    if (winningMove(current.board, false)) { // Our move was a winner!
        current.score = std::numeric_limits<int>::max();
        return current.score;
    }

    if (depth == 0) { // Base case.  Run the heuristic.
        current.score = scoreBoard(current.board);
        return current.score;
    }
    // Recursive case.  Take the min of the maxes.
    int v = std::numeric_limits<int>::max();
    size_t numChildren = current.children.size();
    for (size_t i = 0; i < numChildren; ++i) {
        std::vector<std::string> childBoard = makeMove(current.board, i, false);
        current.children[i] = tree(numChildren, childBoard);
        v = std::min(v, maximize(current.children[i], --depth, alpha, beta));
        if (v <= alpha) { // ***PRUNE***
            return v;
        }
        beta = std::min(beta, v);
    }
    // We didn't prune.
    return v;

}

const int MiniMax::scoreBoard(const std::vector<std::string>& board) {

    // TODO: Return a score for the given board

    return 0;

}

const bool MiniMax::winningMove(const std::vector<std::string>& board, const bool myTurn) {

    // TODO: Return true if the most recent move resulted in a win

    return false;

}

const std::vector<std::string> makeMove(
    const std::vector<std::string> board, const size_t move, const bool myTurn) {

    /* Return a new board after making the requested move */

    // We represent our tokens as Xs and theirs as Os
    char token = myTurn ? 'X' : 'O';
    board[move] += token;
    return board;

}

