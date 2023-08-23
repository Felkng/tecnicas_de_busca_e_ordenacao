#include "listaEstatica.hpp"
#include "listaLigadaSimples.hpp"
#include "listaDuplamenteEncadeada.hpp"
#include <iostream>
#include <fstream>

using namespace std;
void menu(){
    cout << "########################################### \n";
    cout << "Qual tipo de lista deseja criar? \n";
    cout << "1 - Lista estática \n";
    cout << "2 - Lista encadeada simples \n";
    cout << "3 - Lista duplamente encadeada \n";
    cout << "########################################### \n";
}
void menu2(){
    cout << "########################################### \n";
    cout << "Deseja criar a lista a partir de um arquivo ou gerar uma lista aleatória? \n";
    cout << "1 - Arquivo \n";
    cout << "2 - Aleatória \n";
    cout << "########################################### \n";
}
void operacoes(){
    cout << "########################################### \n";
    cout << "Qual operação deseja fazer? \n";
    cout << "1 - inserir um valor em uma posição específica\n";
    cout << "2 - fazer a transposição (swap) de duas posições \n";
    cout << "3 - procurar um valor dado \n";
    cout << "4 - procurar o menor valor \n";
    cout << "5 - mostrar lista \n";
    cout << "6 - mostrar lista em ordem aleatória\n";
    cout << "########################################### \n";
}
int main(){
    HardList lista(1);
    lista.printList();
    lista.printListInv();
    lista.insertPositionValue(1,900);
    lista.printList();
    lista.insertPositionValue(4,1700);
    lista.printList();
    lista.insertPositionValue(1800,2);
    lista.printList();
    lista.swapPositions(1,4);
    lista.printList();
    no* p;
    p = lista.searchValue(1700);
    cout << p->value << endl;
    p = lista.searchLowervalue();
    cout << p->value << endl;
    return 0;
}