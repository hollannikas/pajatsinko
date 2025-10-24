#pragma once
#include "peg.h"
#include <vector>

class Board {
public:
    explicit Board(int rows);
    [[nodiscard]] int rowCount() const;
    [[nodiscard]] size_t totalPegCount() const;

    [[nodiscard]] std::vector<char> dropBall() const;
    [[nodiscard]] int dropBallFinalSlot() const;
    void setHitSequence(const std::vector<char>& sequence);

private:
    int rows_;
    std::vector<std::vector<Peg>> pegs_; // 2D structure for pyramid
    std::vector<char> forcedHits_;
};
