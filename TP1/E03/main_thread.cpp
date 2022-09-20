#include <iostream>
#include <mutex>
#include <algorithm>
#include <thread>
#include <sys/time.h>

using namespace std;

const int n = 3000;
const int thread_count = 32;

//Rangos para cada hilo
pair<int, int> ranges[thread_count];

float matriz_1[n][n];
float matriz_2[n][n];
float result[n][n];
float suma_total;
mutex locker;

void multiplicate (int thread_idx) {
	//Suma total de las columnas asignadas
	float local_total = 0,
		//Suma parcial de la multiplicacion
		partial_result;
	//Recorro las columnas de la matriz 2
	for (int i = ranges[thread_idx].first; i < ranges[thread_idx].second; i++){
		//Recorro las filas de la matriz 1
		for(int j = 0; j < n; j++){
			partial_result = 0;
			//Recorro las columnas de la matriz 1 y las filas de la matriz 2
			for (int k = 0; k < n; k++){
				//Realizo el calculo
				partial_result += (matriz_1[j][k] * matriz_2[k][i]);
			}
			//Guardo el resultado
			locker.lock();
			result[j][i] = partial_result;
			locker.unlock();
			//Sumo el total local
			local_total += partial_result;
		}
	}
	locker.lock();
	suma_total += local_total;
	locker.unlock();
}

int main () {
	timeval time1,time2;
	thread thread_array[thread_count];

    //inicializo las matrices
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz_1[i][j] = 0.1;
            matriz_2[i][j] = 0.2;
        }
    }

	//Divido los calculos que realizara cada thread
	int thread_range = n / thread_count,
		extra = n % thread_count,
		start_range = 0,
		end_range = thread_range;
	
	//start timer
    gettimeofday(&time1, NULL);
	
	//Creo los hilos
	for (int i = 0; i < thread_count; i++){
		//Si sobran columnas, se agrega una a cada thread hasta terminar
		if(extra > 0){
			end_range++;
			extra--;
		}
		//Inicio del rango
		ranges[i].first = start_range;
		//Si el rango es mayor al tamaño de las matrices, acota el intervalo
		if(end_range > n){
			ranges[i].second = n;
		} else {
			ranges[i].second = end_range;
		}
		//Creo el hilo
		thread_array[i] = thread(multiplicate, i);

		//Paso al siguiente rango
		start_range = end_range;
		end_range += thread_range;
	}

	//Espero la ejecucion de los hilos
	for (int i = 0; i < thread_count; i++){
		if(thread_array[i].joinable() == true){
			thread_array[i].join();
		}
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