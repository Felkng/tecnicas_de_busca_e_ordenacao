#include<iostream>
#include "Aluno.h"

using namespace std;
int main(){
    Aluno a1;
    a1.nome = "André";
    a1.notas[0] = 60;
    a1.notas[1] = 40;
    a1.notas[2] = 85;

    cout << a1.nome << endl;
    for(int i=0; i<3; i++){
        cout << a1.notas[i] << endl;
    }
}