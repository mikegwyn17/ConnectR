/* 
 * Minimax Implementation for ConnectR
 * Felipe Spinolo
 * CS4523 Artificial Intelligence
 * Dr. Michael Franklin
 * Project 2
 */

#include "MiniMax.h"
#include <algorithm>        // min and max and some others
#include <stdexcept>        // throw some exceptions
#include <cmath>            // so we can use exponents

size_t MiniMax::alphaBeta(tree& state) {

    /* Return the best move we can find */
    std::vector<int> topMoves;
    maximize(
        state, 6, std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    for (size_t i = 0; i < state.children.size(); ++i) {
        if (state.children[i].score == state.score) {
            topMoves.push_back(i);
        }
    }
    if (topMoves.size() == 1) {
        return topMoves[0];
    }
    // if we have multiple moves with the top score, pick one randomly
    int moveIndex = rand() % topMoves.size();
    return topMoves[moveIndex];


}

void MiniMax::maximize(tree& state, int depth, int alpha, int beta) {

    /* Our turn:
     * Find the best move from here and take its score for the current state
     */

    if (boardFull(state)) {     // can't go any further from here
        scoreState(state);
        if (!isWin(state.score)) {
            state.score = 0;   // a draw
        }
        return;
    }

    if (depth <= 0) {       // Base case.  Run the heuristic.
        scoreState(state);
        return;
    }
    // Recursive case.  Take the max of the mins.
    int v = std::numeric_limits<int>::min();
    size_t numChildren = state.children.size();
    for (size_t i = 0; i < numChildren; ++i) {
        try {
            state.children[i] = makeMove(state, i, true);
        } catch (const std::runtime_error&) {
            continue;
        }
        state.children[i].move = i;
        minimize(state.children[i], --depth, alpha, beta);
        //favor moves in the middle
        if (i == state.children.size() / 2 && !isWin(state.children[i].score)) {
            ++state.children[i].score;
        }
        v = std::max(v, state.children[i].score);
        if (v >= beta) {    // ***PRUNE***
            state.score = v;
            return;
        }
        alpha = std::max(alpha, v);
    }
    // We didn't prune.
    state.score = v;

}

void MiniMax::minimize(tree& state, int depth, int alpha, int beta) {

    /* Their turn:
     * Find the worst (for us, best for opponent) move from here and take its
     * score for the current state
     */

    if (boardFull(state)) {    // can't go any further from here
        scoreState(state);
        if (!isWin(state.score)) {
            state.score = 0;   // a draw
        }
        return;
    }

    if (depth <= 0) {       // Base case.  Run the heuristic.
        scoreState(state);
        return;
    }
    // Recursive case.  Take the min of the maxes.
    int v = std::numeric_limits<int>::max();
    size_t numChildren = state.children.size();
    for (size_t i = 0; i < numChildren; ++i) {
        try {
            state.children[i] = makeMove(state, i, false);
        } catch (const std::runtime_error&) {
            continue;
        }
        state.children[i].move = i;
        maximize(state.children[i], --depth, alpha, beta);
        //favor moves in the middle
        if (i == state.children.size() / 2 && !isWin(state.children[i].score)) {
            --state.children[i].score;
        }
        v = std::min(v, state.children[i].score);
        if (v <= alpha) {   // ***PRUNE***
            state.score = v;
            return;
        }
        beta = std::min(beta, v);
    }
    // We didn't prune.
    state.score = v;

}

void MiniMax::scoreState(tree& state) {

    /* Score the given state */

    int m = state.board.size();                     // num columns
    int n = state.board[0].length() - 1;            // num rows
    int R = state.R;                                // for my convenience
    int d = ((m - R) + (n - R) + 1);                // num diags (usable)
    int s = n - R;                                  // anchor point for diags
    int score = 0;                                  // the score we will assign

    std::vector<std::string> rows;                  // board rows
    std::vector<std::string> diaD;                  // board down diags (usable)
    std::vector<std::string> diaU;                  // board up diags (usable)

    // this prevents multiple resize operations and initializes all values
    // in each vector
    rows.resize(n);
    diaD.resize(d);
    diaU.resize(d);

    // fill in rows, diaD, and diaU
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            rows[j] += state.board[i][j];
            if ((-1 * s) - (m - n) <= (j - i) && (j - i) <= s) {     // up diags
                diaU[s - (j - i)] += state.board[i][j];
            }
            if (s < (i + j) && (i + j) < (s + d)) {      // down diags
                diaD[(i + j) - (s + 1)] += state.board[i][j];
            }
        }
    }
    // score all the things
    for (std::string& column : state.board) {
        int s = scoreLine(column, R);
        if (isWin(s)) {
            state.score = s;
            return;
        }
        score += s;
    }
    for (std::string& row : rows) {
        int s = scoreLine(row, R);
        if (isWin(s)) {
            state.score = s;
            return;
        }
        score += s;
    }
    for (std::string& diag : diaD) {
        int s = scoreLine(diag, R);
        if (isWin(s)) {
            state.score = s;
            return;
        }
        score += s;
    }
    for (std::string& diag : diaU) {
        int s = scoreLine(diag, R);
        if (isWin(s)) {
            state.score = s;
            return;
        }
        score += s;
    }

    state.score = score;

}

