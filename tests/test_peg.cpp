#include <gtest/gtest.h>
#include "peg.h"

TEST(PegTest, BallFallsLeftOrRight) {
    Peg peg;
    auto dir = peg.hit();

    // Must be either 'L' or 'R'
    EXPECT_TRUE(dir == 'L' || dir == 'R');
}

TEST(PegTest, BallFallsLeftOrRight2) {
    Peg peg;
    auto dir = peg.hit();

    // Must be either 'L' or 'R'
    EXPECT_TRUE(dir == 'L' || dir == 'R');
}