#include <iostream>
#include <iomanip>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>
using namespace std;

long double x = 1500000;

long double f (int n){
    return 2*(long double)(n) + 1;
}

long double ln (int n){
    //Calcula la parte 2*n + 1
    long double fn = f(n);
    //Realiza el calculo del termino
    long double result = (1 / fn) * pow((x - 1)/(x + 1), fn);
    //Retorna el valor
    return result;
}


int main () {
    timeval time1,time2;
	int rank, size;
    //Cantidad de terminos a calcular
    int items = 10000000;

	//init mpi
	if(MPI_Init(NULL, NULL)!=MPI_SUCCESS){
		cout<<"Error iniciando MPI"<<endl;
		exit(1);
	}

	//get rank
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //Datos a enviar
    int sender[2 * size];
    //Datos recibidos
    int receive[2];
    
    //Comienza el conteo del tiempo
    gettimeofday(&time1, NULL);
    
    if (rank == 0){
        //Cantidad de terminos que le toca a cada proceso
        int count_items = items / size;
        //Cantidad de items que sobran
        int extra = items % size;
        
        //Completa el array
        int i = 0, start = 0, end = count_items;
        while (i < 2 * size){
            if(extra > 0){
                end += 1;
                extra--;
            }
            sender[i] = start;
            sender[i + 1] = end;

            i += 2;
            start = end;
            end += count_items;
        }
    }

    //Se esparcen los datos
    MPI_Scatter(sender, 2, MPI_INT, receive, 2, MPI_INT, 0, MPI_COMM_WORLD);

    long double current_result = 0;
    long double result[size];

    //Calcula los terminos
    for (int i = receive[0]; i < receive[1]; i++){
        current_result += ln(i);
    }
    //Termina el conteo del tiempo
    gettimeofday(&time2, NULL);
    //Muestra el tiempo de ejecucion
    string message = "\nTiempo de ejecucion para el proceso " + to_string(rank) + ": " + to_string(double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000);
    cout << message << endl;

    //Se reunen los resultados
    MPI_Gather(&current_result, 1, MPI_LONG_DOUBLE, result, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    if(rank == 0){
        //Calcula el resultado final
        long double final_result = 0;
        for (int i = 0; i < size; i++){
            final_result += result[i];
        }
        //Muestra el resultado
        cout << "\nEl resultado final es: " << setprecision(15) << 2 * final_result << endl;
    }

    //end mpi
	if(MPI_Finalize()!=MPI_SUCCESS){
		cout<<"Error finalizando MPI"<<endl;
		exit(1);
	}
    return 0;
}