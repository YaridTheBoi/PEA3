#include "Genetic.h"
#include <iostream>
using namespace std;
Genetic::Genetic(Graph original)
{
	this->grid = original.grid;
	this->size = original.size;
}

vector<int> Genetic::orderCrossover(vector<int> parent1, vector<int> parent2)
{
	srand(time(0));
	vector<int> child;
	int parentSize = parent1.size();
	child.resize(parentSize);
	int segmentStart= rand() % (parentSize+1-parentSize/2);
	int segmentEnd = segmentStart -1 + parentSize / 2;
	//cout << "start " << segmentStart << " end " << segmentEnd << endl;

	for (int i = segmentStart; i <= segmentEnd; i++) {
		child[i] = parent1[i];
	}

	int parentIterator = (segmentEnd + 1) % parentSize;;
	int childIterator = (segmentEnd + 1) % parentSize;;
	int vertexToCopy = parentSize - parentSize / 2;
	bool shouldGo = true;
	//cout << endl << vertexToCopy << endl;
	
	while (vertexToCopy > 0)
	{

		for (int i = segmentStart; i <= segmentEnd; i++) {
			if (parent2[parentIterator] == parent1[i])
			{
				shouldGo = false; 
				break;
			}
		}
		if (shouldGo) {		//przepisujemy z rodzica 2
			child[childIterator] = parent2[parentIterator];
			parentIterator = (parentIterator + 1) % parentSize;
			childIterator = (childIterator + 1) % parentSize;
			vertexToCopy--;
		}
		else {				//trzeba przesunac rodzica 2
			shouldGo = true;
			parentIterator = (parentIterator + 1) % parentSize;
		}
	}
	/*
	cout << "start " << segmentStart << " end " << segmentEnd << endl;
	for (int i = 0; i < child.size(); i++) {
		cout << child[i]<< " ";
	}


	*/
	return child;

}

void Genetic::scrambleMutation(vector<int>&chromosome, int howManyToScramble )
{
	vector<int> vertexesToSwap;
	for (int i = 0; i < howManyToScramble; i++) {
		vertexesToSwap.push_back(rand()%(chromosome.size()));
	}

	//tutaj spacjalnie nie sprawdzam czy nie zamieniam ze soba tego same wierzcholka. Dzieki temu mutacja bedzie bardziej nieprzewidywalna

	for (int i = 0; i < vertexesToSwap.size(); i++) {
		swap(chromosome[vertexesToSwap[i]], chromosome[vertexesToSwap[rand() % vertexesToSwap.size()]]);
	}
}

void Genetic::solveGenetic(double, double, double, int)
{
}
