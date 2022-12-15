#include <iostream>
#include <cmath>

using namespace std;

double datasetx[50];
double datasety[50] = { 139643, 116988, 94433, 80336, 67507, 56978, 46690, 38704, 31821, 26679, 22335, 18384, 15025, 12324, 10712, 8322, 6899, 5276, 4231, 3472, 2850, 2364, 1659, 1480, 1234, 846, 711, 621, 407, 394, 273, 242, 163, 125, 107, 87, 41, 21, 21, 28, 22, 24, 11, 5, 7, 2, 6, 1, 1, 1 };

double lfit(double x, double a, double b)
{
    return b * x + a;
}

double chisq(double a, double b)
{
    double chitemp = 0;
    for (int i = 0; i < 50; i++)
    {
        chitemp += pow((datasety[i] - lfit(datasetx[i], a, b)), 2.0);
    }
    return chitemp;
}


double gradx(double a, double b, double h)
{
    double dfa = (chisq(a + h, b) - chisq(a - h, b)) / (2 * h);
    return dfa;
}

double grady(double a, double b, double h)
{
    double dfb = (chisq(a, b + h) - chisq(a, b - h)) / (2 * h);
    return dfb;
}

int main()
{

    double xmaxima = 2.81201;
    for (int i = 0; i < 50; i++)
    {
        datasetx[i] = xmaxima / 100 * (2*i+1);
    }
    for (int i = 0; i < 50; i++)
    {
        datasety[i] = datasety[i]/ 820513;
    }
    for (int i = 0; i < 50; i++)
    {
        datasety[i] = log(datasety[i]);
    }

    double acc = pow(10.0, -6.0);
    double err = 1.0;
    double paramx = -1.0;
    double paramy = -1.0;
    double h = 0.001;
    double eta = 0.001;

    while (err > acc)
    {
        float deltax = eta * gradx(paramx, paramy, h);
        float deltay = eta * grady(paramx, paramy, h);
        paramx -= deltax;
        paramy -= deltay;
        err = max(fabs(deltax), fabs(deltay));
    }

    cout << paramx << endl << paramy << endl;
    return 0;
}