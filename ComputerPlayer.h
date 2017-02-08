#pragma once

#include <iostream>
#include "GameEngine.h"
#include "Move.h"

using namespace std;

class ComputerPlayer {
public:
  ComputerPlayer(int difficulty, char color) {
    this->difficulty = difficulty;
    this->color = color;
    this->G = GameEngine();
  }

  Move getMove() {
    whiteKingPosition = G.getWhiteKingPosition();
    blackKingPosition = G.getBlackKingPosition();

    return alphaBetaRoot();
  }

private:
  int difficulty;
   char color;

   GameEngine G;

   int whiteKingPosition;
   int blackKingPosition;

   bool CANWHITEKINGSIDECASTLE;
   bool CANWHITEQUEENSIDECASTLE;

   bool CANBLACKKINGSIDECASTLE;
   bool CANBLACKQUEENSIDECASTLE;
    int pawnEvalTableWhite[128] = {
            500,  500,  500,  500,  500,  500,  500,  500,  0,  0,  0,  0,  0,  0,  0,  0,
            50, 50, 50, 50, 50, 50, 50, 50, 0,  0,  0,  0,  0,  0,  0,  0,
            10, 10, 20, 30, 30, 20, 10, 10, 0,  0,  0,  0,  0,  0,  0,  0,
            5,  5, 10, 25, 25, 10,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0, 20, 20,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            5, -5,-10,  0,  0,-10, -5,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10,-20,-20, 10, 10,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    int pawnEvalTableWhiteEnd[128] = {
            900,900,900,900,900,900,900,900,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            50,50,50,50,50,50,50,50,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            40,40,40,40,40,40,40,40,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            30,30,30,30,30,30,30,30,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            20,20,20,20,20,20,20,20,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            10,10,10,10,10,10,10,10,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            0 ,0 ,0 ,0 ,0 ,0 ,0 , 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
    };

    int pawnEvalTableBlackEnd[128] = {
            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            0 ,0 ,0 ,0 ,0 ,0 ,0 , 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            10,10,10,10,10,10,10,10,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            20,20,20,20,20,20,20,20,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            30,30,30,30,30,30,30,30,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            40,40,40,40,40,40,40,40,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            50,50,50,50,50,50,50,50,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
            900,900,900,900,900,900,900,900,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
    };

    int knightEvalTableWhite[128] = {
            -50,-40,-30,-30,-30,-30,-40,-50,    0,  0,  0,  0,  0,  0,  0,  0,
            -40,-20,  0,  0,  0,  0,-20,-40,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  0, 10, 15, 15, 10,  0,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  5, 15, 20, 20, 15,  5,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  0, 15, 20, 20, 15,  0,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  5, 10, 15, 15, 10,  5,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -40,-20,  0,  5,  5,  0,-20,-40,    0,  0,  0,  0,  0,  0,  0,  0,
            -50,-40,-30,-30,-30,-30,-40,-50,    0,  0,  0,  0,  0,  0,  0,  0
    };

    int bishopEvalTableWhite[128] = {
            -20,-10,-10,-10,-10,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  0,  0,  0,  0,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  5, 10, 10,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  5,  5, 10, 10,  5,  5,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0, 10, 10, 10, 10,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10, 10, 10, 10, 10, 10, 10,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  5,  0,  0,  0,  0,  5,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -20,-10,-10,-10,-10,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0
    };

    int rookEvalTableWhite[128] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10, 10, 10, 10, 10,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    int queenEvalTableWhite[128] = {
            -20,-10,-10, -5, -5,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  0,  0,  0,  0,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  5,  5,  5,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  5,  5,  5,  5,  0, -5,     0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  5,  5,  5,  5,  0, -5,      0,  0,  0,  0,  0,  0,  0,  0,
            -10,  5,  5,  5,  5,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  5,  0,  0,  0,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -20,-10,-10, -5, -5,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0
    };

    int kingEvalTableBeginWhite[128] = {
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -20,-30,-30,-40,-40,-30,-30,-20,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,-20,-20,-20,-20,-20,-20,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            20, 20,  0,  0,  0,  0, 20, 20,     0,  0,  0,  0,  0,  0,  0,  0,
            20, 30, 10,  0,  0, 10, 30, 20,     0,  0,  0,  0,  0,  0,  0,  0
    };

    int kingEvalTableEndWhite[128] = {
            -50,-40,-30,-20,-20,-30,-40,-50,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-20,-10,  0,  0,-10,-20,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 20, 30, 30, 20,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 30, 40, 40, 30,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 30, 40, 40, 30,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 20, 30, 30, 20,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-30,  0,  0,  0,  0,-30,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -50,-30,-30,-30,-30,-30,-30,-50,    0,  0,  0,  0,  0,  0,  0,  0
    };

    int pawnEvalTableBlack[128] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10,-20,-20, 10, 10,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            5, -5,-10,  0,  0,-10, -5,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0, 20, 20,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            5,  5, 10, 25, 25, 10,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            10, 10, 20, 30, 30, 20, 10, 10, 0,  0,  0,  0,  0,  0,  0,  0,
            50, 50, 50, 50, 50, 50, 50, 50, 0,  0,  0,  0,  0,  0,  0,  0,
            500,  500,  500,  500,  500,  500,  500,  500,  0,  0,  0,  0,  0,  0,  0,  0
    };

