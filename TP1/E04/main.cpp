#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

//Inicializacion del vector de numeros primos
vector<long long int> primos{2, 3, 5, 7};

mutex locker;

void printVector(vector<long long int> &vec){
    for (const auto &item : vec) {
        cout << item << ", ";
    }
    cout << endl;
}

void validate (int i, long long int start, long long int end, long long int primos_size) {
	//Recorro el rango que le ha sido asignado
	while (start < end) {
		//Variables de control
		int i = 0;
		bool es_primo = true;
		//Valido que sea divisible por todos los primos < sqrt(K)
		for (const auto primo : primos) {
			//Mientras el resto de la division sea distinta de 0, es primo
			es_primo = (start % primo) != 0;
			if(!es_primo){
				break;
			}
	    }
		//Si es primo, lo agrega a la lista
		if(es_primo){
			locker.lock();
			primos.push_back(start);
			locker.unlock();
		}
		//Valida el siguiente numero del rango
		start ++;
	}
}

int main () {
	
	//Rango minimo a analizar
	long long int init = 10;
	//Rango maximo a analizar
	long long int limit = 1000000;
	
	//Maximo ingresado por el usuario
	long long max = 1000;
	
	//Cantidad de hilos
	int thread_count = 64;
	//Array de hilos
	thread thread_array[thread_count];
	
	//Variables de control
	int max_itera = 2, i = 0;

	//Realiza el calculo
	while (i < max_itera){
		//Rango de busqueda
		long long int range = limit - init,
			//Rango para cada hilo
			validate_range = range / thread_count,
			//Inicio del rango actual
			init_current_range = init,
			//Cantidad de numeros que quedaron fuera del rango
			extra = range % thread_count;

		//Creo los hilos
		for (int i = 0; i < thread_count; i++){
			//Inicio del proximo rango
			long long int init_next_range = init_current_range + validate_range,
				//Longitud del vector en el momento
				primos_size = primos.size();
			if(extra > 0){
				init_next_range ++;
				extra --;
			}
			//Creo el hilo
			thread_array[i] = thread(validate, i, init_current_range, init_next_range, primos_size);
			
			//Avanzo al proximo rango de hilos
			init_current_range = init_next_range;
		}

		//Espero la ejecucion de los hilos
		for (int i = 0; i < thread_count; i++){
			if(thread_array[i].joinable() == true){
				thread_array[i].join();
			}
		}
		//Muestra los numeros primos encontrados
		printVector(primos);
		
		//El final ahora es el inicio
		init = limit;
		//El inicio incrementa exponencialmente
		limit = pow(init, 2);
		i++;
	}
    return 0;
}