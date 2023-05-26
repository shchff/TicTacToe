#include "Game.h"

void Game::startGame()
{
    cout << "����� ���������� � ���� ��������-������!" << endl;
    cout << "�� ������� �� 'X'. �������� ������� ���������:" << endl;
    cout << "1. ������" << endl;
    cout << "2. �������" << endl;
    cout << "3. �������" << endl;

    int level;
    cin >> level;

    if (level < 1 || level > 3) {
        cout << "������������ ������� ���������. ���� ���������." << endl;
        return;
    }

    // ��������� ���� ��� ���������� �� �����
    /*if (!computer.loadMoves("moves.txt")) {
        cout << "�� ������� ��������� ���� ��� ����������. ���� ���������." << endl;
        return;
    }*/

    currentGame.printBoard();

    while (!currentGame.isGameOver()) {
        if (currentGame.isPlayerTurn()) {
            playerMove();
        }
        else {
            computerMove(level);
        }
        currentGame.printBoard();
        currentGame.togglePlayerTurn();
    }

    cout << "���� ��������!" << endl;

    if (isWinner('X')) {
        cout << "�� ��������!" << endl;
    }
    else if (isWinner('O')) {
        cout << "��������� �������!" << endl;
    }
    else {
        cout << "�����!" << endl;
    }
}

void Game::playerMove()
{
    cout << "��� ���. ������� ����� ������ (1-3) � ����� ������� (1-3):" << endl;

    int row, col;
    cin >> row >> col;
    --row;
    --col;

    if (currentGame.isValidMove(row, col)) {
        currentGame.makeMove(row, col, 'X');
    }
    else {
        cout << "������������ ���. ���������� �����." << endl;
        playerMove();
    }
}

void Game::computerMove(int level)
{
    cout << "��� ����������:" << endl;

    int row = 0, col = 0;

    if (level == 1) {
        computer.getRandomMove(currentGame, row, col);
    }
    else if (level == 2) {
        computer.getBestMove(currentGame, row, col);
    }
    else if (level == 3) {
        computer.getOptimalMove(currentGame, row, col);
    }

    currentGame.makeMove(row, col, 'O');
}

bool Game::isWinner(char player)
{
    if (player == 'X')
        return currentGame.isGameOver() && currentGame.isPlayerTurn();
    else
        return currentGame.isGameOver() && !currentGame.isPlayerTurn();
}
