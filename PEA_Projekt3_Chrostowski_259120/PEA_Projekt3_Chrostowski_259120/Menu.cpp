#include <iostream>
#include <conio.h>
#include "Menu.h"
#include <fstream>  
#include <sstream>

using namespace std;

void Menu::printStartMenu()
{
    cout << endl;
    cout << "Projekt 3 PEA Kacper Chrostowski 259120" << endl;
    cout << "Wybierz Opcje" << endl;
    cout << "1. Zaladuj dane z pliku" << endl;
    cout << "2. Wyswietl wprowadzony graf" << endl;
    cout << "3. Wprowadz ograniczenie czasowe" << endl;
    cout << "4. Wprowadz wspolczynnik krzyzowania" << endl;
    cout << "5. Wprowadz wspolczynnik mutacji" << endl;
    cout << "6. Wprowadz wielkosc populacji poczatkowej" << endl;
    cout << "7. Algorytm Generyczny" << endl;
    cout << "8. Wyjdz" << endl;
    getInput();
}

void Menu::clearMenu()
{
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
}

void Menu::getInput()
{
    string title;
    int input;
    cout << "Wybierz opcje: ";
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        if (ss >> input)
        {
            if (ss.eof())
            {
                break;
            }
        }
        cout << "Niepoprawne Dane. Sproboj ponownie" << endl;
        cout << "Wybierz opcje: ";
    }


    switch (input) {
    case 1:

        cout << "Podaj nazwe pliku z danymi(z roszerzeniem): ";
        cin >> title;
        cout << endl;
        city.readFromFile(title);
        getchar();
        printStartMenu();
        break;

    case 2:
        if (this->city.size == 0) {
            cout << "Prosze wprowadzic graf" << endl;
        }
        else {
            cout << endl;
            this->city.printGraph();
        }
        printStartMenu();
        break;
    case 3:
        cout << "Wybierz limit czasowy: ";
        while (getline(cin, line)) {
            stringstream ss(line);
            if (ss >> limitTime)
            {
                if (ss.eof())
                {
                    break;
                }
            }
            cout << "Niepoprawne Dane. Sproboj ponownie" << endl;
            cout << "Wybierz limit czasowy: ";
        }
        printStartMenu();
        break;

    case 4:
        cout << "Wybierz wspolczynnik krzyzowania: ";
        while (getline(cin, line)) {
            stringstream ss(line);
            if (ss >> crossFactor)
            {
                if (ss.eof())
                {
                    break;
                }
            }
            cout << "Niepoprawne Dane. Sproboj ponownie" << endl;
            cout << "Wybierz wspolczynnik krzyzowania: ";
        }
        printStartMenu();
        break;

    case 5:
        cout << "Wybierz wspolczynnik mutacji: ";
        while (getline(cin, line)) {
            stringstream ss(line);
            if (ss >> mutationFactor)
            {
                if (ss.eof())
                {
                    break;
                }
            }
            cout << "Niepoprawne Dane. Sproboj ponownie" << endl;
            cout << "Wybierz wspolczynnik mutacji: ";
        }
        printStartMenu();
        break;

    case 6:
        cout << "Wybierz wielkosc populacji poczatkowej: ";
        while (getline(cin, line)) {
            stringstream ss(line);
            if (ss >> startPopulationCount)
            {
                if (ss.eof())
                {
                    break;
                }
            }
            cout << "Niepoprawne Dane. Sproboj ponownie" << endl;
            cout << "Wybierz wielkosc populacji poczatkowej: ";
        }
        printStartMenu();
        break;
    case 7:
        genetic = Genetic(city);
        genetic.solveGenetic(limitTime, crossFactor, mutationFactor, startPopulationCount);
        printStartMenu();
        break;
    case 8:
        clearMenu();
        cout << "Do widzenia" << endl;
        cin.get();
        exit(0);
        break;
    default:
        cout << endl << "Nie ma takiej odpowiedzi" << endl;
        printStartMenu();
        break;
    }
}