#include <iostream>
#include<fstream>
#include <string>

using namespace std;

class Arquivo{
    string *matrizTimes;
    string *matrizMachine;
    string *matrizResultado;

};

int main(){
    
    int nLinhas = 15;
    ifstream ifs ("job.txt", ifstream::in);
    string primeiraLinha;
    string linha;
    int aux=0;
    string machines[3];
    string times[3];
    getline(ifs,primeiraLinha);
    while(getline(ifs,linha)) {
        if(linha.compare("Times")){
            getline(ifs,linha);
            for(int i=0; i<nLinhas;i++){
                getline(ifs,linha);
                times[aux] = times[aux].append(linha);
                times[aux] = times[aux].append("\n");
            }

        }
        if(linha.compare("Machines")){
            getline(ifs,linha);
            for(int i=0; i<nLinhas;i++){
                getline(ifs,linha);
                machines[aux] = machines[aux].append(linha);
                machines[aux] = machines[aux].append("\n");
            }
        }
        if(linha.compare(primeiraLinha)){
            aux+=1;
            if(aux>2)
                break;
        }
    }
    cout << aux << times[aux-1] << endl << machines[aux-1];

    ifs.close();

    return 0;
}
