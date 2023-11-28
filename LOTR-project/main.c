#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 17
#define COLUNAS 26

// Estrutura do tabuleiro
char tabuleiro[LINHAS][COLUNAS];

void menu() {
    printf("(1) New game\n(2) Load game\n(3) Settings\n(4) Exit");
}

// Função para inicializar o tabuleiro (preenchendo com espaços em branco)
void inicializarTabuleiro() {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro() {
    printf("  ");
    for (int j = 0; j < COLUNAS; j++) {
        printf("  %c", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < LINHAS; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < COLUNAS; j++) {
            printf("[");
            printf(" %c ", tabuleiro[i][j]);
            printf("]");
        }
        printf("\n");
    }
}

int main() {
    menu();
    
    int option;
    scanf("%d", &option);
    switch (option) {
        case 1:
            system("cls");
            inicializarTabuleiro();
            imprimirTabuleiro();
        case 2:

            break;
        case 3:

            break;
        case 4:

    }
}
