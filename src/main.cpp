#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include "board.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define CLEAR "\033[2J\033[H"  // Clear screen and move cursor home

void printBoard(const int rows, int ballPos, int currentRow, const std::vector<int>& slotCounts) {
    std::cout << CLEAR;
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

    // Slots row
    for (int s = 0; s <= rows; ++s) {
        if (s == ballPos && currentRow == rows) {
            std::cout << GREEN << "^ " << RESET;
        } else {
            std::cout << s << " ";
        }
    }
    std::cout << "\n";

    // Histogram (slotCounts)
    std::cout << "\nResults so far:\n";
    for (int s = 0; s <= rows; ++s) {
        std::cout << std::setw(2) << s << ": ";
        for (int i = 0; i < slotCounts[s]; ++i) std::cout << GREEN << "#" << RESET;
        std::cout << " (" << slotCounts[s] << ")\n";
    }
}

int main() {
    constexpr int rows = 6;
    constexpr int totalBalls = 20;
    const Board board(rows);

    std::vector<int> slotCounts(rows + 1, 0);

    for (int ball = 1; ball <= totalBalls; ++ball) {
        const auto path = board.dropBall();
        int ballPos = 0;

        for (int r = 0; r <= rows; ++r) {
            printBoard(rows, ballPos, r, slotCounts);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            if (r < rows && static_cast<size_t>(r) < path.size() && path[r] == 'R') {
                ++ballPos;
            }
        }

        // Record final slot
        if (ballPos >= 0 && ballPos <= rows)
            ++slotCounts[ballPos];

        // Short pause between balls
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    // Final summary
    printBoard(rows, -1, rows, slotCounts);

    std::cout << "\n✅ Simulation complete! Dropped " << totalBalls << " balls.\n";
    std::cout << "Final slot counts:\n";
    for (int s = 0; s <= rows; ++s)
        std::cout << "Slot " << s << ": " << slotCounts[s] << "\n";

    return 0;
}
