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
	float local_result[n][end-start];
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
			local_result[j][i - start] = partial_result;
		}
	}

	//Bloquea a los demas hilos
	await.lock();
	//Recorro las columnas de la matriz
	for (int i = start; i < end; i++){
		//Recorro las filas de la matriz
		for(int j = 0; j < n; j++){
			//Guardo el resultado
			result[j][i] = local_result[j][i - start];
		}
	}
	await.unlock();
}

void add (int start, int end) {
	float suma_local = 0;
	for (int i = start; i < end; i++){
        for (int j = 0; j < n; j++){
            suma_local += result[i][j];
        }
    }
	suma_total += suma_local;
}

int main () {
	timeval time1,time2;
	thread array_thread[32];

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
	int count_col = round(n / 32),
		extra = n % 32,
		i = 0;
	//Creo los hilos
	for (int j = 0; j < 32; j++){
		int newValue = i + count_col;
		//Si sobran columnas, se agrega una a cada thread hasta terminar
		if(extra > 0){
			newValue++;
			extra--;
		}
		if(newValue > n){
			array_thread[i] = thread(multiplicate, i, n);
		} else {
			array_thread[i] = thread(multiplicate, i, newValue);
		}
		i = newValue;
	}
	//Espero la ejecucion de los hilos
    for (int j = 0; j < 32; j++){
    	if(array_thread[i].joinable() == true){
    		array_thread[i].join();
    	}
    }

	//Sumo el resultado
	i = 0;
	extra = n % 32;
	for(int j = 0; j < 32; j++){
		int newValue = i + count_col;
		//Si sobran columnas, se agrega una a cada thread hasta terminar
		if(extra > 0){
			newValue++;
			extra--;
		}
		if(newValue > n){
			array_thread[i] = thread(add, i, n);
		} else {
			array_thread[i] = thread(add, i, newValue);
		}
		i = newValue;
	}
	//Espero la ejecucion de los hilos
    for (int j = 0; j < 32; j++){
    	if(array_thread[i].joinable() == true){
    		array_thread[i].join();
    	}
    }

	cout << "Sumatoria: " << suma_total << endl;

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