
#include <vector>
#include "Graph.h"
#pragma once

class Genetic:public Graph {
	
public:
	Genetic() = default;

	Genetic(Graph);

	vector<int> orderCrossover(vector<int>, vector<int>);

	void scrambleMutation(vector<int>&, int);

	void inverseMutation(vector<int>&);

	void solveGenetic(double, double, double, int, bool);

	void solveGeneticTest(double, double, double, int, bool, int ,ofstream&);

};