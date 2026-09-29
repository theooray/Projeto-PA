#ifndef ARQUIVOS_H
#define ARQUIVOS_H
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

extern const std::unordered_map<int, std::string> algoritmos;

string caminhoEntrada(const string& algoritmo, const string& tipo, int tamanho);
string caminhoSaida(const string& algoritmo, const string& tipo, int tamanho);
string caminhoTempo(const string& algoritmo, const string& tipo, int tamanho);

void criarDiretorio(int algoritmo);

void gerarEntrada(const string& tipo, const string& caminhoEntrada, int tamanho);
vector<int> carregarEntrada(const string& caminhoArquivo);
void salvarSaida(vector<int> vetor, const string& caminhoSaida, int tamanho);
void salvarTempo(double duracaoCientifica, const string& caminhoSaida, int tamanho);
void abrirArquivo(const std::string& caminho);

#endif