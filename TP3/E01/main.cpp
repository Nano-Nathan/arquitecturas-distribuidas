#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <mpi.h>

using namespace std;

void obtener_IP(char *respuesta){  
	int mi_socket=socket(AF_INET,SOCK_STREAM,0);
	if(mi_socket==0){
		cout<<"Error creando el socket"<<endl;
	}
	struct sockaddr_in servidor_addr, my_addr;
	servidor_addr.sin_family = AF_INET;
	servidor_addr.sin_addr.s_addr = inet_addr("179.0.132.58"); 
	servidor_addr.sin_port = htons(80);
	if(connect(mi_socket, (struct sockaddr *)&servidor_addr, (socklen_t)sizeof(servidor_addr))<0){
		cout<<"\nError funcion Connect"<<endl;
		exit(1);
	}
	socklen_t len = sizeof(my_addr);
	getsockname(mi_socket, (struct sockaddr *) &my_addr, &len);
	inet_ntop(AF_INET, &my_addr.sin_addr, respuesta, 40); 
	close(mi_socket);  
	return;
}

int main () {
	char ip[20], name[100];
	int rank, size, length;


	//init mpi
	if(MPI_Init(NULL, NULL)!=MPI_SUCCESS){
		cout<<"Error iniciando MPI"<<endl;
		exit(1);
	}

	//get rank, size, ip and processor name
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Get_processor_name(name,&length);
	obtener_IP(ip);
	
	//getName
	cout << "Hola Mundo! soy el proceso " << rank << " de " << size << " corriendo en la máquina " << name <<" IP = " << ip << endl;

	if(MPI_Finalize()!=MPI_SUCCESS){
		cout<<"Error finalizando MPI"<<endl;
		exit(1);
	}
	return 0;
}
