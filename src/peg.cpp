#include "peg.h"
#include <random>
#include <chrono>

// Define the static thread-local members
thread_local std::mt19937 Peg::engine_{ static_cast<std::mersenne_twister_engine<unsigned, 32, 624, 397, 31, 2567483615, 11, 4294967295, 7, 2636928640, 15, 4022730752, 18, 1812433253>::result_type>(static_cast<unsigned long>(
    std::chrono::steady_clock::now().time_since_epoch().count()
))};
thread_local std::uniform_int_distribution<> Peg::dist_{0, 1};

Peg::Peg() = default;

char Peg::hit() const {
    return dist_(engine_) == 0 ? 'L' : 'R';
}
