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

namespace MiniMax {

	/* Representation of the current game state */
	struct gameState {
		int score;
		std::string board;
	};

	/* Tree structure used for minimaxing */
	struct tree {
		tree* children;
		gameState state;
		tree() {}
		tree(unsigned int m, gameState& s) {
			children = new tree[m];
			state = s;
		}
		~tree() { delete children; }
	};

	/* Returns the index of the child node of root representing the best move
	 * found.
	 * @param root: tree representing current state
	 * @param depth: how many moves to look ahead
	 * @param alpha: the alpha value, start with a REALLY low value
	 * @param beta: the beta value, start with a REALLY high value
	 * @param myTurn: is it my turn at this depth? (should I min or max?)
	 */
	unsigned int alphaBeta
		(tree& root, unsigned int depth, int alpha, int beta, bool myTurn);

	/* Returns the integer score of the given board 
	 * @param board: the board you want scored
	 */
	int scoreBoard(std::string& board);

	/* Does the given board have a winning move for whoever's turn it is?
	 * @param board: the board you want evaluated
	 * @param myTurn: is it my turn? (my killer move or his?)
	 */
	bool hasKillerMove(std::string& board, bool myTurn);

}

#endif