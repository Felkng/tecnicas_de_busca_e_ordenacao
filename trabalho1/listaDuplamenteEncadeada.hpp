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


class no{
    public:
        int value;
        no* next;
        no* prev;
};

class HardList{ //cria no cabeça
    private:
        int size;
        no** list;
    public:
        HardList(int decision){
            list = new no*();
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
                (*list) = new no();
                (*list)->next = (*list);
                (*list)->prev = (*list);
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
            (*list) = new no();
            (*list)->next = (*list);
            (*list)->prev = (*list);
            int val=0;
            int ct=0;
            while(inputFile){
                ct++;
                if(ct > size){
                    cout << "Tamanho da lista excedido.\n";
                    break;
                }
                    inputFile >> val;
                    insertList(val);
            }
        }

        void generateRandomList(int begin, int finish) {
            unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
            default_random_engine generator(seed);
            uniform_int_distribution<int> distribution(begin, finish);
            for (int i = 0; i < size; ++i) {
                insertList(distribution(generator));
            }
        }

        void insertList(int val){ //insere ao contrário
            no* littleNew = new no();
            littleNew->prev = (*list)->prev;
            (*list)->prev->next = littleNew;
            (*list)->prev = littleNew;
            littleNew->next = (*list);
            littleNew->value = val;
        }

        void insert_aux(no* aux, int val){//auxilia na inserção na posição
            size++;
            no* littleNew = new no();
            littleNew->next = aux->next;
            aux->next->prev = littleNew;
            aux->next = littleNew;
            littleNew->prev = aux;
            littleNew->value = val;
        }

        void printList(){
            no* aux = (*list)->next;
            while(aux != (*list)){
                cout << aux->value << " ";
                aux = aux->next;
            }
            cout << endl;
        }

        void printListInv(){ //Não é mais recursivo
            no* aux = (*list)->prev;
            while(aux != (*list)){
                cout << aux->value << " ";
                aux = aux->prev;
            }
            cout << endl;
        }

        no* insertPositionValue(int pos, int val){
            if(pos > size){
                cerr << "Não existe essa posição\n";
                return NULL;
            }
            no* aux = (*list)->next;
            if(pos == 1){
                insert_aux((*list),val);
                return NULL;
            }
            for(int i=1;i < pos; i++){
                if(i+1 == pos)
                    break;
                aux = aux->next;
            }
            insert_aux(aux,val);
            return aux;

        }

        void swapPositions(int pos1, int pos2){ //pior caso: quando 1 está exatamente na frente do outro
            no* position1 = (*list)->next;
            no* position2 = (*list)->prev;
            bool aux1,aux2 = false;
            if(pos1>pos2)
                swap(pos1,pos2);
            for(int i=1,j=size;i < size; i++,j--){
                if(i == pos1)
                    aux1 = true;
                if(aux1==false)
                    position1 = position1->next;
                if(j == pos2)
                    aux2=true;
                if(aux2==false)
                    position2 = position2->prev;
                if(aux1 && aux2)
                    break;
            }
            swap(position1->value, position2->value);
        }

        no* searchValue(int val){
            no* aux = (*list)->next;
            int ct=0;
            while(aux != (*list)){
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

        no* searchLowervalue(){
            no* aux = (*list)->next;
            no* lower = aux;
            int ct=0;
            while(aux != (*list)){
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

        no* getList(){
            return (*list);
        }

};