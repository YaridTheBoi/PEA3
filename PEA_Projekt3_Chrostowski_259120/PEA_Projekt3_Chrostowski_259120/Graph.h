#pragma once
#include <string>
#include <fstream>  
#include <vector>
using namespace std;
class Graph {
public:
	int size;
	vector<vector<int>> grid;	//to zrob na vektor

	/// <summary>
	/// Konstruktor
	/// </summary>
	Graph();


	/// <summary>
	/// Czysci graf
	/// </summary>
	void clearGraph();


	/// <summary>
	/// Czyta dane z pliku o zadanej nazwie
	/// </summary>
	/// <param name="filename">Nazwa pliku z ktorego czytamy dane</param>
	void readFromFile(string);

	/// <summary>
	/// Uzywane w readFromFile. Czyta pojedyncza linie
	/// 
	/// </summary>
	/// <param name="file">Plik z ktorego czytamy</param>
	/// <param name="dest">tablica do ktorej trafi odczyt</param>
	/// <param name="size">ile jest do oczytania</param>
	/// <returns>Czy udalo sie odczytac</returns>
	bool readLineFromFile(ifstream&, vector<int>&, int);


	/// <summary>
	/// Drukuje graf
	/// </summary>
	void printGraph();


	/// <summary>
	/// Funkcja ktora pomaga z wczytywaniem. sprawdza czy juz cos jest w matrycy, jak jest to najpierw ja czysci a potem dopiero wpisuje
	/// </summary>
	/// <param name="size">Ilosc miast w grafie</param>
	void scaleForRead(int);





	/// <summary>
	/// Oblicza dlugosc zadanej sciezki
	/// </summary>
	/// <param name="path">Sciezka ktorej dlugosc nalezy obliczyc</param>
	/// <returns>Dlugosc zdanej trasy</returns>
	int calculatePathLength(vector<int>);


};