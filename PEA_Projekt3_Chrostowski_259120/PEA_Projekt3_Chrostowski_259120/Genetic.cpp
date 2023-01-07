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
	srand(time(NULL));
	//cout << "Mutuje" << endl;
	vector<int> vertexesToSwap;
	for (int i = 0; i < howManyToScramble; i++) {
		vertexesToSwap.push_back(rand()%(chromosome.size()));
	}

	//tutaj spacjalnie nie sprawdzam czy nie zamieniam ze soba tego same wierzcholka. Dzieki temu mutacja bedzie bardziej nieprzewidywalna

	for (int i = 0; i < vertexesToSwap.size(); i++) {
		swap(chromosome[vertexesToSwap[i]], chromosome[vertexesToSwap[rand() % vertexesToSwap.size()]]);
	}
}

void Genetic::inverseMutation(vector<int>& chromosome)
{
	srand(time(NULL));
	int startIndex = rand() % chromosome.size();
	int endIndex = rand() % chromosome.size();

	if (startIndex > endIndex) {
		swap(startIndex, endIndex);
	}
	reverse(chromosome.begin() + startIndex, chromosome.begin() + endIndex);
}

void Genetic::solveGenetic(double timeLimit, double crossFactor, double mutationFactor, int startPopulationCount, bool useScramble)
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

	//sortujemy populacje
	sort(population.begin(), population.end(),
		[this](const vector<int>& a, const vector<int>& b) {
			return calculatePathLength(a) < calculatePathLength(b);
		});

	vector<vector<int>> offsprings;

	


	if (startPopulationCount % 2 == 0) {
		offsprings.resize(startPopulationCount);
	}
	else {
		offsprings.resize(startPopulationCount + 2);
	}

	int offspringsSize = offsprings.size();

	Timer timer = Timer();	//do sprawdzania czy minal czas w ktorym mozna sobie operowac
	timer.startCounter();
	while ((timer.getCounter() < timeLimit * 1000)) {


		//czyscimy dzieci z poprzedniej iteracji
		//offsprings.clear();



		for (int i = 0; i < startPopulationCount - 1; i = i + 2) {

			//rozmnazamy i dodajemy dzieci do zbioru dzieci
			offsprings[i] = orderCrossover(population[i], population[i + 1]);
			offsprings[i + 1] = orderCrossover(population[i + 1], population[i]);
			//offsprings.push_back(orderCrossover(population[i], population[i + 1]));
			//offsprings.push_back(orderCrossover(population[i + 1], population[i]));
		}

		if (startPopulationCount % 2 != 0) {

			//jezeli jest nieparzysta populacja to najgorszego skrzyzuj z przedostatnim
			offsprings[offspringsSize-1]=(orderCrossover(population[startPopulationCount - 1], population[startPopulationCount - 2]));
			offsprings[offspringsSize - 2] = (orderCrossover(population[startPopulationCount - 2], population[startPopulationCount - 1]));
		}
		

		//mutacje na dzieci
		for (int i = 0; i < offspringsSize; i++) {
			if (((float)rand() / RAND_MAX) < mutationFactor) {

				if (useScramble) {
					scrambleMutation(offsprings[i], offsprings[i].size() / 3);
				}
				else {
					inverseMutation(offsprings[i]);
				}
				
			}
		}


		//przemieszaj dzieci zeby przy usuwaniu ich losowe ginely to chyba bardzo spowalnia
		//random_shuffle(offsprings.begin(), offsprings.end());
		
		//skasuj tyle dzieci zeby bylo ze ktores sie nie urodzily
		//offsprings.resize((int)(offspringsSize * crossFactor));

		population.resize(startPopulationCount +(int) (offspringsSize * crossFactor));
		for (int i = 0; i < (int)(offspringsSize * crossFactor); i++) {
			population[startPopulationCount + i] = offsprings[i];
		}


		//posortuj populacje
		sort(population.begin(), population.end(),
			[this](const vector<int>& a, const vector<int>& b) {
				return calculatePathLength(a) < calculatePathLength(b);
			});

		//zostaw tylko najlepsze osobniki
		population.resize(startPopulationCount);

	}

	cout << "Uplynelo " << timer.getCounter()/1000 << " s" << endl;



	cout << endl << "Najlepsza znaleziona trasa to: " << endl;
	
	for (int j = 0; j < this->size; j++) {
		cout << population[0][j] << "-";
	}
	cout << population[0][0]<<endl;
	cout << "Dlugosc znalezionej trasy: " << calculatePathLength(population[0])<<endl;
	
	


}

