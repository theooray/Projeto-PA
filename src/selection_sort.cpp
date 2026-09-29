#include "selection_sort.hpp"
#include "arquivos.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

chrono::duration<double> selectionSort(vector<int>& numeros){
    
    auto inicio = chrono::high_resolution_clock::now();

    for(size_t i = 0; i<numeros.size() ; i++){
        int minimo = i;

        for(size_t j = i+1; j<numeros.size() ; j++){
            if(numeros.at(j) < numeros.at(minimo)){
                minimo = j;
            }
        }

        int temp = numeros.at(i);
        numeros.at(i) = numeros.at(minimo);
        numeros.at(minimo) = temp;
    }

    auto fim = chrono::high_resolution_clock::now();

    return fim - inicio;
}