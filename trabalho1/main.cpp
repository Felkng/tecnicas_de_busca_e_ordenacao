#include "listaEstatica.hpp"
#include "listaLigadaSimples.hpp"
#include "listaDuplamenteEncadeada.hpp"
#include <iostream>
#include <fstream>

using namespace std;
int main(){
//LISTA ESTÁTICA
    //================================================
    //Arquivo
    cout << "\n------------LISTA ESTATICA------------\n";
    int aux_est = 0;
    ArrayList lista_est_arq(1);
    cout << "Lista: ";
    lista_est_arq.printArray();
    lista_est_arq.positionInsertion(5,1000);
    cout << "Inserido valor: ";
    lista_est_arq.printArray();
    cout << "Lista invertida: ";
    lista_est_arq.printArrayInv();
    lista_est_arq.swapPosition(0,5); //TO DO VERIFICAR SE OS 2 VALORES EXISTE
    cout << "Posicao trocada: ";
    lista_est_arq.printArray();
    aux_est = lista_est_arq.searchValue(1000);
    cout << "Posicao: " << aux_est << endl;
    aux_est = lista_est_arq.searchLower();
    cout << "Posicao: " << aux_est << endl;

    // //==================================================
    // //Aleatória

    cout << endl << "Lista Aleatória" << endl;
    ArrayList lista_est_ale(2);
    cout << "Lista: ";
    lista_est_ale.printArray();
    lista_est_ale.positionInsertion(5,1000);
    cout << "Inserido valor: ";
    lista_est_ale.printArray();
    cout << "Lista invertida: ";
    lista_est_ale.printArrayInv();
    lista_est_ale.swapPosition(0,5); //TO DO VERIFICAR SE OS 2 VALORES EXISTE
    cout << "Posicao trocada: ";
    lista_est_ale.printArray();
    aux_est = lista_est_ale.searchValue(1000);
    cout << "Posicao: " << aux_est << endl;
    aux_est = lista_est_ale.searchLower();
    cout << "Posicao: " << aux_est << endl;

    //LISTA LIGADA SIMPLES
    //========================================
    //Arquivo
    cout << "\n------------LISTA LIGADA SIMPLES------------\n";
    node* aux;
    SimpleList lista_sim_arq(1);
    cout << "Lista: ";
    lista_sim_arq.printList();
    aux = lista_sim_arq.insertPositionValue(2,1000);
    cout << "Inserido Valor: ";
    lista_sim_arq.printList();
    cout << "Valor do no anterior a insercao: " << aux->value << endl;
    cout << "Lista invertida: ";
    lista_sim_arq.printListInv(lista_sim_arq.getList());
    cout << endl << "Lista: ";
    lista_sim_arq.printList();
    lista_sim_arq.swapPositions(2,5); //TO DO VERIFICAR SE OS 2 VALORES EXISTE
    cout << "Posicao Trocada: ";
    lista_sim_arq.printList();
    aux = lista_sim_arq.searchValue(1000);
    cout << "Valor: " << aux->value << endl;
    aux = lista_sim_arq.searchLowervalue();
    cout << "Menor valor: " << aux->value << endl;
    //===============================================
    //Aleatória
    cout << endl << "Lista Aleatória" << endl;
    SimpleList lista_sim_ale(2);
    cout << "Lista: ";
    lista_sim_ale.printList();
    aux = lista_sim_ale.insertPositionValue(2,1000);
    cout << "Inserido Valor: ";
    lista_sim_ale.printList();
    cout << "Valor do no anterior a insercao: " << aux->value << endl;
    cout << "Lista invertida: ";
    lista_sim_ale.printListInv(lista_sim_ale.getList());
    cout << endl << "Lista: ";
    lista_sim_ale.printList();
    lista_sim_ale.swapPositions(2,5); //TO DO VERIFICAR SE OS 2 VALORES EXISTE
    cout << "Posicao Trocada: ";
    lista_sim_ale.printList();
    aux = lista_sim_ale.searchValue(1000);
    cout << "Valor: " << aux->value << endl;
    aux = lista_sim_ale.searchLowervalue();
    cout << "Menor valor: " << aux->value << endl;

    //LISTA LIGADA DUPLA
    //========================================
    //Arquivo
    cout << "\n------------LISTA DUPLAMENTE LIGADA------------\n";
    no* aux_dup;
    HardList lista_dup_arq(1);
    cout << "Lista: ";
    lista_dup_arq.printList();
    aux_dup = lista_dup_arq.insertPositionValue(2,1000);
    cout << "Inserido Valor: ";
    lista_dup_arq.printList();
    cout << "Valor do no anterior a insercao: " << aux_dup->value << endl;
    cout << "Lista invertida: ";
    lista_dup_arq.printListInv();
    cout << "Lista: ";
    lista_dup_arq.printList();
    lista_dup_arq.swapPositions(2,5); //TO DO VERIFICAR SE OS 2 VALORES EXISTE
    cout << "Posicao Trocada: ";
    lista_dup_arq.printList();
    aux_dup = lista_dup_arq.searchValue(1000);
    cout << "Valor: " << aux_dup->value << endl;
    aux_dup = lista_dup_arq.searchLowervalue();
    cout << "Menor valor: " << aux_dup->value << endl;
    // //===============================================
    // //Aleatória
    cout << endl << "Lista Aleatória" << endl;
    HardList lista_dup_ale(2);
    cout << endl << "Lista: ";
    lista_dup_ale.printList();
    aux_dup = lista_dup_ale.insertPositionValue(2,1000);
    cout << "Inserido Valor: ";
    lista_dup_ale.printList();
    cout << "Valor do no anterior a insercao: " << aux_dup->value << endl;
    cout << "Lista invertida: ";
    lista_dup_ale.printListInv();
    cout << "Lista: ";
    lista_dup_ale.printList();
    lista_dup_ale.swapPositions(2,5); //TO DO VERIFICAR SE OS 2 VALORES EXISTE
    cout << "Posicao Trocada: ";
    lista_dup_ale.printList();
    aux_dup = lista_dup_ale.searchValue(1000);
    cout << "Valor: " << aux_dup->value << endl;
    aux_dup = lista_dup_ale.searchLowervalue();
    cout << "Menor valor: " << aux_dup->value << endl;

    
    return 0;
}