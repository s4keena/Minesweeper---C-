#include "minesweeper.h"
#include <iostream>

int main() {
    int width, height, mines;
    std::cout << "Enter width, height, and number of mines: ";
    std::cin >> width >> height >> mines;

    Minesweeper game(width, height, mines);

    while (true) {
        game.displayBoard();
        char action;
        int x, y;
        std::cout << "Enter action (u for uncover, m for mark) and coordinates (x y): ";
        std::cin >> action >> x >> y;

        if (action == 'u') {
            if (!game.uncoverCell(x, y)) {
                std::cout << "Game Over! You hit a mine.\n";
                game.displayBoard(true);
                break;
            }
        }
        else if (action == 'm') {
            game.markCell(x, y);
        }

        if (game.checkWin()) {
            std::cout << "Congratulations! You won.\n";
            game.displayBoard(true);
            break;
        }
    }

    return 0;
}
