#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>

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
	char ip[20];
	obtener_IP(ip);
	cout << ip << endl;
	return 0;
}
