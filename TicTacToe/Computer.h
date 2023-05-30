#pragma once
//#include "CurrentGame.h"
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
    Computer();
    bool loadMoves(const string& filename);
    //void getRandomMove(CurrentGame& currentGame, int& row, int& col);
    Move getOptionalMove(char board[3][3], int& row, int& col, int level, int rotations);
    Move createMove(int board1[3][3], int board2[3][3]);
private:
    void parseLine(string& line);
    ArrayList<Node*> nodes;
    Move rotateMove(Move old, int rotations);
    bool eqBoards(int board1[3][3], int board2[3][3]);
};