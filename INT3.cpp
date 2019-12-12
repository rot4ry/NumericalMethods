#include <iostream>
#include <cmath>

using namespace std;

double F(double x);
void createNodes(double *matrix, int length, double left, double h);
void GaussJordan(double **matrix, int n);

void printArray(double *array, int length);
void printArray(double **array, int height, int length);


int main(){

    double ALFA = 0.5;  /*f'(-1)*/ 
    double BETA = -0.5; /*f'(1)*/ 
    
    int n = 10;
    double leftBorder = -1.0;
    double rightBorder = 1.0;
    
    double **MRU = new double *[n];
    for(int i=0; i<n; i++){
        MRU[i] = new double[n+1];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j)    MRU[i][j] = 4;
            else if((i==0 && j==1) | (i==n-1 && j==n-2))    MRU[i][j] = 2;
            else if(j == i-1 | i == j-1)    MRU[i][j] = 1;
        }
    }

    double h = (fabs(rightBorder) + fabs(leftBorder)) / n;
    double nodes[n];        //macierz węzłów
    createNodes(nodes, n, leftBorder, h);    
 
    for(int i=0; i<n; i++){ 
        
        if(i==0)        MRU[i][n] = 1./(1+pow(nodes[i], 2) + (1./3*h*ALFA));
        
        else if(i==n-1) MRU[i][n] = 1./(1+pow(nodes[i], 2) - (1./3*h*BETA));
                        
        else            MRU[i][n] = F(nodes[i]);
    }
    
    GaussJordan(MRU, n);
    
    double A[n+3];          //macierz współczynników
    for(int i=1; i<n+1; i++){
        A[i] = MRU[i-1][n];
    }
    A[0] = A[2] - 1./3*h*ALFA;
    A[n+1] = A[n-1] + 1./3*h*BETA;


    double myX, m, Xm, t;
    
    cout<<"Podaj wartosc X: ";
    cin>>myX;

    m = myX == rightBorder ? n-1 : (int)(floor((myX - leftBorder)/h));

    Xm = leftBorder + m * h;    

    t = myX != rightBorder ? ((myX - Xm)/h) : 1;

    int M = (int)m;

    double result = A[M] * pow(1-t, 3) + A[M+1] * ((pow(2-t, 3)) - 4 * pow(1-t, 3)) + (A[M+2] * ((pow(1+t, 3) - 4 * pow(t, 3)))) +A[M+3] * pow(t, 3); 
    
    for(int i=0; i<n+3; i++){
        cout<<"A["<<i<<"] = "<< A[i] <<endl;
    }
    cout<<"P("<<myX<<") = "<< result <<endl;
    return 0;
}

double F(double x){

    return 1.0/(1+pow(x,2));
}

void createNodes(double *matrix, int length, double left, double h){
    
    for(int i=0; i<length; i++){
        matrix[i] = left + h * i;
    }
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

void printArray(double *array, int length){
    
    for(int i=0; i<length; i++){
        cout<<i<<" = "<< array[i]<<endl;
    }
}

void printArray(double **array, int height, int length){

    for(int i=0; i<height; i++){
        for(int j=0; j<length; j++){
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
}