int MiniMax::scoreLine (const std::string& line, const size_t R) {

    size_t countX, countO;           // for counting Xs Os and spaces
    bool isAccessible;               // current grouping accessible?
    bool hasGap;                     // current group has gap?
    int score = 0;                   // the score to return

    countX = 0;
    countO = 0;
    isAccessible = false;
    hasGap = false;

    std::string xWin = "";
    std::string oWin = "";
    for (size_t i = 0; i < R; ++i) {
        xWin += 'X';
        oWin += 'O';
    }

    if (line.find(xWin) != std::string::npos) {
        return std::numeric_limits<int>::max();
    } else if (line.find(oWin) != std::string::npos) {
        return std::numeric_limits<int>::min();
    }

    for (char c : line) {
        if (c == 'X') {
            ++countX;
            if (countO > 1 && isAccessible) {
                score -= int (std::pow(2.0, float (countO - 2)));
                isAccessible = false;
            }
            countO = 0;
        } else if (c == 'O') {
            ++countO;
            if (countX > 1 && isAccessible) {
                score += int (std::pow(2.0, float (countX - 2)));
                isAccessible = false;
            }
            countX = 0;
        } else {
            isAccessible = true;
            if (hasGap) {
                if (countO > 1) {
                    score -= int (std::pow(2.0, float (countO - 2)));
                }
                if (countX > 1) {
                    score += int (std::pow(2.0, float (countX - 2)));
                }
                countO = 0;
                countX = 0;
                hasGap = false;
            }
            if (countX || countO) {
                hasGap = true;
            }
        }
    }

    return score;
}

bool MiniMax::isWin(const int score) {

    /* Return true if the score represents a win */

    return (
        score == std::numeric_limits<int>::max() ||
        score == std::numeric_limits<int>::min()
    );

}

MiniMax::tree MiniMax::makeMove(
    const tree& state, const size_t move, const bool myTurn
) {

    /* Return a new state after making the requested move */

    // We represent our tokens as Xs and theirs as Os
    std::string token = myTurn ? "X" : "O";
    size_t top = state.board[move].find_first_not_of("XO");
    if (top == std::string::npos) {
        throw std::runtime_error("Invalid Move");    // invalid move
    }
    tree result(state);
    result.board[move].replace(top, 1, token);
    return result;

}

bool MiniMax::boardFull(const tree& state) {

    /* Is the board full? */

    size_t top = state.board[0].length() - 1;
    for (auto column : state.board) {
        if (column[top] != 'X' && column[top] != 'O') {
            return false;
        }
    }
    return true;
}
