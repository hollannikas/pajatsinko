#include <iostream>
#include <string>
#include "board.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"

int main() {
    constexpr int rows = 5;
    const Board board(rows);

    std::cout << "🎰 Pachinko Board\n\n";

    // Drop one ball
    const auto path = board.dropBall();

    int ballPos = 0;

    std::cout << "Board (" << GREEN << "O" << RESET " = ball hit, o = peg):\n\n";

    for (int r = 0; r < rows; ++r) {
        // indent for pyramid shape
        std::cout << std::string(rows - r - 1, ' ');

        for (int c = 0; c <= r; ++c) {
            if (c == ballPos) {
                // Print green O for ball hit
                std::cout << GREEN << "O " << RESET;
            } else {
                std::cout << "o ";
            }
        }
        std::cout << '\n';

        // move ballPos according to path
        if (static_cast<size_t>(r) < path.size() && path[r] == 'R') {
            ++ballPos;
        }
    }

    std::cout << "\nBall path: ";
    for (const char dir : path) std::cout << dir << ' ';
    std::cout << "\nBall landed in slot: " << ballPos << "\n";

    return 0;
}
