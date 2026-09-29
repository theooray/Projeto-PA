#include "bubble_sort.hpp"
#include "arquivos.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

chrono::duration<double> bubbleSort(vector<int>& numeros){
    
    auto inicio = chrono::high_resolution_clock::now();

        bool troca;
        int temp;

        for(size_t i = 0; i < numeros.size() - 1 ; i++){
            troca = false;
            for(size_t j = 0 ; j < numeros.size() - i - 1; j++){
                if(numeros[j]>numeros[j+1]){
                    temp = numeros[j+1];
                    numeros[j+1] = numeros[j];
                    numeros[j] = temp;
                    troca = true;
                }
            }
            if(!troca){
                break;
            }
        }

    auto fim = chrono::high_resolution_clock::now();

    return fim - inicio;
}