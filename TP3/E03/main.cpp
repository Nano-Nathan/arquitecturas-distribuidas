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
    //Datos a enviar por el broadcast
    int n;
    
    if (rank == 0){
        cout << "Ingrese el tamaño de la matriz"
        cin >> n;

        //Cantidad de terminos que le toca a cada proceso
        int count_items = n / size;
        //Cantidad de patrones que sobran
        int extra = n % size;
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
    MPI_Bcast(&n, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(sender, 2, MPI_INT, receive, 2, MPI_INT, 0, MPI_COMM_WORLD);

    //Genera las matrices que le corresponde
    int idx = receive[1] - receive[0];
    float matriz_1[n][n];
    float matriz_2[n][idx];
    float local_result[n][idx];

    //Completa las matrices
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz_1[i][j] = 0.1;
            if(j < idx){
                matriz_2[i][j] = 0.2;
            }
        }
    }

    //Realiza el calculo
    float current_sum, partial_sum = 0;
    //Recorro las columnas de la matriz 2 y resultado
    for (int i = 0; i < idx; i++){
        //Recorro las filas de la matriz 1 y resultado
        for (int j = 0; j < n; j++){
            current_sum = 0;
            //Recorro las columnas de la matriz 1 y filas de la matriz 2
            for (int k = 0; k < n; k++){
                //Multiplica
                current_sum += matriz_1[j][k] * matriz_2[k][i];
            }
            //Guarda el resultado
            local_result[j][i] = current_sum;
            //Suma el resultado parcial al proximo global
            partial_sum += current_sum;
        }
    }

    //Se reunen los resultados
    float sum_per_processor[size];
    float global_result[n][n];
    MPI_Gather(&partial_sum, 1, MPI_FLOAT, sum_per_processor, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Gather(local_result, n * idx, MPI_FLOAT, global_result, n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        float global_sum = 0;
        //Suma los elementos de la matriz
        for (int i = 0; i < size; i++){
            global_sum += sum_per_processor[i];
        }
        //Muestra los resultados
        cout << "Sumatoria: " << global_sum << endl;
        //Matriz resultado
        cout << "Matriz resultado: " << endl;
        cout << "| " << global_result[0][0] << " ... " << global_result[0][n - 1] << " |" << endl;
        cout << "| " << global_result[n - 1][0] << " ... " << global_result[n - 1][n - 1] << " |" << endl;
    }

    //end mpi
	if(MPI_Finalize()!=MPI_SUCCESS){
		cout<<"Error finalizando MPI"<<endl;
		exit(1);
	}
    return 0;
}