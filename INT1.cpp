#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void print2DArray(double **array, int height, int length);
void print1DArray(double *array, int length);

void solveArray(double **inputArray, double *outputArray, int n);
void GaussJordan(double **matrix, int n);

void P(double *A, int n, double X);

int main(){
    
    int n = 5;                                      //stopień wielomianu

    double Xi[] = {1.5, 2, 2.5, 3.5, 3.8, 4.1};
    double Yi[] = {2., 5., -1., 0.5, 3., 7.};
    double W[n+1];                                  //macierz współczynników
    
    double **MRU = new double *[n+2];               //macierz rozszerzona układu
    for(int i = 0; i < n+2; i++){
        MRU[i] = new double [n+1];
    }
        
    for(int verse = 0; verse < n+1; verse++){
        for(int column = 0; column < n+2; column++){
                
            if(column == n+1) { MRU[verse][column] = Yi[verse]; }    
            else{ MRU[verse][column] = pow(Xi[verse], column); }
        }
    }

    cout<<"Macierz rozszerzona układu: "<<endl;
    print2DArray(MRU, n+1, n+2);
    
    solveArray(MRU, W, n+1);

    cout<<"Macierz współczynników Ai: "<<endl;
    print1DArray(W, n+1);

    cout<<"\nPodaj punkt, dla którego wyliczyć wartość: ";
    double myX;
    cin >> myX;

    P(W, n+1, myX);

    return 0;
}

void solveArray(double **inputArray, double *outputArray, int n){
    
    GaussJordan(inputArray, n);
    cout<<endl;
    print2DArray(inputArray, n, n+1);

    for(int i=0; i<n; i++){
        outputArray[i] = inputArray[i][n];
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


void print2DArray(double **array, int height, int length){
    
    for(int a=0; a<height; a++){
        for(int b=0; b<length; b++){
            cout<< array[a][b] <<"\t";
        }
        cout<<endl;
    }
}

void print1DArray(double *array, int length){

    for(int i=0; i < length; i++){
        cout<< array[i] <<"\t";
    }
    cout<<endl;
}

void P(double *A, int n, double X){
    
    double value = 0;

    for(int i=0; i<n; i++){
        value += A[i] * pow(X,i);
    }

    cout<< "P(" << X <<") = " << value <<endl;
}
