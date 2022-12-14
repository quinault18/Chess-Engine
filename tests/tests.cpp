#include <gtest/gtest.h>
#include <iostream>
#include "square.h"
#include "basepiece.h"
#include "board.h"
#include "move.h"
#include "castlingRights.h"


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

TEST(BoardTests, equalityTesting) {
    Board b("r1bq1rk1/pppp1ppp/2n1pn2/2b5/2B1P3/P4N2/1PPP1PPP/RNBQ1RK1 w - - 1 6");
    Board b2("r1bq1rk1/pppp1ppp/2n1pn2/2b5/2B1P3/P4N2/1PPP1PPP/RNBQ1RK1 w - - 1 6");
    Board b3("r1bq1rk1/pppp1ppp/2n1pn2/2b5/2B1P3/P4N2/1PPP1PPP/RNBQ1RK1 w - - 1 8");
    EXPECT_EQ(b.toFEN(), b2.toFEN());
    EXPECT_TRUE(b == b2);
    EXPECT_TRUE(b2 != b3);
}

TEST(BoardTests, fenGeneration) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    EXPECT_EQ(b.toFEN(), fen);
    EXPECT_EQ(b.getMoveNumber(), 1);

    Board board("r4rk1/1pqnbpp1/2p1pn1p/p6P/2PP4/3Q1NN1/PP1B1PP1/1K1RR3 w - - 0 1");
    fen = "r4rk1/1pqnbpp1/2p1pn1p/p6P/2PP4/3Q1NN1/PP1B1PP1/1K1RR3 w KQkq - - 0 1";
  
}

TEST(BoardTests, testSquareUnderAttack) {
    Board board("r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 3 3");
    EXPECT_TRUE(board.squareUnderAttack(board[2][2]));
    EXPECT_TRUE(board.squareUnderAttack(board[4][0]));
    EXPECT_TRUE(board.squareUnderAttack(board[3][3]));
    EXPECT_TRUE(board.squareUnderAttack(board[3][5]));

    EXPECT_FALSE(board.squareUnderAttack(board[4][1]));
    EXPECT_FALSE(board.squareUnderAttack(board[4][6]));
    // EXPECT_FALSE(board.squareUnderAttack(board[0][0]));

}

TEST(BoardTests, testPinsAndChecksStartingPosition) {
    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > pinsAndChecks = b.getPinsAndChecks();

    EXPECT_FALSE(std::get<0>(pinsAndChecks));
    EXPECT_EQ(std::get<1>(pinsAndChecks).size(), 0);
    EXPECT_EQ(std::get<2>(pinsAndChecks).size(), 0);

    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1");
    pinsAndChecks = board.getPinsAndChecks();

    EXPECT_FALSE(std::get<0>(pinsAndChecks));
    EXPECT_EQ(std::get<1>(pinsAndChecks).size(), 0);
    EXPECT_EQ(std::get<2>(pinsAndChecks).size(), 0);
}

TEST(BoardTests, testPinsAndChecksOnePin) {
    Board b("rnbqkbnr/ppppp1pp/5p2/7Q/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 1 2");
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > pinsAndChecks = b.getPinsAndChecks();
    EXPECT_TRUE(std::get<0>(pinsAndChecks));
    EXPECT_EQ(std::get<1>(pinsAndChecks).size(), 0);
    EXPECT_EQ(std::get<2>(pinsAndChecks).size(), 1);
}

TEST(BoardTests, testPinsAndChecksTwoPins) {
    Board b("1r2k1r1/pbppnp1p/1bn2P2/8/Q7/B1PB1q2/P4PPP/3RR1K1 w - - 0 20");
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > pinsAndChecks = b.getPinsAndChecks();
    EXPECT_FALSE(std::get<0>(pinsAndChecks));
    EXPECT_EQ(std::get<1>(pinsAndChecks).size(), 2);
    EXPECT_EQ(std::get<2>(pinsAndChecks).size(), 0);
}

TEST(BoardTests, testPinsAndChecksTwoChecks) {
    Board b("1r4r1/pbpknp1p/1b3P2/5B2/8/B1P2q2/P4PPP/3R2K1 b - - 1 22");
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > pinsAndChecks = b.getPinsAndChecks();
    EXPECT_TRUE(std::get<0>(pinsAndChecks));
    EXPECT_EQ(std::get<1>(pinsAndChecks).size(), 0);
    EXPECT_EQ(std::get<2>(pinsAndChecks).size(), 2);
}

