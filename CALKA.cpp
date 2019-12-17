#include <iostream>
#include <cmath>

using namespace std;
typedef void MyType;

double F(double x);
MyType MetTRAPEZOW(double a, double b, int m, double h, double EPS);
MyType MetPARABOL(double a, double b, int m, double h, double EPS);

int main(){

    double a = 0, b = 5;
    double EPS = 10e-5;
    int m = 1;
    double h = 0;
    
    MetTRAPEZOW(a, b, m, h, EPS);
    MetPARABOL(a, b, m, h, EPS);
    return 0;
}

double F(double x){

    return sin(sqrt(x));
}

MyType MetTRAPEZOW(double a, double b, int m, double h, double EPS){
    
    double T_current = 0;
    double T_previous = 0;
    int it = 0;
    
    do{

        it++;
        m *= 2;
        h = (b - a)/m;
        
        double Y[m];
        
        T_previous = T_current;
        double SUMA = 0;

        for(int i=0; i<m; i++){
            
            Y[i] = F(a + i*h);
            SUMA += Y[i];
        }

        T_current = (h/2.)*(F(a) + F(b) + 2*SUMA);
        
    }while(fabs(T_current - T_previous) >= EPS);

    cout.precision(14);
    cout<<"Metoda trapezowa:"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"Wartosc calki = "<< T_current <<endl;
    cout<<"Po "<< it <<" iteracjach z dokladnoscia EPS = "<< EPS <<endl; 
    cout<<"---------------------"<<endl;
}

MyType MetPARABOL(double a, double b, int m, double h, double EPS){

    double P_current = 0;
    double P_previous = 0;
    int it = 0;
    
    do{
    
        it++;
        m *= 2;
        h = (b - a)/m;

        double OddSUM = 0;
        double EvenSUM = 0;

        double Y[m];
        P_previous = P_current;

        for (int i=0; i<m; i++){

            Y[i] = F(a + i*h);
        
            if (i%2 == 0)   EvenSUM += Y[i];
            else            OddSUM +=Y[i];
        }   
     
        P_current = (h/3)*(Y[0] + Y[m-1] + 4*OddSUM + 2*EvenSUM);
    
    }while(fabs(P_current - P_previous) >= EPS);

    cout.precision(14);
    cout<<"Metoda parabolowa:"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"Wartosc calki = "<< P_current <<endl;
    cout<<"Po "<< it <<" iteracjach z dokladnoscia EPS = "<< EPS <<endl; 
    cout<<"---------------------"<<endl;
}