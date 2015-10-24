/* 
 * Minimax with Alpha-Beta pruning for ConnectR
 * Felipe Spinolo
 * CS4523 Artificial Intelligence
 * Dr. Michael Franklin
 * Project 2
 */

#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include <string>           // because strings are pretty handy
#include <limits>           // so we can figure out the limits of int
#include <vector>           // because c arrays are inconvenient for us

namespace MiniMax {

    /* Tree structure used for minimaxing */
    struct tree {
        std::vector<tree> children;
        std::vector<std::string> board;
        size_t R;
        size_t move;
        int score;
        tree() {}
        tree(size_t m, std::vector<std::string>& b, size_t mv, size_t _R) {
            children.resize(m);
            board = b;
            move = mv;
            R = _R;
        }
        tree(const tree& other) {
            children.resize(other.children.size());
            board = other.board;
            R = other.R;
        }
    };

    /* Returns the best move we can find
     * @param state: tree representing current state
     */
    size_t alphaBeta(tree& state);

    /* Our Turn: Take the score of our highest scoring child
     * @param current: tree representing current state
     * @param depth: how many moves to look ahead
     * @param alpha: the current alpha value
     * @param beta: the current beta value
     */
    void maximize(tree& state, size_t depth, int alpha, int beta);

    /* Just like maximize, except it's their turn so take the lowest score */
    void minimize(tree& state, size_t depth, int alpha, int beta);

    /* Heuristic function to score the given state 
     * @param state: the state to be scored
     * @param R: number to connect for a win
     */
    void scoreState(tree& state);

    /* Called by scoreBoard on every row, column, and diagonal
     * @param line: the row, column, or diagonal to score
     * @param R: how many to connect for a win?
     */
    int scoreLine(const std::string& line, const size_t R);

    /* Does the given score represent a win?
     * @param score: the score to evaluate
     */
    bool isWin(const int score);

    /* Returns the new state after the move is made.
     * Throws runtime_error if the move is invalid
     * @param state: the state before making the move
     * @param move: the column in which the move is to be made
     * @param myTurn: is it my move?
     */
    MiniMax::tree makeMove(
        const tree& state, const size_t move, const bool myTurn
    );

    /* Return true if the board is full */
    bool boardFull(const tree& state);

}

#endif

