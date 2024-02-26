#include <iostream>
#include <fstream>
#include <locale.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;
const char* dir_arq = "C:\\Users\\x\\";
     // por favor alterar o usuario ^ pro seu proprio!!!!!
char nome_arq[255];


struct pessoa {
    int codigo;
    char nome[40];
    int idade;
   
};

pessoa dados[50];

int posicao = -1;

void criar_pessoa() {
    ++posicao;
    cout << "Matricula: ";
    cin >> dados[posicao].codigo;
    cout << "Nome do Aluno(a): ";
    cin >> dados[posicao].nome;
    cout << "Idade do Aluno(a): ";
    cin >> dados[posicao].idade;
}

void imprimir_todos() {
    printf("%2s %10s %-40s %-10s\n\n", " #", " Matricula", "Nome", "Idade");
    for (int i = 0; i <= posicao; i++) {
        printf("%2d %10d %-40s %-d\n", i, dados[i].codigo, dados[i].nome, dados[i].idade);
    }
    printf("\n");
}

void remover_pessoa() {
    int pos_remocao;
    cout << "Posicao a ser removida: ";
    cin >> pos_remocao;
    if (pos_remocao < 0 || pos_remocao > dados[posicao].codigo)
        cout << "Posicao inválida para os limites atuais\n";
    else {
        for (int i = pos_remocao; i < dados[posicao].codigo; i++) {
            dados[i].idade = dados[i + 1].idade;
            strcpy_s(dados[i].nome, dados[i + 1].nome);
            dados[i].codigo = dados[i + 1].codigo;
        }
        posicao--;
    }
}

void buscar_pessoa() {
    int pos_busca;
    cout << "Posicao a ser buscada: ";
    cin >> pos_busca;
    if (pos_busca < 0 || pos_busca > dados[posicao].codigo)
        cout << "Posicao inválida para os limites atuais\n";
    else {

        printf(" %10s %-40s %-10s\n\n", "Matricula", "Nome", "Idade");
        printf(" %10d %-40s %-d\n", dados[pos_busca].codigo, dados[pos_busca].nome, dados[pos_busca].idade);
        cout << endl;
    }
}

void alterar_pessoa() {
    int pos_alt;
    cout << "Posicao a ser alterada: ";
    cin >> pos_alt;
    if (pos_alt < 0 || pos_alt > dados[posicao].codigo)
        cout << "Posicao inválida para os limites atuais\n";
    else {

        cout << "Matricula: ";
        cin >> dados[pos_alt].codigo;
        cout << "Nome do Aluno(a): ";
        cin >> dados[pos_alt].nome;
        cout << "Idade do Aluno(a): ";
        cin >> dados[pos_alt].idade;
    }
}

void tratar_linha(char buffer[]) {
    posicao++;
    char* token;
    char* next_token = NULL;
    token = strtok_s(buffer, ";", &next_token);
    dados[posicao].codigo = atoi(token); 
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].nome, token);
    token = strtok_s(NULL, ";", &next_token);
    dados[posicao].idade = atoi(token);

}

void ler_arq() {
    posicao = -1;
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_entrada[255];
    strcpy_s(arq_entrada, dir_arq);
    strcat_s(arq_entrada, nome_arq);
    strcat_s(arq_entrada, ".csv");
    ifstream fin(arq_entrada);
    char linha[255];
    while (!fin.eof()) {
        if (fin >> linha) {
            tratar_linha(linha);
        }
    }
    fin.close();
}

void salvar_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_saida[255];
    strcpy_s(arq_saida, dir_arq);
    strcat_s(arq_saida, nome_arq);
    strcat_s(arq_saida, ".csv");
    ofstream fout(arq_saida);
    for (int i = 0; i <= posicao; i++) {
        fout << dados[i].codigo << ";" << dados[i].nome << ";" << dados[i].idade << endl;
    }
    fout.flush();
    fout.close();
}

void trocar(int pos1, int pos2) {
    int cod_aux = dados[pos1].codigo;
    char nome_aux[50];
    strcpy_s(nome_aux, dados[pos1].nome);
    int qtd_aux = dados[pos1].idade;
    dados[pos1].codigo = dados[pos2].codigo;
    strcpy_s(dados[pos1].nome, dados[pos2].nome);
    dados[pos1].idade = dados[pos2].idade;
    dados[pos2].codigo = cod_aux;
    strcpy_s(dados[pos2].nome, nome_aux);
    dados[pos2].idade = qtd_aux;

}

void ordenar_bubble() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (strcmp(dados[i].nome, dados[i + 1].nome) > 0) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
}

void quick_sort(int inicio, int fim) {
    if (inicio >= fim)
        return;
    int pivot = dados[(inicio + fim) / 2].codigo;
    int i = inicio;
    int j = fim;
    while (i <= j) {
        while (dados[i].codigo < pivot)
            i++;
        while (dados[j].codigo > pivot)
            j--;
        if (i <= j) {
            trocar(i, j);
            i++;
            j--;
        }
    }
    quick_sort(inicio, j);
    quick_sort(i, fim);
}


// Menu e Programa Principal
int menu() {
    cout << "1 - Inserir" << endl;
    cout << "2 - Alterar" << endl;
    cout << "3 - Excluir" << endl;
    cout << "4 - Buscar" << endl;
    cout << "5 - Listar Todos" << endl;
    cout << "6 - Ordenar" << endl;
    cout << "7 - Salvar" << endl;
    cout << "8 - Ler" << endl;
    cout << "0 - Sair" << endl;
    cout << "Sua opção: ";
    int opcao;
    cin >> opcao;
    return opcao;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    cout << "Bem Vindo ao Sistema de Cadastros" << endl;
    cout << "O que gostaria de Fazer?" << endl;
    int opcao;
    while ((opcao = menu()) != 0) {
        switch (opcao) {
        case 1:
            criar_pessoa(); break;
        case 2:
            alterar_pessoa(); break;
        case 3:
            remover_pessoa(); break;
        case 4:
            buscar_pessoa(); break;
        case 5:
            imprimir_todos(); break;
        case 6:
            cout << "Você deseja Ordenar por Nome ou Matricula? (1 - Nome | 2 - Matricula)" << endl;
            int op2;
            cin >> op2;
            if (op2 == 2) {
                quick_sort(0, posicao);
            }
            else if (op2 == 1) {
                ordenar_bubble();
            }; break;
        case 7:
            salvar_arq(); break;
        case 8:
            ler_arq(); break;
            cout << endl;
        }
    }
}
