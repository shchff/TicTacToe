#pragma once
#include "ArrayList.h"
struct Node {

    int state;

    int board[3][3];

    Node* parant;

    ArrayList<Node*> children;
    
    Node() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = 0;
            }
        }
        state = 0;
        parant = nullptr;
    }
};