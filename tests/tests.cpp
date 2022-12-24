#include <gtest/gtest.h>
#include <iostream>
#include "square.h"
#include "basepiece.h"
#include "board.h"
#include "move.h"


TEST(SquareTest, getLocation) {
    Square s(1, 2);
    std::tuple<int, int> loc = s.getLocation();

    EXPECT_EQ(std::get<0>(loc), 1);
    EXPECT_EQ(std::get<1>(loc), 2);
}

TEST(SquareTest, getBasePieceEmpty) {
    Square s(0, 0);
    EXPECT_EQ(s.getPiece(), nullptr);
}

TEST(SquareTest, getBasPiece) {
    
    BasePiece bp("wp");
    Square s(1, 5, &bp);

    EXPECT_EQ(s.getPiece(), &bp);
}

TEST(BasePieceTests, init) {
    BasePiece bp("wp");
    EXPECT_EQ(bp.getID(), "wp");
}

TEST(MoveTests, testID) {
    std::tuple<int, int> start = std::make_tuple(1, 1);
    std::tuple<int, int> end = std::make_tuple(3, 3);
    Move move(start, end, nullptr, nullptr);
    EXPECT_EQ(move.getMoveID(), 1133);
}

TEST(MoveTests, testGetRankFile) {
    std::tuple<int, int> start = std::make_tuple(1, 1);
    std::tuple<int, int> end = std::make_tuple(3, 3);
    Move move(start, end, nullptr, nullptr);

    EXPECT_EQ(move.getRankFile(3, 3), "d5");
    EXPECT_EQ(move.getRankFile(0, 0), "a8");
    EXPECT_EQ(move.getRankFile(2, 6), "g6");
}

TEST(MoveTests, testPieceMoved) {
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::tuple<int, int> start = std::make_tuple(1, 1);
    std::tuple<int, int> end = std::make_tuple(3, 1);
    Move move(start, end, board.getSquare(start).getPiece(), nullptr);

    EXPECT_EQ(move.pieceMoved->getID(), "bp");  

    start = std::make_tuple(7, 4);
    end = std::make_tuple(0, 0);
    Move m(start, end, board.getSquare(start).getPiece(), nullptr);

    EXPECT_EQ(m.pieceMoved->getID(), "wK");
}


TEST(BoardTests, testBoardSize) {
    Board board;
    EXPECT_EQ(board.getBoard().size(), 8);

    for (std::vector<Square> rank : board.getBoard()) {
        EXPECT_EQ(rank.size(), 8);
    }
}

TEST(BoardTests, testSquarePieces) {
    Board board;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::tuple<int, int> loc = std::make_tuple(i, j);
            EXPECT_EQ(board[i][j].getLocation(), loc);
            EXPECT_EQ(board[i][j].getPiece(), nullptr);
        }
    }
}


TEST(BoardTests, testWhiteToPlay) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    EXPECT_TRUE(b.getWhiteToPlay());

    Board board("r2qkb1r/pp1nnpp1/2p1p2p/3pPb2/3P4/5N2/PPPNBPPP/R1BQ1RK1 b kq - 0 8");
    EXPECT_FALSE(board.getWhiteToPlay());
}

TEST(BoardTests, testPieceLocations) {
    Board b("r2qkb1r/pp1nnpp1/2p1p2p/3pPb2/3P4/5N2/PPPNBPPP/R1BQ1RK1 w kq - 0 8");
    EXPECT_TRUE(b[4][0].getPiece() == nullptr);
    EXPECT_FALSE(b[0][0].getPiece() == nullptr);

    EXPECT_EQ(b[7][3].getPiece()->getID(), "wQ");
    EXPECT_FALSE(b[7][6].getPiece()->getID() == "bK");
}
