#include "MiniMax.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

int main(void) {

    // Defaults to standard Connect4
    size_t m = 7;
    size_t n = 6;
    size_t R = 4;

    std::string input = "";

    const std::string BAD_INT = "I'm looking for an integer here...";

    bool myTurn = false;
    size_t move;
    MiniMax::tree gameState;
    std::vector<std::string> startingBoard;
    std::string emptyColumn = "";

    std::cout << "Let's play some ConnectR!  We will play on a board with " <<
        "m columns and n rows.\nConnectR to win!  I'll be Xs and you'll be Os"
        << std::endl;

    std::cout << "Please provide the following values, or just press " <<
        "[ENTER] to use\nthe default value given in parenthesis." <<
        std::endl;

    while (true) {
        std::cout << "m (7): ";
        std::getline(std::cin, input);
        if (input == "") {
            break;
        }
        try {
            m = std::stoi(input);
            input = "";
            break;
        } catch (std::invalid_argument&) {
            std::cerr << BAD_INT << std::endl;
        }
    }
    while (true) {
        std::cout << "n (6): ";
        std::getline(std::cin, input);
        if (input == "") {
            break;
        }
        try {
            n = std::stoi(input);
            input = "";
            break;
        } catch (std::invalid_argument&) {
            std::cerr << BAD_INT << std::endl;
        }
    }
    while (true) {
        std::cout << "R (4): ";
        std::getline(std::cin, input);
        if (input == "") {
            break;
        }
        try {
            R = std::stoi(input);
            input = "";
        } catch (std::invalid_argument&) {
            std::cerr << BAD_INT << std::endl;
        }
    }
    while (true) {
        std::cout << "Do I go first? (y/n): ";
        std::getline(std::cin, input);
        if (input != "y" && input != "n") {
            std::cout << "Please enter 'y' or 'n'" << std::endl;
            continue;
        } else if (input == "y") {
            myTurn = true;
        }
        break;
    }

    startingBoard.resize(m);
    for (size_t i = 0; i < n; ++i) {
        emptyColumn += ' ';
    }
    for (size_t i = 0; i < m; ++i) {
        startingBoard[i] = emptyColumn;
    }
    gameState = MiniMax::tree(startingBoard, m, R);

    if (myTurn) {
        move = MiniMax::alphaBeta(gameState);
        std::cout << "My move: " << move << std::endl;
        gameState = MiniMax::makeMove(gameState, move, myTurn);
        myTurn = false;
        std::cout << gameState.toString() << std::endl;
    }

    while (true) {
        while(!myTurn) {
            try {
                std::cout << "Your move: ";
                std::cin >> input;
                move = std::stoi(input);
                if (move >= m) {
                    std::cout << "What board are you playing on?" << std::endl;
                    continue;
                }
                gameState = makeMove(gameState, move, myTurn);
                myTurn = true;
                std::cout << gameState.toString() << std::endl;
            } catch (const std::invalid_argument&) {
                std::cerr << BAD_INT << std::endl;
            } catch (const std::runtime_error&) {
                std::cerr <<
                    "That doesn't seem to be a valid move." << std::endl;
            }
        }
        MiniMax::scoreState(gameState);
        if (MiniMax::isWin(gameState.score)) {
            std::cout << "You win!" << std::endl;
            break;
        } else if (MiniMax::boardFull(gameState)) {
            std::cout << "We'll call it a draw!" << std::endl;
            break;
        }
        move = MiniMax::alphaBeta(gameState);
        std::cout << "My move: " << move << std::endl;
        gameState = MiniMax::makeMove(gameState, move, myTurn);
        myTurn = false;
        std::cout << gameState.toString() << std::endl;
        MiniMax::scoreState(gameState);
        if (MiniMax::isWin(gameState.score)) {
            std::cout << "I win!" << std::endl;
            break;
        } else if (MiniMax::boardFull(gameState)) {
            std::cout << "We'll call it a draw" << std::endl;
            break;
        }
    }
    system("pause");
    return 0;
}
