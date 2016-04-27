#include <iostream>
#include <math.h>
#include "gnuplot_i.hpp"
#include <vector>
#include <iomanip>

#define GNUPLOT_PATH "C:\\gnuplot\\bin"

using namespace std;

void fun1(vector<double> *tab);
double fun1d(double x);
void fun2(vector<double> *tab);
double fun2d(double x);
void fun3(vector<double> *tab);
double fun3d(double x);
void bisekcja(double a, double b, double (&fun)(double), int n, double &c);
void regulaFalsi(double a, double b, double (&f)(double), int n, double &c);
double pot(double base, int exponent);

typedef double (*fun)(double);

const double Epsi=0.00000001;

int main()
{
    fun f;
    double c1,c2;
    char wybor='0';
    double a=0,b=100;
    int n;
    vector<double> tab;

    Gnuplot::set_GNUPlotPath( GNUPLOT_PATH );
    Gnuplot main_plot;
    Gnuplot main_fals;

  main_plot.set_title( "Poszukiwanie miejsca zerowego za pomoca bisekcji" );
  main_plot.set_xlabel( "x" );
  main_plot.set_ylabel( "y" );

  main_plot.set_style( "lines" );
  main_plot.set_grid();
  main_plot.set_xrange( a , b );

  main_fals.set_title( "Poszukiwanie miejsca zerowego za pomoca reguly falsi" );
  main_fals.set_xlabel( "x" );
  main_fals.set_ylabel( "y" );

  main_fals.set_style( "lines" );
  main_fals.set_grid();
  main_fals.set_xrange( a , b );

  cout << "Wybierz funkcje do obliczenia\n";
  cout << "1.x^2-2\n";
  cout << "2.sin(x)-2*cos(x)\n";
  cout << "3.x^3-28x^2+5x+12\n";

  do
  {
  cin >> wybor;
  switch(wybor)
    {
    case '1':
    {
        fun1(&tab);
        f = fun1d;
        break;
    }
    case '2':
    {
        fun2(&tab);
        f = fun2d;
        break;
    }
    case '3':
    {
        fun3(&tab);
        f = fun3d;
        break;
    }
    default:
        cout << "Wybrano bledna opcje, wybierz jeszcze raz.";
        wybor='0';
        break;
    }
  } while(wybor=='0');

  main_plot.plot_x(tab,"Wybrana funkcja");
  main_fals.plot_x(tab,"Wybrana funkcja");

do
{
  cout << "Podaj zakres w ktorym chcesz szukac miejsca zerowego\n";
  cout << "Poczatek zakresu:"; cin >> a;
  cout << "Koniec zakresu:"; cin >> b;
} while((f(a))*(f(b)) > 0);

    cout << "Podaj ilosc iteracji:"; cin >> n;

  getchar();

    main_plot.set_xrange( a , b ) ;
    main_plot.replot();
    main_fals.set_xrange( a , b ) ;
    main_fals.replot();


  bisekcja(a,b,*f,n,c1);
  cout << setprecision(10) << c1 << endl;

  regulaFalsi(a,b,*f,n,c2);
  cout << setprecision(10) << c2 << endl;

  main_plot.set_style( "points" );
  main_plot.set_pointsize( 2.0 );
  main_fals.set_style( "points" );
  main_fals.set_pointsize( 2.0 );

      vector<double> x1( 1 );
      vector<double> x2( 1 );
  x1[ 0 ] = c1;
  x2[ 0 ] = c2;
  vector<double> y ( 1 );
  y[ 0 ] = 0;
  main_plot.plot_xy( x1, y, "podpis - opcjonalnie" );
  main_plot.replot();
  main_fals.plot_xy( x2, y, "podpis - opcjonalnie" );
  main_fals.replot();
    getchar();
    return 0;
}

void fun1(vector<double> *tab)
{
    for(int i=0;i<=100;i++)
        tab->push_back(i*i-2);
}
double fun1d(double x)
{
    return x*x-2;
}
void fun2(vector<double> *tab)
{
    for(int i=0;i<=100;i++)
        tab->push_back(sin(i)-2*cos(i));
}
double fun2d(double x)
{
    return sin(x)-2*cos(x);
}
void fun3(vector<double> *tab)
{
    for(int i=0;i<=100;i++)
        tab->push_back(i*i*i-28*i*i+5*i+12);
}
double fun3d(double x)
{
    return x*x*x-28*x*x+5*x+12;
}

void bisekcja(double a, double b, double (&f)(double), int n, double &c)
{
    c = 0;
    int i=0;
    while((fabs(f(c)) > Epsi) && (i<n))
    {
        c = (a+b)/2;
        if(f(a)*f(c) < 0) b = c;
        else a = c;
        i++;
    }
    cout << "Metoda Bisekcji: \nilosc wykonanych iteracji: " << i << ", miejsce zerowe: ";
    //return c;
}

void regulaFalsi(double a, double b, double (&f)(double), int n, double &c)
{
    c = b;
    int i=0;
    while((fabs(f(c)) > Epsi) && (i<n))
    {
        c = a - f(a) * (b-a)/(f(b)-f(a));
        if(f(a)*f(c) < 0) b = c;
        else a = c;
        i++;
    }
    cout << "Regula falsi: \nilosc wykonanych iteracji: " << i << ", miejsce zerowe: ";
    //return c;
}

double pot(double base, int exponent)
{
    double result = 1;

    while (exponent>0)
    {
        if(exponent % 2 == 1) result = result * base;

        base = base * base;
        exponent = exponent/2;
    }
    return result;
}
