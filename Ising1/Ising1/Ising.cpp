#include <iostream>
#include <random>
#include <cmath>
#include <list>
#include <fstream>

#define N 5000
#define beta 2.0

using namespace std;

int spin[N];

random_device rd2;
default_random_engine eng2(rd2());
uniform_real_distribution<double> distr2(0.0, 1.0);


double meandomain(void)
{
    double meando = 0;
    int dummyindex = 1, j = 0;
    for (int i = 0; i < N - 1; i++)
    {
        dummyindex += 1;
        if (spin[i] * spin[i + 1] == -1)
        {
            meando += dummyindex;
            j += 1;
            dummyindex = 1;
        }
    }
    return meando / j;
}

double Energy(void)
{
    double energy = 0;
    for (int i = 0; i < N-1; i++)
    {
        energy -= spin[i] * spin[i + 1];
    }
    energy /= N;
    return energy;
}

double Mag(void)
{
    double mag = 0;
    for (int i = 0; i < N; i++)
    {
        mag += spin[i];
    }
    mag /= N;
    return mag;
}

double Heatcap(void)
{
    double cap = 0;
    double energys = 0;
    for (int i = 0; i < N-1; i++)
    {
        energys += pow(spin[i] * spin[i + 1], 2.0);
    }
    energys /= N;
    cap = energys - pow(Energy(), 2.0);
    cap *= beta;
    return cap;
}

double Succep(void)
{
    double suc = 0;
    double mags = 0;
    for (int i = 0; i < N; i++)
    {
        mags += pow(spin[i], 2.0);
    }
    mags /= N;
    suc = mags - pow(Mag(), 2.0);
    suc *= beta;
    return suc;
}

bool Etrue(double E0, int i)
{
    spin[i] *= -1;
    double Enew = Energy();
    double dE = Enew - E0;
    if (dE < 0)
    {
        return true;
    }
    else
    {
        double j = distr2(eng2);
        if (j <= exp(-beta * dE))
        {
            return true;
        }
        else
        {
            spin[i] *= -1;
            return false;
        }
    }
}

void change(void)
{

    for (int i = 0; i < N; i++)
    {
        spin[i] = 1;
    }

    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(0, N);

    int spinnum;

    list<double> M, E, C, chi, meand;

    for (int i = 0; i < 1000000; i++)
    {
        spinnum = static_cast<int>(distr(eng));
        double E0 = Energy();
        Etrue(E0, spinnum);

        M.push_back(Mag());
        E.push_back(Energy());
        C.push_back(Heatcap());
        chi.push_back(Succep());
        meand.push_back(meandomain());
    }

    ///ofstream fp1("isingM.dat");
    ofstream fp2("isingE5000.dat");
    ///ofstream fp3("isingC.dat");
    ///ofstream fp4("isingchi.dat");
    ///ofstream fp5("isingmean20.dat");

    int NN = static_cast<int>(M.size());

    for (int k = 0; k < NN; k++)
    {
        ///fp1 << M.front() << endl;
        fp2 << E.front() << endl;
        ///fp3 << C.front() << endl;
        ///fp4 << chi.front() << endl;
        ///fp5 << meand.front() << endl;
        M.pop_front();
        E.pop_front();
        C.pop_front();
        chi.pop_front();
        meand.pop_front();
    }
    ///fp1.close();
    fp2.close();
    ///fp3.close();
    ///fp4.close();
    ///fp5.close();
}


int main()
{
    change();
    return 0;
}