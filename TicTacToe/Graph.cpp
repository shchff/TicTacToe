#include "Graph.h"

Graph::Graph()
{
    root = new Node();
    add_children(root, CROSS);
}

Graph::~Graph()
{
    delete root;
}

void Graph::print()
{
    dfs(root, 0);
}

int Graph::check_win(int board[3][3])
{
    // Проверяем по строкам и столбцам
    for (int i = 0; i < 3; i++) 
    {
        int row_sum = 0;
        int col_sum = 0;
        for (int j = 0; j < 3; j++) 
        {
            row_sum += board[i][j];
            col_sum += board[j][i];
        }
        if (row_sum == CROSS * 3 || col_sum == CROSS * 3) 
        {
            return CROSS;
        }
        else if (row_sum == CIRCLE * 3 || col_sum == CIRCLE * 3) 
        {
            return CIRCLE;
        }
    }
    // Проверяем по диагоналям
    if ((board[0][0] + board[1][1] + board[2][2] == CROSS * 3) || (board[0][2] + board[1][1] + board[2][0] == CROSS * 3)) 
    {
        return CROSS;
    }
    else if ((board[0][0] + board[1][1] + board[2][2] == CIRCLE * 3) || (board[0][2] + board[1][1] + board[2][0] == CIRCLE * 3)) 
    {
        return CIRCLE;
    }
    // Проверяем на ничью
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
    }

    if (is_tie) {
        return TIE;
    }

    return GAME;
}

void Graph::add_children(Node* node, int player) 
{
    int result = check_win(node->board);
    if (result != 0) 
    {
        return; // Игра закончена, ничего больше не делаем
    }
    int other_player = (player == CROSS) ? CIRCLE : CROSS;

    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < 3; col++) 
        {
            if (node->board[row][col] == 0) 
            {
                // Делаем ход
                //node->board[row][col] = player;

                // Создаем дочерний узел и добавляем его в вектор дочерних узлов родительского узла
                Node* child = new Node();
                for (int k = 0; k < 3; k++) 
                {
                    for (int l = 0; l < 3; l++) 
                    {
                        child->board[k][l] = node->board[k][l];
                    }
                }
                
                child->board[row][col] = player;

                node->children.Append(child);

                // Добавляем дочерние узлы для другого игрока
                add_children(child, other_player);

                // Отменяем ход
                /*node->board[row][col] = 0;*/
            }
        }
    }
}

void Graph::dfs(Node* node, int depth)
{
    int result = check_win(node->board);
    if (result != GAME) {
        // Игра закончена
        cout << string(depth, '-') << " ";
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
        }
        return;
    }

    cout << string(depth, '-') << " Current board state:\n";
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
    cout << endl;

    int num_children = node->children.Length();
    for (int i = 0; i < num_children; i++) 
    {
        dfs(node->children[i], depth + 1);
    }
}
