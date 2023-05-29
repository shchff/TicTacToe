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

    if (level < 1 || level > 3) 
    {
        cout << "������������ ������� ���������. ���� ���������." << endl;
        return;
    }

    if (!computer.loadMoves("dump.txt")) {
        cout << "�� ������� ��������� ���� ��� ����������. ���� ���������." << endl;
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

    cout << "���� ��������!" << endl;

    if (isWinner('X')) 
    {
        cout << "�� ��������!" << endl;
    }
    else if (isWinner('O')) 
    {
        cout << "��������� �������!" << endl;
    }
    else
    {
        cout << "�����!" << endl;
    }
}

void Game::playerMove()
{
    cout << "��� ���. ������� ����� ������ (1-3) � ����� ������� (1-3):" << endl;

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
        cout << "������������ ���. ���������� �����." << endl;
        playerMove();
    }
}

void Game::computerMove(int level, int howManyRotations)
{
    cout << "��� ����������:" << endl;

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
