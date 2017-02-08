#pragma once

#include <cmath>

using namespace std;

class Move {
private:
    int before;
    int after;
    short board[];

public:

    Move(int before, int after, short board[128]) {
        this->before = before;
        this->after = after;
        this->board = board;
    }

    int getRanking() {
        switch (abs(board[after])) {
            case 1:
                switch (abs(board[before])) {
                    case 6: return 36;
                    case 5: return 35;
                    case 4: return 34;
                    case 3: return 33;
                    case 2: return 32;
                    case 1: return 31;
                }
                break;
            case 2:
                switch (abs(board[before])) {
                    case 6: return 20;
                    case 5: return 29;
                    case 4: return 28;
                    case 3: return 27;
                    case 2: return 26;
                    case 1: return 25;
                }
                break;
            case 3:
                switch (abs(board[before])) {
                    case 6: return 24;
                    case 5: return 23;
                    case 4: return 22;
                    case 3: return 21;
                    case 2: return 20;
                    case 1: return 19;
                }
                break;
            case 4:
                switch (abs(board[before])) {
                    case 6: return 18;
                    case 5: return 17;
                    case 4: return 16;
                    case 3: return 15;
                    case 2: return 14;
                    case 1: return 13;
                }
                break;
            case 5:
                switch (abs(board[before])) {
                    case 6: return 12;
                    case 5: return 11;
                    case 4: return 10;
                    case 3: return 9;
                    case 2: return 8;
                    case 1: return 7;
                }
                break;
            case 6:
                switch (abs(board[before])) {
                    case 6: return 6;
                    case 5: return 5;
                    case 4: return 4;
                    case 3: return 3;
                    case 2: return 2;
                    case 1: return 1;
                }
                break;
            default: return 100;
        }
        return -1;
    }

    int getBefore() {
        return before;
    }

    void setBefore(int before) {
        this->before = before;
    }

    int getAfter() {
        return after;
    }

    void setAfter(int after) {
        this->after = after;
    }
};
