#include <iostream>
#include <iomanip>
#include <math.h>
#include <sys/time.h>
#include <thread.h>
using namespace std;

long double result = 0;

long double f (long int n){
    return 2*n + 1;
}

void inThread (long double x, long double start, long double end){
	long double result_local = 0;
	for (long int n = start; n < end ; n++){
		//Calcula la parte 2*n + 1
		long double fn = f(n);
		//Realiza el calculo interno de la serie
		result_local += (1 / fn) * pow((x - 1)/(x + 1), fn);
	}
	result += result_local;
}

void ln (long double x, bool useThread){
    timeval time1,time2;
    thread aThreads[32];
    long double start = 0, end = 320000;

    //Comienza el conteo del tiempo
    gettimeofday(&time1, NULL);

    //Serie de taylor:
    //Crea los hilos
    for (int i = 0; i < 32; i++){
        aThreads[i] = thread(inThread, x, start, end);
        start += 320000;
        end += 320000;
    }
    
    //Espera la ejecucion de los hilos
    for (int n = 0; n < 32; n++){
    	if(aThreads[n].joinable() == true){
    		aThreads[n].join();
    	}
    	//cout << result << endl;
    }

    //Termina el conteo del tiempo
    gettimeofday(&time2, NULL);

    //Muestra el tiempo de ejecucion
    cout<<"Tiempo de ejecucion: "<<double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000<<endl;
}


int main () {
    //Con paralelismo
    ln(1500000, false);
    cout << setprecision(15) << 2 * result << endl;
    return 0;
}
