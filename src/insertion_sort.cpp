#include "insertion_sort.hpp"
#include "arquivos.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

chrono::duration<double> insertionSort(vector<int>& numeros){
    
    auto inicio = chrono::high_resolution_clock::now();

    for(size_t i =1; i<numeros.size() ; i++){
        int chave = numeros[i];
        int j = i - 1;
        while(j>=0 && numeros[j] > chave){
            numeros[j+1] = numeros[j];
            j--;
        }
        numeros[j+1] = chave;
    }

    auto fim = chrono::high_resolution_clock::now();

    return fim - inicio;
}