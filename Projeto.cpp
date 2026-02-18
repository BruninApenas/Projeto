#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Filme {          
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

void ListarIntervalo(Filme* BancoDeDados, int quantidade){ //Buscar o arquivo inteiro ou o trecho informado pelo usuário
    cout << "\n---Listar intervalo de filmes---" << endl;
    cout << "Existem " << quantidade << " filmes cadastrados" << endl;

    int Inicio,Fim;
    cout << "Digite a posição inicial (ex: 1): ";
    cin >> Inicio;
    cout << "Digite a posição final (ex: 10): ";
    cin >> Fim;
    
    if (Inicio < 1 and Fim > quantidade and Inicio > Fim)
    {
        cout << "Intervalo inválido! tente novamente";
        return;
    }

    cout << "\n--- Filmes do " << Inicio << " ao " << Fim << " ---" << endl;

    for (int i = (Inicio - 1); i < Fim; i++)
    {
        if (BancoDeDados[i].id > 0)
        {
            cout << "Posição " << (i +1) << "-->"
                 << "ID: " << BancoDeDados[i].id
                 << "| Nome: " << BancoDeDados[i].nome
                 << "| Ano: " << BancoDeDados[i].ano << endl;
        }
        else
        {
            cout << "Posição " << (i + 1) << " --> [Registro excluído]" << endl;
        }  
    }
}
void SalvarArquivo(Filme* BancoDeDados, int quantidade) { // Salva o arquivo do banco de dados em um .txt conforme solicidtado na tarefa
    ofstream arquivo("C:\\Users\\amara\\Codigos_prog1\\BancoDeDados.txt"); //Cria o fluxo de saída

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
    cout << "Dados salvos corretamentes no arquivo BancoDeDados.txt" << endl;
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
    cin.ignore();

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

void BuscarFilme(Filme* BancoDeDados, int quantidade) { 
    int Opção;
    cout << "\n--- Busca de Filmes ---" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por nome" << endl;
    cout << "3. Buscar por genero" << endl;
    cout << "4. Buscar por ano de lançamento" << endl;
    cout << "Escolha --> ";
    cin >> Opção;


    bool Achou = false;

    if (Opção == 1) 
    {
        int IdProcurado;
        cout << "Digite o ID do Filme: ";
        cin >> IdProcurado;

        for (int i = 0; i < quantidade && !Achou; i++) 
        {
            if (BancoDeDados[i].id == IdProcurado && BancoDeDados[i].id > 0) 
            {
                cout << "\nEncontrado: " << BancoDeDados[i].nome
                     << " (" << BancoDeDados[i].ano << ")"
                     << "\nSinopse: " << BancoDeDados[i].sinopse << endl;
                Achou = true; 
            }    
        }
    }

   
    else if (Opção == 2)
    {
        string NomeProcurado;
        cout << "Digite o nome exato: ";
        cin.ignore();
        getline(cin, NomeProcurado);

        for (int i = 0; i < quantidade; i++)
        {
            if (BancoDeDados[i].nome == NomeProcurado && BancoDeDados[i].id > 0)
            {
                cout << "\nEncontrado: " << BancoDeDados[i].nome
                     << " (" << BancoDeDados[i].ano << ")"
                     << "\nSinopse: " << BancoDeDados[i].sinopse << endl;
                Achou = true;
            }
        } 
    }

    else if (Opção == 3 || Opção == 4) 
    {
        string BuscarGênero;
        int BuscarAno = 0;
        bool EntradaVálida = true;

        if (Opção == 3) {
            cout << "Digite o genero: ";
            cin.ignore();
            getline(cin, BuscarGênero);
        } else if (Opção == 4) {
            cout << "Digite o ano de lancamento: ";
            cin >> BuscarAno;
        } else {
            cout << "Opcao invalida, tente novamente";
            EntradaVálida = false;
        }
    
        if (EntradaVálida) {
            cout << "\n--- Resultados da busca ---" << endl;

            if (Opção == 3) cout << "Genero: " << BuscarGênero << endl;
            if (Opção == 4) cout << "Ano: " << BuscarAno << endl;
            cout << "---------------------------" << endl;

            for (int i = 0; i < quantidade; i++)
            {
                if (BancoDeDados[i].id > 0) 
                {
                    
                    bool match = false;
                    
                    if (Opção == 3 && BancoDeDados[i].genero == BuscarGênero) match = true;
                    if (Opção == 4 && BancoDeDados[i].ano == BuscarAno) match = true;

                    if (match)
                    {
                        cout << "ID: " << BancoDeDados[i].id << " - " << BancoDeDados[i].nome << endl;
                        Achou = true; 
                    }
                }
            }     
        }   
    }
    
    if (!Achou) 
    {
        cout << "Nenhum registro encontrado." << endl;
    }
}
void RemoverFilme(Filme*& BancoDeDados, int& quantidade) {

    cout << "\n--- Remover Filme ---" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por nome" << endl;
    cout << "3. Buscar por gênero" << endl;
    cout << "4. Buscar por ano de lançamento" << endl;
    cout << "Escolha --> ";
    int Opção;
    cin >> Opção;

    bool Removido = false;

    if (Opção == 1) 
    {
        int IdProcurado;
        cout << "Digite o ID do Filme: ";
        cin >> IdProcurado;

        for (int i = 0; i < quantidade and !Removido; i++) 
        {
            if (BancoDeDados[i].id == IdProcurado and BancoDeDados[i].id > 0) // Verifica se Achou e se não está deletado
            {
                BancoDeDados[i].id = -1;
                cout << "Filme " << BancoDeDados[i].nome << " removido!";
                Removido = true;
            }     
        }
        if (!Removido)
        {
        cout << "Id não encontrado." << endl;
        }
    }

    else if (Opção == 2)
    {
        string NomeProcurado;
        cout << "Digite o nome exato: ";

        cin.ignore();
        getline(cin, NomeProcurado);

        for (int i = 0; i < quantidade and !Removido; i++)
        {
            if (BancoDeDados[i].nome == NomeProcurado and BancoDeDados[i].id > 0)
            {
                BancoDeDados[i].id = -1;
                cout << "Filme --" << NomeProcurado << "-- removido!" << endl;
                Removido = true;
            }
        }
        if (!Removido)
        {
        cout << "Nome não encontrado." << endl;
        }    
    }

    else if (Opção == 3 or Opção == 4)
    {
        string BuscarGênero;
        int BuscarAno = 0;
        bool EntradaVálida = true;

        if (Opção == 3)
        {
            cout << "Digite o gênero: ";
            cin.ignore();
            getline(cin, BuscarGênero);
        }
        else if (Opção == 4)
        {
            cout << "Digite o ano de lançamento: ";
            cin >> BuscarAno;
        }
        else
        {
            cout << "Opção inválida, tente novamente";
            EntradaVálida = false;
        }
    
        if (EntradaVálida){
            cout<< "\n--- Filmes Encontrados ---" << endl;

            bool EncontrouAlgum = false;

            for (int i = 0; i < quantidade; i++)
            {
                if (BancoDeDados[i].id < 0) {}

                else
                {
                    bool Achou = false;
                    if (Opção == 3 and BancoDeDados[i].genero == BuscarGênero) Achou = true;
                    if (Opção == 4 and BancoDeDados[i].ano == BuscarAno) Achou = true;

                    if (Achou)
                    {
                    cout << "ID: " << BancoDeDados[i].id << "-" << BancoDeDados[i].nome << endl;
                    EncontrouAlgum = true;
                    }
                }
            }   
        
            if (EncontrouAlgum) 
            {
                int IdParaRemover;
                cout << "\nDigite o ID do filme acima que deseja remover: ";
                cin >> IdParaRemover;

                for (int i = 0; i < quantidade and !Removido; i++)
                {
                    if (BancoDeDados[i].id == IdParaRemover and BancoDeDados[i].id > 0)
                    {
                        BancoDeDados[i].id = -1;
                        cout << "Filme removido!!" << endl;
                        Removido = true;
                    }    
                }
                if (!Removido) {
                    cout << "ID inválido ou não encontrado na lista" << endl;   
                }   
            }
            else
            {
            cout << "Nenhum filme encontrado com esses dados." << endl;
            }        
        }   
    }
}
void CarregarArquivo(Filme*& BancoDeDados, int& capacidade, int& quantidade) { // Faz a leitura do arquivo e preenchimento do vetor
    ifstream arquivo("C:\\Users\\amara\\Codigos_prog1\\BancoDeDados.txt");

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
        cout << "5. Listar por intervalo" << endl;
        cout << "6. Buscar filme" << endl;
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
            Continuar = false;
            break;  
        case 4:
            RemoverFilme(BancoDeDados, quantidade);
            break;
        case 5:
            ListarIntervalo(BancoDeDados, quantidade);
            break;
        case 6:
            BuscarFilme(BancoDeDados, quantidade);
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
    }
}
    delete[] BancoDeDados;
    return 0;    
}

   
