#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <mpi.h>
using namespace std;

int main () {
    timeval time1,time2;
	int rank, size;

	//init mpi
	if(MPI_Init(NULL, NULL)!=MPI_SUCCESS){
		cout<<"Error iniciando MPI"<<endl;
		exit(1);
	}

	//get rank and size
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //Datos a enviar
    int sender[2 * size];
    //Datos recibidos
    int receive[2];
    
    if (rank == 0){
    }

    //Se esparcen los datos
    MPI_Scatter(sender, 2, MPI_INT, receive, 2, MPI_INT, 0, MPI_COMM_WORLD);

    long double current_result = 0;
    long double result[size];
    //Se reunen los resultados
    MPI_Gather(&current_result, 1, MPI_LONG_DOUBLE, result, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank == 0){
    }

    //end mpi
	if(MPI_Finalize()!=MPI_SUCCESS){
		cout<<"Error finalizando MPI"<<endl;
		exit(1);
	}
    return 0;
}