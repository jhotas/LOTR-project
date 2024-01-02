#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 17
#define COLS 26
#define COLOR_TITLE "\x1b[33m"
#define COLOR_PLAYER1 "\x1b[34m"
#define COLOR_PLAYER2 "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

// Estrutura para construcoes
typedef struct {
    char type[3];
    int cost;
    int health;
    int coinGeneration;
    int owner;
} Building;

// Estrutura para unidades
typedef struct {
    char type;
    int cost;
    int health;
    int attackPower;
} Unit;

// Estruturas para bases
typedef struct {
    Building build;
} Base;

// Jogadores
typedef enum {
    PLAYER1,
    PLAYER2
} Player;

// Estrutura do tabuleiro
char tabuleiro[ROWS][COLS];
int tabuleiroOwners[ROWS][COLS];

// Inicia os coins para os jogadores
Player currentPlayer = PLAYER1;
int castarCoinsPlayer1 = 100;
int castarCoinsPlayer2 = 100;

// Função para alterar o jogador
void switchPlayer() {
    currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
}

// Gera a base dos jogadores
Base basePlayer1;
Base basePlayer2;

// Verifica se e possivel construir em determinada posicao
bool canBuildBuilding(int linha, int colunaIndex, const Building* building) {
    // Verifica se a posição é válida
    if (linha < 1 || linha > ROWS || colunaIndex < 0 || colunaIndex + strlen(building->type) > COLS) {
        printf("Posicao invalida. Tente novamente.\n");
        return false;
    }

    // Verifica se as células estão livres
    for (int i = 0; i < strlen(building->type); i++) {
        if (tabuleiro[linha - 1][colunaIndex + i] != ' ') {
            printf("Nao e possivel construir %s nessa posicao. Tente novamente.\n", building->type);
            return false;
        }
    }

    return true;
}

void buildBuilding(Building *building) {
    int linha;

    printf("Escolha a linha (1 a 17): ");
    scanf_s("%d", &linha);
    printf("Escolha a coluna (A a Z): ");
    char colunaChar;
    scanf_s(" %c", &colunaChar);

    int colunaIndex = colunaChar - 'A';

    if (!canBuildBuilding(linha, colunaIndex, building)) {
        return;
    }

    // Verifica se o jogador tem moedas suficientes para construir
    if ((currentPlayer == PLAYER1 && castarCoinsPlayer1 < building->cost) || (currentPlayer == PLAYER2 && castarCoinsPlayer2 < building->cost)) {
        printf("Moedas insuficientes para construir %s.\n", building->type);
        return;
    }

    // Atualiza o tabuleiro
    for (int i = 0; i < strlen(building->type); i++) {
        tabuleiro[linha - 1][colunaIndex + i] = building->type[i];
        tabuleiroOwners[linha - 1][colunaIndex + i] = (currentPlayer == PLAYER1) ? 1 : 2;
    }

    // Define o proprietario da construcao
    building->owner = (currentPlayer == PLAYER1) ? 1 : 2;

    // Atualiza as moedas do jogador
    if (currentPlayer == PLAYER1) {
        castarCoinsPlayer1 -= building->cost;
    } else {
        castarCoinsPlayer2 -= building->cost;
    }

    printf("%s construído com sucesso!\n", building->type);
}

// Gera as construcoes
Building mina1 = { "SS" , 20, 50, 5, 0 };
Building mina2 = { "EE", 20, 50, 5, 0 };
Building barraca1 = { "RR", 25, 70, 0, 0 };
Building barraca2 = { "II", 25, 70, 0, 0 };
Building estabulo1 = { "LL", 25, 70, 0, 0 };
Building estabulo2 = { "MK", 25, 70, 0, 0 };
Building arsenal1 = { "GF", 25, 70, 0, 0 };
Building arsenal2 = { "DF", 25, 70, 0, 0 };

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
            char currentCell = tabuleiro[i][j];

            // Verifica o tipo de construção e aplica a cor apropriada
            if (currentCell == 'G') {
                printf(COLOR_PLAYER1 "[G]" COLOR_RESET);
            }
            else if (currentCell == 'M') {
                printf(COLOR_PLAYER2 "[M]" COLOR_RESET);
            }
            else if (currentCell == 'S' || currentCell == 'E' || currentCell == 'R' || currentCell == 'I' || currentCell == 'L' || currentCell == 'K' || currentCell == 'F') {
                // Verifica o jogador e aplica a cor correspondente
                if (tabuleiroOwners[i][j] == 1) {
                    printf(COLOR_PLAYER1 "[%c]" COLOR_RESET, currentCell);
                }
                else {
                    printf(COLOR_PLAYER2 "[%c]" COLOR_RESET, currentCell);
                }
            }
            else {
                printf("[");
                printf("%c", currentCell);
                printf("]");
            }
        }
        printf("\n");
    }
}

void attackWithUnit() {
    // Implementar código
}

void moveUnit() {
    // Implementar código
}

void playerTurn() {
    // Gera coins para os jogadores dependendo de quantas minas tiverem no tabuleiro
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (tabuleiro[i][j] == 'S' && tabuleiro[i][j + 1] == 'S') {
                if (currentPlayer == PLAYER1) {
                    castarCoinsPlayer1 += mina1.coinGeneration;
                }
            }
            else if (tabuleiro[i][j] == 'E' && tabuleiro[i][j + 1] == 'E') {
                if (currentPlayer == PLAYER2) {
                    castarCoinsPlayer2 += mina2.coinGeneration;
                }
            }
        }
    }
    
    int action;

    do {
        printBoard();
        printf("\nMoedas do jogador 1: %d\n", castarCoinsPlayer1);
        printf("Moedas do jogador 2: %d\n", castarCoinsPlayer2);
        printf("\nJogador %d, escolha sua acao:\n", currentPlayer + 1);
        printf("(1) Construir\n");
        printf("(2) Selecionar\n");
        printf("(3) Encerrar turno\n");
        printf("(4) Sair do jogo e salvar\n");
        scanf_s("%d", &action);

        switch (action) {
            case 1:
                int choice;
                printf("Jogador %d, voce tem %d moedas.\n", currentPlayer + 1, (currentPlayer == PLAYER1 ? castarCoinsPlayer1 : castarCoinsPlayer2));
                printf("Escolha a construcao que deseja construir:\n");
                printf("(1) Mina (20 Castar coins)\n");
                printf("(2) Barraca (25 Castar coins)\n");
                printf("(3) Estabulo (25 Castar coins)\n");
                printf("(4) Arsenal (30 Castar coins)\n");
               
                scanf_s("%d", &choice);

                if (choice == 1) {
                    (currentPlayer == PLAYER1) ? buildBuilding(&mina1) : buildBuilding(&mina2);
                }
                else if (choice == 2) {
                    (currentPlayer == PLAYER1) ? buildBuilding(&barraca1) : buildBuilding(&barraca2);
                }
                else if (choice == 3) {
                    (currentPlayer == PLAYER1) ? buildBuilding(&estabulo1) : buildBuilding(&estabulo2);
                }
                else if (choice == 4) {
                    (currentPlayer == PLAYER1) ? buildBuilding(&arsenal1) : buildBuilding(&arsenal2);
                }
                else {
                    printf("Digite um valor valido. Tente novamente.");
                    return;
                }
                break;
            case 2:

                break;
            case 3:
                printf("Turno encerrado!\n");
                break;
            case 4:
                printf("Salvando...\n");
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
