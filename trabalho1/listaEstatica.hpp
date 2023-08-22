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

class ArrayList{

private:
    int size;
    vector<int> dynamicArray;
public:

    ArrayList(int decision){
        if(decision == 1){
            cout << "Insira o nome do arquivo:" << endl;
            string input;
            cin >> input;
            ReadFromFile(input);
        }else if(decision == 2){
            cout << "Insira o tamanho do array:" << endl;
            cin >> size;
            
            cout << "Insira o inicio do intervalo:" << endl;
            int begin, fim;
            cin >> begin;
            cout << "Insira o fim do intervalo:" << endl;
            cin >> fim;
            generateRandomArray(begin,fim);
        }
    }

    void ReadFromFile(const string& filename){
        ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            cerr << "Failed to open input file." << endl;
        return;
        }

        if (!(inputFile >> size)) {
            cerr << "Failed to read size from input file." << endl;
            return;
        }      

        dynamicArray.resize(size);

        for (int i = 0; i < size; ++i) {
            if (!(inputFile >> dynamicArray[i])) {
                cerr << "Failed to read data element from input file." << endl;
                return;
            }
        }

    }

    void printArray(){
        for (int i = 0; i < size; ++i) {
            cout << dynamicArray[i] << " ";
        }
        cout << endl;
    }

    void printArrayInv(){
        for(int i=size-1; i>=0; i--)
            cout << dynamicArray[i] << " ";
        cout << endl;
    }


    void generateRandomArray(int begin, int finish) {
        dynamicArray.resize(size);
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(begin, finish);
        for (int i = 0; i < size; ++i) {
            dynamicArray[i] = distribution(generator);
        }
    }

    void positionInsertion(unsigned pos, int value){
        dynamicArray.resize(size+1);
        size++;
        for(unsigned i = size - 1; i>pos; i--){
            int aux = dynamicArray[i-1];
            dynamicArray[i] = aux;
        }
        dynamicArray[pos] = value;
    }

    void swapPosition(unsigned pos1, unsigned pos2){
        swap(dynamicArray[pos1],dynamicArray[pos2]);
    }

    int searchValue(int value){
        unsigned i=0;
        for(; i < size; i++){
            if(dynamicArray[i] == value){
                cout << "Numero de acessos: " << i << endl;
                return i;
            }
        }
        cout << "Numero de acessos: " << i << endl;
        return -1;
    }

    int searchLower(){
        int lower = dynamicArray[0];
        int pos= 0;
        unsigned i=0;
        for(;i<size;i++){
            if(dynamicArray[i] < lower){
                pos = i;
                lower = dynamicArray[i];
            }
        }
        cout << "Numero de acessos: " << i << endl;
        cout << "Menor valor: " << lower << endl;
        return pos;
    }
    
    void setSize(int tam){
        size = tam;
    }
    
    int getSize(){
        return size;
    }


};

    /*void shuffler(){
        //srand ( unsigned ( std::time(0) ) );
        //random_shuffle( dynamicArray.begin(), dynamicArray.end());

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(dynamicArray.begin(), dynamicArray.end(), default_random_engine(seed));

    }*/