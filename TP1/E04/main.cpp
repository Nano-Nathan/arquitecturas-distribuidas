#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <sys/time.h>

using namespace std;

//Inicializacion del vector de numeros primos
vector<long long int> primos{2, 3, 5, 7};
long long int vector_size;

//Cantidad de hilos
int const thread_count = 12;

//Rangos para cada hilo
pair<long long int, long long int> ranges[thread_count];

//Variables de control
mutex locker;
const int max_itera = 4;

bool esPrimo (long long int number) {
	bool es_primo = true;
    int i = 0;
    while (i < vector_size && es_primo){
		//Mientras el resto de la division no es 0, es primo
		es_primo = (number % primos.at(i)) != 0;
        i++;
    }
	//Retorna el valor
	return es_primo;
}

void validate (int thread_idx) {
	long long int current_number = ranges[thread_idx].first;
	bool es_primo;
	//Recorro el rango que le ha sido asignado
	while (current_number < ranges[thread_idx].second) {
		//Valida si es primo
		es_primo = esPrimo(current_number);
		//Si es primo, lo agrega a la lista
		if(es_primo){
			locker.lock();
			primos.push_back(current_number);
			locker.unlock();
		}
		//Valida el siguiente numero del rango
		current_number ++;
	}
}

int main () {
	timeval time1,time2;
	long long int range, thread_range, start_range, end_range, extra,
	//Inicio del rango a analizar
	init = 10,
	//Fin del rango a analizar
	limit = 100,
	//Limite del usuario
	maximum;
	cout << "Ingrese un maximo: ";
	cin >> maximum;

    //Array de hilos
    thread thread_array[thread_count];

	//start timer
	gettimeofday(&time1, NULL);
	//Realiza el calculo
	int i = 0;
	while ((i < max_itera) && init < maximum){
		//Si el limite es mayor al maximo ingresado por el usuario
		if(limit > maximum){
			//Acota el intervalo
			limit = maximum;
		}
		
		//Rango de busqueda
		range = limit - init;
		//Rango para cada hilo
		thread_range = range / thread_count;
		//Cantidad de numeros que quedaron fuera del rango
		extra = range % thread_count;
		//Inicio del rango actual
		start_range = init;
		//Fin del rango actual
		end_range = init + thread_range;

		//Longitud del vector en el momento
		vector_size = primos.size();

		//Creo los hilos
		for (int i = 0; i < thread_count; i++){
			//Si quedaron numeros por fuera, lo indica
			if(extra > 0){
				end_range ++;
				extra --;
			}
			//Guarda los rangos
			ranges[i].first = start_range;
			ranges[i].second = end_range;
			//Creo el hilo
			thread_array[i] = thread(validate, i);
			
			//Avanzo al proximo rango de hilos
			start_range = end_range;
			end_range += thread_range;
		}

		//Espero la ejecucion de los hilos
		for (int i = 0; i < thread_count; i++){
			if(thread_array[i].joinable() == true){
				thread_array[i].join();
			}
		}
		
		//El final ahora es el inicio
		init = limit;
		//El inicio incrementa exponencialmente
		limit = pow(init, 2);
		i++;
	}
	//stop timer
    gettimeofday(&time2, NULL);
    //Muestra los numeros primos encontrados
    sort(primos.begin(), primos.end());
    long long int size_total = primos.size();
    cout << endl << "Cantidad de numeros primos: " << size_total << endl << endl;
    cout << "Ultimos 5 primos: " << endl;
    for (int i = size_total - 5; i < size_total; i++){
        cout << primos.at(i) << ", ";
    }
    cout << endl << endl;
	//shows the execution time
    cout << "Tiempo de ejecucion: " << double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000 << endl;
    return 0;
}