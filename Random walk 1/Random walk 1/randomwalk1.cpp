#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <time.h>


using namespace std;

int Randomwalk(int x)
{
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(0, 1);

    double i;
    i = distr(eng);
    if (i > 0.5)
        x += 1;
    else
        x -= 1;
    return x;
}


int ensemble(int finalstep)
{
    int x = 0, t = 0;
    while (x != finalstep)
    {
        x = Randomwalk(x);
        t += 1;
    }
    return t;
}


int main()
{
    clock_t start = clock();
    char filename[100];
    for (int i = 1; i < 9; i++)
    {
        string filename = "randomqone" + to_string(i) + ".dat";
        ofstream fp(filename);
        for (int j = 1; j < 8; j++)
        {
            fp << ensemble(i) << endl;
        }
        fp.close();
    }
    clock_t end = clock();
    cout << (end - start);
    return 0;
}
