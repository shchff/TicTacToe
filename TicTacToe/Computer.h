#pragma once
#include "CurrentGame.h"
#include "Move.h"
#include "ArrayList.h"
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

class Computer {
public:
    bool loadMoves(const string& filename);
    void getRandomMove(CurrentGame& currentGame, int& row, int& col);
    void getBestMove(CurrentGame& currentGame, int& row, int& col);
    int evaluateMove(const CurrentGame& currentGame, int row, int col);
    void getOptimalMove(CurrentGame& currentGame, int& row, int& col);
private:
    ArrayList<Move> moves;
};