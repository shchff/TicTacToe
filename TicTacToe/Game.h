#pragma once
#include "CurrentGame.h"
#include "Computer.h"
#include <iostream>
using namespace std;

class Game {
public:
    void startGame();
    void playerMove();
    void computerMove(int level);
    bool isWinner(char player);
private:
    CurrentGame currentGame;
    Computer computer;
};