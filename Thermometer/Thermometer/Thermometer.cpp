#include <iostream>
#include <random>
#include <cmath>
#include <list>
#include <fstream>
#include <time.h>

using namespace std;

bool Etrue(double E, double vn, double dv)
{
    double KE = 0.5 * 1.0 * pow(vn, 2.0);
    double AKE = 0.5 * 1.0 * pow((vn + dv), 2.0);
    double DE = AKE - KE;
    if (DE <= 0)
    {
        return true;
    }
    else
    {
        if (E >= DE) { return true; }
        else { return false; }
    }

}


void change(void)
{
    double v0 = 1.0;
    double demon = 0.0;
    double particle[10];
    for (int i = 0; i < 10; i++)
    {
        particle[i] = v0;
    }

    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(-5*v0, 5*v0);

    double deltav;

    random_device rd2;
    default_random_engine eng2(rd2());
    uniform_real_distribution<double> distr2(0.0, 10.0);

    int particlenum;

    list<double> meanv, meanK, Edemon;

    for (int i=0; i<1000000; i++)
    {
        deltav = distr(eng);
        particlenum = static_cast<int>(distr2(eng2));

        if (Etrue(demon, particle[particlenum], deltav))
        {
            double KE = 0.5 * 1.0 * pow(particle[particlenum], 2.0);
            double AKE = 0.5 * 1.0 * pow((particle[particlenum] + deltav), 2.0);
            double DE = AKE - KE;
            particle[particlenum] += deltav;
            demon -= DE;
        }
        else
        {
            double meanvv = 0, meanKK = 0;
            for (int j = 0; j < 10; j++)
            {
                meanvv += particle[j];
                meanKK += 0.5 * 1.0 * pow(particle[j], 2.0);
            }
            meanvv /= 10;
            meanKK /= 10;
            meanv.push_back(meanvv);
            meanK.push_back(meanKK);
            Edemon.push_back(demon);
        }
    }

    int N = static_cast<int>(meanv.size());

    cout << N << endl;

    double mmeanv = 0, mmeanK = 0, meandemon = 0;

    
    ofstream fp1("thermo1D.dat");

    for (int k = 0; k < N; k++)
    {
        fp1 << Edemon.front() << endl;
        mmeanv += meanv.front();
        mmeanK += meanK.front();
        meandemon += Edemon.front();
        meanv.pop_front();
        meanK.pop_front();
        Edemon.pop_front();

        
    }
    cout << mmeanv / N << " " << mmeanK / N << " " << meandemon / N << endl;
    fp1.close();


    ofstream fp2("thermov.dat");
    for (int i = 0; i < 10; i++)
    {
        fp2 << particle[i] << ',';
    }

    fp2.close();
}


int main()
{
    clock_t start = clock();
    change();

    clock_t end = clock();
    cout << (end - start);
    return 0;
}