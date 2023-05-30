#pragma once

#include <iostream>
#include "Move.h"
#include "Computer.h"

using namespace std;

class CurrentGame 
{
public:
    CurrentGame();
    void startGame();
    
private:
    char board[3][3];
    bool playerTurn;
    void playerMove();
    void computerMove(int level, int howManyRotations);
    bool isWinner(char player);
    void printBoard();
    bool isGameOver();
    bool isValidMove(int row, int col);
    void makeMove(int row, int col, char player);
    bool isPlayerTurn();
    void togglePlayerTurn();
    int defineRotations(Move move);
    Computer computer;
};