#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>  
#include <random>  
#include <chrono>  

using namespace std;


class node{
    public:
        int value;
        node* next;
};

class SimpleList{
    private:
        int size;
        node** list;
    public:
        SimpleList(int decision){
            if(decision==1){
                cout << "Informe o nome do arquivo: " << endl;
                string archive;
                cin >> archive;
                readFromFile(archive);
            }else if(decision==2){
                cout << "Insira o tamanho da lista:" << endl;
                cin >> size;
                cout << "Insira o inicio do intervalo:" << endl;
                int begin, fim;
                cin >> begin;
                cout << "Insira o fim do intervalo:" << endl;
                cin >> fim;
                (*list) = NULL;
                generateRandomList(begin,fim);
            }
        };

        void readFromFile(string filename){
            ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                cerr << "Failed to open input file." << endl;
            return;
            }
            if (!(inputFile >> size)) {
                cerr << "Failed to read size from input file." << endl;
                return;
            }     
            (*list) = NULL;
            vector<int> list_aux;
            list_aux.resize(size);
            for(unsigned i=0; i<size; i++){
                if (!(inputFile >> list_aux[i])) {
                    cerr << "Failed to read data element from input file." << endl;
                    return;
                }
            }
            for(int i = size-1; i>=0; i--)
                insertList(list_aux[i]);
        }

        void generateRandomList(int begin, int finish) {
            unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
            default_random_engine generator(seed);
            uniform_int_distribution<int> distribution(begin, finish);
            for (int i = 0; i < size; ++i) {
                insertList(distribution(generator));
            }
        }

        void insertList(int val){
            node* littleNew = new node();
            littleNew->next = (*list);
            (*list) = littleNew;
            littleNew->value = val;
        }

        void printList(){
            node* aux = (*list);
            while(aux != NULL){
                cout << aux->value << " ";
                aux = aux->next;
            }
            cout << endl;
        }

        void printListInv(node * prox){
            if(prox == NULL){
                return;
            }
            printListInv(prox->next);
            cout << prox->value << " ";
        }

        node* insertPositionValue(int pos, int val){
            node* aux = (*list);
            if(pos == 1){
                insertList(val);
                size++;
                return NULL;
            }
            for(int i=1;i < pos; i++){
                if(i+1 == pos)
                    break;
                aux = aux->next;
            }
            node* newNo = new node();
            newNo->value = val;
            newNo->next = aux->next;
            aux->next = newNo;
            size++;
            return aux;

        }

        void swapPositions(int pos1, int pos2){
            node* position1 = (*list);
            node* position2 = (*list);
            for(int i=0;i < pos1; i++){
                if(i+1 == pos1)
                    break;
                position1 = position1->next;
            }
            for(int i=0;i < pos2; i++){
                if(i+1 == pos2)
                    break;
                position2 = position2->next;
            }
            int aux = position1->value;
            position1->value = position2->value;
            position2->value = aux;
        }

        node* searchValue(int val){
            node* aux = (*list);
            int ct=0;
            while(aux != NULL){
                ct++;
                if(aux->value == val){
                    cout << "Numero de acessos: " << ct << endl;
                    return aux;
                }
                aux = aux->next;
            }
            cout << "Numero de acessos: " << ct << endl;
            return NULL;
        }

        node* searchLowervalue(){
            node* aux = (*list);
            node* lower = aux;
            int ct=0;
            while(aux != NULL){
                ct++;
                if(aux->value < lower->value)
                    lower = aux;
                aux = aux->next;
            }
            cout << "Numero de acessos: " << ct << endl;
            return lower;

        }

        int getSize(){
            return size;
        }

        void setSize(int siz){
            size = siz;
        }

        node* getList(){
            return (*list);
        }

};