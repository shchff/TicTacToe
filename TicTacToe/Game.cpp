#include "Game.h"



void Game::startStream()
{
    /*if (!computer.loadMoves("dump.txt")) {
        cout << "Не удалось загрузить ходы для компьютера. Игра завершена." << endl;
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


