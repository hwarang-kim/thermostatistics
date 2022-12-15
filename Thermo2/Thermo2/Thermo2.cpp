#include <iostream>
#include <random>
#include <cmath>
#include <list>
#include <fstream>

using namespace std;

bool Etrue(double E, double vxn, double vyn, double dvx, double dvy)
{
    double KE = 0.5 * 1.0 * (pow(vxn, 2.0)+pow(vyn, 2.0));
    double AKE = 0.5 * 1.0 * (pow((vxn+dvx), 2.0) + pow((vyn+dvy), 2.0));
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
    double particlex[10];
    double particley[10];
    for (int i = 0; i < 10; i++)
    {
        particlex[i] = v0;
        particley[i] = 0;
    }

    const double PI = acos(-1);
    random_device rda;
    default_random_engine enga(rda());
    uniform_real_distribution<double> distra(0, 2 * PI);

    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(-5.0 * v0, 5.0 * v0);

    double deltavx, deltavy;

    random_device rd2;
    default_random_engine eng2(rd2());
    uniform_real_distribution<double> distr2(0.0, 10.0);

    int particlenum;

    list<double> meanv, meanK, Edemon;

    for (int i = 0; i < 1000000; i++)
    {
        double v0 = distr(eng);
        double theta = distra(enga);
        deltavx = v0 * cos(theta);
        deltavy = v0 * sin(theta);
        particlenum = static_cast<int>(distr2(eng2));

        if (Etrue(demon, particlex[particlenum], particley[particlenum], deltavx, deltavy))
        {
            double KE = 0.5 * 1.0 * (pow(particlex[particlenum], 2.0) + pow(particley[particlenum], 2.0));
            double AKE = 0.5 * 1.0 * (pow((particlex[particlenum]+deltavx), 2.0) + pow((particley[particlenum]+deltavy), 2.0));
            double DE = AKE - KE;
            particlex[particlenum] += deltavx;
            particley[particlenum] += deltavy;
            demon -= DE;
        }
        else
        {
            double meanvv = 0, meanKK = 0;
            for (int j = 0; j < 10; j++)
            {
                meanvv += pow(pow(particlex[j], 2.0) + pow(particley[j], 2.0), 0.5);
                meanKK += 0.5 * 1.0 * (pow(particlex[j], 2.0) + pow(particley[j], 2.0));
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


    ofstream fp1("thermo2D.dat");

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

    fp1.close();

    cout << mmeanv / N << " " << mmeanK / N << " " << meandemon / N << endl;


    ofstream fp2("thermov2D.dat");
    for (int i = 0; i < 10; i++)
    {
        fp2 << particlex[i]<< ',' << particley[i] << endl;
    }

    fp2.close();
}


int main()
{
    change();
    return 0;
}