#include <time.h>       
#include <windows.h>
#include <iostream>
#include "Timer.h"
using namespace std;

Timer::Timer() {
    this->PCFreq = 0.0;
    this->CounterStart = 0;
}

void Timer::startCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double Timer::getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}