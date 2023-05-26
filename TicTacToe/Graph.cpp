#include "Graph.h"
#include <iostream>
using namespace std;

void Graph::buildGraph(Node* node, char currentPlayer, int depth, unordered_map<string, bool>& memo)
{
    string stateString(node->state, node->state + SIZE);

    if (memo.find(stateString) != memo.end()) {
        return;
    }

    memo[stateString] = true;

    for (int i = 0; i < SIZE; i++) {
        if (node->state[i] == ' ') {
            Node* child = new Node();
            child->state[i] = currentPlayer;
            addNode(node, child);
            bool win = false;
            
            for (int j = 0; j < 3; j++) {
                if (child->state[j * 3] == currentPlayer &&
                    child->state[j * 3 + 1] == currentPlayer &&
                    child->state[j * 3 + 2] == currentPlayer) {
                    win = true;
                    break;
                }
            }
            
            for (int j = 0; j < 3; j++) {
                if (child->state[j] == currentPlayer &&
                    child->state[j + 3] == currentPlayer &&
                    child->state[j + 6] == currentPlayer) {
                    win = true;
                    break;
                }
            }
            
            if ((child->state[0] == currentPlayer &&
                child->state[4] == currentPlayer &&
                child->state[8] == currentPlayer) ||
                (child->state[2] == currentPlayer &&
                    child->state[4] == currentPlayer &&
                    child->state[6] == currentPlayer)) {
                win = true;
            }

            cout << depth << endl;
            if (!win) {
                buildGraph(child, (currentPlayer == 'X') ? 'O' : 'X', depth - 1, memo);
            }
        }
    }
}

void Graph::printState(const Node* node)
{
    cout << "==================" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << node->state[i];
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
    cout << endl;
    for (int i = 0; i < node->children.Length(); i++)
    {
        printState(node->children.Get(i));
    }
}

void Graph::addNode(Node* parent, Node* child) {
    parent->children.Append(child);
}


