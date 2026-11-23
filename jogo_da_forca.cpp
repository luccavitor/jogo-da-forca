
#include <iostream> // Biblioteca para utilizar entrada e saída de dados
#include <string> // Biblioteca para trabalhar com textos (strings)
#include <map> // Biblioteca para armazenar pares de chave e valor
#include <vector> // Biblioteca para criar listas dinâmicas
#include <fstream> // Biblioteca para ler e escrever arquivos
#include <ctime> // Biblioteca para trabalhar com data e horário
#include <cstdlib> // Biblioteca para utilizar funções como rand() e exit()
using namespace std;

// Armazena a palavra secreta que será sorteada pelo programa
string palavra_secreta;

// Tabela que registra as letras que já foram chutadas
map<char, bool> chutou;

// Lista que armazena os chutes de letras erradas
vector<char> chutes_errados;


// Verifica se a letra digitada pelo jogador existe na palavra secreta
bool letra_existe(char chute){
    // Percorre todas as letras da palavra secreta
    for(char letra : palavra_secreta){
        if(chute == letra){
            return true; // Retorna true se encontrar a letra
        }
    }
    return false; // Retorna false se a letra não estiver na palavra
}


// Verifica se ainda existem letras que não foram descobertas
bool nao_acertou(){
    // Percorre todas as letras da palavra secreta
    for(char letra : palavra_secreta){
        if(!chutou[letra]){
            return true; // Retorna true se existir alguma letra não descoberta
        }
    }
    return false; // Retorna false quando todas as letras forem descobertas
}


// Verifica se o jogador ainda possui tentativas disponíveis
bool nao_enforcou(){
    return chutes_errados.size() < 5; // O jogador pode errar até 4 vezes
}


// Exibe o cabeçalho e o nome do jogo
void imprime_cabecalho(){
    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}


// Imprime a lista de letras que o jogador chutou incorretamente
void imprime_erros(){
    cout << "Chutes errados: ";

    // Percorre a lista de chutes errados e imprime cada letra
    for(char letra: chutes_errados){
        cout << letra << " ";
    }
    cout << endl;
}


// Exibe as letras descobertas e os espaços das letras ainda não encontradas
void imprime_palavra(){
    // Percorre todas as letras da palavra secreta
    for(char letra : palavra_secreta){
        if(chutou[letra]){
            cout << letra << " "; // Exibe a letra quando ela já foi chutada
        }
        else{
            cout << "_ "; // Exibe um espaço quando a letra ainda não foi descoberta
        }
    }
    cout << endl;
}


// Recebe o chute do jogador e verifica se a letra está na palavra secreta
void chuta(){
    cout << "Seu chute: ";
    char chute;
    cin >> chute; // Recebe uma letra digitada pelo jogador

    // Registra no map que a letra já foi chutada
    chutou[chute] = true;

    // Verifica se a letra digitada existe na palavra secreta
    if(letra_existe(chute)){
        cout << "Você acertou! Seu chute está na palavra." << endl;
    }
    else{
        cout << "Você errou! Seu chute não está na palavra." << endl;

        // Adiciona a letra incorreta ao vetor de chutes errados
        chutes_errados.push_back(chute);
    }
    cout << endl;
}


// Lê o arquivo palavras.txt e retorna uma lista com as palavras armazenadas
vector<string> le_arquivo(){
    ifstream arquivo; // Cria um objeto para realizar a leitura do arquivo
    arquivo.open("palavras.txt"); // Abre o arquivo palavras.txt

    // Verifica se o arquivo foi aberto corretamente
    if(arquivo.is_open()){
        int quantidade_palavras;

        // Lê a quantidade de palavras armazenadas no arquivo
        arquivo >> quantidade_palavras;

        // Cria um vetor para armazenar as palavras lidas
        vector<string> palavras_do_arquivo;

        // Repete a leitura de acordo com a quantidade de palavras informada
        for(int i=0;i<quantidade_palavras;i++){
            string palavra_lida;

            // Lê uma palavra do arquivo
            arquivo >> palavra_lida;

            // Adiciona a palavra lida ao vetor
            palavras_do_arquivo.push_back(palavra_lida);
        }

        arquivo.close(); // Fecha o arquivo após a leitura

        return palavras_do_arquivo; // Retorna o vetor com todas as palavras
    }
    else{
        // Exibe uma mensagem caso não consiga abrir o arquivo
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0); // Encerra o programa
    }
}


