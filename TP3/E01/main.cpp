#include <iostream>
#include <iomanip>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>
using namespace std;

long double f (long int n){
    return 2*n + 1;
}

long double ln (long double x){
    timeval time1,time2;
    long double result = 0, n = 0;

    //Comienza el conteo del tiempo
    gettimeofday(&time1, NULL);

    //Serie de taylor:
    while (n < 10000000){
        //Calcula la parte 2*n + 1
        long double fn = f(n);
        //Realiza el calculo interno de la serie
        result += (1 / fn) * pow((x - 1)/(x + 1), fn);
        //Pasa al siguiente termino
        n++;
    }
    //Termina el calculo
    result = 2 * result;

    //Termina el conteo del tiempo
    gettimeofday(&time2, NULL);

    //Muestra el tiempo de ejecucion
    cout << "Tiempo de ejecucion: " << double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000 << endl;

    //Retorna el valor
    return result;
}


int main (int argc, char** argv) {
	int rank, size, total;

	//init mpi
	if(MPI_Init(NULL, NULL)!=MPI_SUCCESS){
		cout<<"Error iniciando MPI"<<endl;
		exit(1);
	}

	//get rank
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Scatter(&total, 1, MPI_LONG_DOUBLE, void*recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);


    //end mpi
	if(MPI_Finalize()!=MPI_SUCCESS){
		cout<<"Error finalizando MPI"<<endl;
		exit(1);
	}

    //Muestro resultados
    cout << setprecision(15) << ln(1500000, false) << endl;
    return 0;
}