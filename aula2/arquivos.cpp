#include <iostream>
#include<fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class Arquivo{
public:
    int ***matrizTimes;
    int ***matrizMachine;
    int ***matrizResultado;

};

int main(){
    
    int nLinhas = 15;
    ifstream ifs ("job.txt", ifstream::in); // abre o arquivo
    string primeiraLinha;
    string linha;
    int aux=0; //contador de matrizes
    int entradas = 10; //quantidade de matrizes
    string machines[entradas];
    // string times[entradas];
    getline(ifs,primeiraLinha); // pega a primeira linha
    string num = "";
    Arquivo arq;

    arq.matrizMachine = new int**[entradas];
    arq.matrizTimes = new int**[entradas];
    arq.matrizResultado = new int**[entradas];

    for(int i=0; i<entradas; i++){
        arq.matrizMachine[i] = new int*[nLinhas];
        arq.matrizTimes[i] = new int*[nLinhas];
        arq.matrizResultado[i] = new int*[nLinhas];
        for(int j=0; j<nLinhas; j++){
            arq.matrizMachine[i][j] = new int[nLinhas];
            arq.matrizTimes[i][j] = new int[nLinhas];
            arq.matrizResultado[i][j] = new int[nLinhas];
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
                        arq.matrizTimes[aux][i][col]  = int_num;
                        col++;
                        num = "";
                    }
                    if(helper[j] == '\0'){ // se for o final da linha atribui o ultimo valor de num a matriz
                        istringstream(num) >> int_num;
                        arq.matrizTimes[aux][i][col]  = int_num;
                        num = "";
                    }
                }
                    for(int j=0; j<nLinhas; j++){
                        cout << arq.matrizTimes[aux][i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl;

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
                        arq.matrizMachine[aux][i][col]  = int_num;
                        col++;
                        num = "";
                    }
                    if(helper[j] == '\0'){ // se for o final da linha atribui o ultimo valor de num a matriz
                        istringstream(num) >> int_num;
                        arq.matrizMachine[aux][i][col]  = int_num;
                        num = "";
                    }
                }
                    for(int j=0; j<nLinhas; j++){
                        cout << arq.matrizMachine[aux][i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            if(linha == primeiraLinha){ // se a linha for igual a primeira linha passa para a proxima posição do vetor
                aux+=1;
                if(aux==entradas) //evita falha de segmentação
                    break;
            }
        }
    }
    ifs.close();
    return 0;
}
