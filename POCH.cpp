#include <iostream>
#include <math.h>

using namespace std;

double F(double x);
void RSP(double x, double h, double i);
void RSC(double x, double h, double i);
void RST(double x, double h, double i);

int main(){
    double x=1;
    double h=1e-4;
    double i=0;
    cout.precision(10);
    cout<<"h = "<<h<<endl;
    RSP(x,h,i);
    RSC(x,h,i);
    RST(x,h,i);
    return 0;
}

double F(double x){
    return exp(-0.5*x)*sin(5*M_PI*x);
}

void RSP(double x, double h, double i){   //różnice skończone w przód
    cout<<"RSP:"<<endl;
    

    cout<<"f'("<<x<<") = "<<    (-F(x+(i+2)*h)+4*F(x+(i+1)*h)-3*F(x+i*h))/(2*h) <<endl;
    cout<<"f''("<<x<<") = "<<   (-F(x+(i+3)*h)+4*F(x+(i+2)*h)-5*F(x+(i+1)*h)+2*F(x+i*h))/pow(h,2) <<endl;
    cout<<"f'''("<<x<<") = "<<  (-3*F(x+(i+4)*h)+14*F(x+(i+3)*h)-24*F(x+(i+2)*h)+18*F(x+(i+1)*h)-5*F(x+i*h))/(2*pow(h,3)) <<endl;
    cout<<endl;
}

void RST(double x, double h, double i){   //różnice skończone w tył
    cout<<"RST:"<<endl;
    
    cout<<"f'("<<x<<") = "<< (3*F(x+i*h)-4*F(x+(i-1)*h)+F(x+(i-2)*h))/(2*h) <<endl;
    cout<<"f''("<<x<<") = "<< (2*F(x+i*h)-5*F(x+(i-1)*h)+4*F(x+(i-2)*h)-F(x+(i-3)*h))/pow(h,2) <<endl;//pow(h,3)?
    cout<<"f'''("<<x<<") = "<< (5*F(x+i*h)-18*F(x+(i-1)*h)+24*F(x+(i-2)*h)-14*F(x+(i-3)*h)+3*F(x+(i-4)*h))/(2*pow(h,3)) <<endl;
    cout<<endl;
}

void RSC(double x, double h, double i){   //różnice skończone centralne
    cout<<"RSC:"<<endl;
    
    cout<<"f'("<<x<<") = "<< (F(x+(i+1)*h)-F(x+(i-1)*h))/(2*h) <<endl;
    cout<<"f''("<<x<<") = "<< (F(x+(i+1)*h)-2*F(x+i*h)+F(x+(i-1)*h))/pow(h,2) <<endl;
    cout<<"f'''("<<x<<") = "<< (F(x+(i+2)*h)-2*F(x+(i+1)*h)+2*F(x+(i-1)*h)-F(x+(i-2)*h))/(2*pow(h,3)) <<endl;
    cout<<endl;
}