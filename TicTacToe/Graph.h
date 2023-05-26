#pragma once
#include "ArrayList.h"
#include <unordered_map>

const int SIZE = 9;

struct Node
{
	char state[SIZE];
	ArrayList<Node*> children;
	Node() {
		for (int i = 0; i < SIZE; i++) {
			state[i] = ' ';
		}
	}
};

class Graph
{
public:
	void buildGraph(Node* node, char currentPlayer, int depth, unordered_map<string, bool>& memo);
	void printState(const Node* node);
private:
	void addNode(Node* parent, Node* child);
};