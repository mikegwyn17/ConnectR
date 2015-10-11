/* 
 * Minimax with Alpha-Beta pruning
 * Felipe Spinolo
 * CS4523 Artificial Intelligence
 * Dr. Michael Franklin
 * Project 2
 */

#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include <memory>
#include <string>

namespace MiniMax {

	struct gameState {
		unsigned int score;
		bool hasWinningMove;
		std::string board;
	};

	struct tree {
		tree* children;
		gameState state;
		int alpha;
		int beta;
		tree() {}
		tree(unsigned int m) { children = new tree[m]; }
		~tree() { delete children; }
	};

	unsigned int alphaBeta(gameState& state);

}

#endif