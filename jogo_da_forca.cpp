#include <iostream> // Biblioteca para utilizar entrada e saída de dados
#include <string>
using namespace std;  


// Declarando a palavra secreta
    const string PALAVRA_SECRETA = "MELANCIA";
    
    
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


    

int main(){
    
    //Nome do jogo
    cout << "Bem-vindo ao jogo da forca." << endl;
    

    // Criando uma variável para quando não acertar ou não perder os chutes
    bool nao_acertou = true;  
    bool nao_enforcou = true; 
    
    
    // Estrutura de repetição para quando não estiver certo ainda continuar executando
    while(nao_acertou && nao_enforcou){
        
        char chute;
        cout << "Digite a letra que você deseja chutar: " << endl;
        cin >> chute;
        
        //Condição para ver se a letra está dentro da palavra secreta
        if(letra_existe(chute)){
            cout << "Você acertou! Seu chute está na palavra." << endl;
        }
        else {
            cout << "Você errou! Seu chute não está na palavra. Tente outra letra." << endl;
        }
    }
}
