#include "Game.h"



void Game::startStream()
{
    /*if (!computer.loadMoves("dump.txt")) {
        cout << "�� ������� ��������� ���� ��� ����������. ���� ���������." << endl;
        return;
    }*/
    string line = "";
    while (true)
    {
        cin >> line;
        if (line == "game")
        {
            CurrentGame currentGame;
            currentGame.startGame();
        }
        else if (line == "exit")
        {
            break;
        }
    }
}


