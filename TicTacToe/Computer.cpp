#include "Computer.h"

Computer::Computer()
{
}

bool Computer::loadMoves(const string& fileName)
{
    cout << "Загрузка графа" << endl;

    ifstream file(fileName);
    string line = "";

    while (file >> line)
    {
        parseLine(line);
    }

    file.close();

    cout << "Граф загружен!" << endl;

    return true;
}

void Computer::parseLine(string& line)
{
    Node* currNode = new Node;

    string strBoard = line.substr(0, line.find("-"));

    line.erase(0, 10);

    int countBoard = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (strBoard[countBoard] == 'X')
                currNode->board[i][j] = 1;
            else if (strBoard[countBoard] == 'O')
                currNode->board[i][j] = 2;
            else
                currNode->board[i][j] = 0;
            countBoard++;
        }
    }

    while (true)
    {
        Node* child = new Node;

        child->parant = currNode;

        string childStr = line.substr(0, line.find(";"));

        string childStrBoard = childStr.substr(0, childStr.find(":"));

        childStr.erase(0, 10);

        int countChildBoard = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {

                if (childStrBoard[countChildBoard] == 'X')
                    child->board[i][j] = 1;
                else if (childStrBoard[countChildBoard] == 'O')
                    child->board[i][j] = 2;
                else
                    child->board[i][j] = 0;

                countChildBoard++;
            }
        }

        child->state = stoi(childStr.substr(0, childStr.length()));


        line.erase(0, line.find(";") + 1);


        currNode->children.Append(child);

        if ((line.find(";") < 0) || (line.find(";") > line.size()))
            break;
    }

    nodes.Append(currNode);
}

Move Computer::rotateMove(Move oldMove, int rotations)
{
    Move newMove = oldMove;
    for (int i = 0; i < rotations; i++)
    {

    }
    return newMove;
}

Move Computer::createMove(int board1[3][3], int board2[3][3])
{
    Move move;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board1[i][j] != board2[i][j])
            {
                move = { i, j };
            }
        }
    }

    return move;
}

bool Computer::eqBoards(int board1[3][3], int board2[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int one = board1[i][j];
            int two = board2[i][j];
            if (one != two)
            {
                return false;
            }
        }
    }
    return true;
}

Move Computer::getOptionalMove(char board[3][3], int& row, int& col, int level, int rotations)
{
    ArrayList<Move> availableMoves;
    ArrayList<int> states;

    int currGameBoard[3][3] = { 0 };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                currGameBoard[i][j] = 1;
            }
            else if (board[i][j] == 'O')
            {
                currGameBoard[i][j] = 2;
            }
            else
            {
                currGameBoard[i][j] = 0;
            }
        }
    }

    if (rotations == 1)
    {
        int temp[3][3] = { 0 };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[j][2 - i] = currGameBoard[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                currGameBoard[i][j] = temp[i][j];
            }
        }
    }
    else if (rotations == 2)
    {
        int temp[3][3] = { 0 };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[2 - i][2 - j] = currGameBoard[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                currGameBoard[i][j] = temp[i][j];
            }
        }
    }
    else if (rotations == 3)
    {
        int temp[3][3] = { 0 };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
            {
                temp[2 - j][i] = currGameBoard[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                currGameBoard[i][j] = temp[i][j];
            }
        }
    }

    for (int i = 0; i < nodes.Length(); i++)
    {
        Node* nodeItem = nodes[i];

        if (eqBoards(nodeItem->board, currGameBoard))
        {
            for (int j = 0; j < nodeItem->children.Length(); j++)
            {
                Move move = createMove(currGameBoard, nodeItem->children[j]->board);
                availableMoves.Append(move);
                states.Append(nodeItem->children[j]->state);
            }
            break;
        }
    }

    if (level == 1)
    {
        int idx = 0;
        for (int i = 0; i < states.Length(); i++)
        {
            if (states[i] > states[idx])
                idx = i;
        }
        row = availableMoves[idx].row;
        col = availableMoves[idx].col;
        
    }
    else if (level == 2)
    {

        int sum = 0;

        for (int i = 0; i < states.Length(); i++)
        {
            sum += states[i];
        }

        double average = double(sum) / states.Length();


        int idx = 0;
        double minDiff = abs(states[0] - average);

        for (int i = 0; i < states.Length(); i++)
        {
            if (abs(states[i] - average) < minDiff)
            {
                idx = i;
                minDiff = abs(states[i] - average);
            }
        }
        
        row = availableMoves[idx].row;
        col = availableMoves[idx].col;

    }
    else if (level == 3)
    {
        int idx = 0;
        for (int i = 0; i < states.Length(); i++)
        {
            if (states[i] < states[idx])
                idx = i;
        }
        row = availableMoves[idx].row;
        col = availableMoves[idx].col;
    }

    int boardToBack[3][3] = { 0 };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            boardToBack[i][j] = currGameBoard[i][j];
        }
    }

    boardToBack[row][col] = 2;
    
    if (rotations == 3)
    {
        int temp[3][3] = { 0 };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[j][2 - i] = boardToBack[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                boardToBack[i][j] = temp[i][j];
            }
        }
    }
    else if (rotations == 2)
    {
        int temp[3][3] = { 0 };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[2 - i][2 - j] = boardToBack[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                boardToBack[i][j] = temp[i][j];
            }
        }
    }
    else if (rotations == 1)
    {
        int temp[3][3] = { 0 };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
            {
                temp[2 - j][i] = boardToBack[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                boardToBack[i][j] = temp[i][j];
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                currGameBoard[i][j] = 1;
            }
            else if (board[i][j] == 'O')
            {
                currGameBoard[i][j] = 2;
            }
            else
            {
                currGameBoard[i][j] = 0;
            }
        }
    }

    return createMove(currGameBoard, boardToBack);
}