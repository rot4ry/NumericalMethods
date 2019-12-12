#include <iostream>
#include <cmath>

using namespace std;

double g(double x);
void zadanie1();

double f(double x);
double fp(double x);
void zadanie2();

int main(){                 // RÓWNANIA NIELINIOWE    
    
    //zadanie1();
    zadanie2();    
    return 0;
}



double g(double x){         // 3x - cosx = 0
   return (1./3 * cos(x));    
}

void zadanie1(){            // METODA ITERACJI PROSTEJ 
    
    double x0, x1;
    double eps = 1.0e-7;
    unsigned int counter = 0;
    cin >> x0;
    x1 = x0;

    do{
        x0 = x1;
        x1 = g(x0);
        counter++;
    }while( fabs(x1-x0) >= eps);

    cout.precision(8);
    cout<<"x1= "<<x1<<"\neps = " << eps << "\nlicznik  = " <<counter<<endl;
}





double f(double x){         // 3x + sinx - exp(x)       xe<0,1>
    return (3*x +sin(x) - exp(x));
}


double fp(double x){         // 3 + cosx - exp(x)
    return (3 + cos(x) - exp(x));
}

void zadanie2(){            // METODA NEWTONA

    double x0, x1;
    double eps = 1.0e-7;
    unsigned int counter = 0;
    x0 = 0;
    x1 = x0;

    do{
        x0=x1;
        x1 = (x0 - f(x0)/fp(x0));
        counter++;    
    }while(fabs(x1-x0)>=eps);
    cout.precision(8);
    cout<<"x1= "<<x1<<"\neps = " << eps << "\nlicznik  = " <<counter<<endl;
}


