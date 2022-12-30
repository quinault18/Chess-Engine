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

TEST(PieceTestsQueen, testGetValidMoves) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> moves = b[7][3].getPiece()->getValidMoves(&b);

    EXPECT_EQ(moves.size(), 0);

    Board b1("rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
    std::vector<Move> m = b1[7][3].getPiece()->getValidMoves(&b1);

    EXPECT_EQ(m.size(), 4);

    Board b2("rnbqkbnr/ppppp1pp/8/8/P7/4Pp2/1PPP1PPP/RNBQKBNR w KQkq - 0 4");
    std::vector<Move> ms = b2[7][3].getPiece()->getValidMoves(&b2);

    EXPECT_EQ(ms.size(), 2);

    Board b3("8/8/8/4Q3/8/8/8/8 w - - 0 1");
    std::vector<Move> ms2 = b3[3][4].getPiece()->getValidMoves(&b3);

    EXPECT_EQ(ms2.size(), 27);

    Board board("r1b1k1nr/pppp1qpp/2n5/b7/4P3/1QPp1N2/P4PPP/RNB2RK1 w kq - 0 10");

    std::vector<Move> ms1 = board[5][1].getPiece()->getValidMoves(&board);

    EXPECT_EQ(ms1.size(), 13);
}
