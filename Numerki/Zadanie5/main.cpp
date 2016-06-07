#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:\\gnuplot\\bin"

using namespace std;

double x=2,a,b;
const int rozmiar=9;
vector<double> wezly[rozmiar];
vector<double> wspolczynniki[rozmiar];
int wybor,n,iwezlow;
fstream plik;
vector<double> wektorX, wektorY, wektorZ, LambdaK, suma;
double orto[6]={2.0,2.0/3.0,2.0/5.0,2.0/7.0,2.0/9.0,2.0/11.0};

void wczytajWezly() {
    plik.open( "plik.txt", ios::in | ios::out );
    if(plik.good()==true) {
        double temp;
        for(int i=0;i<rozmiar;i++) {
            for(int j=0;j<i+2;j++) {
                plik >> temp;
                wezly[i].push_back(temp);
            }
        }
        plik.close();
    }
    else cout << "Brak pliku z wezlami kwadratur Gaussa-Legendre'a, lub inny problem z plikiem.";
}
void wczytajWspolczynniki() {
    plik.open( "plik1.txt", ios::in | ios::out );
    if(plik.good()==true) {
        double temp;
        for(int i=0;i<rozmiar;i++) {
            for(int j=0;j<i+2;j++) {
                plik >> temp;
                wspolczynniki[i].push_back(temp);
            }
        }
        plik.close();
    }
    else cout << "Brak pliku z wezlami kwadratur Gaussa-Legendre'a, lub inny problem z plikiem.";
}

double Horner(double tab[], int stopien, double x) {
    double wynik = tab[0];

    for(int i = 1; i <= stopien; i++)
    {
        wynik = wynik*x + tab[i];
    }

    return wynik;
}

typedef double (*funkcja)(double);
double Legendre0(double x) {
    return 1;
}
double Legendre1(double x) {
    return x;
}
double Legendre2(double x) {
    return 1.0/2.0*(3.0*pow(x,2.0)-1.0);
}
double Legendre3(double x) {
    return 1.0/2.0*(5.0*pow(x,3.0)-3.0*x);
}
double Legendre4(double x) {
    return 1.0/8.0*(35.0*pow(x,4.0)-30.0*pow(x,2.0)+3.0);
}
double Legendre5(double x) {
    return 1.0/8.0*(63.0*pow(x,5.0)-70.0*pow(x,3.0)+15.0*pow(x,2.0));
}

funkcja Legendre[6]={Legendre0,Legendre1,Legendre2,Legendre3,Legendre4,Legendre5};

double fun1(double x) {
    double tab[] = { -3, 5, -4, sin(x)};
    int st = 3;

    return Horner(tab, st, x);
}
double fun2(double x) {
    return fabs(x);
}
double fun3(double x) {
    double tab[] = { 1.3, 4.1, 5.6};
    int st = 2;

    return fabs(0.45 - x) + cos(x) - Horner(tab,st,x);
}

funkcja fun;

double calka(int n, funkcja fun1) {
    float temp=0;
    float p=(b-a)/2;
    float q=(a+b)/2;
    for(int i=0;i<=n+1;i++) {
        //temp+=wspolczynniki[n][i]*fun1(fun(q+p*wezly[n][i]));
        temp+=wspolczynniki[n][i]*fun1(q+p*wezly[n][i])*fun(q+p*wezly[n][i]);
    }
    return temp*p;
}

double funAproksymacja(double x) {
    double x1 = suma[5];
    double x2 = suma[4];
    double x3 = suma[3];
    double x4 = suma[2];
    double x5 = suma[1];
    double x6 = suma[0];

    return (x1 * x * x * x * x * x + x2 * x * x * x * x + x3 * x * x * x + x4 * x * x + x5 * x + x6);

}

void preAprox() {
    for(int i = 0; i<n; i++) {
        LambdaK.push_back(calka(iwezlow-2, Legendre[i])/orto[i]);
        cout << LambdaK[i] << endl;
        }

    for(;LambdaK.size()<6;)
        LambdaK.push_back(0.0);

    suma.push_back(LambdaK[0]-(1.0/2.0*LambdaK[2])+(3.0/8.0*LambdaK[4]));
    suma.push_back(LambdaK[1]-(3.0/2.0*LambdaK[3]));
    suma.push_back((3.0/2.0*LambdaK[2])-(30.0/8.0*LambdaK[4])+(15.0/8.0*LambdaK[5]));
    suma.push_back((5.0/2.0*LambdaK[3])-(70.0/8.0*LambdaK[5]));
    suma.push_back((35.0/8.0*LambdaK[4]));
    suma.push_back((63.0/8.0*LambdaK[5]));
}

void liczFunkcje() {
    for(double i=a; i<=b; i=i+(b-a)/1000.0)
    {
        wektorX.push_back(i);
        wektorY.push_back(fun(i));
        wektorZ.push_back(funAproksymacja((2*i-a-b)/(b-a))); // Nie dzia³a przekszta³cenie na przedzia³ -1 do 1
    }
}

void wczytajDane() {
    cout << "Wybierz jedna z funkcji:" << endl;
    cout << "1) -3x^3 + 5x^2 -4x + sin(x)" << endl;
    cout << "2) |x|" << endl;
    cout << "3) |0.45 - x| + cos(x) - (1.3x^2 + 4.1x + 5.6)" << endl;
    cin >> wybor;

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
    default:
        cout << "Zle wybrano funkcje \n";
        break;
    }

    cout << "Podaj przedzial aproksymacji:" << endl << "Poczatek: ";
    cin >> a;
    cout << "Koniec: ";
    cin >> b;

    cout << "Podaj stopien wielomianu aproksymujacego: ";
    cin >> n;
    n++;

    cout << "podaj ilosc wezlow [2,10]\n";
    cin >> iwezlow;
    if(iwezlow<2) iwezlow=2;
    if(iwezlow>10) iwezlow=10;
}

int main()
{
    Gnuplot::set_GNUPlotPath(GNUPLOT_PATH);
    Gnuplot aproksymacja;
    aproksymacja.set_style("lines");
    aproksymacja.set_grid();

    wczytajWezly();
    wczytajWspolczynniki();
    wczytajDane();
    aproksymacja.set_xrange(a,b);
    preAprox();
    liczFunkcje();

    aproksymacja.plot_xy(wektorX,wektorY,"Funkcja");
    aproksymacja.plot_xy(wektorX,wektorZ,"Aproksymacja");
    getchar();
    getchar();

    return 0;
}
