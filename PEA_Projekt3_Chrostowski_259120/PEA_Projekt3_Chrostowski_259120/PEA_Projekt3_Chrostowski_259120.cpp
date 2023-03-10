#include <iostream>
#include "Menu.h"

//PONIZEJ SA RZECZY DO TESTOW WIEC DO WYWLENIA
#include "Genetic.h"
#include <vector>

using namespace std;

void testGenetic(int repeats, string filename, string tesFileName, int timeLimit, int interval, double crossFactor, double mutationFactor, int startPopulationCount, bool useScramble) {
    ofstream MyFile;
    Graph g = Graph();
    g.readFromFile(tesFileName);
    Genetic genetic = Genetic(g);

    MyFile.open(filename.c_str());
    if (MyFile.is_open()) {
        for (int i = 0; i < repeats; i++) {
            genetic.solveGeneticTest(timeLimit,crossFactor, mutationFactor, startPopulationCount, useScramble, interval, MyFile );
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
    /*
    //2-13-12-10-9-1-11-0-16-7-8-6-14-5-15-4-3-2   25
    Graph g = Graph();
    g.readFromFile("data17.txt");
    vector<int> test = { 2 , 13 , 12 , 10 , 9 , 1 , 11 , 0 , 16 , 7 , 8 , 6 , 14 , 5 , 15 , 4 , 3};
    cout << g.calculatePathLength(test) << endl;
    */

    /*
    Menu m = Menu();
    m.printStartMenu();
    */
    //testGenetic(1, "test17", "data17.txt", 120, 10, 0.8, 0.01, 100000, true);
   
    
    testGenetic(10, "test171Inverse100Turniej", "data171.txt", 120, 10, 0.8, 0.01, 100, false);
    testGenetic(10, "test171Scramble100Turniej", "data171.txt", 120, 10, 0.8, 0.01, 100, true);
    
    testGenetic(10, "test171Inverse500Turniej", "data171.txt", 120, 10, 0.8, 0.01, 500, false);
    testGenetic(10, "test171Scramble500Turniej", "data171.txt", 120, 10, 0.8, 0.01, 500, true);

    testGenetic(10, "test171Inverse1000Turniej", "data171.txt", 120, 10, 0.8, 0.01, 1000, false);
    testGenetic(10, "test171Scramble1000Turniej", "data171.txt", 120, 10, 0.8, 0.01, 1000, true);
    

    /*
    string plikWynik, plikDane;
    int repeats, timeLimit, interval, mutacja;
    int startPopulation = 100000;
    double mutationFactor = 0.01;
    double crossFactor = 0.8;
    bool useScramble=true;
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

    testGenetic(repeats, plikWynik, plikDane, timeLimit, interval, crossFactor, mutationFactor, startPopulation, useScramble);
    */
}

