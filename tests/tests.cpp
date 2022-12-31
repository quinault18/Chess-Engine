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

TEST(SquareTest, getBasePiece) {
    
    BasePiece bp("wp");
    Square s(1, 5, &bp);

    EXPECT_EQ(s.getPiece(), &bp);
}

TEST(SquareTest, testEquality) {
    BasePiece bp("wQ");
    Square s(0, 0, &bp);
    Square s2 = s;
    Square s3(s);
    EXPECT_TRUE(s2 == s);
    EXPECT_TRUE(s3 == s);
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
    Move m(start, end, board.getSquare(start).getPiece(), board.getSquare(end).getPiece());

    EXPECT_EQ(m.pieceMoved->getID(), "wK");
    start = std::make_tuple(6, 0);
    end = std::make_tuple(4, 0);
    Move mv(start, end, board.getSquare(start).getPiece(), board.getSquare(end).getPiece());
    std::cout << mv << std::endl;
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

TEST(BoardTests, testClearBoard) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    b.clearBoard();
    b.loadFromFEN("r2qkb1r/pp1nnpp1/2p1p2p/3pPb2/3P4/5N2/PPPNBPPP/R1BQ1RK1 b kq - 0 8");
}

TEST(BoardTests, testCopyConstructor) {
    Board b("r2qkb1r/pp1nnpp1/2p1p2p/3pPb2/3P4/5N2/PPPNBPPP/R1BQ1RK1 b kq - 0 8");
    Board copy(b);

    EXPECT_EQ(b.getWhiteToPlay(), copy.getWhiteToPlay());
}

TEST(BoardTests, testEquality) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Board b2 = b;
    Board b3(b);
    EXPECT_TRUE(b2 == b);
    EXPECT_TRUE(b3 == b);

    Board b4("r4rk1/1pqnbpp1/2p1pn1p/p6P/2PP4/3Q1NN1/PP1B1PP1/1K1RR3 w - - 0 18");
    Board b5(b4);
    EXPECT_TRUE(b != b4);
    EXPECT_TRUE(b5 == b4);
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

TEST(PieceTestsKing, testGetValidMoves) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> moves = b[7][4].getPiece()->getValidMoves(&b);

    EXPECT_EQ(moves.size(), 0);

    Board b1("5k2/8/8/8/3K4/8/8/8 w - - 0 1");
    std::vector<Move> moves1 = b1[4][3].getPiece()->getValidMoves(&b1);
    std::vector<Move> movesBK = b1[0][5].getPiece()->getValidMoves(&b1);
    
    EXPECT_EQ(moves1.size(), 8);
    EXPECT_EQ(movesBK.size(), 5);
}

TEST(PieceTestsRook, testGetValidMoves) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> movesA8 = b[0][0].getPiece()->getValidMoves(&b);
    std::vector<Move> movesH8 = b[0][7].getPiece()->getValidMoves(&b);
    std::vector<Move> movesA1 = b[7][0].getPiece()->getValidMoves(&b);
    std::vector<Move> movesH1 = b[7][7].getPiece()->getValidMoves(&b);

    EXPECT_EQ(movesA8.size(), 0);
    EXPECT_EQ(movesH8.size(), 0);
    EXPECT_EQ(movesA1.size(), 0);
    EXPECT_EQ(movesH1.size(), 0);

    Board b1("r1bqkb1r/1pppppp1/1n3n2/p6p/P6P/2N2N2/1PPPPPP1/R1BQKB1R w KQkq - 0 1");
    movesA8 = b1[0][0].getPiece()->getValidMoves(&b1);
    movesH8 = b1[0][7].getPiece()->getValidMoves(&b1);
    movesA1 = b1[7][0].getPiece()->getValidMoves(&b1);
    movesH1 = b1[7][7].getPiece()->getValidMoves(&b1);

    EXPECT_EQ(movesA8.size(), 3);
    EXPECT_EQ(movesH8.size(), 3);
    EXPECT_EQ(movesA1.size(), 3);
    EXPECT_EQ(movesH1.size(), 3);

    Board b2("r1bqkb1r/1pppppp1/1n3n2/P6P/p6p/2N2N2/1PPPPPP1/R1BQKB1R w KQkq - 0 1");
    movesA8 = b2[0][0].getPiece()->getValidMoves(&b2);
    movesH8 = b2[0][7].getPiece()->getValidMoves(&b2);
    movesA1 = b2[7][0].getPiece()->getValidMoves(&b2);
    movesH1 = b2[7][7].getPiece()->getValidMoves(&b2);

    EXPECT_EQ(movesA8.size(), 4);
    EXPECT_EQ(movesH8.size(), 4);
    EXPECT_EQ(movesA1.size(), 4);
    EXPECT_EQ(movesH1.size(), 4);
}

