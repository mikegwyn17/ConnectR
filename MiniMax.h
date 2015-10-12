/* 
 * Minimax with Alpha-Beta pruning for ConnectR
 * Felipe Spinolo
 * CS4523 Artificial Intelligence
 * Dr. Michael Franklin
 * Project 2
 */

#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include <string>
#include <limits>
#include <vector>

namespace MiniMax {

    /* Tree structure used for minimaxing */
    struct tree {
        std::vector<tree> children;
        std::vector<std::string> board;
        int score;
        tree() {}
        tree(size_t m, std::vector<std::string>& b) {
            children.resize(m);
            board = b;
        }
    };

    /* Returns the index of the child node of root representing the best move
     * found.
     * @param root: tree representing current state
     */
    const size_t alphaBeta(tree& root);

    /* Returns the highest heuristic value for all children of current if we
     * look depth moves ahead
     * @param current: tree representing current state
     * @param depth: how many moves to look ahead
     * @param alpha: the current alpha value
     * @param beta: the current beta value
     */
    const int maximize(tree& current, size_t depth, int alpha, int beta);

    /* Exactly like maximize, except we're going for lowest heuristic value. */
    const int minimize(tree& current, size_t depth, int alpha, int beta);

    /* Heuristic function to return score of the given board 
     * @param board: the board you want scored
     */
    const int scoreBoard(const std::vector<std::string>& board);

    /* Did the most recent move result in a win?
     * @param board: the board you want evaluated
     * @param myTurn: did I just move?
     */
    const bool winningMove(
        const std::vector<std::string>& board, const bool myTurn);

    const std::vector<std::string> makeMove(
        const std::vector<std::string> board,
        const size_t move,
        const bool myTurn
    );

}

#endif
