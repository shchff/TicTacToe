#include "CurrentGame.h"

CurrentGame::CurrentGame()
{
    // Инициализируем игровое поле пустыми ячейками
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    // Задаем первый ход случайному игроку
    playerTurn = rand() % 2 == 0;
}

void CurrentGame::printBoard()
{
    cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool CurrentGame::isGameOver()
{
    // Проверяем выигрышные комбинации
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return true;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return true;
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return true;
    }

    // Проверяем ничью
    bool isFull = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                isFull = false;
                break;
            }
        }
        if (!isFull) {
            break;
        }
    }
    if (isFull) {
        return true;
    }

    return false;
}

bool CurrentGame::isValidMove(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        return true;
    }
    return false;
}

void CurrentGame::makeMove(int row, int col, char player)
{
    board[row][col] = player;
}

bool CurrentGame::isPlayerTurn()
{
    return playerTurn;
}

void CurrentGame::togglePlayerTurn()
{
    playerTurn = !playerTurn;
}
