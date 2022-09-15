#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <thread>

using namespace std;



void search(int idx, string patron, string texto){
    int n = texto.length();
    int q = 0;
    int count = 0;
    
    //calcule to pi
    int m = patron.length();
    int array_pi[m];
    string prefixs[m];

    //get prefx
    for (int i = 0; i < m; i++){
        prefixs[i] = patron.substr(0, i + 1);
    }
    
    //compare
    for (int i = 0; i < m; i++){
        string suf = patron.substr(0, i + 1);
        int maxSuf = 0;
        for (int j = 0; j < i; j++){
            string pref = prefixs[j];
            if(suf.find(pref, i - j) != string::npos){
                maxSuf = j + 1;
            }
        }
        array_pi[i] = maxSuf;
    }

    for (int i = 0; i < n; i++){
        while (q > 0 and patron[q+1] != texto[i]){
            q = array_pi[q];
        }
        if(patron[q+1] == texto[i]){
            q = q + 1;
        }
        if(q == m){
            count += 1;
            q = array_pi[q];
        }
    }
    
    
    cout << "El patron " << idx << " se repite " << count << " veces." << endl;
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

    //save size
    //dim = buffer.length();

    //start timer
    gettimeofday(&time1, NULL);
    //search
    for (int i = 0; i < 1; i++){
        search(i, patterns[i], buffer);
    }
    //stop timer
    gettimeofday(&time2, NULL);
    
    //shows the execution time
    cout << "Tiempo de ejecucion: " << double(time2.tv_sec - time1.tv_sec) + double(time2.tv_usec - time1.tv_usec)/1000000 << endl;
    return 0;
}
