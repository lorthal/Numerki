#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int n = 10;
double eps = 0.00001;

double A[n][n] = {0};

double B[n] = {0};

bool stop(double x1[], double x2[], int iloscRownan)
{
    bool sprawdz = true;

    bool tab[n];

    for(int i = 0; i < iloscRownan; i++)
    {
        tab[i] = false;
    }

    for(int i = 0; i < iloscRownan; i++)
    {
        if(fabs(x1[i]-x2[i]) <= eps) tab[i] = true;
    }

    for(int i = 0; i < iloscRownan && sprawdz == true; i++)
    {
        if(tab[i] != true) sprawdz = false;
    }

    return sprawdz;
}

void wypiszMacierz(double tab[][n], int iloscRownan)
{
    for (int i = 0; i < iloscRownan; i++)
    {
        for (int j =0; j < iloscRownan; j++)
            cout << tab[i][j] << "\t";
        cout << endl;
    }
}

void wypiszTablice(double tab[], int iloscRownan)
{
    for (int i = 0; i < iloscRownan; i++)
    {
        cout << tab[i] << "\t";
        cout << endl;
    }
}

void wyznaczMacierzU(double tab[][n], double wynik[][n], int iloscRownan)
{
    for (int i = 0; i < iloscRownan; i++)
    {
        for (int j = i+1; j < iloscRownan; j++)
        {
            wynik[i][j] = tab[i][j];
        }
    }
}

void wyznaczMacierzL(double tab[][n], double wynik[][n], int iloscRownan)
{
    for (int i = 0; i < iloscRownan; i++)
    {
        for (int j = i-1; j >= 0; j--)
        {
            wynik[i][j] = tab[i][j];
        }
    }
}

void wyznaczMacierzD(double tab[][n], double wynik[][n], int iloscRownan)
{
    for (int i = 0; i < iloscRownan; i++)
    {
        for (int j = 0; j < iloscRownan; j++)
        {
            if (i == j) wynik[i][j] = tab[i][j];
        }
    }
}

void wyznaczMacierzOdwr(double tab[][n], int iloscRownan)
{
    for (int i = 0; i < iloscRownan; i++)
    {
        for (int j = 0; j < iloscRownan; j++)
        {
            if(tab[i][j] != 0)
                tab[i][j] = 1/tab[i][j];
        }
    }
}

void mnozenieMacierz(double tab[][n], double wynik[][n], int iloscRownan)
{
    for(int i = 0; i < iloscRownan; i++)
    {
        for(int j = 0; j < iloscRownan; j++)
        {
            double w = 0;
            for (int k = 0; k < iloscRownan; k++)
            {
                w = w + tab[i][k] * wynik[k][j];
            }
            wynik[i][j] = w;
        }
    }
}

void mnozenieWektor(double tab[][n], double wynik[], int iloscRownan)
{
    for(int i = 0; i < iloscRownan; i++)
    {
        double w = 0;
        for(int j = 0; j < iloscRownan; j++)
        {
            w = w + tab[i][j] * wynik[j];
        }
        wynik[i] = w;
    }
}