TEST(PieceTestsBishop, testGetValidMoves) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> movesC8 = b[0][2].getPiece()->getValidMoves(&b);
    std::vector<Move> movesF8 = b[0][5].getPiece()->getValidMoves(&b);
    std::vector<Move> movesC1 = b[7][2].getPiece()->getValidMoves(&b);
    std::vector<Move> movesF1 = b[7][5].getPiece()->getValidMoves(&b);

    EXPECT_EQ(movesC8.size(), 0);
    EXPECT_EQ(movesF8.size(), 0);
    EXPECT_EQ(movesC1.size(), 0);
    EXPECT_EQ(movesF1.size(), 0);

    Board b1("r1bqk1nr/p1p2ppp/1pnp4/2b1p3/2B1P3/1P1P1N2/P1P2PPP/RNBQK2R w KQkq - 0 1");
    movesC8 = b1[0][2].getPiece()->getValidMoves(&b1);
    std::vector<Move> movesC5 = b1[3][2].getPiece()->getValidMoves(&b1);
    std::vector<Move> movesC4 = b1[4][2].getPiece()->getValidMoves(&b1);
    movesC1 = b1[7][2].getPiece()->getValidMoves(&b1);

    EXPECT_EQ(movesC8.size(), 7);
    EXPECT_EQ(movesC5.size(), 5);
    EXPECT_EQ(movesC4.size(), 5);
    EXPECT_EQ(movesC1.size(), 7);
}

TEST(PieceTestsKnight, testGetValidMoves) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> movesB8 = b[0][1].getPiece()->getValidMoves(&b);
    std::vector<Move> movesG8 = b[0][6].getPiece()->getValidMoves(&b);
    std::vector<Move> movesB1 = b[7][1].getPiece()->getValidMoves(&b);
    std::vector<Move> movesG1 = b[7][6].getPiece()->getValidMoves(&b);

    EXPECT_EQ(movesB8.size(), 2);
    EXPECT_EQ(movesG8.size(), 2);
    EXPECT_EQ(movesB1.size(), 2);
    EXPECT_EQ(movesG1.size(), 2);

    Board b1("8/8/2N2n2/3n4/8/4N3/8/8 w - - 0 1");
    std::vector<Move> movesC6 = b1[2][2].getPiece()->getValidMoves(&b1);
    std::vector<Move> movesF6 = b1[2][5].getPiece()->getValidMoves(&b1);
    std::vector<Move> movesD5 = b1[3][3].getPiece()->getValidMoves(&b1);
    std::vector<Move> movesE3 = b1[5][4].getPiece()->getValidMoves(&b1);

    EXPECT_EQ(movesC6.size(), 8);
    EXPECT_EQ(movesF6.size(), 7);
    EXPECT_EQ(movesD5.size(), 7);
    EXPECT_EQ(movesE3.size(), 8);
}

TEST(PieceTestsPawn, testGetValidMoves) {
    Board b("8/8/8/8/8/8/P7/8 w - - 0 1");

    std::vector<Move> movesA2 = b[6][0].getPiece()->getValidMoves(&b);

    EXPECT_EQ(movesA2.size(), 2);

    Board b1("8/8/8/8/8/2p5/2P5/8 w - - 0 1");
    std::vector<Move> movesC2 = b1[6][2].getPiece()->getValidMoves(&b1);

    EXPECT_EQ(movesC2.size(), 0);

    Board b2("8/8/8/8/8/1p1N4/2P5/8 w - - 0 1");
    movesC2 = b2[6][2].getPiece()->getValidMoves(&b2);

    EXPECT_EQ(movesC2.size(), 3);

    Board b3("8/8/8/8/2N5/1prp4/2P5/8 w - - 0 1");
    movesC2 = b3[6][2].getPiece()->getValidMoves(&b3);

    EXPECT_EQ(movesC2.size(), 2);
    
}

TEST(MoveGenerationTests, testMoveGeneration) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> moves = b.generateMoves();

    EXPECT_EQ(moves.size(), 20);

    b.makeMove(moves[0]);

    moves = b.generateMoves();

    EXPECT_FALSE(b.getWhiteToPlay());
    EXPECT_EQ(moves.size(), 20);

    Board b1("rnbqkbnr/p3pppp/2p5/1p1p4/3PP3/2N5/PPP2PPP/R1BQKBNR w KQkq - 0 4");
    moves = b1.generateMoves();

    b1.makeMove(moves[0]);
    moves = b1.generateMoves();
 
}

TEST(MakeMoveTests, makeMove) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");


    std::vector<Move> moves = b.generateMoves();
    b.makeMove(moves[0]);
    EXPECT_EQ(b.getSquare(moves[0].end).getPiece(), moves[0].pieceMoved);
    EXPECT_TRUE(b.getSquare(moves[0].start).getPiece() == nullptr);
    EXPECT_FALSE(b.getWhiteToPlay());
}

TEST(BoardTests, fenGeneration) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    EXPECT_EQ(b.toFEN(), fen);
    EXPECT_EQ(b.getMoveNumber(), 1);

    Board board("r4rk1/1pqnbpp1/2p1pn1p/p6P/2PP4/3Q1NN1/PP1B1PP1/1K1RR3 w - - 0 1");
    fen = "r4rk1/1pqnbpp1/2p1pn1p/p6P/2PP4/3Q1NN1/PP1B1PP1/1K1RR3 w KQkq - - 0 1";
  
}