#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <mpi.h>
#include <list>
using namespace std;

int search(string patron, string texto){
    int count = 0;
    int i = texto.find(patron);
    while (i != string::npos){
        count += 1;
        i = texto.find(patron, i + 1);
    }
    return count;
}

int main () {
    timeval time1,time2;
	int rank, size;
    //Cantidad de patrones a buscar
    int count_patterns = 32;

	//init mpi
	if(MPI_Init(NULL, NULL)!=MPI_SUCCESS){
		cout<<"Error iniciando MPI"<<endl;
		exit(1);
	}

	//get rank and size
	MPI_Comm_rank(MPI_COMM_WORLD,&rank  );
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //Datos a enviar
    int sender[2 * size];
    //Datos recibidos
    int receive[2];
    //Datos a enviar por el broadcast
    string text, patterns[count_patterns];
    //Comienza el conteo del tiempo
    gettimeofday(&time1, NULL);
    if (rank == 0){
        //Cantidad de terminos que le toca a cada proceso
        int count_items = count_patterns / size;
        //Cantidad de patrones que sobran
        int extra = count_patterns % size;
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

        //Abre los archivos
        ifstream texto, patrones;
        texto.open("texto.txt");
        patrones.open("patrones.txt");
        //Lee la data
        getline(texto, text);
        for (int i = 0; i < count_patterns; i++){
            getline(patrones, patterns[i]);
        }
        //Cierra los archivos
        texto.close();
        patrones.close();
    }

    //Se esparcen los datos
    MPI_Bcast(&text, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(patterns, count_patterns, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(sender, 2, MPI_INT, receive, 2, MPI_INT, 0, MPI_COMM_WORLD);
    //Resultados
    string message_result;
    for (int i = receive[0]; i < receive[1]; i++){
        message_result = "El patron " + to_string(i) + " se repite " + to_string(search(patterns[i], text)) + " veces";
        cout << message_result << endl;
    }
    //Termina el conteo del tiempo
    gettimeofday(&time2, NULL);
    //Muestra el tiempo de ejecucion
    string message = "\nTiempo de ejecucion para el proceso " + to_string(rank) + ": " + to_string(double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000);
    cout << message << endl;

    //end mpi
	if(MPI_Finalize()!=MPI_SUCCESS){
		cout<<"Error finalizando MPI"<<endl;
		exit(1);
	}
    return 0;
}