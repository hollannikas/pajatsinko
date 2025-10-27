#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include "board.h"

#define GREEN "\033[32m"
#define CYAN  "\033[36m"
#define RESET "\033[0m"
#define CLEAR "\033[2J\033[H"  // clear screen and move cursor home

struct FallingBall {
    int row = 0;
    int col = 0;
    std::vector<char> path;
    bool finished = false;
};

void printBoard(const int rows,
                const std::vector<FallingBall>& balls,
                const std::vector<int>& slotCounts) {
    std::cout << CLEAR;
    std::cout << "🎰 Pachinko Board — Multiple Balls in Motion\n\n";
    std::cout << "(" << GREEN << "o" << RESET << " = ball, . = peg)\n\n";

    // Print pegs and moving balls
    for (int r = 0; r < rows; ++r) {
        std::cout << std::string(rows - r, ' ');
        for (int c = 0; c <= r; ++c) {
            bool ballHere = false;
            for (const auto& b : balls) {
                if (!b.finished && b.row == r && b.col == c) {
                    std::cout << GREEN << "o " << RESET;
                    ballHere = true;
                    break;
                }
            }
            if (!ballHere) std::cout << ". ";
        }
        std::cout << '\n';
    }

    // Slots
    for (int s = 0; s <= rows; ++s) std::cout << s << ' ';
    std::cout << "\n";

    // Histogram
    std::cout << "\nResults so far:\n";
    for (int s = 0; s <= rows; ++s) {
        std::cout << std::setw(2) << s << ": ";
        for (int i = 0; i < slotCounts[s]; ++i) std::cout << CYAN << "#" << RESET;
        std::cout << " (" << slotCounts[s] << ")\n";
    }
}

int main() {
    constexpr int rows = 6;
    constexpr int totalBalls = 30;
    const Board board(rows);

    std::vector<int> slotCounts(rows + 1, 0);
    std::vector<FallingBall> balls;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> delayDist(0, 8); // random entry delay for realism

    int frame = 0;
    while (true) {
        // Occasionally spawn a new ball
        if (balls.size() < totalBalls && delayDist(rng) == 0) {
            FallingBall b;
            b.path = board.dropBall(); // precompute its random route
            balls.push_back(b);
        }

        // Update all active balls
        for (auto&[row, col, path, finished] : balls) {
            if (finished) continue;

            // Move the ball down one row per frame
            if (row < rows) {
                // At each peg, move left or right
                if (row < static_cast<int>(path.size()) && path[row] == 'R')
                    ++col;
                ++row;
            } else {
                // Landed in a slot
                if (col >= 0 && col <= rows)
                    ++slotCounts[col];
                finished = true;
            }
        }

        // Render frame
        printBoard(rows, balls, slotCounts);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        // Stop when all balls finished
        bool allDone = true;
        for (const auto& b : balls)
            if (!b.finished) { allDone = false; break; }
        if (allDone && balls.size() == totalBalls)
            break;

        ++frame;
    }

    printBoard(rows, balls, slotCounts);
    std::cout << "\n✅ All " << totalBalls << " balls have landed.\n";

    return 0;
}
