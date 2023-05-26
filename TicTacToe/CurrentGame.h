#pragma once

#include <iostream>

using namespace std;

class CurrentGame {
public:
    CurrentGame();
    void printBoard();
    bool isGameOver();
    bool isValidMove(int row, int col);
    void makeMove(int row, int col, char player);
    bool isPlayerTurn();
    void togglePlayerTurn();
private:
    char board[3][3];
    bool playerTurn;
};