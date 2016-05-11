#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;

typedef float (*funkcja)(float);
const int rozmiar=9;
int iwezlow=9;
fstream plik;
vector<float> wezly[rozmiar];
vector<float> wspolczynniki[rozmiar];
funkcja fun;
float a,b;
bool a_lower_b;

float fun1(float x) {
    return x*x;
}

float fun2(float x) {
    return 1/(1+x*x);
}

float fun3(float x) {
    return 1/(x+1);
}

void wybierzFunkcje() {
    int wybor;
    cout << "Podaj dla ktorej funkcji chcesz obliczyc calke\n";
    cout << "1. x*x\n";
    cout << "2. 1/(1+x*x)\n";
    cout << "3. 1/(x+1)\n";
    cin >> wybor;
    switch (wybor) {
        case 1: fun=fun1; break;
        case 2: fun=fun2; break;
        case 3: fun=fun3; break;
        default : cout << "bledna funkcja.\n"; break;
    }

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

float obliczanieP(int i, float x) {
    if(i==0) return 1;
    if(i==1) return x;
    else return (((2*(i-1)+1)/(i-1)+1)*x*obliczanieP(i-1,x)-((i-1)/((i-1)+1))*obliczanieP(i-2,x));
    }

float obliczaniePprim(int i,float x) {
    return (i/(x*x-1))*x*obliczanieP(i,x)-(i/(x*x-1))*obliczanieP(i-1,x);
}

float pow(float x, int n) {
    float temp=x;
    if(n==0) return 1;
    if(n==1) return x;
    else {
    for(int i=1;i<n;i++) {
        x=x*temp;
        }
    return x;
    }
}

int silnia(int n) {
    /*int temp=1;
    if(n==0) return 1;
    else {
    for(int i=1;i<=n;i++) {
        temp=temp*i;
        }
    return temp;
    }*/
}

float obliczanieA(int k, int n) {
    //return (-2/((n+2)*obliczanieP(n+2,dane[n+2][k])*obliczaniePprim(n+1,dane[n+1][k])));
}

void ustawZakres() {
    do {
    a_lower_b=true;
    cout << "Podaj poczatek oraz koniec zakresu calkowania.\n";
    cout << "Poczatek:";
    cin >> a;
    cout << "Koniec:";
    cin >> b;
    if(b<=a) { cout << "Blad zakresu\n"; a_lower_b=false; }
    } while(!a_lower_b);
    cout << "podaj ilosc wezlow [2,10]\n";
    cin >> iwezlow;
    if(iwezlow<2) iwezlow=2;
    if(iwezlow>10) iwezlow=10;
}

float GaussLegendre(int n) {
    float temp=0;
    float p=(b-a)/2;
    float q=(a+b)/2;
    for(int i=0;i<=n+1;i++) {
        temp+=wspolczynniki[n][i]*fun(q+p*wezly[n][i]);
    }
    return temp*p;
}

void wys_ww() {
            cout << "Wezly:  ";
            for (int i = 0; i <= rozmiar; ++i) {
                cout << ' ' << wezly[rozmiar-1][i];
            }
            cout << '\n';
            cout << "Wspolczynniki:";
            for (int i = 0; i <= rozmiar; ++i) {
                cout << ' ' << wspolczynniki[rozmiar-1][i];
            }
            cout << '\n';
        }

int main()
{
    wczytajWezly();
    wczytajWspolczynniki();
    wys_ww();
    wybierzFunkcje();
    ustawZakres();

    cout << GaussLegendre(iwezlow-2);
    return 0;
}
