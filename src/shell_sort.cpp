#include "shell_sort.hpp"
#include "arquivos.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

chrono::duration<double> shellSort(vector<int>& numeros){
    auto inicio = chrono::high_resolution_clock::now();
    
    for(size_t gap = numeros.size()/2 ; gap>0 ; gap /= 2){
        for(size_t i = gap ; i<numeros.size() ; i++){
            int temp = numeros[i];
            size_t j = i;

            while(j >= gap && numeros[j-gap] > temp){
                numeros[j] = numeros[j-gap];
                j -= gap;
            }

            numeros[j] = temp;
        }
    }

    auto fim = chrono::high_resolution_clock::now();

    return fim - inicio;
}