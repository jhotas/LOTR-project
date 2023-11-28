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
