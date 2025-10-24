#include "board.h"
#include <gtest/gtest.h>

TEST(BoardTest, CreatesCorrectNumberOfPegs) {
    const Board board(3); // 3 rows
    EXPECT_EQ(board.rowCount(), 3);
    EXPECT_EQ(board.totalPegCount(), static_cast<size_t>(6)); // 1 + 2 + 3 = 6
}

TEST(BoardTest, BallFallsThroughRows) {
    const Board board(3);

    const auto path = board.dropBall();

    EXPECT_EQ(path.size(), 3); // one decision per row
    for (const char dir : path)
        EXPECT_TRUE(dir == 'L' || dir == 'R');
}

TEST(BoardTest, BallLandsInValidSlot) {
    Board board(3);
    const size_t slot = board.dropBallFinalSlot();
    EXPECT_GE(slot, 0);
    EXPECT_LE(slot, 3); // for 3 rows => 4 possible slots
}

TEST(BoardTest, BallGoesAllLeft) {
    Board board(3);
    board.setHitSequence({'L', 'L', 'L'});
    EXPECT_EQ(board.dropBallFinalSlot(), 0);
}

TEST(BoardTest, BallGoesAllRight) {
    Board board(3);
    board.setHitSequence({'R', 'R', 'R'});
    EXPECT_EQ(board.dropBallFinalSlot(), 3);
}

TEST(BoardTest, BallPathIsCorrectLength) {
    Board board(3);
    auto path = board.dropBall();
    EXPECT_EQ(path.size(), 3);
}
