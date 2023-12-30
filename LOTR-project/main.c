#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 17
#define COLS 26
#define COLOR_TITLE "\x1b[33m"
#define COLOR_PLAYER1 "\x1b[34m"
#define COLOR_PLAYER2 "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

typedef struct {
    char type[3];
    int cost;
    int health;
} Building;

typedef struct {
    char type;
    int cost;
    int health;
    int attackPower;
} Unit;

typedef struct {
    Building build;
} Base;

typedef enum {
    PLAYER1,
    PLAYER2
} Player;

// Estrutura do tabuleiro
char tabuleiro[ROWS][COLS];

Player currentPlayer = PLAYER1;

// Função para alterar o jogador
void switchPlayer() {
    currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
}

Base basePlayer1;
Base basePlayer2;

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

// Função para inicializar o tabuleiro (preenchendo com espa�os em branco)
void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Função para imprimir o tabuleiro
void printBoard() {
    printf("  ");
    for (int j = 0; j < COLS; j++) {
        printf("  %c", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < COLS; j++) {
            if (tabuleiro[i][j] == 'G') {
                printf(COLOR_PLAYER1 "[G]" COLOR_RESET);
            }
            else if (tabuleiro[i][j] == 'M') {
                printf(COLOR_PLAYER2 "[M]" COLOR_RESET);
            }
            else {
                printf("[");
                printf("%c", tabuleiro[i][j]);
                printf("]");
            }
        }
        printf("\n");
    }
}
void addStructure() {
    char tipo;
    int linha, coluna;

    printf("Escolha o tipo de estrutura (M para Mina, B para Barraca): ");
    scanf_s(" %c", &tipo);

    printf("Escolha a linha (1 a 17): ");
    scanf_s("%d", &linha);
    printf("Escolha a coluna (A a Z): ");
    char colunaChar;
    scanf_s(" %c", &colunaChar);

    // Convertendo a letra da coluna para um �ndice (A=0, B=1, ..., Z=25)
    int colunaIndex = colunaChar - 'A';

    // Atualizando o tabuleiro
    tabuleiro[linha - 1][colunaIndex] = tipo;
}

void buildBuilding() {
    // Implementar código
}

void attackWithUnit() {
    // Implementar código
}

void moveUnit() {
    // Implementar código
}

void playerTurn() {
    int action;

    do {
        printBoard();
        printf("Jogador %d, escolha sua acao:\n", currentPlayer + 1);
        printf("(1) Construir\n");
        printf("(2) Selecionar\n");
        printf("(3) Encerrar turno\n");
        scanf_s("%d", &action);

        switch (action) {
            case 1:
                printf("Escolha qual construcao deseja colocar:\n");
                printf("(1) Mina\n");
                printf("(2) Barraca\n");
                printf("(3) Estabulo\n");
                printf("(4) Arsenal\n");
                break;
            case 2:

                break;
            case 3:
                printf("Turno encerrado!\n");
                break;
            default:
                printf("Opçao invalida. Tente novamente.\n");
        }
    } while (action != 3);
}

void placeBase() {
    printf("Jogador %d, coloque sua base no tabuleiro.\n", currentPlayer + 1);

    int linha, coluna;
    printf("Escolha a linha (1 a 17): ");
    scanf_s("%d", &linha);
    printf("Escolha a coluna (A a Z): ");
    char colunaChar;
    scanf_s(" %c", &colunaChar);

    int colunaIndex = colunaChar - 'A';

    tabuleiro[linha - 1][colunaIndex] = (currentPlayer == PLAYER1 ? 'G' : 'M');

    for (int i = 1; i < 4; i++) {
        colunaIndex++;
        tabuleiro[linha - 1][colunaIndex] = (currentPlayer == PLAYER1 ? 'G' : 'M');
    }
}

void initializeBase(Base *base, char type) {
    base->build.type[0] = type;
    base->build.type[1] = type;
    base->build.type[2] = type;
    base->build.type[3] = type;
    base->build.cost = 0;
    base->build.health = 100;
}

void destroyBase(Base *base) {
    initializeBase(base, ' ');
}

int main() {
    menu();
    
    int option;
    scanf_s("%d", &option);
    switch (option) {
    case 1:
        system("cls");
        initializeBoard();
        initializeBase(&basePlayer1, 'G');
        initializeBase(&basePlayer2, 'M');
        printBoard();

        placeBase();
        system("cls");
        printBoard();

        switchPlayer();
        placeBase();
        system("cls");
        printBoard();
        switchPlayer();

        while (true) {
            playerTurn();
            switchPlayer();
            system("cls");
        }
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    };
}
