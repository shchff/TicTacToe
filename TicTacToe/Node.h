#pragma once
#include "ArrayList.h"
struct Node {
    int board[3][3];
    ArrayList<Node*> children;

    Node() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = 0;
            }
        }
    }
};