#include <iostream>
#include "GameEngine.h"

using namespace std;

int main(){

    GameEngine ge = GameEngine();
    vector<int> moves = ge.getPossibleMoves(100);
    for (int i = 0; i < moves.size(); i++){
        cout << moves[i] << ",";
    }
    cout << endl;
    return 0;
}
