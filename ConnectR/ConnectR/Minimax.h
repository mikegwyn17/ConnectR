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
	};

	struct tree {
		tree* parent;
		std::unique_ptr<tree> firstChild;
		std::unique_ptr<tree> nextSibling;
		gameState state;
	};

	unsigned int alphaBeta(gameState& state);

}

#endif