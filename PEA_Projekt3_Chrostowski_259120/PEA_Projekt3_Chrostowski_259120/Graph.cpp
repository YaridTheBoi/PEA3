#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>  
#include <stdio.h>
#include <sstream>
#include <random>
#include<vector>

using namespace std;

Graph::Graph()
{
	this->size = 0;
	grid.resize(0, vector<int>(0));
}


void Graph::clearGraph()
{
	if (this->size == 0) {
		return;
	}
	this->size = 0;
	grid.clear();
	grid.resize(0);

}

void Graph::readFromFile(string fileName)
{
	ifstream file;
	vector<int> tab;
	tab.resize(1);
	file.open(fileName.c_str());
	if (file.is_open())
	{
		if (readLineFromFile(file, tab, 1))
		{
			this->scaleForRead(tab[0]);

			for (int i = 0; i < this->size; i++)
				if (!readLineFromFile(file, grid[i], size))
				{
					cout << "File error - NIEPOPRAWNY FORMAT DANYCH" << endl;
					clearGraph();
					this->size = 0;
					break;
				}
		}
		else {
			cout << "File error - NIE MA INFORMACJI O ROZMIARZE" << endl;
		}

		file.close();
	}
	else
	{
		cout << "File error - NIE MOZNA OTWORZYC PLIKU" << endl;
	}

}

bool Graph::readLineFromFile(ifstream& file, vector<int>& dest, int size)
{
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	istringstream in_ss(s);
	int num;
	for (int i = 0; i < size; i++)
	{
		in_ss >> num;
		dest.at(i) = num;
		if (in_ss.fail()) {
			return(false);
		}

	}
	return(true);
}



void Graph::printGraph()
{
	if (this->size == 0) {
		cout << endl << "BRAK GRAFU " << endl;
		return;
	}
	cout << "Wydruk grafu";
	cout << endl;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			printf("%6d ", this->grid[i][j]);
		}
		cout << endl;
	}


}


void Graph::scaleForRead(int amountOfCities)
{
	if (this->size != 0) {
		this->clearGraph();
	}
	this->size = amountOfCities;
	this->grid.resize(amountOfCities, vector<int>(amountOfCities));

}

void Graph::generateRandomGraph(int citiesAmount)
{
	srand(time(0));
	this->size = citiesAmount;
	this->grid.resize(citiesAmount, vector<int>(citiesAmount));
	for (int i = 0; i < citiesAmount; i++) {
		for (int j = 0; j < citiesAmount; j++) {
			if (i == j) {
				this->grid[i][j] = 0;
			}
			else {
				this->grid[i][j] = 1 + rand() % 20;
			}
		}
	}
}

int Graph::calculatePathLength(vector<int> path)
{
	int sum = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		sum += this->grid[path.at(i)][path.at(i + 1)];
	}
	return sum;
}

void Graph::makeNeighbour(vector<int>& path, int swapStart, int swapEnd)
{
	int swapper = path.at(swapStart);
	path.at(swapStart) = path.at(swapEnd);
	path.at(swapEnd) = swapper;
}