#include <gtest/gtest.h>
#include "peg.h"

TEST(PegTest, BallFallsLeftOrRight) {
    const auto dir = Peg::hit();

    // Must be either 'L' or 'R'
    EXPECT_TRUE(dir == 'L' || dir == 'R');
}

TEST(PegTest, BallFallsLeftOrRight2) {
    const auto dir = Peg::hit();

    // Must be either 'L' or 'R'
    EXPECT_TRUE(dir == 'L' || dir == 'R');
}