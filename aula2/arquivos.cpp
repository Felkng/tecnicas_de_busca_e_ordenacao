#include <iostream>
#include<fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class Arquivo{
public:
    int **matrizTimes;
    int **matrizMachine;
    int **matrizResultado;
    
};

int main(){
    
    int nLinhas = 15;
    ifstream ifs ("job.txt", ifstream::in); // abre o arquivo
    string primeiraLinha;
    string linha;
    int aux=0; //contador de matrizes
    int entradas = 10; //quantidade de matrizes
    getline(ifs,primeiraLinha); // pega a primeira linha
    string num = "";
    Arquivo arq[entradas];


    for (int i = 0; i < entradas; i++) {
        arq[i].matrizMachine = new int*[nLinhas];
        arq[i].matrizTimes = new int*[nLinhas];
        arq[i].matrizResultado = new int*[nLinhas];
        for (int j = 0; j < nLinhas; j++) {
            arq[i].matrizMachine[j] = new int[nLinhas];
            arq[i].matrizTimes[j] = new int[nLinhas];
            arq[i].matrizResultado[j] = new int[nLinhas];
        }
}

    while(getline(ifs,linha)) { // enquanto end of file for false continua
        if(linha == "Times"){
            for(int i=0; i<nLinhas;i++){
                getline(ifs,linha);
                char *helper = new char[(linha.length()+1)];
                strcpy(helper, linha.c_str());
                int col=0;
                int int_num;


                for(int j=0; j<linha.length()+1; j++){
                    if(helper[j] != ' '){
                        num.push_back(helper[j]); //concatena os caracteres em uma string
                    }
                    else if(helper[j] == ' '  && num != ""){
                        istringstream(num) >> int_num;
                        arq[aux].matrizTimes[i][col]  = int_num;
                        col++;
                        num = "";
                    }
                    if(helper[j] == '\0'){ // se for o final da linha atribui o ultimo valor de num a matriz
                        istringstream(num) >> int_num;
                        arq[aux].matrizTimes[i][col]  = int_num;
                        num = "";
                    }
                }
                // for(int j=0; j<nLinhas; j++){
                //     cout << arq[aux].matrizTimes[i][j] << " ";
                // }
                // cout << endl;
                }
                // cout << endl;
        }
        if(linha == "Machines"){
            for(int i=0; i<nLinhas;i++){
                getline(ifs,linha);
                char *helper = new char[(linha.length()+1)];
                strcpy(helper, linha.c_str());
                int col=0;
                int int_num;
                for(int j=0; j<linha.length()+1; j++){
                    if(helper[j] != ' '){
                        num.push_back(helper[j]); //concatena os caracteres em uma string
                        
                    }
                    else if(helper[j] == ' '  && num != ""){
                        istringstream(num) >> int_num;
                        arq[aux].matrizMachine[i][col]  = int_num;
                        col++;
                        num = "";
                    }
                    if(helper[j] == '\0'){ // se for o final da linha atribui o ultimo valor de num a matriz
                        istringstream(num) >> int_num;
                        arq[aux].matrizMachine[i][col]  = int_num;
                        num = "";
                    }
                }
                // for(int j=0; j<nLinhas; j++){
                //     cout << arq[aux].matrizMachine[i][j] << " ";
                // }
                // cout << endl;
                }
                // cout << endl;
        }
        if(linha == primeiraLinha){ // se a linha for igual a primeira linha passa para a proxima posição do vetor
            aux+=1;
        }
    }
    

    for(int i=0; i<entradas; i++){
        for(int j=0; j<nLinhas; j++){
            for(int k=0; k<nLinhas; k++){
                arq[i].matrizResultado[j][k] = arq[i].matrizTimes[j][arq[i].matrizMachine[j][k]-1];
                cout << arq[i].matrizResultado[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    ifs.close();
    return 0;
}
