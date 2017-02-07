#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class GameEngine {
public:
  GameEngine() {}

  vector<int> getValidMoves() {
      vector<int> steve;
      return steve;
  }

  int updateGameState(int loc1, int loc2, int updateStatus, int promotionPiece) {
    return -1;
  }

  vector<int> getGameBoard() {
      vector<int> steve;
      return steve;
  }

  vector<int> getPossibleMoves(int position) {
    vector<int> possibleMoves;

    switch (board[position]) {
            /*  White Pieces  */
        // Pawn
        case 1:
            // Normal
            if(((position-16) & 0x88)==0) {
                if(board[position-16]==0) {
                    short taken = simulateMove(position,position-16);
                    if(!isWhiteKingInCheck()) {
                        possibleMoves.push_back(position - 16);
                    }
                    undoMove(taken,position,position-16);

                    if ((position & 0x60) == 0x60 && board[position-32]==0) {
                        taken = simulateMove(position,position-32);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(position - 32);
                        }
                        undoMove(taken,position,position+-32);

                    }
                }

            }
            // Eating
            if(((position-15) & 0x88)==0) {
                if (board[position - 15] < 0) {
                    short taken = simulateMove(position,position-15);
                    if(!isWhiteKingInCheck()) {
                        possibleMoves.push_back(position - 15);
                    }
                    undoMove(taken,position,position-15);

                }
            }
            if(((position-17) & 0x88)==0) {
                if (board[position - 17] < 0) {
                    short taken = simulateMove(position,position-17);
                    if(!isWhiteKingInCheck()) {
                        possibleMoves.push_back(position - 17);
                    }
                    undoMove(taken,position,position-17);

                }
            }

            break;

        // Rook
        case 2:
            for(int i = 0; i < 4; i++) {
                int index = position+rookDeltaValues[i];
                while((index&0x88) == 0) {
                    if(board[index] == 0) {
                        short taken = simulateMove(position,index);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        index += rookDeltaValues[i];
                    } else if(board[index] > 0){
                        break;
                    } else {
                        short taken = simulateMove(position,index);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        break;
                    }

                }
            }
            break;

        // Knight
        case 3:
            for(int i = 0; i < 8; i++) {
                if(((position+knightDeltaValues[i])&0x88) == 0 &&(board[position+knightDeltaValues[i]]) <= 0) {
                    short taken = simulateMove(position,position+knightDeltaValues[i]);
                    if(!isWhiteKingInCheck()) {
                        possibleMoves.push_back(position + knightDeltaValues[i]);
                    }
                    undoMove(taken,position,position+knightDeltaValues[i]);

                }
            }
            break;

        // Bishop
        case 4:
            for(int i = 0; i < 4; i++) {
                int index = position+bishopDeltaValues[i];
                while((index&0x88) == 0) {
                    if(board[index] == 0) {
                        short taken = simulateMove(position,index);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        index += bishopDeltaValues[i];
                    } else if(board[index] > 0){
                        break;
                    } else {
                        short taken = simulateMove(position,index);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        break;
                    }

                }
            }
            break;

        // Queen
        case 5:
            for(int i = 0; i < 8; i++) {
                int index = position+queenDeltaValues[i];
                while((index&0x88) == 0) {
                    if(board[index] == 0) {
                        short taken = simulateMove(position,index);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        index += queenDeltaValues[i];
                    } else if(board[index] > 0){
                        break;
                    } else {
                        short taken = simulateMove(position,index);
                        if(!isWhiteKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        break;
                    }

                }
            }
            break;

        // King
        case 6:
            for(int i = 0; i < 8; i++) {
                if(((position+kingDeltaValues[i])&0x88) == 0 &&(board[position+kingDeltaValues[i]]) <= 0) {
                    short taken = simulateMove(position,position+kingDeltaValues[i]);
                    if(!isWhiteKingInCheck()) {
                        possibleMoves.push_back(position + kingDeltaValues[i]);
                    }
                    undoMove(taken,position,position+kingDeltaValues[i]);
                }
            }
            // King side castle
            if(canWhiteKingSideCastle &&
                    board[117] == 0 && board[118] == 0 &&
                    !isAttackedByBlack(116) && !isAttackedByBlack(117) && !isAttackedByBlack(118)) {
               possibleMoves.push_back(118);
            }

            // Queen side castle
            if(canWhiteQueenSideCastle &&
                    board[115] == 0 && board[114] == 0 && board[113] == 0 &&
                    !isAttackedByBlack(116) && !isAttackedByBlack(115) && !isAttackedByBlack(114)) {
                possibleMoves.push_back(114);
            }
            break;

            /*  Black Pieces  */
        // Pawn
        case -1:
            // Normal
            if(((position+16)&0x88)==0) {
                if(board[position+16]==0) {
                    short taken = simulateMove(position,position+16);
                    if(!isBlackKingInCheck()) {
                        possibleMoves.push_back(position + 16);
                    }
                    undoMove(taken,position,position+16);
                    if ((position & 0xf0) == 0x10 && board[position+32]==0) {
                        taken = simulateMove(position,position+32);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(position + 32);
                        }
                        undoMove(taken,position,position+32);
                    }
                }

            }
            // Eating
            if(((position+15) & 0x88)==0) {
                if (board[position + 15] > 0) {
                    short taken = simulateMove(position,position+15);
                    if(!isBlackKingInCheck()) {
                        possibleMoves.push_back(position + 15);
                    }
                    undoMove(taken,position,position+15);
                }
            }
            if(((position+17) & 0x88)==0) {
                if (board[position + 17] > 0) {
                    short taken = simulateMove(position,position+17);
                    if(!isBlackKingInCheck()) {
                        possibleMoves.push_back(position + 17);
                    }
                    undoMove(taken,position,position+17);
                }
            }
            break;

        // Rook
        case -2:
            for(int i = 0; i < 4; i++) {
                int index = position+rookDeltaValues[i];
                while((index&0x88) == 0) {
                    if(board[index] == 0) {
                        short taken = simulateMove(position,index);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);

                        index += rookDeltaValues[i];
                    } else if(board[index] < 0){
                        break;
                    } else {
                        short taken = simulateMove(position,index);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);
                        break;
                    }

                }
            }
            break;

        // Knight
        case -3:
            for(int i = 0; i < 8; i++) {
                if(((position+knightDeltaValues[i])&0x88) == 0 && (board[position+knightDeltaValues[i]]) >= 0) {
                    short taken = simulateMove(position,position+knightDeltaValues[i]);
                    if(!isBlackKingInCheck()) {
                        possibleMoves.push_back(position + knightDeltaValues[i]);
                    }
                    undoMove(taken,position,position+knightDeltaValues[i]);
                }
            }
            break;

        // Bishop
        case -4:
            for(int i = 0; i < 4; i++) {
                int index = position+bishopDeltaValues[i];
                while((index&0x88) == 0) {
                    if(board[index] == 0) {
                        short taken = simulateMove(position,index);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);
                        index += bishopDeltaValues[i];
                    } else if(board[index] < 0){
                        break;
                    } else {
                        short taken = simulateMove(position,index);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);
                        break;
                    }

                }
            }
            break;

        // Queen
        case -5:
            for(int i = 0; i < 8; i++) {
                int index = position+queenDeltaValues[i];
                while((index&0x88) == 0) {
                    if(board[index] == 0) {
                        short taken = simulateMove(position,index);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);
                        index += queenDeltaValues[i];
                    } else if(board[index] < 0){
                        break;
                    } else {
                        short taken = simulateMove(position,index);
                        if(!isBlackKingInCheck()) {
                            possibleMoves.push_back(index);
                        }
                        undoMove(taken,position,index);
                        break;
                    }

                }
            }
            break;

        // King
        case -6:
            for(int i = 0; i < 8; i++) {
                if(((position+kingDeltaValues[i])&0x88) == 0 &&(board[position+kingDeltaValues[i]]) >= 0) {
                    short taken = simulateMove(position,position+kingDeltaValues[i]);
                    if(!isBlackKingInCheck()) {
                        possibleMoves.push_back(position + kingDeltaValues[i]);
                    }
                    undoMove(taken,position,position+kingDeltaValues[i]);
                }
            }
            // King side castle
            if(canBlackKingSideCastle &&
                    board[5] == 0 && board[6] == 0 &&
                    !isAttackedByWhite(4) && !isAttackedByWhite(5) && !isAttackedByWhite(6)) {
                possibleMoves.push_back(6);
            }
            // Queen side castle
            if(canBlackQueenSideCastle &&
                    board[1] == 0 && board[2] == 0 && board[3] ==0 &&
                    !isAttackedByWhite(2) && !isAttackedByWhite(3) && !isAttackedByWhite(4)){
                possibleMoves.push_back(2);
            }
            break;
    }

    return possibleMoves;
}



