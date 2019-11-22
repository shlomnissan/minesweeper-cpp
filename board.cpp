//
// Created by Shlomi Nissan on 11/21/19.
//

#include <iostream>
#include <random>

#include "board.hpp"

//region private

void Board::plotMines() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, m_level.size - 1);

    auto row = 0, col = 0;
    for (auto i = 0; i < m_level.mines; i++) {
        row = dist(mt);
        col = dist(mt);

        Cell& cell = m_board[row][col];
        if (!cell.isMine()) { cell.setState(CS_MINE); } else { --i; }
    }
}

void Board::plotAdjacentMineCount() {
    auto count = 0;
    for (int row = 0; row < m_level.size; row++) {
        for (int col = 0; col < m_level.size; col++) {
            count = 0;
            Cell& cell = m_board[row][col];

            if (cell.isMine()) continue;

            if (isValid(row - 1, col) && m_board[row - 1][col].isMine()) { count++; } // N
            if (isValid(row + 1, col) && m_board[row + 1][col].isMine()) { count++; } // S
            if (isValid(row, col + 1) && m_board[row][col + 1].isMine()) { count++; } // E
            if (isValid(row, col - 1) && m_board[row][col - 1].isMine()) { count++; } // W
            if (isValid(row - 1, col + 1) && m_board[row - 1][col + 1].isMine()) { count++; } // N.E
            if (isValid(row - 1, col - 1) && m_board[row - 1][col - 1].isMine()) { count++; } // N.W
            if (isValid(row + 1, col + 1) && m_board[row + 1][col + 1].isMine()) { count++; } // S.E
            if (isValid(row + 1, col - 1) && m_board[row + 1][col - 1].isMine()) { count++; } // S.W

            cell.setCount(count);
        }
    }
}

void Board::expand(int row, int col) {
    Cell& cell = m_board[row][col];

    if (cell.isRevealed() || cell.isMine()) return;

    cell.setState(CS_REVEALED);

    if (cell.getCount() == 0) {
        if (isValid(row, col + 1)) { expand(row, col + 1); }
        if (isValid(row + 1, col)) { expand(row + 1, col); }
        if (isValid(row, col - 1)) { expand(row, col - 1); }
        if (isValid(row - 1, col)) { expand(row - 1, col); }
    }
}

char Board::getChar(Cell& cell, bool showMines) {
    if (cell.isMine()) {
        if (cell.isRevealed() || showMines) { return '*'; }
    }
    if (cell.isRevealed()) {
        return std::to_string(cell.getCount())[0];
    }
    return '#';
}

//endregion

//region public

Board::Board(Level level): m_level(level), m_board(level.size, std::vector<Cell>(level.size)) {
    plotMines();
    plotAdjacentMineCount();
}

bool Board::reveal(int row, int col) {
    if (isValid(row, col)) {
        if (!m_board[row][col].isMine()) {
            // expand recursively
            expand(row, col);
        } else {
            // game over
            return false;
        }
    }
    return true;
}

void Board::printBoard(bool showMines) {
    for (auto& row: m_board) {
        for (auto& cell: row) {
            std::cout << getChar(cell, showMines) << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

//endregion