#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "board.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define CLEAR "\033[2J\033[H"  // Clear screen & move cursor home

void printBoard(const int rows, int ballPos, int currentRow) {
    std::cout << CLEAR; // clear terminal for animation
    std::cout << "🎰 Pachinko Board\n\n";
    std::cout << "Board (" << GREEN << "o" << RESET << " = ball hit, . = peg):\n\n";

    for (int r = 0; r < rows; ++r) {
        std::cout << std::string(rows - r, ' ');

        for (int c = 0; c <= r; ++c) {
            if (r == currentRow && c == ballPos) {
                std::cout << GREEN << "o " << RESET;
            } else {
                std::cout << ". ";
            }
        }
        std::cout << '\n';
    }

    // Print the final row of slots
    for (int c = 0; c <= rows; ++c) {
        if (c == ballPos && currentRow == rows) {
            std::cout << GREEN << "^ " << RESET;
        } else {
            std::cout << c << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    constexpr int rows = 5;
    const Board board(rows);

    const auto path = board.dropBall();

    int ballPos = 0;

    for (int r = 0; r <= rows; ++r) {
        printBoard(rows, ballPos, r);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        if (r < rows && static_cast<size_t>(r) < path.size() && path[r] == 'R') {
            ++ballPos;
        }
    }

    // Final frame
    printBoard(rows, ballPos, rows);

    std::cout << "\nBall path: ";
    for (const char dir : path) std::cout << dir << ' ';
    std::cout << "\nBall landed in slot: " << ballPos << "\n\n";

    return 0;
}
