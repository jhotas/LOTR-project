#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINHAS 17
#define COLUNAS 26
#define COLOR_TITLE "\x1b[33m"
#define COLOR_PLAYER1 "\x1b[34m"
#define COLOR_PLAYER2 "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

// Estrutura do tabuleiro
char tabuleiro[LINHAS][COLUNAS];

void menu() {
    printf(COLOR_TITLE "         ___ . .  _\n");
    printf("%cT$$$P%c   |  |_| |_\n", 34, 34);
    printf(" :$$$     |  | | |_\n");
    printf(" :$$$                                                      %cT$$$$$$$b.\n", 34);
    printf(" :$$$     .g$$$$$p.   T$$$$b.    T$$$$$bp.                   BUG    %cTb      T$b      T$P.g$P ^ ^T$$, gP ^ ^T$$\n", 34);
    printf("  $$$    d^%c     %c^b   $$  %cTb    $$    %cTb    .s^s. :sssp   $$$     :$; T$$P $^b.     $   dP%c     `T :$P    `T\n", 34, 34, 34, 34, 34);
    printf("  :$$   dP         Tb  $$   :$;   $$      Tb  d'   `b $      $$$     :$;  $$  $ `Tp    $  d$           Tbp.   \n");
    printf("  :$$  :$;         :$; $$   :$;   $$      :$; T.   .P $^^    $$$    .dP   $$  $   ^b.  $ :$;            %cT$$p.\n",     34);
    printf("  $$$  :$;         :$; $$...dP    $$      :$;  `^s^' .$.     $$$...dP%c    $$  $    `Tp $ :$;     %cT$$      %cT$b\n", 34, 34, 34);
    printf("  $$$   Tb.       ,dP  $$%c%c%cTb    $$      dP %c%c$%c%c$%c %c$%c$^^  $$$%c%cT$b     $$  $      ^b$  T$       T$ ;      $$;\n", 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34);
    printf("  $$$    Tp._   _,gP   $$   `Tb.  $$    ,dP    $  $...$ $..  $$$   T$b    :$  $       `$   Tb.     :$ T.    ,dP \n");
    printf("  $$$;    %c^$$$$$^%c   d$$     `T.d$$$$$P^%c     $  $%c%c%c$ $%c%c, $$$    T$b  d$$bd$b      d$b   %c^TbsssP%c 'T$bgd$P  \n", 34, 34, 34, 34, 34, 34, 34, 34, 34, 34);
    printf("  $$$b.____.dP                                 $ .$. .$.$ss,d$$$b.   T$b.\n");
    printf(".d$$$$$$$$$$P                                                         `T$b.\n");
    printf("                    Art by Blazej Kozlowski\n\n" COLOR_RESET);

    printf("(1) New game\n(2) Load game\n(3) Settings\n(4) Exit\n");
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
            printf("%c", tabuleiro[i][j]);
            printf("]");
        }
        printf("\n");
    }
}

int main() {
    menu();
    
    int option;
    scanf_s("%d", &option);
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

        break;
    };
}
