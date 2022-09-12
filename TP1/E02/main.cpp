#include <fstream>
#include <iostream>
#include <sys/time.h>

using namespace std;


int search(string patron, string texto){
    int count = 0;
    int exist;
    for (int i = 0; i < patron.length(); i++){
        exist = texto.find(patron, i);
        if(exist != string::npos){
            count += 1;
        }
    }
    return count;
}

int main () {
    timeval time1,time2;
    ifstream patrones, texto;
    string buffer;
    string patterns[32];

    //open files
    patrones.open("patrones.txt");
    texto.open("texto.txt");

    //get text
    getline(texto, buffer);
    //get pattern
    for (int i = 0; i < 32; i++){
        getline(patrones, patterns[i]);
    }
    //close files
    patrones.close();
    texto.close();


    //start timer
    gettimeofday(&time1, NULL);
    //search
    for (int i = 0; i < 32; i++){
        cout << "El patron " << patterns[i] << " se repite " << search(patterns[i], buffer) << " veces." << endl;
    }
    //stop timer
    gettimeofday(&time2, NULL);
    
    //shows the execution time
    cout << "Tiempo de ejecucion: " << double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000 << endl;
    return 0;
}
