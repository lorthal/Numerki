#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef float (*funkcja)(float);
const int rozmiar=9;
int iwezlow=9;
fstream plik;
vector<float> wezly[rozmiar];
vector<float> wspolczynniki[rozmiar];
funkcja fun;
float a,b, eps;
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

float Simpson(float eps)
{
    float wynik = 0, temp = 0;
    float N = 1;
    float x, wynik_poprz_iter = 0;
    float h = (b-a)/N;

    bool flag = true;



    while(flag)
    {
        for(int i = 0; i <= N; i++)
        {
            x = a + i*h;
            temp += fun(x-(h/2));

            if(i < N) wynik += fun(x);
        }
        wynik = h/6*(fun(a)+fun(b)+2*wynik+4*temp);

        //cout << setprecision(15) << endl << wynik << endl << wynik_poprz_iter << endl;
        if(fabs(wynik-wynik_poprz_iter) <= eps) {flag = false; cout << N-1 << endl;}
        else
        {
            wynik_poprz_iter = wynik;
            N++;
            h = (b-a)/N;
            temp = 0;
            wynik = 0;

        }

    }

    return wynik;
}

int main()
{
    wczytajWezly();
    wczytajWspolczynniki();
    wys_ww();
    wybierzFunkcje();
    ustawZakres();

    for(int i = 2; i <= iwezlow; i++)
//    {
        cout << setprecision(9) <<  GaussLegendre(i-2) << endl;
//        cout << setprecision(15) << Simpson(i) << endl << endl;
//    }
    cout << setprecision(9) << Simpson(0.00001) << endl << endl;
    return 0;
}
