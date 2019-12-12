#include <iostream>
#include <cmath>

using namespace std;

void printMatrix(double **a, int height, int length){

    for(int i=0; i<height; i++){
        for(int j=0; j<length; j++){
            cout<<"|"<< a[i][j] << "|";
        }
        cout<<endl;
    }
    cout<<endl;
}

void fillMatrix(double **a, int height, int length){

    for(int i=0; i<height; i++){
        for(int j=0; j<length; j++){
            cout<<"A["<<i<<"]["<<j<<"]=";
            cin>>a[i][j];
        }
    }
}

void printResults(double **a, int height, int length){
    for(int i=0; i<height; i++){
        cout<<"|"<< a[i][length-1]<<"|"<<endl;
    }
}

int main(){
    
    int n;
    cout<<"Podaj ilość równań: ";
    cin >> n;
    int length = n+1;
    int height = n;

    double max;
    int r;

    double **matrix = new double *[length];    
    for(int i=0; i<length; i++){
        matrix[i] = new double[height];
    }

    fillMatrix(matrix, height, length);
    printMatrix(matrix, height, length);

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
            return 0;
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
    
    printResults(matrix, height, length);
    

    return 0;
}
