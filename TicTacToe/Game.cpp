#include "Game.h"

void Game::startGame()
{
    cout << "Добро пожаловать в игру Крестики-нолики!" << endl;
    cout << "Вы играете за 'X'. Выберите уровень сложности:" << endl;
    cout << "1. Легкий" << endl;
    cout << "2. Средний" << endl;
    cout << "3. Тяжелый" << endl;

    int level;
    cin >> level;

    if (level < 1 || level > 3) {
        cout << "Некорректный уровень сложности. Игра завершена." << endl;
        return;
    }

    // Загружаем ходы для компьютера из файла
    /*if (!computer.loadMoves("moves.txt")) {
        cout << "Не удалось загрузить ходы для компьютера. Игра завершена." << endl;
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

    cout << "Игра окончена!" << endl;

    if (isWinner('X')) {
        cout << "Вы победили!" << endl;
    }
    else if (isWinner('O')) {
        cout << "Компьютер победил!" << endl;
    }
    else {
        cout << "Ничья!" << endl;
    }
}

void Game::playerMove()
{
    cout << "Ваш ход. Введите номер строки (1-3) и номер столбца (1-3):" << endl;

    int row, col;
    cin >> row >> col;
    --row;
    --col;

    if (currentGame.isValidMove(row, col)) {
        currentGame.makeMove(row, col, 'X');
    }
    else {
        cout << "Некорректный ход. Попробуйте снова." << endl;
        playerMove();
    }
}

void Game::computerMove(int level)
{
    cout << "Ход компьютера:" << endl;

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
