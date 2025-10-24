#include "board.h"

Board::Board(const int rows) : rows_(rows) {
    for (int r = 1; r <= rows; ++r) {
        pegs_.emplace_back(r);
    }
}

int Board::rowCount() const {
    return rows_;
}

size_t Board::totalPegCount() const {
    size_t count = 0;
    for (const auto& row : pegs_)
        count += row.size();
    return count;
}

std::vector<char> Board::dropBall() const {
    std::vector<char> path;
    int i = 0;

    for (int r = 0; r < rows_; ++r) {
        char dir;

        // If a forced sequence exists, use it
        if (!forcedHits_.empty() && i < static_cast<int>(forcedHits_.size())) {
            dir = forcedHits_[i++];
        } else {
            // Otherwise use peg hit
            dir = pegs_[r].front().hit();
        }

        path.push_back(dir);
    }

    return path;
}

int Board::dropBallFinalSlot() const {
    const auto path = dropBall(); // reuse logic
    int position = 0;
    for (const char dir : path) {
        if (dir == 'R') ++position;
    }
    return position;
}

void Board::setHitSequence(const std::vector<char>& sequence) {
    forcedHits_ = sequence;
}