#include "peg.h"
#include <cstdlib>

char Peg::hit() {
    return std::rand() % 2 == 0 ? 'L' : 'R';
}