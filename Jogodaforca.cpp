#include<iostream>
#include<string>
#include<stdlib.h>
#include<map>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
using namespace std;

string palavra_secreta = "MELANCIA";
map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe (char chute){
       for (int i = 0; i < palavra_secreta.size();i++){
        if (chute == palavra_secreta[i]){
            return true;
        }
    }
    return false;
}
    
bool nao_acertou(){
	for(char letra : palavra_secreta){
		if(!chutou[letra]){
			return true;
		}
	}
	return false;
}

bool nao_enforcou(){
	return chutes_errados.size() < 5;
}

void imprime_cabecalho(){
	cout << "  *************************" << endl;
	cout << "  **    JOGO DA FORCA    **" << endl;
	cout << "  *************************" << endl;
	cout << endl;
	
}

void imprime_erros(){
	cout << "\n  Chutes errados: ";
    	for(char letra: chutes_errados){
    		cout << letra << " ";
		}
    	cout << endl;
    	cout << endl;
}

void imprime_palavra(){
	for(char letra : palavra_secreta){
    		if( chutou [letra]){
    			cout << letra << " ";
			}
			else{
				cout << "_ ";
			}
		}
		cout << endl;
}

void chuta(){
	cout << "\n  Seu chute: ";
        char chute;
        cin >> chute;
        
        chutou [chute] = true;

        if (letra_existe(chute)){
            cout << "Voce acertou! Seu chute está na palavra." << endl;
        }
        else {
            cout << "Voce errou! Seu chute não está na palavra." << endl;
            chutes_errados.push_back(chute);
        }
        cout << endl;
}

vector<string> ler_arquivo(){
	ifstream arquivo;
	arquivo.open("palavras.txt");
	int i;
	
	if(arquivo.is_open()){
	
	int quantidade_palavras;
	arquivo >> quantidade_palavras;
	
	vector<string> palavras_do_arquivo;
	
	for(i=0; i<quantidade_palavras; i++){
		string palavra_lida;
		arquivo >> palavra_lida;
		palavras_do_arquivo.push_back(palavra_lida);
	}
	
	arquivo.close();
	return palavras_do_arquivo;
    }
    else{
    	cout << "não foi possivel acessar o banco de palavras" << endl;
    	exit(0);
	}
}

void sorteia_palavra(){
	vector<string> palavras=ler_arquivo();
	
	srand(time(NULL));
	int indice_sorteado = rand() % palavras.size();
	
	palavra_secreta = palavras[indice_sorteado];
}

void salva_arquivo(vector<string> nova_lista){
	
	ofstream arquivo;
	arquivo.open("palavras.txt");
	if(arquivo.is_open()){
		arquivo << nova_lista.size() << endl;
		
		for(string palavra : nova_lista){
			arquivo << palavra << endl;
		}
		
		arquivo.close();
	}
	else{
		cout << "não foi possivel acessar o banco de palavras" << endl;
    	exit(0);
	}
	
}

void adiciona_palavra(){
	
	cout << " digite a nova palavra usando letras maiusculas: " << endl;
	string nova_palavra;
	cin >> nova_palavra;
	
	vector<string> lista_palavras = ler_arquivo();
	lista_palavras.push_back(nova_palavra);
	
	salva_arquivo(lista_palavras);
}

int main(){
	imprime_cabecalho();
	
	ler_arquivo();
	sorteia_palavra();
	
    while (nao_acertou() && nao_enforcou()){
    	
    	imprime_erros();
    	
    	imprime_palavra();
    	
    	chuta();
    }
    
    cout << " Fim de jogo!" << endl;
    if(nao_acertou()){
    	cout<< "  VOCE PERDEU! TENTE NOVAMENTE! \n";
    	cout<< "  A palavra secreta era: " << palavra_secreta << endl;
	}
	else{
		cout << "  Parabens, voce acertou a palavra secreta!" << endl;
		cout<< "  A palavra secreta era: " << palavra_secreta << endl;
		
		cout<< " voce deseja adicionar uma nova palavra ao banco? (S/N)" << endl;
		char resposta;
		cin >> resposta;
		if(resposta =='S'){
			adiciona_palavra();
		}
		
	}
	
}
