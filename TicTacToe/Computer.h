#pragma once
#include "CurrentGame.h"
#include "Move.h"
#include "Node.h"
#include "ArrayList.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Computer 
{
public:
    bool loadMoves(const string& filename);
    void getRandomMove(CurrentGame& currentGame, int& row, int& col);/*
    void getBestMove(CurrentGame& currentGame, int& row, int& col);
    int evaluateMove(const CurrentGame& currentGame, int row, int col);*/
    Move getOptionalMove(CurrentGame& currentGame, int& row, int& col, int level, int rotations);
    Move createMove(int board1[3][3], int board2[3][3]);

private:
    void parseLine(string& line);
    //ArrayList<Move> moves;
    ArrayList<Node*> nodes;
    Move rotateMove(Move old, int rotations);
    bool eqBoards(int board1[3][3], int board2[3][3]);
};