#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
using namespace std;

string palavra_secreta = "MELANCIA";
map<char, bool> chutes;
vector<char> chutes_errados;

bool letraexiste(char chute) {

    // VERSÃO MELHORADA NO C++ 11
    for(char letra : palavra_secreta) {
        if(letra == chute)
            return true;
    }

    // SINTAXE ANTIGA
    // for(short i = 0; i < palavra_secreta.size(); i++) {
    //     if(chute == palavra_secreta[i])
    //         return true;
    // }

    return false;
}

bool ganhou() {
    for(char letra : palavra_secreta) {
        if(!chutes[letra])
            return false;
    }

    return true;
}

bool enforcou() {
    return chutes_errados.size() > 5;
}

void imprimecabecalho() {
    cout << "************************" << endl;
    cout << "***JOGO DA FORCA C++ ***" << endl;
    cout << "************************" << endl;
}

void imprimechuteserrados() {
    cout << "Chutes errados: ";

    for(char chute : chutes_errados) {
        cout << chute << " ";
    }

    cout << endl;
}

void imprimepalavrasecreta() {
    for (char letra : palavra_secreta) {
        if(chutes[letra])
            cout << letra << " ";
        else
            cout << "_ ";
    }

    cout << endl;
}

void chuta() {
    cout << "Seu chute: ";
    char chute;
    cin >> chute;

    if(letraexiste(chute)) {
        cout << "Esta na palavra" << endl;
    } else {
        chutes_errados.push_back(chute);
        cout << "Não está na palavra" << endl;
    }

    chutes[chute] = true;
}

vector<string> letodaspalavras() {
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if(!arquivo.is_open()) {
        cout << "Falha ao abrir banco de palavras" << endl;
        exit(0);
    }

    int quantidade_palavras;
    arquivo >> quantidade_palavras;

    vector<string> palavras;

    for (short i = 0; i < quantidade_palavras; i++) {
        string palavra;
        arquivo >> palavra;

        palavras.push_back(palavra);
    }

    arquivo.close();

    return palavras;
}

void sorteiapalavra() {

    vector<string> palavras = letodaspalavras();

    if(palavras.size() == 0) {
        cout << "Não foram localizadas palavras para sortear" << endl;
        exit(0);
    }
    
    srand(time(NULL));
    short index = rand() % palavras.size();

    palavra_secreta = palavras[index];
}

void inserirnovapalavra() {

    vector<string> palavras = letodaspalavras();

    cout << "Digite a nova palavra (USANDO LETRAS MAIUSCULAS)";
    string nova_palavra;
    cin >> nova_palavra;

    ofstream arquivo;
    arquivo.open("palavras.txt");

    if(!arquivo.is_open()) {
        cout << "Falha ao abrir arquivo de palavras" << endl;
        exit(0);
    }

    palavras.push_back(nova_palavra);
    arquivo << palavras.size();

    for(short i = 0; i < palavras.size(); i++) {
        arquivo << endl << palavras[i];
    }

    arquivo.close();
}

int main() {

    sorteiapalavra();

    while(!ganhou() && !enforcou()) {
        system("clear||cls");
        imprimecabecalho();
        imprimechuteserrados();
        imprimepalavrasecreta();
        chuta();
    }

    cout << "A palavra secreta era " << palavra_secreta << endl;
    if(ganhou()){
        cout << "Parabéns, você ganhou" << endl;
        cout << "Deseja adicionar uma nova palavra ao banco? (S/N)";
        char op;
        cin >> op;

        if(op == 'S') {
            inserirnovapalavra();
        }
    }
    else
        cout << "Você perdeu! jogue novamente" << endl;
}