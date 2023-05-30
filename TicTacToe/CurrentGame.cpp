#include "CurrentGame.h"

CurrentGame::CurrentGame()
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            board[i][j] = ' ';
        }
    }

    this->computer.loadMoves("dump.txt");
    this->playerTurn = true;
}

void CurrentGame::printBoard()
{
    /*cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) 
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " | ";
        }

        //cout << endl;

        cout << endl;
        cout << "+---+---+---+" << endl;

    }
}

bool CurrentGame::isGameOver()
{
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) 
        {
            return true;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) 
        {
            return true;
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return true;
    }

    bool isFull = true;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (board[i][j] == ' ')
            {
                isFull = false;
                break;
            }
        }
        if (!isFull) 
        {
            break;
        }
    }
    if (isFull) 
    {
        return true;
    }

    return false;
}

bool CurrentGame::isValidMove(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') 
    {
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



void CurrentGame::startGame()
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


    bool firstStep = false;
    int howManyRotations = 0;
    int zeroBoard[3][3] = { 0 };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            zeroBoard[i][j] = 0;

    printBoard();

    while (!isGameOver())
    {
        if (isPlayerTurn())
        {
            playerMove();

            if (firstStep == false)
            {
                int intCurrentGameBoard[3][3] = { 0 };
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == 'X')
                        {
                            intCurrentGameBoard[i][j] = 1;
                        }
                        else if (board[i][j] == 'O')
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
        printBoard();
        togglePlayerTurn();
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

void CurrentGame::playerMove()
{
    cout << "Ваш ход. Введите номер строки (1-3) и номер столбца (1-3):" << endl;

    int row, col;
    cin >> row >> col;
    row -= 1;
    col -= 1;

    if (isValidMove(row, col))
    {
        makeMove(row, col, 'X');
    }
    else
    {
        cout << "Некорректный ход. Попробуйте снова." << endl;
        playerMove();
    }
}

void CurrentGame::computerMove(int level, int howManyRotations)
{
    cout << "Ход компьютера:" << endl;

    int row = 0, col = 0;

    Move move = computer.getOptionalMove(board, row, col, level, howManyRotations);

    row = move.row;
    col = move.col;

    makeMove(row, col, 'O');
}

bool CurrentGame::isWinner(char player)
{
    if (player == 'X')
        return isGameOver() && !isPlayerTurn();
    else
        return isGameOver() && isPlayerTurn();
}


int CurrentGame::defineRotations(Move move)
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
    return -1;
}