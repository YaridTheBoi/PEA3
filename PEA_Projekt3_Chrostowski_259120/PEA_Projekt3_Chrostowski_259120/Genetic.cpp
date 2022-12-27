#include "Genetic.h"
#include "Timer.h"
#include <iostream>
#include <random>
#include <algorithm>
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
	cout << "Mutuje" << endl;
	vector<int> vertexesToSwap;
	for (int i = 0; i < howManyToScramble; i++) {
		vertexesToSwap.push_back(rand()%(chromosome.size()));
	}

	//tutaj spacjalnie nie sprawdzam czy nie zamieniam ze soba tego same wierzcholka. Dzieki temu mutacja bedzie bardziej nieprzewidywalna

	for (int i = 0; i < vertexesToSwap.size(); i++) {
		swap(chromosome[vertexesToSwap[i]], chromosome[vertexesToSwap[rand() % vertexesToSwap.size()]]);
	}
}

void Genetic::solveGenetic(double timeLimit, double crossFactor, double mutationFactor, int startPopulationCount)
{

	srand(time(0));

	if (timeLimit <= 0.0) {
		cout << "Ograniczenie czasowe posiada niepoprawna wartosc" << endl;
		return;
	}
	if (crossFactor <= 0.0) {
		cout << "Wspolczynnik krzyzowania posiada niepoprawna wartosc" << endl;
		return;
	}
	if (mutationFactor <= 0.0) {
		cout << "Wspolczynnik mutacji posiada niepoprawna wartosc" << endl;
		return;
	}
	if (startPopulationCount <= 0.0) {
		cout << "Rozmiar startowej populacji posiada niepoprawna wartosc" << endl;
		return;
	}

	vector<int> chromosome;
	vector<vector<int>> population;

	//stworz startowe miasto
	for (int i = 0; i < this->size; i++) {
		chromosome.push_back(i);
	}

	//stworz startowa populacje
	for (int i = 0; i < startPopulationCount; i++) {
		random_shuffle(chromosome.begin() + 1, chromosome.end() );
		population.push_back(chromosome);
	}

	cout << "przed posortowaniem" << endl;
	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < this->size; j++) {
			cout << population[i][j] << " ";
		}
		cout << "len: " << calculatePathLength(population[i]);
		cout << endl;
	}

	//sortujemy populacje
	sort(population.begin(), population.end(),
		[this](const std::vector<int>& a, const std::vector<int>& b) {
			return calculatePathLength(a) < calculatePathLength(b);
		});


	cout << endl<<"po posortowaniu" << endl;
	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < this->size; j++) {
			cout << population[i][j] << " ";
		}
		cout << "len: " << calculatePathLength(population[i]);
		cout << endl;
	}

	vector<vector<int>> offsprings;


	/*

	//testowe czy sie nie robia nielegalne dzieci

	cout << endl;
	//sortujemy nasza populacje bo zrobimy dobor elitarny
	sort(population.begin(), population.end(),
		[this](const std::vector<int>& a, const std::vector<int>& b) {
			return calculatePathLength(a) < calculatePathLength(b);
		});

	//czyscimy dzieci z poprzedniej iteracji
	offsprings.clear();

	for (int i = 0; i < startPopulationCount - 1; i = i + 2) {

		//rozmnazamy i dodajemy dzieci do zbioru dzieci
		offsprings.push_back(orderCrossover(population[i], population[i + 1]));
		offsprings.push_back(orderCrossover(population[i + 1], population[i]));
	}

	if (startPopulationCount % 2 != 0) {

		//jezeli jest nieparzysta populacja to najgorszego skrzyzuj z przedostatnim
		offsprings.push_back(orderCrossover(population[startPopulationCount - 1], population[startPopulationCount - 2]));
		offsprings.push_back(orderCrossover(population[startPopulationCount - 2], population[startPopulationCount - 1]));
	}


	cout << endl << "dzieci" << endl;
	for (int i = 0; i < offsprings.size(); i++) {
		for (int j = 0; j < this->size; j++) {
			cout << offsprings[i][j] << " ";
		}
		cout << "len: " << calculatePathLength(offsprings[i]);
		cout << endl;
	}
	*/

	Timer timer = Timer();	//do sprawdzania czy minal czas w ktorym mozna sobie operowac
	timer.startCounter();
	while ((timer.getCounter() < timeLimit * 1000)) {

		//cout << endl;
		//sortujemy nasza populacje bo zrobimy dobor elitarny
		sort(population.begin(), population.end(),
			[this](const std::vector<int>& a, const std::vector<int>& b) {
				return calculatePathLength(a) < calculatePathLength(b);
			});

		//czyscimy dzieci z poprzedniej iteracji
		offsprings.clear();

		for (int i = 0; i < startPopulationCount - 1; i = i + 2) {

			//rozmnazamy i dodajemy dzieci do zbioru dzieci
			offsprings.push_back(orderCrossover(population[i], population[i + 1]));
			offsprings.push_back(orderCrossover(population[i+1], population[i]));
		}

		if (startPopulationCount % 2 != 0) {

			//jezeli jest nieparzysta populacja to najgorszego skrzyzuj z przedostatnim
			offsprings.push_back(orderCrossover(population[startPopulationCount-1], population[startPopulationCount-2]));
			offsprings.push_back(orderCrossover(population[startPopulationCount - 2], population[startPopulationCount - 1]));
		}



		//mutacje na dzieci
		for (int i = 0; i < offsprings.size(); i++) {
			if (((float)rand() / RAND_MAX) < mutationFactor) {
				scrambleMutation(offsprings[i], offsprings[i].size() / 3);
			}
		}


		//przemieszaj dzieci zeby przy usuwaniu ich losowe ginely

		random_shuffle(offsprings.begin(), offsprings.end());



		//skasuj tyle dzieci zeby bylo ze ktores sie nie urodzily
		offsprings.resize(offsprings.size() * crossFactor);

		population.resize(population.size() + offsprings.size());
		population.insert(population.end(), offsprings.begin(), offsprings.end());

		sort(population.begin(), population.end(),
			[this](const std::vector<int>& a, const std::vector<int>& b) {
				return calculatePathLength(a) < calculatePathLength(b);
			});


		population.resize(startPopulationCount);

	}

	cout << "Uplynelo " << timer.getCounter()/1000 << " s" << endl;
}