bool isBlackKingInCheck() {
    for(int i = 0; i < 128; i++) {
        // If we found a white piece
        if(board[i] > 0) {
            if (ATTACK_ARRAY[(blackKingPosition - i + 128)] != 0) {
                // Find the delta
                int delta = DELTA_ARRAY[blackKingPosition-i+128];
                int index = i;
                int attackIndex = ATTACK_ARRAY[(blackKingPosition - i + 128)];
                switch (board[i]) {
                    case 1:
                        if(attackIndex != 4) {
                            continue;
                        }
                        break;
                    case 2:
                        if(attackIndex != 1 && attackIndex != 2) {
                            continue;
                        }
                        break;
                    case 3:
                        if(attackIndex != 6) {
                            continue;
                        }
                        break;
                    case 4:
                        if(attackIndex != 4 &&
                                attackIndex != 3 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case 5:
                        if(attackIndex != 1 &&
                                attackIndex != 2 &&
                                attackIndex != 3 &&
                                attackIndex != 4 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case 6:
                        if(attackIndex != 1 &&
                                attackIndex != 3 &&
                                attackIndex != 4) {
                            continue;
                        }
                        break;
                }
                if(delta>0) {
                    while(true) {
                        index += delta;
                        if(index > blackKingPosition) {
                            break;
                        }
                        if(index == blackKingPosition) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }
                } else {
                    while(true) {
                        index += delta;
                        if(index < blackKingPosition) {
                            break;
                        }
                        if(index == blackKingPosition) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }

                }
            }
        }

    }

    return false;
}

bool isWhiteKingInCheck() {
    for(int i = 0; i < 128; i++) {
        // skip fake board
        if((i & 0x0f) == 8) {
            i += 7;
            continue;
        }

        // If we found a black piece
        if(board[i] < 0) {
            if (ATTACK_ARRAY[(whiteKingPosition - i + 128)] != 0) {
                // Find the delta
                int delta = DELTA_ARRAY[whiteKingPosition-i+128];
                int index = i;
                int attackIndex = ATTACK_ARRAY[(whiteKingPosition - i + 128)];
                switch (board[i]) {
                    case -1:
                        if(attackIndex != 3) {
                            continue;
                        }
                        break;
                    case -2:
                        if(attackIndex != 1 && attackIndex != 2) {
                            continue;
                        }
                        break;
                    case -3:
                        if(attackIndex != 6) {
                            continue;
                        }
                        break;
                    case -4:
                        if(attackIndex != 4 &&
                                attackIndex != 3 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case -5:
                        if(attackIndex != 1 &&
                                attackIndex != 2 &&
                                attackIndex != 3 &&
                                attackIndex != 4 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case -6:
                        if(attackIndex != 1 &&
                                attackIndex != 3 &&
                                attackIndex != 4) {
                            continue;
                        }
                        break;
                }
                if(delta>0) {
                    while(true) {
                        index += delta;
                        if(index > whiteKingPosition) {
                            break;
                        }
                        if(index == whiteKingPosition) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }
                } else {
                    while(true) {
                        index += delta;
                        if(index < whiteKingPosition) {
                            break;
                        }
                        if(index == whiteKingPosition) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }

                }
            }
        }
    }

    return false;
}

bool isAttackedByBlack(int position) {
    for(int i = 0; i < 128; i++) {
        // skip fake board
        if((i & 0x0f) == 8) {
            i += 7;
            continue;
        }

        // If we found a black piece
        if(board[i] < 0) {
            if (ATTACK_ARRAY[(position - i + 128)] != 0) {
                // Find the delta
                int delta = DELTA_ARRAY[position-i+128];
                int index = i;
                int attackIndex = ATTACK_ARRAY[(position - i + 128)];
                switch (board[i]) {
                    case -1:
                        if(attackIndex != 3) {
                            continue;
                        }
                        break;
                    case -2:
                        if(attackIndex != 1 && attackIndex != 2) {
                            continue;
                        }
                        break;
                    case -3:
                        if(attackIndex != 6) {
                            continue;
                        }
                        break;
                    case -4:
                        if(attackIndex != 4 &&
                                attackIndex != 3 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case -5:
                        if(attackIndex != 1 &&
                                attackIndex != 2 &&
                                attackIndex != 3 &&
                                attackIndex != 4 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case -6:
                        if(attackIndex != 1 &&
                                attackIndex != 3 &&
                                attackIndex != 4) {
                            continue;
                        }
                        break;
                }
                if(delta>0) {
                    while(true) {
                        index += delta;
                        if(index > position) {
                            break;
                        }
                        if(index == position) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }
                } else {
                    while(true) {
                        index += delta;
                        if(index < position) {
                            break;
                        }
                        if(index == position) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }

                }
            }
        }

    }

    return false;
}

bool isAttackedByWhite(int position) {
    for(int i = 0; i < 128; i++) {
        // If we found a white piece
        if(board[i] > 0) {
            if (ATTACK_ARRAY[(position - i + 128)] != 0) {
                // Find the delta
                int delta = DELTA_ARRAY[position-i+128];
                int index = i;
                int attackIndex = ATTACK_ARRAY[(position - i + 128)];
                switch (board[i]) {
                    case 1:
                        if(attackIndex != 4) {
                            continue;
                        }
                        break;
                    case 2:
                        if(attackIndex != 1 && attackIndex != 2) {
                            continue;
                        }
                        break;
                    case 3:
                        if(attackIndex != 6) {
                            continue;
                        }
                        break;
                    case 4:
                        if(attackIndex != 4 &&
                                attackIndex != 3 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case 5:
                        if(attackIndex != 1 &&
                                attackIndex != 2 &&
                                attackIndex != 3 &&
                                attackIndex != 4 &&
                                attackIndex != 5) {
                            continue;
                        }
                        break;
                    case 6:
                        if(attackIndex != 1 &&
                                attackIndex != 3 &&
                                attackIndex != 4) {
                            continue;
                        }
                        break;
                }
                if(delta>0) {
                    while(true) {
                        index += delta;
                        if(index > position) {
                            break;
                        }
                        if(index == position) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }
                } else {
                    while(true) {
                        index += delta;
                        if(index < position) {
                            break;
                        }
                        if(index == position) {
                            return true;
                        }
                        if(board[index] != 0) {
                            break;
                        }
                    }

                }
            }
        }

    }

    return false;
}




short simulateMove(int source, int target) {
    short taken = board[target];
    board[target] = board[source];
    board[source] = 0;
    if(board[target] == -6) {
        blackKingPosition = target;
    } else if(board[target] == 6) {
        whiteKingPosition = target;
    }
    return taken;
}

void undoMove(short taken, int source, int target) {
    board[source] = board[target];
    board[target] = taken;
    if(board[source] == -6) {
        blackKingPosition = source;
    } else if(board[source] == 6) {
        whiteKingPosition = source;
    }
}


private:

    // Delta values
   short knightDeltaValues[8] = {31,-31,33,-33,18,-18,14,-14};
   short kingDeltaValues[8] = {-1,1,-16,16,17,15,-17,-15};
   short rookDeltaValues[4] = {-1,1,16,-16};
   short queenDeltaValues[8] = {-1,1,16,-16,15,-15,17,-17};
   short bishopDeltaValues[4] = {15,-15,17,-17};

   int numWhiteQueen = 1;
   int numWhiteRook = 2;
   int numWhiteKnight = 2;
   int numWhiteBishop = 2;

   int numBlackQueen = 1;
   int numBlackRook = 2;
   int numBlackKnight = 2;
   int numBlackBishop = 2;

   // en passant stuff someday goes here


    // castling stuff
    bool canWhiteKingSideCastle = true;
    bool canWhiteQueenSideCastle = true;

    bool canBlackKingSideCastle = true;
    bool canBlackQueenSideCastle = true;

    /*
        0 - empty space
        negative - black
        positive - white
        1 - pawn
        2 - rook
        3 - knight
        4 - bishop
        5 - queen
        6 - king
     */
    short board[128] = {
            -2,-3,-4,-5,-6,-4,-3,-2,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            -1,-1,-1,-1,-1,-1,-1,-1,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
            2 ,3 ,4 ,5 ,6 ,4 ,3 ,2 ,    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
    };
    /*
    0 - no highlight
    1 - selected square highlight
    2 - possible move highlight
     */

    int ATTACK_NONE = 0;
    int ATTACK_KQR = 1;
    int ATTACK_QR = 2;
    int ATTACK_KQBwP = 4; // i switcted them
    int ATTACK_KQBbP = 3;
    int ATTACK_QB = 5;
    int ATTACK_N = 6;

    int ATTACK_ARRAY[257] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 2, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 1, 4, 6, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 6, 3, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 2, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int DELTA_ARRAY[257] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, -17, 0, 0, 0, 0, 0, 0, -16, 0, 0, 0, 0, 0, 0, -15, 0, 0, -17, 0, 0, 0, 0, 0, -16, 0, 0, 0, 0, 0, -15, 0, 0, 0, 0, -17, 0, 0, 0, 0, -16, 0, 0, 0, 0, -15, 0, 0, 0, 0, 0, 0, -17, 0, 0, 0, -16, 0, 0, 0, -15, 0, 0, 0, 0, 0, 0, 0, 0, -17, 0, 0, -16, 0, 0, -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17, -33, -16, -31, -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -18, -17, -16, -15, -14, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 14, 15, 16, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 16, 33, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 16, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 16, 0, 0, 0, 0, 17, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 17, 0, 0, 15, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int UPDATED_DELTA_ARRAY[257] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 15, 0, 0, 17, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 17, 0, 0, 0, 0, 16, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 16, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 16, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 33, 16, 31, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 17, 16, 15, 14, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, -14, -15, -16, -17, -18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -31, -16, -33, -17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, 0, 0, -16, 0, 0, -17, 0, 0, 0, 0, 0, 0, 0, 0, -15, 0, 0, 0, -16, 0, 0, 0, -17, 0, 0, 0, 0, 0, 0, -15, 0, 0, 0, 0, -16, 0, 0, 0, 0, -17, 0, 0, 0, 0, -15, 0, 0, 0, 0, 0, -16, 0, 0, 0, 0, 0, -17, 0, 0, -15, 0, 0, 0, 0, 0, 0, -16, 0, 0, 0, 0, 0, 0, -17, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    short converter[64] = {
            0,1,2,3,4,5,6,7,
            16,17,18,19,20,21,22,23,
            32,33,34,35,36,37,38,39,
            48,49,50,51,52,53,54,55,
            64,65,66,67,68,69,70,71,
            80,81,82,83,84,85,86,87,
            96,97,98,99,100,101,102,103,
            112,113,114,115,116,117,118,119
    };

    int currentSelectedPosition = -1;
    vector<int> currentPossibleMoves;

    int whiteKingPosition = 116;
    int blackKingPosition = 4;
};
