#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "bubble_sort.hpp"
#include "shell_sort.hpp"
#include "arquivos.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <random>
#include <chrono>

// execução dos algoritmos
chrono::duration<double> chamarAlgoritmo(int algoritmo, vector<int>& numeros){
    switch(algoritmo){
        case 1:
            return insertionSort(numeros);
        case 2:
            return selectionSort(numeros);
        case 3:
            return shellSort(numeros);
        case 4:
            return bubbleSort(numeros);
        default:
            cerr << "Algoritmo nao implementado\n";
            return chrono::duration<double>::zero();
    }
}


void executar(int algoritmo, const string& caminhoEntrada, const string& caminhoSaida, const string& caminhoTempo){
    vector<int> numeros;

    numeros = carregarEntrada(caminhoEntrada);

    cout << "\nExecutando " << algoritmos.at(algoritmo) << ", ordenando "<< numeros.size() << " elementos" << "...\n\n";
    
    chrono::duration<double> duracaoCientifica = chamarAlgoritmo(algoritmo, numeros);

    salvarSaida(numeros, caminhoSaida, numeros.size());
    salvarTempo(duracaoCientifica.count(), caminhoTempo, numeros.size());
    abrirArquivo(caminhoSaida);
    cout << "\nTempo de execucao: " << duracaoCientifica.count() << " segundos\n";
    cin.ignore();
    cin.get();
}

void executar(int algoritmo, vector<int> vetor){
    cout << "\nExecutando " << algoritmos.at(algoritmo) << "...\n";

    chrono::duration<double> duracaoCientifica = chamarAlgoritmo(algoritmo, vetor);

    for(int numeros : vetor){
        cout << numeros << " ";
    }

    cout << "\nTempo de execucao: " << duracaoCientifica.count() << " segundos\n";
    cin.ignore();
    cin.get();
}

//navegação do menu
void definirCaminhos(int chave, const string& tipo){
    int tamanho;
    string algoritmo = algoritmos.at(chave);
    static const vector<int> tamanhoValido = {10, 100, 1000, 10000, 100000, 1000000};

    do{
        cout << "\nDigite a quantidade de numeros: (10, 100, 1000, 10000, 100000, 1000000)\n";
        cin >> tamanho;
    }while(find(tamanhoValido.begin(), tamanhoValido.end(), tamanho) == tamanhoValido.end());

    string entrada = caminhoEntrada(algoritmo,tipo,tamanho);
    string saida = caminhoSaida(algoritmo, tipo, tamanho);
    string tempo = caminhoTempo(algoritmo, tipo, tamanho);

    criarDiretorio(chave);
    gerarEntrada(tipo,entrada,tamanho);
    executar(chave, entrada, saida, tempo);
}

void benchmark(int chave){
    const double TEMPO_MINIMO = 0.1;
    const size_t LIMITE_AQUECIMENTO = 100000;
    string algoritmo = algoritmos.at(chave);
    static const vector<int> tamanhos = {10, 100, 1000, 10000, 100000, 1000000};
    static const vector<string> tipos = {"crescente","decrescente","random"};

    criarDiretorio(chave);

    for(const string& tipo : tipos){
        for(int tamanho : tamanhos){
            string entrada = caminhoEntrada(algoritmo, tipo, tamanho);
            string saida = caminhoSaida(algoritmo, tipo, tamanho);
            string tempo = caminhoTempo(algoritmo, tipo, tamanho);

            gerarEntrada(tipo, entrada, tamanho);

            vector<int> original = carregarEntrada(entrada);
            vector<int> numeros;

            cout << "\nExecutando " << algoritmo << ", ordenando " << original.size() << " elementos" << "...\n\n";

            if (original.size() <= LIMITE_AQUECIMENTO) {
                numeros = original;
                chamarAlgoritmo(chave, numeros);
            }

            chrono::duration<double> total(0);
            int repeticoes = 0;

            while (total.count() < TEMPO_MINIMO) {
                numeros = original;
                total += chamarAlgoritmo(chave, numeros);
                repeticoes++;
            }

            double media = total.count() / repeticoes;

            salvarSaida(numeros, saida, numeros.size());
            salvarTempo(media, tempo, numeros.size());

            cout << "Tempo medio: " << media << " segundos (" << repeticoes << " execucoes)\n";
        }
    }
}

void escolherEntrada(int algoritmo){
    int opcao, numeros, tipo;
    vector<int> vetor;

    do{
        cout << "\n==================\n";
        cout << "1 - inserir vetor\n";
        cout << "2 - Selecionar instancia\n";
        cout << "0 - Voltar\n";
        cout << "==================\n";
        cout << "Digite sua escolha: ";
        cin >> opcao;
 
    }while(opcao < 0 || opcao > 4);

    if(opcao == 1){
        cout << "\nInsira o numero: (0 para sair): \n";

        cin >> numeros;
        while(numeros != 0){
            vetor.push_back(numeros);
            cin >> numeros;
        }

        executar(algoritmo, vetor);

    }else if(opcao == 2){
        do{
            cout << "\n==================\n";
            cout << "1 - Crescente\n";
            cout << "2 - Decrescente\n";  
            cout << "3 - Aleatorio\n"; 
            cout << "0 - Voltar\n"; 
            cout << "==================\n";
            cout << "Digite sua escolha: ";
            cin >> tipo;
        
        }while(tipo < 0 || tipo > 3);

        switch(tipo){
            case 1:
                definirCaminhos(algoritmo,"crescente");
                break;
            case 2:
                definirCaminhos(algoritmo, "decrescente");
                break;
            case 3:
                definirCaminhos(algoritmo, "random");
                break;
            case 0:
                break;
        }   

    }else if(opcao == 0){
        return;
    }else if(opcao == 4){
        benchmark(algoritmo);
    }    
  
}

void menu(){
    int opcao;

    do{
    cout << "========MENU=======\n";
    cout << "1. Insertion Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Shell Sort\n";
    cout << "4. Bubble Sort\n";
    cout << "0. Sair\n";
    cout << "===================\n";
    cout << "Digite o numero do algoritmo correspondente: ";
    cin >> opcao;
    
    if(opcao > 0 && opcao < 6) escolherEntrada(opcao);
    if(opcao < 0 || opcao > 5) cout << "Insira uma opcao valida!\n\n";

    }while(opcao != 0);
}

int main(){
    menu();
    return 0;
}