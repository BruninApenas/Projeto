#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
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
void SalvarArquivo(Filme* BancoDeDados, int quantidade) { // Salva o arquivo do banco de dados em um .txt conforme solicidtado na tarefa
    ofstream arquivo("C:\\Users\\amara\\C++\\bancodedados.txt"); //Cria o fluxo de saída

    if (!arquivo.is_open()) { // Verificar se o arquivo abriu corretamente
        cout << "Não foi possivel criar o arquivo" << endl;
        return;
    }

    for (int i = 0; i < quantidade; i++) { // Percorrer o banco de dados linha por linha
        arquivo << BancoDeDados[i].id << ";"
                << BancoDeDados[i].nome << ";"
                << BancoDeDados[i].genero << ";"
                << BancoDeDados[i].ano << ";"
                << BancoDeDados[i].sinopse << endl;
    }

    arquivo.close();
    cout << "Dados salvos corretamentes no arquivo bancodedados.txt" << endl;
} 

void CarregarArquivo(Filme*& BancoDeDados, int& capacidade, int& quantidade) { // Faz a leitura do arquivo e preenchimento do vetor
    ifstream arquivo("C:\\Users\\amara\\C++\\bancodedados.txt");

    if (!arquivo.is_open()) {  // Se o arquivo não existir (primeira vez que usa), não faz nada
        cout << "Nenhum arquivo encontrado. Começando do zero." << endl;
        return;
    }

    string TempId, nome, genero, TempAno, sinopse; // Variáveis temporárias para ler o texto do arquivo, está em string pq o id e o ano são números, então vou converte-los futuramente

    while (getline(arquivo, TempId, ';')) {  // Enquanto conseguir ler o primeiro pedaço
        
        if (quantidade >= capacidade) { // Verifica se precisa redimensionar antes de adicionar
            redimensionar(BancoDeDados, capacidade, quantidade);
        }

        getline(arquivo, nome, ';'); // Lê o resto da linha, pedaço por pedaço
        getline(arquivo, genero, ';');
        getline(arquivo, TempAno, ';');
        getline(arquivo, sinopse);

        BancoDeDados[quantidade].id = atoi(TempId.c_str()); // 3. Converter texto para número e salvar no vetor
        BancoDeDados[quantidade].nome = nome;
        BancoDeDados[quantidade].genero = genero;
        BancoDeDados[quantidade].ano =atoi(TempAno.c_str());
        BancoDeDados[quantidade].sinopse = sinopse;

        quantidade++;
    }

    arquivo.close();
    cout << quantidade << " filmes carregados com sucesso" << endl;
}


int main() {
    int quantidade = 0;   // Comecei com 0 filmes cadastrados 
    int capacidade = 40;   // Capacidade inicial para 40 filmes, mas posso mudar futuramente
    Filme* BancoDeDados = new Filme[capacidade];

  
    delete[] BancoDeDados;
    return 0;    
}
