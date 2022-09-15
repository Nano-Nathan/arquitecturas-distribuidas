#include <iostream>
#include <cmath>
#include <mutex>
#include <thread>
#include <sys/time.h>

using namespace std;

const int n = 3000;

float matriz_1[n][n];
float matriz_2[n][n];
float result[n][n];
float suma_total;
mutex await;

void multiplicate (int start, int end) {
	//float local_result[n][end-start];
	float local_total = 0;
	//Recorro las columnas de la matriz 2
	for (int i = start; i < end; i++){
		//Recorro las filas de la matriz 1
		for(int j = 0; j < n; j++){
			float partial_result = 0;
			//Recorro las columnas de la matriz 1 y las filas de la matriz 2
			for (int k = 0; k < n; k++){
				//Realizo el calculo
				partial_result += (matriz_1[j][k] * matriz_2[k][i]);
			}
			//Guardo el resultado
			await.lock();
			result[j][i] = partial_result;
			await.unlock();
			//Sumo el total local
			local_total += partial_result;
		}
	}
	suma_total += local_total;

	//Bloquea a los demas hilos
	//await.lock();
	//Recorro las columnas de la matriz
	//for (int i = start; i < end; i++){
	//	//Recorro las filas de la matriz
	//	for(int j = 0; j < n; j++){
	//		//Guardo el resultado
	//		result[j][i] = local_result[j][i - start];
	//	}
	//}
	//await.unlock();
	//Sumo al total
}

int main () {
	timeval time1,time2;
	int cant_thread = 32;

    //inicializo las matrices
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz_1[i][j] = 0.1;
            matriz_2[i][j] = 0.2;
        }
    }

	//start timer
    gettimeofday(&time1, NULL);

	//Divido los calculos que realizara cada thread
	int count_col = round(n / cant_thread),
		extra = n % cant_thread,
		i = 0;
	//Creo los hilos
	for (int j = 0; j < cant_thread; j++){
		int newValue = i + count_col;
		//Si sobran columnas, se agrega una a cada thread hasta terminar
		if(extra > 0){
			newValue++;
			extra--;
		}
		if(newValue > n){
			thread(multiplicate, i, n);
		} else {
			thread(multiplicate, i, newValue);
		}
		i = newValue;
	}

	//stop timer
    gettimeofday(&time2, NULL);

    //Resultado
	cout << "Sumatoria: " << suma_total << endl;
	cout << "Matriz resultado: " << endl;
	cout << "| " << result[0][0] << " ... " << result[0][n - 1] << " |" << endl;
	cout << "| " << result[n - 1][0] << " ... " << result[n - 1][n - 1] << " |" << endl;

	//shows the execution time
    cout << "Tiempo de ejecucion: " << double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000 << endl;
    return 0;
}