#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

void twoDRandomwalk(double* my_xy)
{
    const double PI = acos(-1);
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(0, 2 * PI);

    double i;
    i = distr(eng);

    my_xy[0] += cos(i);
    my_xy[1] += sin(i);
}


int main()
{
    clock_t start = clock();
    string filename[3] = { "randomqtwo100.dat","randomqtwo1000.dat" };
    int numlist[3] = { 100, 1000 };
    double object[2] = { 0.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        ofstream fp(filename[i]);
        fp << setprecision(10);
        clock_t end = clock();
        cout << (end - start);

        int t = 0;
        while (t != 1000)
        {
            object[0] = 0.0;
            object[1] = 0.0;
            for (int j = 0; j < numlist[i]; j++)
            {
                twoDRandomwalk(object);
            }
            t += 1;
            double radius = sqrt(pow(object[0], 2.0) + pow(object[1], 2.0));
            fp << radius << endl;
        }
        fp.close();
    }

    return 0;
}