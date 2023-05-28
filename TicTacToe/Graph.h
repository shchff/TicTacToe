#pragma once
#include "Node.h"

class Graph
{
public:
    Graph();
    ~Graph();
    void print();
private:
    int check_win(int board[3][3]);
    void add_children(Node* node, int player);
    void dfs(Node* node, int depth);
    Node* root;

    const int GAME = 0;
    const int CROSS = 1;
    const int CIRCLE = 2;
    const int TIE = 3;
};