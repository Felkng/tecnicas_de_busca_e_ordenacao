#include "listaEstatica.hpp"
#include "listaLigadaSimples.hpp"
#include "listaDuplamenteEncadeada.hpp"
#include <iostream>
#include <fstream>

using namespace std;
int main(){
    //LISTA LIGADA SIMPLES
    //========================================
    //Arquivo
    node* aux;
    SimpleList lista_sim_arq(1);
    lista_sim_arq.printList();
    lista_sim_arq.insertPositionValue(2,1000);
    lista_sim_arq.printListInv(lista_sim_arq.getList());
    cout << endl;
    lista_sim_arq.swapPositions(2,5);
    lista_sim_arq.printList();
    aux = lista_sim_arq.searchValue(1000);
    cout << aux->next->value << endl;
    aux = lista_sim_arq.searchLowervalue();
    cout << aux->next->value << endl;
    //===============================================
    //Aleatória
    SimpleList lista_sim_ale(2);
    lista_sim_ale.printList();
    lista_sim_ale.insertPositionValue(2,1000);
    lista_sim_ale.printListInv(lista_sim_ale.getList());
    cout << endl;
    lista_sim_ale.swapPositions(2,5);
    lista_sim_ale.printList();
    aux = lista_sim_ale.searchValue(1000);
    cout << aux->next->value << endl;
    aux = lista_sim_ale.searchLowervalue();
    cout << aux->next->value << endl;
    return 0;
}