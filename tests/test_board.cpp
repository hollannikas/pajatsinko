#include "Board.h"
#include <gtest/gtest.h>

TEST(BoardTest, CreatesCorrectNumberOfPegs) {
    Board board(3); // 3 rows
    EXPECT_EQ(board.rowCount(), 3);
    EXPECT_EQ(board.totalPegCount(), 6); // 1 + 2 + 3 = 6
}
