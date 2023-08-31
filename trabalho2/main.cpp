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

void print(vector<int> &a){
    for(auto x: a){
            cout << x << " ";
        }
    // cout << "\n";
}

void insertionSort(vector<int> &a){
    int ct=0;
    int n = a.size();
    for (int i = 1; i < n; ++i) {
        int f = a[i];
        int j = i - 1;
        // print(a);
        while (j >= 0 && a[j] > f) {
            ++ct;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = f;
        // cout << "\n";
    }

    cout << ct << "\n";
}

void selectionSort(vector<int> &a){
    int ct=0;
    for(int i=0; i<a.size()-1;++i){
        int min = i;
        // print(a);
        for(int j=i+1; j<a.size(); ++j){
            ++ct;
            if(a[j] < a[min]){
                min = j;
            }
        }
        if(min != i){
            swap(a[min],a[i]);
        }
        
        // cout << "\n";
    }
    cout << ct << "\n";
}

int main(){
    // vector<int> aq;
    // int cd;
    // while(cin >> cd){
    //     aq.push_back(cd);
    // }

    // insertionSort(aq);
    // cout << "Vetor ordenado utilizando InsertionSort: ";
    // print(aq);
    for(int i=1; i<=100; i++){
        vector<int> a;
        generateRandomArray(i,1,1000,a);
        insertionSort(a);
    }
    cout << "\n========================================================\n\n";
    for(int i=1; i<=100; i++){
        vector<int> b;
        generateRandomArray(i,1,1000,b);
        selectionSort(b);
    }
    return 0;
}