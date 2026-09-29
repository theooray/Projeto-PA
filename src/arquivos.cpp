#include "insertion_sort.hpp"
#include "arquivos.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <random>

using namespace std;
namespace fs = std::filesystem;

const unordered_map<int, string> algoritmos ={
    {1, "Insertion Sort"},
    {2, "Selection Sort"},
    {3, "Shell Sort"},
    {4, "Bubble Sort"}
};

// construção de caminho
string caminhoEntrada(const string& algoritmo, const string& tipo, int tamanho){
    return "Arquivos/" + algoritmo + "/Entrada/" + tipo + "/entrada_" + tipo + "_" + to_string(tamanho) + ".txt";
}

string caminhoSaida(const string& algoritmo, const string& tipo, int tamanho){
    return "Arquivos/" + algoritmo + "/Saida/" + tipo + "/saida_" + tipo + "_" + to_string(tamanho) + ".txt";
}

string caminhoTempo(const string& algoritmo, const string& tipo, int tamanho){
    return "Arquivos/" + algoritmo + "/Tempo/" + tipo + "/tempo_" + tipo + "_" + to_string(tamanho) + ".txt";
}

// estrutura de diretorio
void criarDiretorio(int algoritmo){
    if(!fs::exists("Arquivos/" + algoritmos.at(algoritmo) + "/")){    
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Entrada/crescente");
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Entrada/decrescente");
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Entrada/random");
        
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Saida/crescente");
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Saida/decrescente");
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Saida/random");
        
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Tempo/crescente");
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Tempo/decrescente");
        fs::create_directories("Arquivos/" + algoritmos.at(algoritmo) + "/Tempo/random");
    }    
}

// leitura e escrita de dados
void gerarEntrada(const string& tipo, const string& caminhoEntrada, int tamanho){
    vector<int> vetor;
    ofstream arquivo(caminhoEntrada);

    if(!arquivo.is_open()){
        cerr << "Erro ao salvar arquivo: " << caminhoEntrada << "\n";
        return;
    }

    if(tipo == "crescente"){
        for(int i = 0; i<tamanho;i++){
            vetor.push_back(i+1);
        }
    }else if(tipo == "decrescente"){
        for(int i = tamanho; i>0; i--){
            vetor.push_back(i);
        }
    }else if(tipo == "random"){
        for(int i = 0; i<tamanho;i++){
            vetor.push_back(i+1);
        }
        random_device rd;
        mt19937 gerador(rd());
        shuffle(vetor.begin(),vetor.end(),gerador);
    }

    arquivo << tamanho << "\n";
    for(int valor : vetor){
        arquivo << valor << "\n";
    }

    cout << "Entrada gerada com sucesso em: " << caminhoEntrada << "\n";
    arquivo.close();
}

vector<int> carregarEntrada(const string& caminhoEntrada){
    vector<int> numeros;
    ifstream arquivo(caminhoEntrada);

    if(!arquivo.is_open()){
        cerr << "Erro ao abrir arquivo: " << caminhoEntrada << "\n";
        return numeros;
    }

    int qtd;
    arquivo >> qtd;

    int valor;
    while(arquivo >> valor){
        numeros.push_back(valor);
    }

    arquivo.close();
    return numeros;

}

void salvarSaida(vector<int> vetor, const string& caminhoSaida, int tamanho){
    ofstream arquivo(caminhoSaida);

    if(!arquivo.is_open()){
        cerr << "Erro ao salvar arquivo: " << caminhoSaida << "\n";
        return;
    }

    arquivo << tamanho << "\n";
    for(int valor : vetor){
        arquivo << valor << "\n";
    }
    cout << "Saida salva com sucesso em: " << caminhoSaida << "\n";
    arquivo.close();
}

void salvarTempo(double tempoCientifico, const string& caminhoTempo, int tamanho){
    ofstream arquivo(caminhoTempo);

    if(!arquivo.is_open()){
        cerr << "Erro ao salvar arquivo: " << caminhoTempo << "\n";
        return;
    }

    arquivo << "Tamanho:" << tamanho << "\n";
    arquivo << "Tempo de execucao:" << tempoCientifico << "\n";

    cout << "Tempo salvo com sucesso em: " << caminhoTempo << "\n";
    arquivo.close();
}

void abrirArquivo(const string& caminho) {
    #ifdef _WIN32
        string comando = "start \"\" \"" + caminho + "\"";
    #else
        string comando = "xdg-open \"" + caminho + "\"";
    #endif
        system(comando.c_str());
}