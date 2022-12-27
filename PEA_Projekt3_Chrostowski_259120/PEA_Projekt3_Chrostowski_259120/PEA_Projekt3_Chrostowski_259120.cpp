﻿#include <iostream>
#include "Menu.h"

//PONIZEJ SA RZECZY DO TESTOW WIEC DO WYWLENIA
#include "Genetic.h"
#include <vector>

using namespace std;
int main()
{
    //Menu m = Menu();
    //m.printStartMenu();

    Graph g = Graph();
    g.readFromFile("data5.txt");
    Genetic gen = Genetic(g);
    gen.printGraph();

    gen.solveGenetic(10, 0.8, 0.01, 9);

    /*
    vector<int> p1 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> p2 = {7, 4, 2, 1, 6, 3, 5};

    vector <int>child= g.orderCrossover(p1, p2);

    for (int i = 0; i < child.size(); i++) {
        cout << child[i] << " ";
    }

    g.scrambleMutation(child, 3);
    cout << endl;
    for (int i = 0; i < child.size(); i++) {
        cout << child[i] << " ";
    }
    */
}

