#include <iostream> // Biblioteca para utilizar entrada e saída de dados
#include <string>
#include <map>
#include <vector>
using namespace std;  

    
    // Declarando a palavra secreta
    const string PALAVRA_SECRETA = "MELANCIA";
    // Tabela das letras de chutes
    map <char, bool> chutou;
    // Tabela para chutes de letras erradas
    vector<char> chutes_errados;
        
    // for diferente:serve para percorrer todos os elementos do início ao fim, de forma automática.
    // char letra:A cada repetição,ela recebe automaticamente o valor da próxima letra da palavra.
    // : Leia como "em" ou "dentro de".
    
    bool letra_existe(char chute){
        for(char letra : PALAVRA_SECRETA){
            if(chute == letra){
             return true;
            }
        }
    return false; // depois que o loop parou ele retorna false pois a letra não esta na palavra.
    }
    
    bool nao_acertou(){
        for(char letra : PALAVRA_SECRETA){
            if(!chutou[letra]){
                return true;
            }
        }
        return false;
    }
    
    
    bool nao_enforcou(){
        return chutes_errados.size() < 5;
    }
    
    
    //Nome do jogo
    void imprime_cabecalho(){
        cout << "Bem-vindo ao jogo da forca." << endl;
        cout << endl;
    }   
    
    //imprimi a lista de chutes errados 
    void imprime_chutes_errados(){
        cout << "Chutes errados: " ;
        for(char letra : chutes_errados){
            cout << letra << " ";
        }
        cout << endl;
    }
    
    // Imprime palavra 
    void imprime_palavra(){
        for(char letra : PALAVRA_SECRETA){
            if(chutou[letra]){
                cout << letra << " ";
            }
            else {
                cout << " _ ";
            }
        }
        cout << endl;
    }
    
    //Recebe um chute e ve se a letra existe ou não existe e da uma mensagem
    void chuta(){
        char chute;
            cout << "Digite a letra que você deseja chutar: " << endl;
            cin >> chute;
            
            // Marcar no map que a letra já foi chutada
            chutou[chute] = true;
            
            //Condição para ver se a letra está dentro da palavra secreta
            if(letra_existe(chute)){
                cout << "Você acertou! Seu chute está na palavra." << endl;
            }
            else {
                cout << "Você errou! Seu chute não está na palavra. Tente outra letra." << endl;
                chutes_errados.push_back(chute);
            }
            cout << endl;
    }
    
    int main(){
        
        //Chamando a função do nome do jogo
        imprime_cabecalho();
        
        // Estrutura de repetição para quando não estiver certo ainda continuar executando
        while(nao_acertou() && nao_enforcou()){
            imprime_chutes_errados();
        
        
        //Para saber se o usuário já chutou a letra e colocar no devido lugar dela
        imprime_palavra();
            
        chuta(); 
        }
        
        cout << "Fim de jogo!" << endl;
        cout << "A palavra secreta é: " << PALAVRA_SECRETA << endl;
        if(nao_acertou()){
            cout << "Você perdeu! Tente novamente!" << endl;
        }
        else{
            cout << "Parabéns! Você acertou a palavra secreta!" << endl;
        }
    }
