#include <iostream>
#include "Game.h"
#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
    srand(time(0));
	/*Game newGame;
	newGame.startGame();*/
    Node* root = new Node(); // Создание корневого узла
    Graph graph;
    unordered_map<string, bool> memo; // Хэш-таблица для хранения уже посещенных состояний
    int maxDepth = 9; // Максимальная глубина рекурсии
    graph.buildGraph(root, 'X', maxDepth, memo); // Заполнение графа

    // Вывод всех игр из графа
    cout << "Все возможные игры в крестики-нолики:" << endl;

    for (int i = 0; i < root->children.Length(); i++) {
        Node* child = root->children[i];
        cout << "____________" << endl;
        graph.printState(child);
    }

	return 0;
}