double* GaussSeidel(double macierzA[][n], double wolneB[], int maxIteracji, int iloscRownan)
{
    double D[n][n] = {{0,0,0},
                      {0,0,0},
                      {0,0,0}};
    double U[n][n] = {{0,0,0},
                      {0,0,0},
                      {0,0,0}};
    double L[n][n] = {{0,0,0},
                      {0,0,0},
                      {0,0,0}};
    double X[n] = {0,0,0};
    double tmp[n];

    int iter = 0;
    cout << "Macierz A:" << endl;
    wypiszMacierz(macierzA,iloscRownan);
    cout << endl;
    cout << "Macierz wyrazow wolnych B:" << endl;
    wypiszTablice(wolneB,iloscRownan);
    cout << endl;

    wyznaczMacierzD(macierzA, D, iloscRownan);
    cout << "Macierz D:" << endl;
    wypiszMacierz(D,iloscRownan);
    cout << endl;
    wyznaczMacierzL(macierzA, L, iloscRownan);
    cout << "Macierz L:" << endl;
    wypiszMacierz(L,iloscRownan);
    cout << endl;
    wyznaczMacierzU(macierzA, U, iloscRownan);
    cout << "Macierz U:" << endl;
    wypiszMacierz(U,iloscRownan);
    cout << endl;
    wyznaczMacierzOdwr(D, iloscRownan);
    cout << "Macierz D^(-1):" << endl;
    wypiszMacierz(D,iloscRownan);
    cout << endl;

    mnozenieWektor(D, wolneB, iloscRownan);
    cout << "Macierz D^(-1)*B:" << endl;
    wypiszTablice(wolneB,iloscRownan);
    cout << endl;
    mnozenieMacierz(D, U, iloscRownan);
    cout << "Macierz D^(-1)*U:" << endl;
    wypiszMacierz(U,iloscRownan);
    cout << endl;
    mnozenieMacierz(D, L, iloscRownan);
    cout << "Macierz D^(-1)*L:" << endl;
    wypiszMacierz(L,iloscRownan);
    cout << endl;

    do
    {
        for(int i = 0; i < iloscRownan; i++)
        {
            tmp[i] = X[i];
            X[i] = wolneB[i];
            for(int j = 0; j < i; j++)
            {
                X[i] = X[i] - L[i][j]*X[j];
            }
            for(int j = i+1; j < iloscRownan; j++)
            {
                X[i] = X[i] - U[i][j]*X[j];
            }
        }
        iter++;
    }while(iter < maxIteracji && !stop(X,tmp,iloscRownan));
    cout << "Macierz Rozwiazan ukladu:" << endl;
    return X;
}

bool wczytajZPliku(int iloscRownan)
{
    cout << "Macierz wczytana z pliku:\n";
    fstream plik;
    plik.open( "macierz9.txt", std::ios::in | std::ios::out ); //<====================================================podaj plik====================================================================

    if( plik.good() == true )
    {
        for(int i=0;i<iloscRownan;i++)
            for(int j=0;j<iloscRownan+1;j++)
                if(j==iloscRownan) plik >> B[i];
                else plik >> A[i][j];
        for(int i=0;i<iloscRownan;i++)
            for(int j=0;j<iloscRownan+1;j++)
                if(j==iloscRownan) cout << B[i] << endl;
                else cout << A[i][j] << "\t";
        plik.close();
    }

    float temp=0;
    float maxkol=0;
    int nrwie=0;

    for(int i=0;i<iloscRownan;i++)
        {for(int j=i;j<iloscRownan;j++)
            if(abs(A[j][i])>abs(maxkol))
            {maxkol=A[j][i];
            nrwie=j;}

        for(int k=0;k<iloscRownan;k++)
        {
            temp=A[i][k];
            A[i][k]=A[nrwie][k];
            A[nrwie][k]=temp;
        }
        temp=B[i];
        B[i]=B[nrwie];
        B[nrwie]=temp;
        maxkol=0;
        nrwie=0;
        }

    bool czyzbiezna = 1;
    double* tempsum = new double[iloscRownan];
    for(int i=0;i<iloscRownan;i++)
        tempsum[i]=0;

    for(int i=0;i<iloscRownan;i++)
        {
            for(int j=0;j<iloscRownan;j++)
            if(i!=j)
            {
                tempsum[i]+=abs(A[j][i]);
            }
            //cout << tempsum[i] << " " << abs(A[i][i]);
            if(tempsum[i]>abs(A[i][i]))
                {
                cout << "Suma wartosci z " << i+1 << " kolumny jest wieksza badz rowna wartosci na przekatnej (" << tempsum[i] << ">" << abs(A[i][i]) << ")\n";
                czyzbiezna=0;
                break;
                }
        }

    return czyzbiezna;
}

int main()
{
    int maxIteracji = 30;
    int iloscRownan = 3;//<====================================================podaj ilosc rownan====================================================================
    bool czyzbiezna = 1;

    czyzbiezna=wczytajZPliku(iloscRownan);
    cout << endl;
    if(czyzbiezna==1)
    wypiszTablice(GaussSeidel(A, B, maxIteracji, iloscRownan),iloscRownan);
    else cout << "Macierz nie jest zbiezna";
    return 0;
}
