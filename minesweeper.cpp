#include "minesweeper.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Minesweeper::Minesweeper(int w, int h, int m) : width(w), height(h), mines(m) {
    initializeBoard();
}

void Minesweeper::initializeBoard() {
    board.resize(height, std::vector<char>(width, ' '));
    uncovered.resize(height, std::vector<bool>(width, false));
    marked.resize(height, std::vector<bool>(width, false));
    mineCounts.resize(height, std::vector<int>(width, 0));
    placeMines();
    calculateAdjacentMines();
}

void Minesweeper::placeMines() {
    srand(static_cast<unsigned int>(time(0)));
    int placedMines = 0;
    while (placedMines < mines) {
        int x = rand() % width;
        int y = rand() % height;
        if (board[y][x] != 'o') {
            board[y][x] = 'o';
            placedMines++;
        }
    }
}

void Minesweeper::calculateAdjacentMines() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (board[y][x] == 'o') continue;
            int mineCount = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int ny = y + i;
                    int nx = x + j;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && board[ny][nx] == 'o') {
                        mineCount++;
                    }
                }
            }
            mineCounts[y][x] = mineCount;
        }
    }
}

void Minesweeper::displayBoard(bool revealMines) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (uncovered[y][x]) {
                std::cout << mineCounts[y][x] << ' ';
            }
            else if (marked[y][x]) {
                std::cout << 'M' << ' ';
            }
            else {
                if (revealMines && board[y][x] == 'o') {
                    std::cout << 'o' << ' ';
                }
                else {
                    std::cout << '.' << ' ';
                }
            }
        }
        std::cout << '\n';
    }
}

bool Minesweeper::uncoverCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || uncovered[y][x] || marked[y][x]) {
        return false;
    }
    uncovered[y][x] = true;
    if (board[y][x] == 'o') {
        return false; // Hit a mine
    }
    if (mineCounts[y][x] == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                uncoverCell(x + j, y + i);
            }
        }
    }
    return true;
}

void Minesweeper::markCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || uncovered[y][x]) {
        return;
    }
    marked[y][x] = !marked[y][x];
}

bool Minesweeper::checkWin() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (board[y][x] != 'o' && !uncovered[y][x]) {
                return false;
            }
        }
    }
    return true;
}
