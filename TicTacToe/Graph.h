#pragma once
#include "Node.h"
#include <fstream>
#include <string>

class Graph
{
public:
    Graph();
    ~Graph();
    void print();
    void makeDump();
private:
    int check_win(int board[3][3]);
    void add_children(Node* node, int player);
    void dfsToPrint(Node* node);
    void dfsToWrite(Node* node, ofstream &fileName);
    void rewriteResults(Node* startnode);
    Node* root;

    const int GAME = 0;
    const int CROSS = 1;
    const int CIRCLE = 2;
    const int TIE = 3;

    int count = 0;
};