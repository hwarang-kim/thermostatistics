#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <time.h>

using namespace std;


bool isInside(void)
{
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(0, 1);

    double i,j;
    i = distr(eng);
    j = distr(eng);

    bool inside = false;
    if (pow(i, 2.0) + pow(j, 2.0) < 1)
    {
        inside = true;
    }

    return inside;
}


int main()
{
    clock_t start = clock();
    double N = 0;
    int M = 100000;
    for (int i = 0; i < M; i++)
    {
        N += isInside();
    }
    N /= M;

    const double PI = acos(-1);
    clock_t end = clock();
    cout << (end - start);
    cout << N << endl;
    cout << abs(PI / 4 - N);
}