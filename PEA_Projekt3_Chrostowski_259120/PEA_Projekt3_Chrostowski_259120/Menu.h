#pragma once
#include "Graph.h"
#include "Genetic.h"
class Menu {
	Graph city = Graph();
	Genetic genetic = Genetic();
	double limitTime = 0.0;
	double crossFactor = 0.8;
	double mutationFactor = 0.01;
	int startPopulationCount = 0;
public:

	/// <summary>
	/// Wyswietla startowe menu z ktorego mozna wybierac operacje
	/// </summary>
	void printStartMenu();


	/// <summary>
	/// Czysci konsole poprzez wydrukowanie wielu znakow nowej linii
	/// </summary>
	void clearMenu();


	/// <summary>
	/// Przyjmuje argumenty od uzytkownika i na ich podstawie steruje menu
	/// </summary>
	void getInput();
};