#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Filme {          // O molde do projeto
    int id;             // Identificador (inteiro)
    string nome;        // Nome (string com espaço)
    string genero;      // Gênero (string com espaço)
    int ano;            // Ano de lançamento (inteiro)
    string sinopse;     // Sinopse (string com espaço)
};

void redimensionar(Filme*& BancoDeDados, int& capacidade, int quantidade) {  // Função para aumentar de tamanho
    
    int NovaCapacidade = capacidade + 10;

    Filme* NovoBancoDeDados = new Filme[NovaCapacidade];  // Declaração de variavel

    for (int i = 0; i < quantidade; i++) {  // For feito para trocar a posição do banco de dados anttigo pro novo na mesma posição
        NovoBancoDeDados [i] = BancoDeDados [i];
    }

    delete [] BancoDeDados;  // Apaga o array antigo da memória

    BancoDeDados = NovoBancoDeDados;  // O ponteiro principal agora olha pro novo banco de dados
    capacidade = NovaCapacidade;  // Atualiza a nova capacidade

    cout <<"Redimensionado para " << NovaCapacidade << endl;

} 

int main() {
    int quantidade = 0;   // Comecei com 0 filmes cadastrados 
    int capacidade = 40;   // Capacidade inicial para 40 filmes, mas posso mudar futuramente

    Filme* BancoDeDados = new Filme[capacidade];

    if (quantidade == 0) {
        redimensionar(BancoDeDados, capacidade, quantidade);
    }

    delete[] BancoDeDados;
    return 0;
}
