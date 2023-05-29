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

    if (level < 1 || level > 3) 
    {
        cout << "Некорректный уровень сложности. Игра завершена." << endl;
        return;
    }

    if (!computer.loadMoves("dump.txt")) {
        cout << "Не удалось загрузить ходы для компьютера. Игра завершена." << endl;
        return;
    }

    bool firstStep = false;
    int howManyRotations = 0;
    int zeroBoard[3][3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            zeroBoard[i][j] = 0;

    currentGame.printBoard();

    while (!currentGame.isGameOver()) 
    {
        if (currentGame.isPlayerTurn()) 
        {
            playerMove();

            if (firstStep == false)
            {
                int intCurrentGameBoard[3][3];
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (currentGame.board[i][j] == 'X')
                        {
                            intCurrentGameBoard[i][j] = 1;
                        }
                        else if (currentGame.board[i][j] == 'O')
                        {
                            intCurrentGameBoard[i][j] = 2;
                        }
                        else
                        {
                            intCurrentGameBoard[i][j] = 0;
                        }
                    }
                }
                      
                Move lastMove = computer.createMove(zeroBoard, intCurrentGameBoard);

                howManyRotations = defineRotations(lastMove);
            }
            firstStep = true;
        }
        else 
        {
            computerMove(level, howManyRotations);
        }
        currentGame.printBoard();
        currentGame.togglePlayerTurn();
    }

    cout << "Игра окончена!" << endl;

    if (isWinner('X')) 
    {
        cout << "Вы победили!" << endl;
    }
    else if (isWinner('O')) 
    {
        cout << "Компьютер победил!" << endl;
    }
    else
    {
        cout << "Ничья!" << endl;
    }
}

void Game::playerMove()
{
    cout << "Ваш ход. Введите номер строки (1-3) и номер столбца (1-3):" << endl;

    int row, col;
    cin >> row >> col;
    row -= 1;
    col -= 1;

    if (currentGame.isValidMove(row, col)) 
    {
        currentGame.makeMove(row, col, 'X');
    }
    else 
    {
        cout << "Некорректный ход. Попробуйте снова." << endl;
        playerMove();
    }
}

void Game::computerMove(int level, int howManyRotations)
{
    cout << "Ход компьютера:" << endl;

    int row = 0, col = 0;

    Move move = computer.getOptionalMove(currentGame, row, col, level, howManyRotations);

    row = move.row;
    col = move.col;

    //computer.getRandomMove(currentGame, row, col);
    currentGame.makeMove(row, col, 'O');
}

bool Game::isWinner(char player)
{
    if (player == 'X')
        return currentGame.isGameOver() && !currentGame.isPlayerTurn();
    else
        return currentGame.isGameOver() && currentGame.isPlayerTurn();
}

int Game::defineRotations(Move move)
{
    if ((move.row == 0 && move.col == 0) || (move.row == 1 && move.col == 1) || (move.row == 0 && move.col == 1))
    {
        return 0;
    }
    else if ((move.row == 0 && move.col == 2) || (move.row == 1 && move.col == 2))
    {
        return 3;
    }
    else if ((move.row == 2 && move.col == 2) || (move.row == 2 && move.col == 1))
    {
        return 2;
    }
    else if ((move.row == 2 && move.col == 0) || (move.row == 1 && move.col == 0))
    {
        return 1;
    }
}
