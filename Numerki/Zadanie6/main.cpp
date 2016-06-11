#include <iostream>
#include <cmath>
#include <vector>

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

double e(double t) {
    return Em*sin(OMG*t+Fi);
}

void warunkiPoczatkowe() {
x.push_back(0.0);
y.push_back(0.0);
z.push_back(0.0);
t.push_back(t0);
}

double delta(double value) {
    return 1/6*(k1+2*k2+2*k3+k4);
}

kx1 = h * f1(x,y,z)
ky1 = h * f2(x,y,z)
kz1 = h * f3(x,y,z)

void Rk() {
    int j=0;
    for(int i=t0+h; i<=t1; i+=h)
    {
        x.push_back(x[j]+Dx)
        j++;
    }
}

/*
x'(t) = -R1/L1*x + 0*y - 1/L1*z + 1/L1 * e(t)
y'(t) = 0*x - R3/L3*y + 1/L3*z + 0
z'(t) = 1/C2*x - 1/C2*y + 0*z + 0
*/
int main()
{
    warunkiPoczatkowe();
    cout << "Hello world!" << endl;
    return 0;
}
