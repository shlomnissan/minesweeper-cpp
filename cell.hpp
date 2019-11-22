//
// Created by Shlomi Nissan on 11/21/19.
//

#ifndef MINE_SWEEPER_CELL_HPP
#define MINE_SWEEPER_CELL_HPP

#include <cstdint>

#define CS_REVEALED    0x0001
#define CS_MINE        0x0010

class Cell {
private:
    uint8_t m_state;
    uint8_t m_adjacentMinesCount;
public:
    Cell(): m_state(0), m_adjacentMinesCount(0) {}

    void setState(uint8_t state) { m_state |= state; }
    void setCount(uint8_t count) { m_adjacentMinesCount = count; }

    uint8_t getCount() { return m_adjacentMinesCount; }
    bool isMine() { return m_state & CS_MINE; }
    bool isRevealed() { return m_state & CS_REVEALED; }
};


#endif //MINE_SWEEPER_CELL_HPP