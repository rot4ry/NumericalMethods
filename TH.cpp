#include <iostream>
#include <cmath>

using namespace std;

void print1DArray(double *array, int length);
void fillArray(double *array, int length);

int main(){

    //Dane zadania:
    //double A[5] = {0, 3, 1, 1, 2};
    //double B[5] = {2, 1, 2, 1, 2};
    //double C[5] = {2, 1, 4, 1, 0};
    //double D[5] = {2, 6, 4, 1, 4};

    int length = 5;
    
    double A[length];
    double B[length];
    double C[length];
    double D[length];
    
    cout<<"Wartosci tablicy A:"<<endl;
    fillArray(A, length);
    cout<<"Wartosci tablicy B:"<<endl;
    fillArray(B, length);
    cout<<"Wartosci tablicy C:"<<endl;
    fillArray(C, length);
    cout<<"Wartosci tablicy D:"<<endl;
    fillArray(D, length);


    double X[length];
    double BETA[length];
    double GAMMA[length];

    BETA[0] = -(C[0]/B[0]);
    GAMMA[0] = D[0]/B[0];

    for(int i=1; i<length; i++){
        BETA[i] = -(C[i]/(A[i]*BETA[i-1]+B[i]));
    }

    for(int i=0; i<length; i++){
        GAMMA[i] = (D[i]-A[i]*GAMMA[i-1])/(A[i]*BETA[i-1]+B[i]);
    }

    X[length-1] = GAMMA[length-1];

    for(int i=length-2; i>=0; i--){
        X[i] = BETA[i]*X[i+1]+GAMMA[i];
    }

    cout<<"Beta:"<<endl;
    print1DArray(BETA, length);

    cout<<"Gamma:"<<endl;
    print1DArray(GAMMA, length);
    
    cout<<"X:"<<endl;
    print1DArray(X, length);

    return 0;         
}


void print1DArray(double *array, int length){
    for(int i=0; i<length; i++){
        cout<<array[i]<<"\t";
    }
    cout<<endl;
}

void fillArray(double *array, int length){
    for(int i=0; i<length; i++){
        cin>>array[i];
    }
}