#pragma once
#include "Graph.h"

class Menu {
	Graph city = Graph();
	double limitTime = 0.0;
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