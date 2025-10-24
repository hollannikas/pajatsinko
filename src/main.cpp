#include <iostream>
#include "board.h"

int main() {
    std::cout << "🎰 Welcome to Pachinko!\n";

    Board board(5);  // create a board with 5 rows

    // Drop one ball
    auto path = board.dropBall();
    int finalSlot = board.dropBallFinalSlot();

    std::cout << "Ball path: ";
    for (char dir : path)
        std::cout << dir << ' ';
    std::cout << "\n";

    std::cout << "Ball landed in slot: " << finalSlot << "\n";

    return 0;
}
