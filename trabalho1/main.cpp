#include "listaEstatica.hpp"
#include "listaLigadaSimples.hpp"
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
    SimpleList lista(1);
    lista.printList();
    lista.insertPositionValue(4,700);
    lista.printListInv(lista.getList());
    cout << endl;
    lista.printList();
    lista.swapPositions(1,4);
    lista.printList();
    node* lol = lista.searchValue(700);
    cout << lol->value << endl;
    lista.printList();
    lol = lista.searchLowervalue();
    cout << lol->value << endl;
    cout << lista.getSize();
    return 0;
}