#include <iostream>
#include <cmath>
#include <sys/time.h>

using namespace std;

const int n = 3000;

float matriz_1[n][n];
float matriz_2[n][n];
float result[n][n];

void multiplicate () {
	//Recorro las columnas de la matriz 2
	for (int i = 0; i < n; i++){
		//Recorro las filas de la matriz 1
		for(int j = 0; j < n; j++){
			float partial_result = 0;
			//Recorro las columnas de la matriz 1 y las filas de la matriz 2
			for (int k = 0; k < n; k++){
				//Realizo el calculo
				partial_result += (matriz_1[j][k] * matriz_2[k][i]);
			}
			//Guardo el resultado
			result[j][i] = partial_result;
		}
	}
}

void add () {
	float iResult = 0;
	for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            iResult += result[i][j];
        }
    }
	cout << "Sumatoria: " << iResult << endl;
}

int main () {
	timeval time1,time2;

    //inicializo las matrices
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz_1[i][j] = 0.1;
            matriz_2[i][j] = 0.2;
        }
    }

	//start timer
    gettimeofday(&time1, NULL);

	//Realizo la multiplicacion
	multiplicate();

	//Sumo el resultado
	add();

	//stop timer
    gettimeofday(&time2, NULL);

    //Matriz resultado
	cout << "Matriz resultado: " << endl;
	cout << "| " << result[0][0] << " ... " << result[0][n - 1] << " |" << endl;
	cout << "| " << result[n - 1][0] << " ... " << result[n - 1][n - 1] << " |" << endl;

	//shows the execution time
    cout << "Tiempo de ejecucion: " << double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000 << endl;
    return 0;
}