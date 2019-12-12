#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

double F(double x, double y){
    return (pow(x, 3)*pow(y, 2) + x*y + x*pow(y,3) - 3); 
}

double dFdx(double x, double y){
    return (3*pow(x,2)*pow(y,2) + y + pow(y,3));
}

double dFdy(double x, double y){
    return (2*pow(x,3)*y + x + 3*x*pow(y,2));
}



double G(double x, double y){
    return (pow(x,2) + pow(x,2)* pow(y,2) - 2*x*y);
}

double dGdx(double x, double y){
    return (2*x + 2*x*pow(y,2) -2*y);
}

double dGdy(double x, double y){
    return (2*pow(x,2)*y - 2*x);
}




int main(){

    double x, x0, y, y0, epsX, epsF;
    x0 = x = 1.1;
    y0 = y = 1.05;
    epsX = epsF = 1.0e-8;
    
    double W, Wx, Wy, Hx, Hy;
    int iteracja = 0;

    do{
        iteracja++;
        W = (-1)*dGdx(x, y) * dFdy(x, y) + dFdx(x, y) *dGdy(x, y);
        Wx = G(x, y) * dFdy(x, y) - F(x, y) * dGdy(x, y);
        Wy = F(x, y) * dGdx(x, y) - G(x, y) * dFdx(x, y);
        Hx = Wx/W;
        Hy = Wy/W;
        double xp = x;
        double yp = y;

        x = xp + Hx;
        y = yp + Hy;
    } while(!( max (fabs(Hx), fabs(Hy)) < epsX && max( fabs(F(x, y)), fabs(G(x, y)) ) < epsF));
    
    cout<<"X = " << x <<"\nY = "<< y << "\nIteracji = "<< iteracja << endl;

    return 0;
}