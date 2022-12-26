#pragma once
#include <time.h>       
#include <iostream>
using namespace std;

class Timer {
private:
    double PCFreq;
    __int64 CounterStart;
public:
    //Konstructor
    Timer();

    /// <summary>
    /// uruchamia timer
    /// </summary>
    void startCounter();

    /// <summary>
    /// zwraca czas ktory minal od uruchomienia timera
    /// </summary>
    /// <returns>czas od uruchomienia timera[ms]</returns>
    double getCounter();
};