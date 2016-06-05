#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

typedef double (*funkcja)(double);
funkcja fun;
int wybor, stopienAproksymacji, n;
const int rozmiar = 5;
double xMin, xMax;

fstream plik;
vector<float> wezly[rozmiar];
vector<float> wspolczynniki[rozmiar];

double Horner(double tab[], int stopien, double x)
{
    double wynik = tab[0];

    for(int i = 1; i <= stopien; i++)
    {
        wynik = wynik*x + tab[i];
    }

    return wynik;
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

float GaussLegendre(int n)
{
    float temp=0;
    float p=(xMax-xMin)/2;
    float q=(xMin+xMax)/2;
    for(int i=0;i<=n+1;i++) {
        temp+=wspolczynniki[n][i]*fun(q+p*wezly[n][i]);
    }
    return temp*p;
}

void wczytajWezly() {
    plik.open( "plik.txt", ios::in | ios::out );
    if(plik.good()==true) {
        float temp;
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
        float temp;
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

void wprowadzDane()
{
    cout << "Wybierz jedna z funkcji:" << endl;
    cout << "1) -3x^3 + 5x^2 -4x + sin(x)" << endl;
    cout << "2) |x - 4.75|" << endl;
    cout << "3) |0.45 - x| + cos(x) - (1.3x^2 + 4.1x + 5.6)" << endl;
    cin >> wybor;

    cout << "Podaj przedzial aproksymacji:" << endl << "Poczatek: ";
    cin >> xMin;
    cout << "Koniec: ";
    cin >> xMax;

    cout << "Podaj stopien aproksymacji:" << endl;
    cin >> stopienAproksymacji;

    cout << "Podaj ilosc wezlow dla ca³kowania:" << endl;
    cin >> n;
}

int main()
{
    wczytajWezly();
    wczytajWspolczynniki();
    wprowadzDane();
    return 0;
}
