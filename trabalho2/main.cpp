#include <iostream>
#include <vector>
#include <chrono> 
#include <random> 

using namespace std;

void generateRandomArray(int size, int begin, int finish, vector<int> &x) {
        x.resize(size);
        // unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        unsigned seed = 28394843;
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(begin, finish);
        for (int i = 0; i < size; ++i) {
            x[i] = distribution(generator);
        }
}

bool printar=true;
void print(vector<int> &a){
    for(auto x: a){
            cout << x << " ";
        }
    cout << "\n";
}

void insertionSort(vector<int> &a){
    int ct=0;
    int n = a.size();
    for (int i = 1; i < n; ++i) {
        int f = a[i];
        int j = i - 1;
        if(printar)
        print(a);
        while (j >= 0 && a[j] > f) {
            ++ct;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = f;
        if(printar)
        cout << "\n";
    }
    if(!printar)
    cout << ct << "\n";
}

void selectionSort(vector<int> &a){
    int ct=0;
    for(int i=0; i<a.size()-1;++i){
        int min = i;
        if(printar)
        print(a);
        for(int j=i+1; j<a.size(); ++j){
            ++ct;
            if(a[j] < a[min]){
                min = j;
            }
        }
        if(min != i){
            swap(a[min],a[i]);
        }
        if(printar)
        cout << "\n";
    }
    if(!printar)
    cout << ct << "\n";
}


int main(){
    vector <int> listaDada1 = {70,1, 12, 8, 99, 72, 5, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90};
    vector <int> listaDada2 = {70,1, 12, 8, 99, 72, 5, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90};
    
    cout << "\n\nUtilizando Insertion Sort: \n\n";
    insertionSort(listaDada1);
    print(listaDada1);

    cout << "\n\nUtilizando Selection Sort: \n\n";
    selectionSort(listaDada2);
    print(listaDada2);

    //Para plotar os gráficos é preciso pegar os valores utilizados e colocar na planilha
    //disponibilizada nesse link: https://docs.google.com/spreadsheets/d/1nANyr0wiBslqqW6vpD1PDDWV2-2Nb0EWlkUOo0MlXV4/edit?usp=sharing
    //denominada "analise de dados", em que uma coluna será utilizada para representar
    //os acessos utilizando selection sort, outra coluna para o insertion sort e mais uma
    //coluna para colocar a quantidade de elementos dentro do vetor [1, 100]
    //Depois é só selecionar as três colunas simultaneamente e ir
    // no cabeçalho na opçao de inserir > gráfico, e selecionar
    // a opção "gráfico de linha". Depois, Remova a coluna que utilizou para colocar
    // a quantidade de elementos "n" e coloque-a para representar o "eixo x"
    printar = false;
    cout << "\n\n========================================================\n\n";
    cout << "Mostrando o número de acessos a estrutura utilizando valores aleatórios de 1 a 1000 no intervalo de 1 a 100\n\n";
    cout << "Insertion sort:\n\n";
    for(int i=1; i<=100; i++){
        vector<int> a;
        generateRandomArray(i,1,1000,a);
        insertionSort(a);
    }
    cout << "\n\n========================================================\n\n";
    cout << "Selection sort: \n\n";
    for(int i=1; i<=100; i++){
        vector<int> b;
        generateRandomArray(i,1,1000,b);
        selectionSort(b);
    }
    return 0;
}
