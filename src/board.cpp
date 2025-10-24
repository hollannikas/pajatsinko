#include "Board.h"

Board::Board(const int rows) : rows_(rows) {
    for (int r = 1; r <= rows; ++r) {
        pegs_.emplace_back(r);
    }
}

int Board::rowCount() const {
    return rows_;
}

int Board::totalPegCount() const {
    int count = 0;
    for (const auto& row : pegs_) count += row.size();
    return count;
}

std::vector<char> Board::dropBall() const {
    std::vector<char> path;
    for (auto& row : pegs_) {
        for (auto& peg : row) {
            path.push_back(peg.hit());
            break; // one peg hit per row for now
        }
    }
    return path;
}
