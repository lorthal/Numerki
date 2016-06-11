#include <iostream>
#include <cmath>
#include <vector>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:\\gnuplot\\bin"

using namespace std;

double Em = 220*sqrt(2),
Fi = M_PI/4.0,
OMG = 100*M_PI,
R1 = 2.5,
R3 = 50,
L1 = 2.5/OMG,
L3 = 50/OMG,
OMGr = 500*M_PI,
C2 = 1/(OMGr*OMGr*L1),
t0 = 0,
t1 = 0.04,
M1 = 512,
h = (t1-t0)/(10*M1);
vector<double> x,y,z,t;
vector<double> xx,yy,zz,tt;
double kx1,kx2,kx3,kx4,ky1,ky2,ky3,ky4,kz1,kz2,kz3,kz4;

double e(double t) {
    return Em*sin(OMG*t+Fi);
}

void warunkiPoczatkowe() {
x.push_back(0.0);
y.push_back(0.0);
z.push_back(0.0);
t.push_back(t0);
xx.push_back(0.0);
yy.push_back(0.0);
zz.push_back(0.0);
tt.push_back(t0);
}

double f1(double x, double y, double z, double t) {
    return -R1/L1*x + 0*y - 1/L1*z + 1/L1 * e(t);
}

double f2(double x, double y, double z) {
    return 0*x - R3/L3*y + 1/L3*z + 0;
}

double f3(double x, double y, double z) {
    return 1/C2*x - 1/C2*y + 0*z + 0;
}

void Rk4() {
    int j=0;
    for(double i=t0+h; i<=t1; i+=h)
    {
        kx1 = f1(x.back(),y.back(),z.back(),t.back());
        ky1 = f2(x.back(),y.back(),z.back());
        kz1 = f3(x.back(),y.back(),z.back());

        kx2 = f1(x.back()+h/2,y.back()+h/2,z.back()+h/2,t.back());
        ky2 = f2(x.back()+h/2,y.back()+h/2,z.back()+h/2);
        kz2 = f3(x.back()+h/2,y.back()+h/2,z.back()+h/2);

        kx3 = f1(x.back()+h/2,y.back()+h/2,z.back()+h/2,t.back());
        ky3 = f2(x.back()+h/2,y.back()+h/2,z.back()+h/2);
        kz3 = f3(x.back()+h/2,y.back()+h/2,z.back()+h/2);

        kx4 = f1(x.back()+h,y.back()+h,z.back()+h,t.back());
        ky4 = f2(x.back()+h,y.back()+h,z.back()+h);
        kz4 = f3(x.back()+h,y.back()+h,z.back()+h);

        x.push_back(x.back()+1.0/6.0*(kx1+2*kx2+2*kx3+kx4) * h);
        y.push_back(y.back()+1.0/6.0*(ky1+2*ky2+2*ky3+ky4) * h);
        z.push_back(z.back()+1.0/6.0*(kz1+2*kz2+2*kz3+kz4) * h);
        t.push_back(i);
    }
}

void Rk2() {
    int j=0;
    for(double i=t0+h; i<=t1; i+=h)
    {
        kx1 = f1(xx.back(),yy.back(),zz.back(),tt.back());
        ky1 = f2(xx.back(),yy.back(),zz.back());
        kz1 = f3(xx.back(),yy.back(),zz.back());

        kx2 = f1(xx.back()+h*2/3,yy.back()+h*2/3,zz.back()+h*2/3,tt.back());
        ky2 = f2(xx.back()+h*2/3,yy.back()+h*2/3,zz.back()+h*2/3);
        kz2 = f3(xx.back()+h*2/3,yy.back()+h*2/3,zz.back()+h*2/3);

        xx.push_back(xx.back()+(1.0/4.0*kx1+3.0/4.0*kx2) * h);
        yy.push_back(yy.back()+(1.0/4.0*ky1+3.0/4.0*ky2) * h);
        zz.push_back(zz.back()+(1.0/4.0*kz1+3.0/4.0*kz2) * h);
        tt.push_back(i);
    }
}

int main()
{
    warunkiPoczatkowe();
    Rk2();
    Rk4();
    Gnuplot::set_GNUPlotPath(GNUPLOT_PATH);
    Gnuplot rysowanie;
    rysowanie.set_pointsize(0.5);
    rysowanie.set_style("linespoints");
    rysowanie.set_grid();
    rysowanie.set_xrange(t0,t1);
    rysowanie.plot_xy(t,x,"x2");
    rysowanie.plot_xy(t,y,"y2");
    rysowanie.plot_xy(t,z,"z2");
    rysowanie.set_style("lines");
    rysowanie.plot_xy(tt,xx,"x2");
    rysowanie.plot_xy(tt,yy,"y2");
    rysowanie.plot_xy(tt,zz,"z2");
    getchar();
    return 0;
}
