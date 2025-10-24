#include "peg.h"
#include <cstdlib>

char Peg::hit() const {
    return std::rand() % 2 == 0 ? 'L' : 'R';
}