TEST(BoardTests, testPinsAndChecksKnight) {
    Board b("r3r1k1/pp3pbp/2p1B1p1/1qB5/3P4/Q4Nn1/P4PPP/3R1K1R w - - 5 21");
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > pinsAndChecks = b.getPinsAndChecks();
    EXPECT_TRUE(std::get<0>(pinsAndChecks));
    EXPECT_EQ(std::get<1>(pinsAndChecks).size(), 0);
    EXPECT_EQ(std::get<2>(pinsAndChecks).size(), 2);
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

TEST(PieceTestsPawn, testGetAttackingMoves) {
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> moves = board[6][1].getPiece()->getAttackingMoves(&board);

    EXPECT_EQ(moves.size(), 2);

    moves = board[6][0].getPiece()->getAttackingMoves(&board);
    EXPECT_EQ(moves.size(), 1);

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


TEST(CastlingRightsTest, testToString) {
    CastlingRights cr(true, true, true, true);
    EXPECT_EQ(cr.toString(), "KQkq");

    CastlingRights cr1(false, true, true, true);
    EXPECT_EQ(cr1.toString(), "Qkq");

    CastlingRights cr2(false, false, true, true);
    EXPECT_EQ(cr2.toString(), "kq");

    CastlingRights cr3(false, false, false, true);
    EXPECT_EQ(cr3.toString(), "q");

    CastlingRights cr4(false, false, false, false);
    EXPECT_EQ(cr4.toString(), "-");

    CastlingRights cr5("KQkq");
    EXPECT_TRUE(cr5.whiteKingSide);

    CastlingRights cr6("Qkq");
    EXPECT_FALSE(cr6.whiteKingSide);
    EXPECT_TRUE(cr6.whiteQueenSide);
    EXPECT_TRUE(cr6.blackQueenSide);
    EXPECT_TRUE(cr6.blackKingSide);

    CastlingRights cr7("-");
    EXPECT_FALSE(cr7.whiteKingSide);
    EXPECT_FALSE(cr7.whiteQueenSide);
    EXPECT_FALSE(cr7.blackKingSide);
    EXPECT_FALSE(cr7.blackQueenSide);
}

TEST(CastlingTests, whiteKingSide) {
    Board board("r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4");
    Board check("r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 5 4");
    std::vector<Move> moves = board.generateMoves();

    for (Move move : moves) {
        if (move.isCastleMove) {
            board.makeMove(move);
            break;
        }
    }
    EXPECT_TRUE(board == check);   
    EXPECT_FALSE(board.getCastlingRights().whiteKingSide);
    EXPECT_FALSE(board.getCastlingRights().whiteQueenSide);
}

TEST(CastlingTests, whiteQueenSide) {
    Board board("rnbqkb1r/1ppppppp/p4n2/6B1/3P4/2N5/PPPQPPPP/R3KBNR w KQq - 5 5");
    Board check("rnbqkb1r/1ppppppp/p4n2/6B1/3P4/2N5/PPPQPPPP/2KR1BNR b q - 6 5");
    std::vector<Move> moves = board.generateMoves();
    
    for (Move move : moves) {
        if (move.isCastleMove) {
            board.makeMove(move);
            break;
        }
    }

    EXPECT_TRUE(board == check);
    EXPECT_FALSE(board.getCastlingRights().whiteKingSide);
    EXPECT_FALSE(board.getCastlingRights().whiteQueenSide);
}

TEST(CastlingTests, blackKingSide) {
    Board board("3rk2r/ppqnbpp1/2p1pn1p/7P/2PP4/5NN1/PP1BQPP1/1K1R3R b k - 6 17");
    Board check("3r1rk1/ppqnbpp1/2p1pn1p/7P/2PP4/5NN1/PP1BQPP1/1K1R3R w - - 7 18");
    std::vector<Move> moves = board.generateMoves();
    
    for (Move move : moves) {
        if (move.isCastleMove) {
            board.makeMove(move);
            break;
        }
    }

    EXPECT_TRUE(board == check);
    EXPECT_FALSE(board.getCastlingRights().blackKingSide);
    EXPECT_FALSE(board.getCastlingRights().blackQueenSide);
}

TEST(CastlingTests, blackQueenSide) {
    Board board("r3kr2/ppqnbpp1/2p1pn1p/7P/2PP4/P2Q1NN1/1P1B1PP1/1K1R3R b q - 0 17");
    Board check("2kr1r2/ppqnbpp1/2p1pn1p/7P/2PP4/P2Q1NN1/1P1B1PP1/1K1R3R w - - 1 18");
    std::vector<Move> moves = board.generateMoves();
    
    for (Move move : moves) {
        if (move.isCastleMove) {
            board.makeMove(move);
            break;
        }
    }

    EXPECT_TRUE(board == check);
    EXPECT_FALSE(board.getCastlingRights().blackKingSide);
    EXPECT_FALSE(board.getCastlingRights().blackQueenSide);
}
