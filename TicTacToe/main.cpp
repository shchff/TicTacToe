#include <iostream>
#include "Game.h"
#include "Graph.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    //srand(time(0));

    Game newGame;
    newGame.startGame();

    //Graph G;
    ////G.print();
    //G.makeDump();

    /*string line = "XXOX*XO**-XXOXOXO**:-1;XXOX*XOO*:0;XXOX*XO*O:0;";

    string strBoard = line.substr(0, line.find("-"));

    line.erase(0, 10);

    int countBoard = 0;

    char board[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = strBoard[countBoard];
            countBoard++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                cout << "X";
            }
            else if (board[i][j] == 'O')
            {
                cout << "O";
            }
            else
            {
                cout << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << strBoard << endl;
    cout << line << endl;*/

    return 0;
}