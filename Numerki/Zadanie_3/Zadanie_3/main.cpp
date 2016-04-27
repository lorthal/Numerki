#include <iostream>
#include <cmath>
#include <vector>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:\\gnuplot\\bin"

using namespace std;

typedef double (*funkcja)(double);

int wybor, n;
double xMin, xMax;
funkcja fun;
vector<double> wektorX, wektorY, wektorZ, wektorNX, wektorNY;

double Horner(double tab[], int stopien, double x)
{
    double wynik = tab[0];

    for(int i = 1; i <= stopien; i++)
    {
        wynik = wynik*x + tab[i];
    }

    return wynik;
}

double Lagrange(double tabX[], double tabY[], double x)
{
    double temp;
    double y = 0;

    for(int i = 0; i < n; i++)
    {
        temp = 1;
        for(int j = 0; j < n; j++)
        {
            if(j != i)
            {
                temp *= (x - tabX[j])/(tabX[i] - tabX[j]);
            }
        }
        y += temp*tabY[i];
    }

    return y;
}

double fun1(double x)
{
    double tab[] = { -3, 5, -4, sin(x)};
    int st = 3;

    return Horner(tab, st, x);
}

double fun2(double x)
{
    return fabs(x-4.75);
}

double fun3(double x)
{
    double tab[] = { 1.3, 4.1, 5.6};
    int st = 2;

    return fabs(0.45 - x) + cos(x) - Horner(tab,st,x);
}

double fun4(double x)
{
    double y;
    cout << "Podaj wartosc dla wezla " << x << ": " ;
    cin >> y;
    return y;
}

void wczytajDane()
{
    cout << "Wybierz jedna z funkcji:" << endl;
    cout << "1) -3x^3 + 5x^2 -4x + sin(x)" << endl;
    cout << "2) |x - 4.75|" << endl;
    cout << "3) |0.45 - x| + cos(x) - (1.3x^2 + 4.1x + 5.6)" << endl;
    cout << "4) wartosci z tablicy" << endl;
    cin >> wybor;

    cout << "Podaj przedzial interpolacji:" << endl << "Poczatek: ";
    cin >> xMin;
    cout << "Koniec: ";
    cin >> xMax;

    cout << "Podaj ilosc wezlow: ";
    cin >> n;

    switch(wybor)
    {
    case 1:
        fun = fun1;
        break;
    case 2:
        fun = fun2;
        break;
    case 3:
        fun = fun3;
        break;
    case 4:
        fun = fun4;
        break;
    default:
        cout << "Zle wybrano funkcje \n";
        break;
    }
}

void obliczWezlyRownoodlegle(double tabX[], double tabY[])
{
    double odl = (xMax-xMin)/(n-1);

    tabX[0] = xMin;

    for(int i = 1; i < n; i++)
    {
        tabX[i] = tabX[0] + i*odl;
    }

    for(int i = 0; i < n; i++)
    {
        tabY[i] = fun(tabX[i]);
    }
}

int main()
{
    Gnuplot::set_GNUPlotPath(GNUPLOT_PATH);
    Gnuplot interpolacja;
    interpolacja.set_style("lines");
    interpolacja.set_grid();

    wczytajDane();
    double tabX[n];
    double tabY[n];

    obliczWezlyRownoodlegle(tabX,tabY);

    for(int i = 0; i < n; i++)
    {
        cout << tabX[i] << ", ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << tabY[i] << ", ";
    }
    double x;
    cout << endl << "Podaj dla jakiej wartosci chcesz obliczyc: ";
    cin >> x;
    cout << Lagrange(tabX,tabY,x);

    interpolacja.set_xrange(xMin,xMax);

    int g=0;
    for(double i=xMin; i<=xMax; i=i+(tabX[1]-tabX[0])/100.0)
        {
            wektorX.push_back(i);
            if(fun != fun4)
                wektorY.push_back(fun(i));
            wektorZ.push_back(Lagrange(tabX,tabY,i));
        }

    for(int i=0;i<n;i++)
    {
        wektorNX.push_back(tabX[i]);
        wektorNY.push_back(tabY[i]);
    }

    interpolacja.plot_xy(wektorX,wektorZ,"Lagrange");
    if(fun != fun4)
        interpolacja.plot_xy(wektorX,wektorY,"Funkcja");
    interpolacja.set_pointsize(2.5);
    interpolacja.set_style("points");
    interpolacja.plot_xy(wektorNX,wektorNY,"Wezly");
    getchar();
    getchar();

    return 0;
}
