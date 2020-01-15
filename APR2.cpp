#include <iostream>
#include <cmath>

using namespace std;

double F(double x);
double P(double x, int k, double *ps);

double DELTA(double a, double b, int j);

double S(double a, double b, double EPS, int k, double *ps, double h = 0, int m = 1);
double M(double x, int k, double *ps);

void GaussJordan(double **matrix, int n);

double G(double x, int j);
double G_Integral(double a, double b, double EPS, int j, double h = 0, int m = 1);

int main(){
    
    double a, b;
    int k;

    double EPS = 1e-5;

    cout<<"Podaj lewą granicę przedziału:\ta = ";
    cin>>a;
    cout<<"Podaj prawą granicę przedziału:\tb = ";
    cin>>b;
    cout<<"Podaj stopień wielomianu:\tk = ";
    cin>>k;

    int length = k+2;
    int height = k+1;

    double **MUU = new double *[height];
    for(int i=0; i<height; i++){

        MUU[i] = new double [length];
    }

    for(int i=0; i<height; i++){
        
        for(int j=0; j<length; j++){
            
            if(j < length-1){
                
                MUU[i][j] = DELTA(a, b, j+i)/(j+i+1);
            }
            if(j==length-1){

                MUU[i][j]=G_Integral(a, b, EPS, i);
            }
        }
    }

    cout<<"\nUzupełniona macierz układu:"<<endl;
    for(int i=0; i<height; i++){

        for(int j=0; j<length; j++){

            cout<<MUU[i][j]<<"\t";
        }
        cout<<endl;
    }

    GaussJordan(MUU, k+1);

    cout<<"\nPo GJ"<<endl;
   
    for(int i=0; i<height; i++){

        for(int j=0; j<length; j++){

            cout<<MUU[i][j]<<"\t";
        }
        cout<<endl;
    }

    double P_factors[height];

    cout<<"\nWspółczynniki wielomianu P(x): "<<endl;
    for(int i=0; i<height; i++){

        P_factors[i] = MUU[i][length-1];
        cout<<"P["<<i<<"] = "<<P_factors[i]<<endl;
    }
    
    cout<<"Błąd aproksymacji wynosi S(k ="<<k+1<<") = "<<S(a, b, EPS, k+1, P_factors)<<" ~ "<<round(S(a, b, EPS, k+1, P_factors))<<"\n"<<endl;
    
    double myX;
    cout<<"Podaj x: ";
    cin>>myX;
    cout<<"P("<<myX<<") = "<<P(myX, k+1, P_factors)<<endl;

    return 0;
}


double F(double x){
//wartosc funkcji F
    return 2+x;
}

double P(double x, int k, double *ps){
//wartosc wielomianu P w danym punkcie x
    double value = 0;

    for(int i=0; i<k; i++){

        value += pow(x,i) * ps[i];
    }

    return value;
}

double DELTA(double a, double b, int j){
    
    int i = j + 1;
    return (pow(b,i)-pow(a,i));
}

double S(double a, double b, double EPS, int k, double *ps, double h, int m){     
//oblicza wartosc błędu aproksymacji
    double P_current = 0;
    double P_previous = 0;
    
    do{
    
        m *= 2;
        h = (b - a)/m;

        double OddSUM = 0;
        double EvenSUM = 0;

        P_previous = P_current;

        for (int i=0; i<m; i++){

            if (i%2 == 0)   EvenSUM += M(a + i*h, k, ps);
            else            OddSUM += M(a + i*h, k, ps);
        }   
        
        P_current = (h/3)*(M(a, k, ps) + M(a + (m-1)*h, k, ps) + 4*OddSUM + 2*EvenSUM);
    
    }while(fabs(P_current - P_previous) >= EPS);

    return P_current;
}

double M(double x, int k, double *ps){

    return F(x)-P(x, k, ps);
}


void GaussJordan(double **matrix, int n){

    double max;
    int r;

    for(int k=0; k<n; k++){

        max = matrix[k][k];
        r=k;

        for(int i=k; i<n; i++){
            if( fabs(matrix[i][k]) > fabs(max) ){
                max = matrix[i][k];
                r = i;
            }
        }

        if(max == 0){
            cout<<"Macierz układu osobliwa, det.A = 0"<<endl;
            break;
        }
        
        for(int j=k; j<n+1; j++){
            double temporary = matrix[k][j];
            matrix[k][j] = matrix[r][j];
            matrix[r][j] = temporary;
        }

        for(int j=k; j<n+1; j++){
            matrix[k][j] = matrix[k][j]/max;
        }

        for(int i=0; i<n; i++){
            
            if(i==k){
                continue;
            }
            else{
                double p = matrix[i][k];

                for(int j=k; j<n+1; j++){
                    matrix[i][j] = matrix[i][j] - p*matrix[k][j];
                }    
            }
        }
    }
}

double G(double x, int j){
//funkcja do całki

    return F(x) * pow(x,j);
}

double G_Integral(double a, double b, double EPS, int j, double h, int m){     
// zwraca wartość całki obliczaną metodą parabolową 

    double P_current = 0;
    double P_previous = 0;
    
    do{
    
        m *= 2;
        h = (b - a)/m;

        double OddSUM = 0;
        double EvenSUM = 0;

        P_previous = P_current;

        for (int i=0; i<m; i++){

            if (i%2 == 0)   EvenSUM += G(a + i*h, j);
            else            OddSUM += G(a + i*h, j);
        }   
        
        P_current = (h/3.)*(G(a, j) + G(a + (m-1)*h, j) + 4*OddSUM + 2*EvenSUM);
    
    }while(fabs(P_current - P_previous) >= EPS);

    return P_current;
}