void Genetic::solveGeneticTest(double timeLimit, double crossFactor, double mutationFactor, int startPopulationCount, bool useScramble, int interval, ofstream& file)
{
	srand(time(0));

	if (timeLimit <= 0.0) {
		
		return;
	}
	if (crossFactor <= 0.0) {
	
		return;
	}
	if (mutationFactor <= 0.0) {

		return;
	}
	if (startPopulationCount <= 0.0) {
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
		random_shuffle(chromosome.begin() + 1, chromosome.end());
		population.push_back(chromosome);
	}

	//sortujemy populacje
	sort(population.begin(), population.end(),
		[this](const vector<int>& a, const vector<int>& b) {
			return calculatePathLength(a) < calculatePathLength(b);
		});

	vector<vector<int>> offsprings;


	if (startPopulationCount % 2 == 0) {
		offsprings.resize(startPopulationCount);
	}
	else {
		offsprings.resize(startPopulationCount + 2);
	}

	int offspringsSize = offsprings.size();

	// okresla w jakiej probce juz pobralismy pomiar(kilka iteracji moglo dac tkai sam czas przez zaokraglenia)
	int timeStamp = 0;

	//przed zaczeciem algorytmu
	file << calculatePathLength(population[0]) << "\t";

	Timer timer = Timer();	//do sprawdzania czy minal czas w ktorym mozna sobie operowac
	timer.startCounter();
	while ((timer.getCounter() < timeLimit * 1000)) {

		if ((int)(timer.getCounter() / 1000) >timeStamp) {

			timeStamp = timeStamp + interval;
			cout << timeStamp << endl;
			file << calculatePathLength(population[0]) << "\t";

			//pobierz probke co interwal
			/*
			if (timeStamp != (int)(timer.getCounter() / (1000)) && (int)(timer.getCounter() / (1000)) % interval ==0 && (int)(timer.getCounter() / (1000)) != timeLimit) {
				timeStamp = (int)(timer.getCounter() / (1000));
				cout << timeStamp << endl;
				file << calculatePathLength(population[0]) << "\t";
			}
			*/
		}


		//czyscimy dzieci z poprzedniej iteracji
		//offsprings.clear();



		for (int i = 0; i < startPopulationCount - 1; i = i + 2) {

			//rozmnazamy i dodajemy dzieci do zbioru dzieci
			offsprings[i] = orderCrossover(population[i], population[i + 1]);
			offsprings[i + 1] = orderCrossover(population[i + 1], population[i]);
			//offsprings.push_back(orderCrossover(population[i], population[i + 1]));
			//offsprings.push_back(orderCrossover(population[i + 1], population[i]));
		}

		if (startPopulationCount % 2 != 0) {

			//jezeli jest nieparzysta populacja to najgorszego skrzyzuj z przedostatnim
			offsprings[offspringsSize - 1] = (orderCrossover(population[startPopulationCount - 1], population[startPopulationCount - 2]));
			offsprings[offspringsSize - 2] = (orderCrossover(population[startPopulationCount - 2], population[startPopulationCount - 1]));
		}




		//mutacje na dzieci
		for (int i = 0; i < offsprings.size(); i++) {
			if (((float)rand() / RAND_MAX) < mutationFactor) {
				if (useScramble) {
					scrambleMutation(offsprings[i], rand() % offsprings[i].size() );
				}
				else {
					inverseMutation(offsprings[i]);
				}
			}
		}


		//przemieszaj dzieci zeby przy usuwaniu ich losowe ginely to chyba bardzo spowalnia
		//random_shuffle(offsprings.begin(), offsprings.end());

		//skasuj tyle dzieci zeby bylo ze ktores sie nie urodzily
		//offsprings.resize((int)(offspringsSize * crossFactor));

		population.resize(startPopulationCount + (int)(offspringsSize * crossFactor));
		for (int i = 0; i < (int)(offspringsSize * crossFactor); i++) {
			population[startPopulationCount + i] = offsprings[i];
		}


		//posortuj populacje
		sort(population.begin(), population.end(),
			[this](const vector<int>& a, const vector<int>& b) {
				return calculatePathLength(a) < calculatePathLength(b);
			});

		//zostaw tylko najlepsze osobniki
		population.resize(startPopulationCount);


	}

	//po skonczeniu algorytmu
	file << calculatePathLength(population[0]) << endl;





}



