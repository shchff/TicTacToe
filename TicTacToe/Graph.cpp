#include "Graph.h"

Graph::Graph()
{
    root = new Node();
    root->parant = nullptr;

    Node* corner = new Node();
    corner->board[0][0] = CROSS;
    corner->parant = root;
    add_children(corner, CROSS);

    Node* top = new Node();
    top->board[0][1] = CROSS;
    top->parant = root;
    add_children(top, CROSS);

    Node* center = new Node();
    center->board[1][1] = CROSS;
    center->parant = root;
    add_children(center, CROSS);

    root->children.Append(corner);
    root->children.Append(top);
    root->children.Append(center);
}

Graph::~Graph()
{
    delete root;
}

void Graph::print()
{
    dfsToPrint(root);
}

void Graph::makeDump()
{
    ofstream dumpFile;
    dumpFile.open("dump.txt");

    dfsToWrite(root, dumpFile);

    dumpFile.close();
}

int Graph::check_win(int board[3][3])
{
    for (int i = 0; i < 3; i++) 
    {
        if (((board[i][0] == CROSS) && (board[i][1] == CROSS) && (board[i][2] == CROSS)) || ((board[0][i] == CROSS) && (board[1][i] == CROSS) && (board[2][i] == CROSS)))
        {
            return CROSS;
        }
        else if (((board[i][0] == CIRCLE) && (board[i][1] == CIRCLE) && (board[i][2] == CIRCLE)) || ((board[0][i] == CIRCLE) && (board[1][i] == CIRCLE) && (board[2][i] == CIRCLE)))
        {
            return CIRCLE;
        }
    }
    if (((board[0][0] == CROSS) && (board[1][1] == CROSS) && (board[2][2] == CROSS)) || ((board[0][2] == CROSS) && (board[1][1] == CROSS) && (board[2][0] == CROSS)))
    {
        return CROSS;
    }
    else if (((board[0][0] == CIRCLE) && (board[1][1] == CIRCLE) && (board[2][2] == CIRCLE)) || ((board[0][2] == CIRCLE) && (board[1][1] == CIRCLE) && (board[2][0] == CIRCLE)))
    {
        return CIRCLE;
    }
    bool is_tie = true;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (board[i][j] == 0) 
            {
                is_tie = false;
                break;
            }
        }
        if (!is_tie)
        {
            break;
        }
    }

    if (is_tie) 
    {
        return TIE;
    }

    return GAME;
}

void Graph::add_children(Node* node, int player) 
{
    int result = check_win(node->board);
    if (result != GAME) 
    {
        if (result == CROSS)
        {
            node->state += 1;
            rewriteResults(node);
        }
        else if (result == CIRCLE)
        {
            node->state -= 1;
            rewriteResults(node);
        }
        return; 
    }
    int other_player = (player == CROSS) ? CIRCLE : CROSS;

    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < 3; col++) 
        {
            if (node->board[row][col] == 0) 
            {
                Node* child = new Node();

                for (int k = 0; k < 3; k++) 
                {
                    for (int l = 0; l < 3; l++) 
                    {
                        child->board[k][l] = node->board[k][l];
                    }
                }
                
                child->board[row][col] = player;

                child->parant = node;

                node->children.Append(child);

                add_children(child, other_player);
            }
        }
    }
}

void Graph::dfsToPrint(Node* node)
{
    int result = check_win(node->board);

    if (result != GAME)
    {
        
        /*cout << ++count << " Current board state:\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (node->board[i][j] == CROSS)
                {
                    cout << "X";
                }
                else if (node->board[i][j] == CIRCLE)
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
        cout << endl;*/
        /*cout << ++count << ". ";
        if (result == CROSS)
        {
            cout << "X wins!\n";
        }
        else if (result == CIRCLE)
        {
            cout << "O wins!\n";
        }
        else
        {
            cout << "Tie game.\n";
        }*/
        return;
    }

    int num_children = node->children.Length();
    for (int k = 0; k < num_children; k++) 
    {
        cout << ++count << ". " << node->children[k]->state << "\n";
        /*for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (node->children[k]->board[i][j] == CROSS)
                {
                    cout << "X";
                }
                else if (node->children[k]->board[i][j] == CIRCLE)
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
        cout << endl;*/
        dfsToPrint(node->children[k]);
    }
}

void Graph::dfsToWrite(Node* node, ofstream &fileName)
{
    int result = check_win(node->board);

    if (result != GAME)
    {

        return;
    }

    string line = "";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (node->board[i][j] == CROSS)
                line += "X";
            else if (node->board[i][j] == CIRCLE)
                line += "O";
            else
                line += "*";
        }
    }

    line += "-";

    int num_children = node->children.Length();

    for (int k = 0; k < num_children; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (node->children[k]->board[i][j] == CROSS)
                    line += "X";
                else if (node->children[k]->board[i][j] == CIRCLE)
                    line += "O";
                else
                    line += "*";
            }
        }

        line += ":";
        line += to_string(node->children[k]->state);
        line += ";";


        //dfsToWrite(node->children[k], fileName);
    }

    line += "\n";
    fileName << line;

    for (int k = 0; k < num_children; k++)
    {
        dfsToWrite(node->children[k], fileName);
    }
}

void Graph::rewriteResults(Node* node)
{
    int res = node->state;

    while (node != nullptr)
    {
        node = node->parant;
        if (node != nullptr)
            node->state += res;
    }
}
