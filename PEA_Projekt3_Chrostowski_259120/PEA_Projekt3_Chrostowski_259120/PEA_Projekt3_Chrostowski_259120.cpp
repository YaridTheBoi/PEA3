#include <iostream>
#include "Menu.h"

//PONIZEJ SA RZECZY DO TESTOW WIEC DO WYWLENIA
#include "Genetic.h"
#include <vector>

using namespace std;

void testGenetic(int repeats, string filename, string tesFileName, int timeLimit, int interval, double crossFactor, double mutationFactor, int startPopulationCount) {
    ofstream MyFile;
    Graph g = Graph();
    g.readFromFile(tesFileName);
    Genetic genetic = Genetic(g);

    MyFile.open(filename.c_str());
    if (MyFile.is_open()) {
        for (int i = 0; i < repeats; i++) {
            genetic.solveGeneticTest(timeLimit,crossFactor, mutationFactor, startPopulationCount, interval, MyFile );
            cout << "Dla Genetic test " << i + 1 << " zakonczyl sie" << endl;
        }
        MyFile.close();
    }
    else {
        cout << "Jestem niedzialajacy" << endl;
    }


}







int main()
{
    Menu m = Menu();
    m.printStartMenu();


    /*
    string plikWynik, plikDane;
    int repeats, timeLimit, interval;
    int startPopulation = 100000;
    double mutationFactor = 0.01;
    double crossFactor = 0.8;
    cout << "Podaj nazwe pliku docelowego: ";
    cin >> plikWynik;


    cout << endl << "Podaj nazwe pliku zrodlowego: ";
    cin >> plikDane;

    cout << endl << "Czas trwania testu: ";
    cin >> timeLimit;

    cout << endl << "Co ile pobierac probke: ";
    cin >> interval;

    cout << endl << "Powtorzen: ";
    cin >> repeats;

    testGenetic(repeats, plikWynik, plikDane, timeLimit, interval, crossFactor, mutationFactor, startPopulation);
    */
}

