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

    BancoDeDados = NovoBancoDeDados;  // Volta para a variável padrão com o tamannho aumentado 
    capacidade = NovaCapacidade;  // Atualiza a nova capacidade

    cout <<"Redimensionado para " << NovaCapacidade << endl;

}
void SalvarArquivo(Filme* BancoDeDados, int quantidade) { // Salva o arquivo do banco de dados em um .txt conforme solicidtado na tarefa
    ofstream arquivo("C:\\Users\\amara\\C++\\bancodedados.txt"); //Cria o fluxo de saída

    if (!arquivo.is_open()) 
    { // Verificar se o arquivo abriu corretamente
        cout << "Não foi possivel criar o arquivo" << endl;
        return;
    }

    for (int i = 0; i < quantidade; i++) // Percorrer o banco de dados linha por linha
    {
        if (BancoDeDados[i].id > 0)
        {
        arquivo << BancoDeDados[i].id << ";"
                << BancoDeDados[i].nome << ";"
                << BancoDeDados[i].genero << ";"
                << BancoDeDados[i].ano << ";"
                << BancoDeDados[i].sinopse << endl;
        }
    }

    arquivo.close();
    cout << "Dados salvos corretamentes no arquivo bancodedados.txt" << endl;
} 

void Inserirfilme (Filme*& BancoDeDados, int& capacidade, int& quantidade) {

    string TempAno; // O getline não consegue ler o Ano pq esta função só lê string, então vou fazer ela ler o ano em string e no final converto pra número
    
    if (quantidade >= capacidade) 
    { // Verifica se a capacidade está cheia e aumenta caso esteja
        cout << "Aumentando espaço" << endl;
        redimensionar(BancoDeDados, capacidade, quantidade);
    }

    cout <<"\n --- Cadastro de Novo Filme ---" << endl;

    BancoDeDados[quantidade].id = quantidade + 1; // Gera o id automaticamente
    cout << "ID Gerado: " << BancoDeDados[quantidade].id << endl;

    cout << "Nome do filme: ";
    getline(cin, BancoDeDados[quantidade].nome);

    cout<< "Genero: ";
    getline(cin, BancoDeDados[quantidade].genero);

    cout<< "Qual o ano de lançamento do filme: ";
    getline(cin, TempAno);
    
    BancoDeDados[quantidade].ano = atoi(TempAno.c_str());

    cout<< "Diga a sinopse: ";
    getline(cin, BancoDeDados[quantidade].sinopse);


    quantidade++;
    cout << "Filme cadastrado!" << endl;
}

void RemoverFilme(Filme*& BancoDeDados, int& quantidade) {

    cout << "\n--- Remover Filme ---" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por Nome" << endl;
    cout << "3. Buscar por gênero" << endl;
    cout << "4. Buscar por ano de lançamento" << endl;
    cout << "Escolha: ";
    int Opção;
    cin >> Opção;

    bool encontrou = true;

    if (Opção == 1)
    {
        int IdProcurado;
        cout << "Digite o ID do Filme: "
        cin >> IdProcurado;

        for (int i = 0; i < quantidade; i++) 
        {
            if (BancoDeDados[i].id == IdProcurado and BancoDeDados[i].id > 0) // Verifica se achou e se não está deletado
            {
                BancoDeDados[i].id = -1;
                cout << "Filme removido!";
                return;
            }     
        }
        cout << "Id não encontrado." << endl;
    }

    else if (Opção == 2);
    {
        string NomeProcurado;
        cout << "Digite o nome exato: ":
        getline(cin, NomeProcurado);

        for (int i = 0; i < quantidade; i++)
        {
            if (BancoDeDados[i].nome == NomeProcurado and BancoDeDados[i].id > 0)
            {
                BancoDeDados[i].id = -1;
                cout << "Filme" << NomeProcurado << "removido!" << endl;
                return;
            }
        }
        cout << "Nome não encontrado." << endl;    
    }

    else if (Opção == 3 or Opção == 4)
    {
        string BuscarGenero;
        int BuscarAno = 0;
    }
    

    
    
    for (int i = 0; i < quantidade; i++)
    {
        if (BancoDeDados[i].nome == NomeProcurado)
        {
            encontrou = false;
            cout << "Filme " << NomeProcurado << "encontrado!" << endl;

            for (int j = i; j < quantidade - 1; j++)
            {
                BancoDeDados[j] = BancoDeDados [j + 1];
            }

            quantidade --;

            cout << "Filme removido com sucesso!" << endl; 
        }

        else if (BancoDeDados[i].id = IdProcurado)
        {
           
        }
        

        else
        {
            cout << "Erro : Filme não encontrado com esse nome exato" << endl;
        }
        
        

        
    }
}
void CarregarArquivo(Filme*& BancoDeDados, int& capacidade, int& quantidade) { // Faz a leitura do arquivo e preenchimento do vetor
    ifstream arquivo("C:\\Users\\amara\\C++\\bancodedados.txt");

    if (!arquivo.is_open()) 
    {  // Se o arquivo não existir, não faz nada
        cout << "Nenhum arquivo encontrado. Começando do zero." << endl;
        return;
    }

    string TempId, nome, genero, TempAno, sinopse; // Variáveis temporárias para ler o texto do arquivo, está em string pq o id e o ano são números, então vou converte-los futuramente

    while (getline(arquivo, TempId, ';')) {  // Getline funciona assim:  getline(DE ONDE LER, PARA ONDE GUARDAR, ATE QUAL LETRA PARAR);
        
        if (quantidade >= capacidade) 
        { // Verifica se precisa redimensionar antes de adicionar
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
}


int main() {
    int quantidade = 0;   // Comecei com 0 filmes cadastrados 
    int capacidade = 40;   // Capacidade inicial para 40 filmes, mas posso mudar com a função redimensionar
    bool Continuar = true;
    int Opção_usuário = 0;
    Filme* BancoDeDados = new Filme[capacidade];

    CarregarArquivo(BancoDeDados, capacidade, quantidade);

    while (Continuar)
    {
        cout << "\n----- BEM VINDO A LISTA DE FILMES -----" << endl;
        cout << "1. Inserir novo filme " << endl;
        cout << "2. Listar todos" << endl;
        cout << "3. Salvar e sair" << endl;
        cout << "4. Remover filme" << endl;
        cout << "Escolha uma opção" << endl << "--> ";
        cin >> Opção_usuário;

        switch (Opção_usuário)
        {
        case 1:
            Inserirfilme ( BancoDeDados, capacidade, quantidade);
            break;
        case 2:
            cout << "\n----- LISTA DE FILMES -----" << endl;
            for (int i = 0; i < quantidade; i++)
            {
                if (BancoDeDados[i].id > 0)
                {
                    cout << "ID: " << BancoDeDados[i].id << "-" << BancoDeDados[i].nome << endl;
                }
                
            }
            break;
        case 3:
            SalvarArquivo(BancoDeDados, quantidade);
            cout << "Saindo.." << endl;
            break;  
        case 4:
            RemoverFilme(BancoDeDados, quantidade);
            break;
    }
}
    


    delete[] BancoDeDados;
    return 0;    
}

   
