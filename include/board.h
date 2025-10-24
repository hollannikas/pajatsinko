#pragma once
#include "Peg.h"
#include <vector>

class Board {
public:
    explicit Board(int rows);
    [[nodiscard]] int rowCount() const;
    [[nodiscard]] int totalPegCount() const;

private:
    int rows_;
    std::vector<std::vector<Peg>> pegs_; // 2D structure for pyramid
};
