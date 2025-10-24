#pragma once
#include <random>

class Peg {
public:
    Peg();

    [[nodiscard]] char hit() const;

private:
    static thread_local std::mt19937 engine_;
    static thread_local std::uniform_int_distribution<int> dist_;
};
