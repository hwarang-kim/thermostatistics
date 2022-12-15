#include <iostream>
#include <random>
#include <fstream>
#include <time.h>

using namespace std;

double S(void)
{
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(0, 1);

    double i, isum=0;
    for (int j = 0; j < 10000; j++)
    {
        i = distr(eng);
        isum += i;
    }
    return isum;
}


int main()
{
    clock_t start = clock();
    int H[10000];
    for (int j = 0; j < 10000; j++)
    {
        H[j] = 0;
    }
    for (int j = 0; j < 1000; j++)
    {
        H[static_cast<int>(S())] += 1;
    }
    clock_t end = clock();
    cout << (end - start);
    ofstream fp("montecarlo1.dat");
    for (int j = 0; j < 10000; j++)
    {
        fp << H[j] << endl;
    }
    fp.close();
    return 0;
}

