#include <iostream>
#include <cmath>

using namespace std;

double S(int n, int m, double *Xi, double *Yi, double *Ai);
double P(double x, double *Ai, int m);

double ArrayElementValue(int j_vertical, double *Xi, int n); 
double ExtendedArrayElementValue(int j_horizontal, double *Xi, double *Yi, int n);  
void GaussJordan(double **matrix, int n);

void printArray(double *array, int length);
void printArray(double **array, int height, int length);

int main(){

    int n = 6;  
    int m;      
    
    do{
        cout<<"Podaj stopien wielomianu aproksymującego: ";
        cin>>m;

    }while(m>=n || m<=0);
    
    double Xi[n] = {    1.  , 1.5   , 2.    , 4.    , 6.    , 7.    };
    double Yi[n] = {    -0.7, -0.35 , -0.05 , 1.45  , 3.95  , 5.35  };

    double Ai[m+1];
    
    double **MRU = new double *[m+1];
    for(int i=0; i<m+1; i++){
        MRU[i] = new double [m+2];
    }
    
    for(int height=0; height<m+1; height++){
        for(int length=0; length<m+2; length++){
            
            MRU[height][length] = ArrayElementValue(length + height, Xi, n); 
            
            if(length==m+1){
                MRU[height][length] = ExtendedArrayElementValue(height, Xi, Yi, n);
            }
        }
    }

    GaussJordan(MRU,  m+1);

    for(int i=0; i<m+1; i++){
        Ai[i] = MRU[i][m+1];    
    }

    printArray(Ai,m+1);
    
    cout<<"Wartość funkcji błędu: "<< S(n, m, Xi, Yi, Ai) <<endl;
    
    double myX;
    cout<<"Podaj X: ";
    cin>>myX;
    cout<<"P("<< myX <<")= "<< P(myX, Ai, m) <<endl;
}



double ArrayElementValue(int j_vertical, double *Xi, int n){
    
    double result = 0;
    
    for(int i=0; i<n; i++){
        result += pow(Xi[i], j_vertical);
    }
    return result;
}

double ExtendedArrayElementValue(int j_horizontal, double *Xi, double *Yi, int n){
    
    double result = 0;
    
    for(int i=0; i<n; i++){
        result += Yi[i] * pow(Xi[i], j_horizontal);
    }
    return result;
}

double S(int n, int m, double *Xi, double *Yi, double *Ai){
    
    double result = 0;
    
    for(int j=0; j<n; j++){
        
        result += pow((P(Xi[j], Ai,m)-Yi[j]),2);
    }
    return result;
}

double P(double x, double *Ai, int m){
    
    double result = 0;

    for(int i=0; i<m+1; i++)
    {
        result += Ai[i]*pow(x,i);
    }
    return result;
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
    
    cout<<"Macierz współczynników:\n";
    for(int i=0; i<length; i++){
        cout<<"A"<<i<<" = "<< array[i]<<endl;
    }
}

void printArray(double **array, int height, int length){

    for(int i=0; i<height; i++){
        for(int j=0; j<length; j++){
            cout<<array[i][j]<<"\t";
        }
        cout<<endl;
    }
}