#pragma once
#include "CurrentGame.h"
#include "Computer.h"
#include <iostream>
using namespace std;

class Game 
{
public:
    void startGame();
    void playerMove();
    void computerMove(int level, int howManyRotations);
    bool isWinner(char player);
private:
    CurrentGame currentGame;
    Computer computer;
    int defineRotations(Move move);
};