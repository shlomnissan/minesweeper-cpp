#include <iostream>
#include <vector>

#include "level.hpp"
#include "board.hpp"

int main() {
    std::cout << "Choose level of difficulty:\n\n";
    std::cout << "0. Easy 9 x 9 board (10 mines)\n";
    std::cout << "1. Intermediate 16 x 16 board (40 mines)\n";
    std::cout << "2. Advanced 24 x 24 board (99 mines)\n\n";

    int lvl = 0;
    std::vector<Level> levels {
        {9, 10},    // easy
        {16, 40},   // intermediate
        {24, 99}    // advanced
    };
    std::cin >> lvl;
    std::cout << '\n';

    Board board(levels[lvl]);

    bool playing = true;
    int row, col;

    while (playing) {
        board.printBoard(false);

        std::cout << "Make a move: ";
        std::cin >> row >> col;
        std::cout << '\n';

        if (!board.reveal(row, col)) {
            board.printBoard(true);
            std::cout << "GAME OVER! \n\n";
            playing = false;
        }
    }

    return 0;
}
