//
// Created by Shlomi Nissan on 11/21/19.
//

#ifndef MINE_SWEEPER_BOARD_HPP
#define MINE_SWEEPER_BOARD_HPP

#include <vector>

#include "level.hpp"
#include "cell.hpp"

class Board {
private:
    std::vector<std::vector<Cell>> m_board;
    Level m_level;

    void plotMines();
    void plotAdjacentMineCount();
    void expand(int row, int col);

    static char getChar(Cell& cell, bool showMines = false);

    inline bool isValid(int row, int col) {
        return (row >= 0 && row < m_level.size) && (col >= 0 && col < m_level.size);
    }
public:
    explicit Board(Level level);
    bool reveal(int row, int col);
    void printBoard(bool showMines = false);
};


#endif //MINE_SWEEPER_BOARD_HPP
