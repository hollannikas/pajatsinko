#include "Board.h"
#include <gtest/gtest.h>

TEST(BoardTest, CreatesCorrectNumberOfPegs) {
    Board board(3); // 3 rows
    EXPECT_EQ(board.rowCount(), 3);
    EXPECT_EQ(board.totalPegCount(), 6); // 1 + 2 + 3 = 6
}

TEST(BoardTest, BallFallsThroughRows) {
    const Board board(3);

    const auto path = board.dropBall();

    EXPECT_EQ(path.size(), 3); // one decision per row
    for (const char dir : path)
        EXPECT_TRUE(dir == 'L' || dir == 'R');
}
