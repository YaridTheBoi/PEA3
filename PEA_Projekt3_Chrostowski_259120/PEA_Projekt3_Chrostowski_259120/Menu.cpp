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
    cout << "4. Algorytm Generyczny" << endl;
    cout << "5. Wyjdz" << endl;
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
        cout << "TUTAJ BEDZIE GENERYCZNY" << endl;
        printStartMenu();
        break;
    case 5:
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