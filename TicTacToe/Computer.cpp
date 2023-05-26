#include "Computer.h"

bool Computer::loadMoves(const string& filename)
{
    ifstream file(filename);

    if (!file) {
        return false;
    }

    int row, col;
    while (file >> row >> col) {
        Move move = { row, col };
        moves.Append(move);
    }

    file.close();
    return true;
}

void Computer::getRandomMove(CurrentGame& currentGame, int& row, int& col)
{
    ArrayList<Move> availableMoves;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (currentGame.isValidMove(i, j)) {
                Move move = { i, j };
                availableMoves.Append(move);
            }
        }
    }

    int randomIndex = rand() % availableMoves.Length();
    row = availableMoves[randomIndex].row;
    col = availableMoves[randomIndex].col;
}

void Computer::getBestMove(CurrentGame& currentGame, int& row, int& col)
{
    ArrayList<Move> availableMoves;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (currentGame.isValidMove(i, j)) {
                Move move = { i, j };
                availableMoves.Append(move);
            }
        }
    }

    int bestScore = INT_MIN;
    int bestIndex = -1;

    for (int i = 0; i < availableMoves.Length(); ++i) {
        int moveScore = evaluateMove(currentGame, availableMoves[i].row, availableMoves[i].col);
        if (moveScore > bestScore) {
            bestScore = moveScore;
            bestIndex = i;
        }
    }

    row = availableMoves[bestIndex].row;
    col = availableMoves[bestIndex].col;
}

int Computer::evaluateMove(const CurrentGame& currentGame, int row, int col)
{
    CurrentGame copyGame = currentGame;
    copyGame.makeMove(row, col, 'O');

    if (copyGame.isGameOver() && !copyGame.isPlayerTurn()) {
        return 10; // Выигрышный ход
    }
    else if (copyGame.isGameOver() && copyGame.isPlayerTurn()) {
        return -10; // Проигрышный ход
    }
    else {
        return 0; // Ничья или игра продолжается
    }
}

void Computer::getOptimalMove(CurrentGame& currentGame, int& row, int& col)
{
    for (int i = 0; i < moves.Length(); i++) {
        int moveRow = moves.Get(i).row;
        int moveCol = moves.Get(i).col;
        if (currentGame.isValidMove(moveRow, moveCol)) {
            row = moveRow;
            col = moveCol;
            return;
        }
    }

    getRandomMove(currentGame, row, col);
}