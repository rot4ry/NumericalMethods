#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

void fillMatrix(double **matrix, int dim){

    for(int verse = 0; verse < dim; verse++){
        for(int column = 0; column < dim; column++){
            cout << "A["<< verse << "]["<< column <<"] = ";
            cin >> matrix[verse][column];
        }
    }
}

int main(){

    int n;
    cout<<"Wymiar macierzy: ";
    cin >> n;

    double **matrix = new double *[n];
	
    for(int i = 0; i < n; i++){
        matrix[i] = new double[n];
    }

    fillMatrix(matrix, n);
    
	int sign = 1;
	double det = 1;
	
    for (int k = 0; k < n; k++){
		
        double max = matrix[k][k];
		int verse = k;

		for (int i = k; i < n; i++){
		    if ( abs(matrix[i][k] ) > abs(max)){
    		    max = matrix[i][k];
			    verse = i;
		    }
	    }
		    
        if (max == 0){
		    cout << "Wyznacznik = 0" << endl;
		    return 0;
	    }
	
        if (verse != k){
			
            sign *= -1;
			for (int j = 0; j < n; j++){
			
            	double temporary = matrix[k][j];
				matrix[k][j] = matrix[verse][j];
				matrix[verse][j] = temporary;
			}
		}

		for (int i = k + 1; i < n; i++){
			
            double temporary = matrix[i][k];
			for (int j = 0; j < n; j++){
				matrix[i][j] = matrix[i][j] - matrix[k][j] * temporary / max;
			}
		}
	}       

	for (int i = 0; i < n; i++)
	{
		det *= matrix[i][i];
	}
	det *= sign;
	
    cout << "Wyznacznik = " << det << endl;    
    return 0;
}