    int knightEvalTableBlack[128] = {
            -50,-40,-30,-30,-30,-30,-40,-50,    0,  0,  0,  0,  0,  0,  0,  0,
            -40,-20,  0,  5,  5,  0,-20,-40,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  5, 10, 15, 15, 10,  5,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  0, 15, 20, 20, 15,  0,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  5, 15, 20, 20, 15,  5,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,  0, 10, 15, 15, 10,  0,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -40,-20,  0,  0,  0,  0,-20,-40,    0,  0,  0,  0,  0,  0,  0,  0,
            -50,-40,-30,-30,-30,-30,-40,-50,    0,  0,  0,  0,  0,  0,  0,  0
    };
    int bishopEvalTableBlack[128] = {
            -20,-10,-10,-10,-10,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  5,  0,  0,  0,  0,  5,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10, 10, 10, 10, 10, 10, 10,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0, 10, 10, 10, 10,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  5,  5, 10, 10,  5,  5,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  5, 10, 10,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  0,  0,  0,  0,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -20,-10,-10,-10,-10,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0
    };
    int rookEvalTableBlack[128] = {
            0,  0,  0,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  0,  0,  0,  0,  0, -5, 0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10, 10, 10, 10, 10,  5,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    int queenEvalTableBlack[128] = {
            -20,-10,-10, -5, -5,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  0,  0,  0,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  5,  5,  5,  5,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  5,  5,  5,  5,  0, -5,      0,  0,  0,  0,  0,  0,  0,  0,
            -5,  0,  5,  5,  5,  5,  0, -5,     0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  5,  5,  5,  5,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -10,  0,  0,  0,  0,  0,  0,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -20,-10,-10, -5, -5,-10,-10,-20,    0,  0,  0,  0,  0,  0,  0,  0
    };
    int kingEvalTableBeginBlack[128] = {
            20, 30, 10,  0,  0, 10, 30, 20,     0,  0,  0,  0,  0,  0,  0,  0,
            20, 20,  0,  0,  0,  0, 20, 20,     0,  0,  0,  0,  0,  0,  0,  0,
            -10,-20,-20,-20,-20,-20,-20,-10,    0,  0,  0,  0,  0,  0,  0,  0,
            -20,-30,-30,-40,-40,-30,-30,-20,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-40,-40,-50,-50,-40,-40,-30,    0,  0,  0,  0,  0,  0,  0,  0
    };
    int kingEvalTableEndBlack[128] = {
            -50,-30,-30,-30,-30,-30,-30,-50,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-30,  0,  0,  0,  0,-30,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 20, 30, 30, 20,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 30, 40, 40, 30,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 30, 40, 40, 30,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-10, 20, 30, 30, 20,-10,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -30,-20,-10,  0,  0,-10,-20,-30,    0,  0,  0,  0,  0,  0,  0,  0,
            -50,-40,-30,-20,-20,-30,-40,-50,    0,  0,  0,  0,  0,  0,  0,  0
    };

     vector<Move> getBlackCaptureMoves(bool canWhiteKingSideCastle, bool canWhiteQueenSideCastle,bool canBlackKingSideCastle,bool canBlackQueenSideCastle) {
        vector<Move> possibleMoves;
        for(int i = 0; i < 128; i++) {
            // skip fake board
            if ((i & 0x0f) == 8) {
                i += 7;
                continue;
            }
            if(board[i] < 0) {
                vector<int> miniMoves = G.getPossibleMoves(i,canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle);
                for(int j = 0; j < miniMoves.size(); j++) {
                    Move move = Move(i,miniMoves.get(j),G.board);
                    if(G.board[move.getAfter()] != 0) {
                        possibleMoves.push_back(move);
                    }
                }
            }
        }
        return possibleMoves;
    }

    vector<Move> getWhiteCaptureMoves(bool canWhiteKingSideCastle, bool canWhiteQueenSideCastle,bool canBlackKingSideCastle,bool canBlackQueenSideCastle) {
      vector<Move> possibleMoves;
      for(int i = 0; i < 128; i++) {
          // skip fake board
          if ((i & 0x0f) == 8) {
              i += 7;
              continue;
          }
          if(G.board[i] > 0) {
              vector<int> miniMoves = G.getPossibleMoves(i,canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle);
              for(int j = 0; j < miniMoves.size(); j++) {
                  Move move = Move(i,miniMoves.get(j),G.board);
                  if(G.board[move.getAfter()] != 0) {
                      possibleMoves.push_back(move);
                  }
              }
          }
      }
      return possibleMoves;

  }

  Move alphaBetaRoot() {
       int alpha = INT_MIN;
       int beta = INT_MAX;
       Move bestMove = null;

       bool canWhiteKingSideCastle = G.isCanWhiteKingSideCastle();
       bool canWhiteQueenSideCastle = G.isCanWhiteQueenSideCastle();

       bool canBlackKingSideCastle = G.isCanBlackKingSideCastle();
       bool canBlackQueenSideCastle = G.isCanBlackQueenSideCastle();



       if(color == 'w') {
           int score = INT_MIN;
           vector<Move> possibleMoves = prioritize(G.getAllPossibleWhiteMoves(canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle));
           for(int i = 0; i < possibleMoves.size(); i++) {
               CANWHITEKINGSIDECASTLE = canWhiteKingSideCastle;
               CANWHITEQUEENSIDECASTLE = canWhiteQueenSideCastle;
               CANBLACKKINGSIDECASTLE = canBlackKingSideCastle;
               CANBLACKQUEENSIDECASTLE = canBlackQueenSideCastle;
               Move move = possibleMoves.get(i);

               short taken = G.simulateMove(move);
               int value = alphaBeta('b', alpha,beta,depth,CANWHITEKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE,CANBLACKKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE);
               if(value > score) {
                   score = value;
                   bestMove = move;
               }
               G.undoMove(taken,move);
           }

       } else {
           double score = INT_MAX;
           vector<Move> possibleMoves = prioritize(G.getAllPossibleBlackMoves(canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle));
           for(int i = 0; i < possibleMoves.size(); i++) {
               CANWHITEKINGSIDECASTLE = canWhiteKingSideCastle;
               CANWHITEQUEENSIDECASTLE = canWhiteQueenSideCastle;
               CANBLACKKINGSIDECASTLE = canBlackKingSideCastle;
               CANBLACKQUEENSIDECASTLE = canBlackQueenSideCastle;
               Move move = possibleMoves.get(i);

               short taken = G.simulateMove(move);
               int value = alphaBeta('w', alpha,beta,depth,CANWHITEKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE,CANBLACKKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE);
               if(value < score) {
                   score = value;
                   bestMove = move;
               }
               G.undoMove(taken,move);
           }

       }
       return bestMove;
   }

   int alphaBeta(char turn, int alpha, int beta, int depth,bool canWhiteKingSideCastle,bool canWhiteQueenSideCastle,bool canBlackKingSideCastle,bool canBlackQueenSideCastle) {
       depth--;
       if(depth == 0) {
           //return evaluateBoard();/*
           if(turn == 'w') {
               return quiesent('w',alpha, beta,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle,canBlackKingSideCastle);
           } else {
               return quiesent('b',alpha, beta,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle,canBlackKingSideCastle);

           }
       }
       if(turn == 'w') {
           vector<Move> possibleMoves = prioritize(G.getAllPossibleWhiteMoves(canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle));
           if(possibleMoves.size() == 0) {
               if(!G.isWhiteKingInCheck()) {
                   return 0;
               }
               return -100000;
           }
           for(int i = 0; i < possibleMoves.size(); i++) {
               CANWHITEKINGSIDECASTLE = canWhiteKingSideCastle;
               CANWHITEQUEENSIDECASTLE = canWhiteQueenSideCastle;
               CANBLACKKINGSIDECASTLE = canBlackKingSideCastle;
               CANBLACKQUEENSIDECASTLE = canBlackQueenSideCastle;

               Move move = possibleMoves.get(i);
               short taken = G.simulateMove(move);
               int score = alphaBeta('b', alpha,beta,depth,CANWHITEKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE,CANBLACKKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE);
               G.undoMove(taken,move);

               if(score > alpha) {
                   alpha = score;
               }
               if(alpha >= beta) {
                   return alpha;
               }
           }
           return alpha;
       } else {
           vector<Move> possibleMoves = prioritize(G.getAllPossibleBlackMoves(canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle));
           if(possibleMoves.size() == 0) {
               if(!G.isBlackKingInCheck()) {
                   return 0;
               }
               return 100000;
           }
           for(int i = 0; i < possibleMoves.size(); i++) {
               CANWHITEKINGSIDECASTLE = canWhiteKingSideCastle;
               CANWHITEQUEENSIDECASTLE = canWhiteQueenSideCastle;
               CANBLACKKINGSIDECASTLE = canBlackKingSideCastle;
               CANBLACKQUEENSIDECASTLE = canBlackQueenSideCastle;

               Move move = possibleMoves.get(i);
               short taken = G.simulateMove(move);

               int score = alphaBeta('w', alpha,beta,depth,CANWHITEKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE,CANBLACKKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE);
               G.undoMove(taken,move);

               if(score < beta) {
                   beta = score;
               }
               if(alpha >= beta) {
                   return beta;
               }
           }
           return beta;
       }
   }



   int evaluateBoard() {
      /* if(isThreeFoldDraw()) {
           return 0;
       }*/




       int score = 0;
       for (int i = 0; i < 128; i++) {
           // skip fake board
           if ((i & 0x0f) == 8) {
               i += 7;
               continue;
           }
           switch (G.board[i]) {
               case 1:
                   score += 100;
                   if(G.getNumBlackQueen() == 0 &&
                           (G.getNumBlackBishop() + G.getNumBlackKnight()) <= 2 &&
                           G.getNumBlackRook() < 2) {
                       score += pawnEvalTableWhiteEnd[i];
                   } else {
                       score += pawnEvalTableWhite[i];
                   }
                   break;
               case 2:
                   score += 525;
                   score += rookEvalTableWhite[i];
                   break;
               case 3:
                   score += 350;
                   score += knightEvalTableWhite[i];
                   break;
               case 4:
                   score += 350;
                   score += bishopEvalTableWhite[i];
                   break;
               case 5:
                   score += 1000;
                   score += queenEvalTableWhite[i];
                   break;
               case 6:
                   score += 100000;
                   if(G.getNumBlackQueen() == 0 &&
                           (G.getNumBlackBishop() + G.getNumBlackKnight()) <= 2 &&
                           G.getNumBlackRook() < 2) {
                       score += kingEvalTableEndWhite[i];
                   } else {
                       score += kingEvalTableBeginWhite[i];
                   }
                   break;

               case -1:
                   score -= 100;

                   if(G.getNumWhiteQueen() == 0 &&
                           (G.getNumWhiteBishop() + G.getNumWhiteKnight()) <= 2 &&
                           G.getNumWhiteRook() < 2) {
                       score -= pawnEvalTableBlackEnd[i];
                   } else {
                       score -= pawnEvalTableBlack[i];
                   }
                   break;
               case -2:
                   score -= 525;
                   score -= rookEvalTableBlack[i];
                   break;
               case -3:
                   score -= 350;
                   score -= knightEvalTableBlack[i];
                   break;
               case -4:
                   score -= 350;
                   score -= bishopEvalTableBlack[i];

                   break;
               case -5:
                   score -= 1000;
                   score -= queenEvalTableBlack[i];
                   break;
               case -6:
                   score -= 100000;
                   if(G.getNumWhiteQueen() == 0 &&
                           (G.getNumWhiteBishop() + G.getNumWhiteKnight()) <= 2 &&
                           G.getNumWhiteRook() < 2) {
                       depth = 4;

                       score -= kingEvalTableEndBlack[i];
                   } else {
                       score -= kingEvalTableBeginBlack[i];
                   }
                   break;
           }
       }
       return score;
   }




   int quiesent(char turn, int alpha, int beta,bool canWhiteKingSideCastle,bool canWhiteQueenSideCastle,bool canBlackKingSideCastle,bool canBlackQueenSideCastle) {



       if(turn == 'w') {

           int stand_pat = evaluateBoard();
           if(stand_pat > alpha) {
               alpha = stand_pat;
           }
           if(alpha >= beta) {
               return alpha;
           }



           vector<Move> possibleMoves = prioritize(getWhiteCaptureMoves(canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle));
           /*if(possibleMoves.size() == 0) {
               if(getAllPossibleWhiteMoves(false,false,false,false).size() == 0) {
                   if(isWhiteKingInCheck()) {
                       return -10000;
                   }
                   return 0;
               }
           }*/
           for(int i = 0; i < possibleMoves.size(); i++) {
               Move move = possibleMoves.get(i);
               short taken = G.simulateMove(move);
               int score = quiesent('b', alpha,beta,CANWHITEKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE,CANBLACKKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE);
               G.undoMove(taken,move);

               if(score > alpha) {
                   alpha = score;
               }
               if(alpha >= beta) {
                   return alpha;
               }
           }
           return alpha;
       } else {

           int stand_pat = evaluateBoard();
           if(stand_pat < beta) {
               beta = stand_pat;
           }
           if(alpha >= beta) {
               return beta;
           }

           vector<Move> possibleMoves = prioritize(getBlackCaptureMoves(canWhiteKingSideCastle,canWhiteQueenSideCastle,canBlackKingSideCastle,canBlackQueenSideCastle));
           /*if(possibleMoves.size()== 0) {
               if(getAllPossibleBlackMoves(false,false,false,false).size() == 0) {
                   if(isBlackKingInCheck()) {
                       return 10000;
                   }
                   return 0;
               }
           }*/
           for(int i = 0; i < possibleMoves.size(); i++) {

               Move move = possibleMoves.get(i);
               short taken = G.simulateMove(move);

               int score = quiesent('w', alpha,beta,CANWHITEKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE,CANBLACKKINGSIDECASTLE,CANWHITEQUEENSIDECASTLE);
               G.undoMove(taken,move);

               if(score < beta) {
                   beta = score;
               }
               if(alpha >= beta) {
                   return beta;
               }
           }
           return beta;
       }
   }

};
