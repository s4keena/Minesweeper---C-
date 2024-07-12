#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>

class Minesweeper {
public:
    Minesweeper(int width, int height, int mines);
    void displayBoard(bool revealMines = false) const;
    bool uncoverCell(int x, int y);
    void markCell(int x, int y);
    bool checkWin() const;

private:
    int width;
    int height;
    int mines;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> uncovered;
    std::vector<std::vector<bool>> marked;
    std::vector<std::vector<int>> mineCounts;

    void initializeBoard();
    void placeMines();
    void calculateAdjacentMines();
};

#endif // MINESWEEPER_H