// Sorteia aleatoriamente uma palavra do banco de palavras
void sorteia_palavra(){
    // Recebe a lista de palavras retornada pela função le_arquivo()
    vector<string> palavras = le_arquivo();

    // Inicializa o gerador de números aleatórios utilizando o horário atual
    srand(time(NULL));

    // Sorteia um índice entre zero e o tamanho do vetor menos um
    int indice_sorteado = rand() % palavras.size();

    // Atribui à palavra secreta a palavra que corresponde ao índice sorteado
    palavra_secreta = palavras[indice_sorteado];
}


// Salva a lista atualizada de palavras no arquivo palavras.txt
void salva_arquivo(vector<string> nova_lista){
    ofstream arquivo; // Cria um objeto para escrever no arquivo
    arquivo.open("palavras.txt"); // Abre o arquivo para escrita

    // Verifica se o arquivo foi aberto corretamente
    if(arquivo.is_open()){

        // Salva a quantidade atual de palavras na primeira linha
        arquivo << nova_lista.size() << endl;

        // Percorre o vetor e salva cada palavra no arquivo
        for(string palavra : nova_lista){
            arquivo << palavra << endl;
        }

        arquivo.close(); // Fecha o arquivo após salvar as informações
    }
    else{
        // Exibe uma mensagem caso não consiga abrir o arquivo
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0); // Encerra o programa
    }
}


// Permite adicionar uma nova palavra ao banco de palavras
void adiciona_palavra(){
    cout << "Digite a nova palavra, usando letras maiúsculas." << endl;

    string nova_palavra;
    cin >> nova_palavra; // Recebe a nova palavra digitada pelo jogador

    // Lê todas as palavras que já estão armazenadas no arquivo
    vector<string> lista_palavras = le_arquivo();

    // Adiciona a nova palavra ao final do vetor
    lista_palavras.push_back(nova_palavra);

    // Salva o vetor atualizado no arquivo palavras.txt
    salva_arquivo(lista_palavras);
}


// Função principal: inicia e controla a execução do jogo
int main () {

    // Exibe o cabeçalho do jogo
    imprime_cabecalho();

    // Lê o banco de palavras e sorteia a palavra secreta
    le_arquivo();
    sorteia_palavra();

    // Continua executando enquanto o jogador não acertar todas as letras
    // e ainda possuir tentativas disponíveis
    while(nao_acertou() && nao_enforcou()){

        // Exibe as letras que foram chutadas incorretamente
        imprime_erros();

        // Exibe a palavra com as letras descobertas
        imprime_palavra();

        // Solicita uma nova letra ao jogador
        chuta();
    }

    // Exibe a mensagem de encerramento do jogo
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;

    // Verifica se o jogador perdeu ou conseguiu descobrir a palavra
    if(nao_acertou()){
        cout << "Você perdeu! Tente novamente!" << endl;
    }
    else{
        cout << "Parabéns! Você acertou a palavra secreta!" << endl;

        // Pergunta se o jogador deseja adicionar uma nova palavra ao banco
        cout << "Você deseja adicionar uma nova palavra ao banco? (S/N) ";

        char resposta;
        cin >> resposta; // Recebe a resposta do jogador

        // Verifica se o jogador escolheu adicionar uma nova palavra
        if(resposta == 'S'){
            adiciona_palavra(); // Chama a função responsável pelo cadastro
        }
    }
}
