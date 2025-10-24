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

    std::cout << "Board (" << GREEN << "o" << RESET " = ball hit, . = peg):\n\n";

    for (int r = 0; r < rows; ++r) {
        // indent for pyramid shape
        std::cout << std::string(rows - r, ' ');

        for (int c = 0; c <= r; ++c) {
            if (c == ballPos) {
                // Print green O for ball hit
                std::cout << GREEN << "o " << RESET;
            } else {
                std::cout << ". ";
            }
        }
        std::cout << '\n';

        // move ballPos according to path
        if (static_cast<size_t>(r) < path.size() && path[r] == 'R') {
            ++ballPos;
        }
    }

    // Print the final row of slots
    for (int c = 1; c <= rows + 1 ; ++c)
        std::cout << (c == ballPos + 1 ? GREEN + std::to_string(c) + RESET : std::to_string(c)) << " ";

    std::cout << "\nBall path: ";
    for (const char dir : path) std::cout << dir << ' ';
    std::cout << "\nBall landed in slot: " << ballPos << "\n";

    return 0;
}
