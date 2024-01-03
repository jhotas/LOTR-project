#define _CRT_SECURE_NO_WARNINGS
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
    char type[2];
    int cost;
    int health;
    int attackPower;
    int range;
    int move;
    int moveCost;
    int owner;
    int row;
    int col;
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
Unit tabuleiroUnits[ROWS][COLS];

// Inicia os coins para os jogadores
Player currentPlayer = PLAYER1;
int castarCoinsPlayer1 = 100;
int castarCoinsPlayer2 = 100;

// Função para alterar o jogador
void switchPlayer() {
    currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
}

// Gera a base dos jogadores
Base bases[2];

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

    printf("%s construida com sucesso!\n", building->type);
}

void destroyBuilding(int linha, int colunaIndex) {
    printf("Construcao destruida!\n");
    tabuleiro[linha - 1][colunaIndex - 1] = ' ';
    tabuleiro[linha - 1][colunaIndex] = ' ';
    tabuleiro[linha - 1][colunaIndex + 1] = ' ';
    tabuleiroOwners[linha - 1][colunaIndex] = 0;
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

void recruitUnit(const char* unitType, int linha, int colunaIndex) {
    Unit recruitedUnit;
    strcpy(recruitedUnit.type, unitType);

    // Define os valores de custo, saúde, poder de ataque e alcance com base no tipo de unidade
    if ((currentPlayer == PLAYER1 && strcmp(unitType, "G") == 0) ||
        (currentPlayer == PLAYER2 && strcmp(unitType, "OW") == 0)) {
        recruitedUnit.cost = 10;
        recruitedUnit.health = 30;
        recruitedUnit.attackPower = 5;
        recruitedUnit.move = 3;
        recruitedUnit.moveCost = 2;
        recruitedUnit.owner = (currentPlayer == PLAYER1) ? 1 : 2;
        recruitedUnit.range = 1;  // Alcance de 1 célula
        recruitedUnit.row = linha - 1;
        recruitedUnit.col = colunaIndex;
    }
    else if ((currentPlayer == PLAYER1 && strcmp(unitType, "SK") == 0) ||
        (currentPlayer == PLAYER2 && strcmp(unitType, "W") == 0)) {
        recruitedUnit.cost = 15;
        recruitedUnit.health = 40;
        recruitedUnit.attackPower = 7;
        recruitedUnit.move = 4;
        recruitedUnit.moveCost = 1;
        recruitedUnit.owner = (currentPlayer == PLAYER1) ? 1 : 2;
        recruitedUnit.range = 2;  // Alcance de 2 células
        recruitedUnit.row = linha - 1;
        recruitedUnit.col = colunaIndex;
    }
    else if ((currentPlayer == PLAYER1 && strcmp(unitType, "T") == 0) ||
        (currentPlayer == PLAYER2 && strcmp(unitType, "ST") == 0)) {
        recruitedUnit.cost = 20;
        recruitedUnit.health = 20;
        recruitedUnit.attackPower = 10;
        recruitedUnit.move = 2;
        recruitedUnit.moveCost = 3;
        recruitedUnit.owner = (currentPlayer == PLAYER1) ? 1 : 2;
        recruitedUnit.range = 3;  // Alcance de 3 células
        recruitedUnit.row = linha - 1;
        recruitedUnit.col = colunaIndex;
    }
    else {
        printf("Tipo de unidade desconhecido!\n");
        return;
    }

    // Verifique se o jogador tem moedas suficientes para recrutar
    if ((currentPlayer == PLAYER1 && castarCoinsPlayer1 < recruitedUnit.cost) ||
        (currentPlayer == PLAYER2 && castarCoinsPlayer2 < recruitedUnit.cost)) {
        printf("Moedas insuficientes para recrutar a unidade %s.\n", unitType);
        return;
    }

    // Atualize as moedas do jogador
    if (currentPlayer == PLAYER1) {
        castarCoinsPlayer1 -= recruitedUnit.cost;
    }
    else {
        castarCoinsPlayer2 -= recruitedUnit.cost;
    }

    // Adicione a unidade recrutada ao tabuleiro
    if (strlen(unitType) == 1) {
        // Se já houver uma unidade, avança para a próxima coluna
        while (tabuleiro[linha - 1][colunaIndex] != ' ') {
            colunaIndex++;
        }
        tabuleiro[linha - 1][colunaIndex] = unitType[0];
    }
    else if (strlen(unitType) == 2) {
        // Se já houver uma unidade, avança para a próxima coluna
        while (tabuleiro[linha - 1][colunaIndex] != ' ' || tabuleiro[linha - 1][colunaIndex + 1] != ' ') {
            colunaIndex++;
        }
        tabuleiro[linha - 1][colunaIndex] = unitType[0];    
        tabuleiro[linha - 1][colunaIndex + 1] = unitType[1];
    }

    // Adicione a unidade recrutada ao tabuleiroUnits
    tabuleiroUnits[linha - 1][colunaIndex] = recruitedUnit;

    printf("Unidade %s recrutada com sucesso!\n", unitType);
}

void moveUnit(int linha, int colunaIndex) {
    char selectedUnit = tabuleiro[linha - 1][colunaIndex];
    int selectedUnitRange = tabuleiroUnits[linha - 1][colunaIndex].move;

    // Verifique se a posição é válida
    if (linha < 1 || linha > ROWS || colunaIndex < 0 || colunaIndex >= COLS) {
        printf("Posicao invalida. Tente novamente.\n");
        return;
    }

    //// Verifique se a unidade pertence ao jogador atual
    //if ((currentPlayer == PLAYER1 && tabuleiroOwners[linha - 1][colunaIndex] != 1) ||
    //    (currentPlayer == PLAYER2 && tabuleiroOwners[linha - 1][colunaIndex] != 2)) {
    //    printf("Esta unidade nao pertence ao jogador atual. Tente novamente.\n");
    //    return;
    //}

    // Mova a unidade para a nova posição
    int newLinha, newColunaIndex;
    printf("Escolha a nova linha (1 a 17): ");
    scanf_s(" %d", &newLinha);
    printf("Escolha a nova coluna (A a Z): ");
    char newColunaChar;
    scanf_s(" %c", &newColunaChar);

    newColunaIndex = newColunaChar - 'A';

    // Verificar se a nova posição escolhida é válida
    if (((newColunaIndex - colunaIndex) > selectedUnitRange) ||
        ((newLinha - (linha - 1)) > selectedUnitRange) ||
        (((newColunaIndex - colunaIndex) == 0) && ((newLinha - (linha - 1)) == 0))) {
        printf("Movimento invalido. A unidade so pode se mover ate %d celulas em linha ou coluna.\n", selectedUnitRange);
        return;
    }

    // Verificar se a nova posição está livre
    if (tabuleiro[linha - 1][newColunaIndex] != ' ') {
        printf("Nova posicao ocupada. Tente novamente.\n");
        return;
    }

    // Verificar se o jogador tem moedas suficientes para mover
    if ((currentPlayer == PLAYER1 && castarCoinsPlayer1 < tabuleiroUnits[linha - 1][colunaIndex].moveCost) ||
        (currentPlayer == PLAYER2 && castarCoinsPlayer2 < tabuleiroUnits[linha - 1][colunaIndex].moveCost)) {
        printf("Moedas insuficientes para mover a unidade.\n");
        return;
    }

    // Atualizar o tabuleiro e a posse do tabuleiro
    tabuleiro[linha - 1][newColunaIndex] = selectedUnit;
    tabuleiro[linha - 1][colunaIndex] = ' ';
    tabuleiroOwners[linha - 1][newColunaIndex] = tabuleiroOwners[linha - 1][colunaIndex];
    tabuleiroOwners[linha - 1][colunaIndex] = 0;

    // Atualizar moedas do jogador
    if (currentPlayer == PLAYER1) {
        castarCoinsPlayer1 -= tabuleiroUnits[linha - 1][colunaIndex].moveCost;
    }
    else {
        castarCoinsPlayer2 -= tabuleiroUnits[linha - 1][colunaIndex].moveCost;
    }

    printf("Unidade movida com sucesso!\n");
}

void select(int linha, int colunaIndex) {
    char selectedCell = tabuleiro[linha - 1][colunaIndex];
    Building* selectedBuildingData = NULL;

    if ((selectedCell == 'S' && (tabuleiro[linha - 1][colunaIndex + 1] == 'S' || tabuleiro[linha - 1][colunaIndex - 1] == 'S'))
        || (selectedCell == 'E' && (tabuleiro[linha - 1][colunaIndex + 1] == 'E' || tabuleiro[linha - 1][colunaIndex - 1] == 'E'))
        || (selectedCell == 'R' && (tabuleiro[linha - 1][colunaIndex + 1] == 'R' || tabuleiro[linha - 1][colunaIndex - 1] == 'R'))
        || (selectedCell == 'I' && (tabuleiro[linha - 1][colunaIndex + 1] == 'I' || tabuleiro[linha - 1][colunaIndex - 1] == 'I'))
        || (selectedCell == 'L' && (tabuleiro[linha - 1][colunaIndex + 1] == 'L' || tabuleiro[linha - 1][colunaIndex - 1] == 'L'))
        || ((selectedCell == 'M' || selectedCell == 'K') && (tabuleiro[linha - 1][colunaIndex + 1] == 'K' || tabuleiro[linha - 1][colunaIndex - 1] == 'M'))
        || ((selectedCell == 'G' || selectedCell == 'F') && (tabuleiro[linha - 1][colunaIndex + 1] == 'F' || tabuleiro[linha - 1][colunaIndex - 1] == 'G'))
        || ((selectedCell == 'D' || selectedCell == 'F') && (tabuleiro[linha - 1][colunaIndex + 1] == 'F' || tabuleiro[linha - 1][colunaIndex - 1] == 'D'))) {
        switch (selectedCell) {
        case 'S':
            selectedBuildingData = &mina1;
            if (tabuleiro[linha - 1][colunaIndex + 1] == 'S' || tabuleiro[linha - 1][colunaIndex - 1] == 'S') {
                if (currentPlayer == PLAYER1) {
                    printf("Selecionou uma mina!\n");
                    printf("Vida: %d\n", selectedBuildingData->health);
                    printf("(D) Destruir\n");
                    printf("(V) Voltar\n");

                    char option;
                    scanf_s(" %c", &option);

                    if (option == 'D') {
                        destroyBuilding(linha, colunaIndex);
                    }
                }
                else {
                    printf("Selecionou uma mina inimiga!\n");
                    printf("Vida: %d\n", selectedBuildingData->health);
                    printf("(V) Voltar\n");

                    char option;
                    scanf_s(" %c", &option);
                }
            }
            break;
        case 'E':
            selectedBuildingData = &mina2;
            if (currentPlayer == PLAYER2) {
                printf("Selecionou uma mina!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(D) Destruir\n");
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
            }
            else {
                printf("Selecionou uma mina inimiga!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        case 'R':
            selectedBuildingData = &barraca1;
            if (currentPlayer == PLAYER1) {
                printf("Selecionou uma barraca!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(R) Recrutar\n");
                printf("(D) Destruir\n");
                printf("(V) Voltar");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
                else if (option == 'R') {
                    recruitUnit((currentPlayer == PLAYER1) ? "G" : "OW", linha + 1, colunaIndex);
                }
            }
            else {
                printf("Selecionou uma barraca inimiga!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        case 'I':
            selectedBuildingData = &barraca2;
            if (currentPlayer == PLAYER2) {
                printf("Selecionou uma barraca!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(R) Recrutar\n");
                printf("(D) Destruir\n");
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
                else if (option == 'R') {
                    recruitUnit((currentPlayer == PLAYER1) ? "G" : "OW", linha, colunaIndex + 1);
                }
            }
            else {
                printf("Selecionou uma barraca inimiga!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        case 'L':
            selectedBuildingData = &estabulo1;
            if (currentPlayer == PLAYER1) {
                printf("Selecionou um estabulo!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(R) Recrutar\n");
                printf("(D) Destruir\n");
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
                else if (option == 'R') {
                    recruitUnit((currentPlayer == PLAYER1) ? "SK" : "W", linha, colunaIndex + 1);
                }
            }
            else {
                printf("Selecionou um estabulo inimigo!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        case 'M':
            selectedBuildingData = &estabulo2;
            if (currentPlayer == PLAYER2) {
                printf("Selecionou um estabulo!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(R) Recrutar\n");
                printf("(D) Destruir\n");
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
                else if (option == 'R') {
                    recruitUnit((currentPlayer == PLAYER1) ? "SK" : "W", linha, colunaIndex + 1);
                }
            }
            else {
                printf("Selecionou um estabulo inimigo!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        case 'G':
            selectedBuildingData = &arsenal1;
            if (currentPlayer == PLAYER1) {
                printf("Selecionou um arsenal!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(R) Recrutar\n");
                printf("(D) Destruir\n");
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
                else if (option == 'R') {
                    recruitUnit((currentPlayer == PLAYER1) ? "T" : "ST", linha, colunaIndex + 1);
                }
            }
            else {
                printf("Selecionou um arsenal inimigo!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        case 'D':
            selectedBuildingData = &arsenal2;
            if (currentPlayer == PLAYER2) {
                printf("Selecionou um arsenal!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(R) Recrutar\n");
                printf("(D) Destruir\n");
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);

                if (option == 'D') {
                    destroyBuilding(linha, colunaIndex);
                }
                else if (option == 'R') {
                    recruitUnit((currentPlayer == PLAYER1) ? "T" : "ST", linha, colunaIndex + 1);
                }
            }
            else {
                printf("Selecionou um arsenal inimigo!\n");
                printf("Vida: %d\n", selectedBuildingData->health);
                printf("(V) Voltar\n");

                char option;
                scanf_s(" %c", &option);
            }
            break;
        default:
            printf("Nao selecionou uma construcao!\n");
            break;
        }
    } 
    else {
        Unit* selectedUnit = &tabuleiroUnits[linha - 1][colunaIndex];

        printf("Vida: %d\n", selectedUnit->health);
        printf("Poder de Ataque: %d\n", selectedUnit->attackPower);
        printf("Alcance: %d\n", selectedUnit->range);
        printf("Custo de Movimento: %d\n", selectedUnit->moveCost);
        printf("(M) Mover\n");
        printf("(A) Atacar\n");
        printf("(V) Voltar\n");

        char option;
        scanf_s(" %c", &option);

        switch (option) {
        case 'M':
            moveUnit(linha, colunaIndex);
            break;
        case 'A':
            // Implementar lógica de ataque
            break;
        }
    }
}

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
            else if (currentCell == 'G' || currentCell == 'SK' || currentCell == 'T' || currentCell == 'OW' || currentCell == 'W' || currentCell == 'ST') {
                // Verifica a unidade e aplica a cor correspondente
                if (tabuleiroUnits[i][j].owner == 1) {
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
        // Exibir informacoes sobre o jogo
        printf("\nVida da base do Jogador 1: %d\n", bases[0].build.health);
        printf("Vida da base do Jogador 2: %d\n", bases[1].build.health);
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
                int linha, colunaIndex;

                printf("Escolha a linha (1 a 17): ");
                scanf_s("%d", &linha);
                printf("Escolha a coluna (A a Z): ");
                char colunaChar;
                scanf_s(" %c", &colunaChar);
                colunaIndex = colunaChar - 'A';

                // Verificar se a posição escolhida é válida
                if (linha < 1 || linha > ROWS || colunaIndex < 0 || colunaIndex >= COLS) {
                    printf("Posicao invalida. Tente novamente.\n");
                    break;
                }

                // Chamar a função para selecionar a construção
                select(linha, colunaIndex);
                break;
            case 3:
                printf("Turno encerrado!\n");
                break;
            case 4:
                printf("Salvando...\n");
                carregarJogo();
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
    base->build.type[2] = '\0';
    base->build.cost = 0;
    base->build.health = 100;
}

void destroyBase(Base *base) {
    initializeBase(base, ' ');
}

void salvarJogo() {
    FILE* arquivo = fopen("savegame.txt", "w");

    // Salvar informações relevantes do jogo no arquivo
    fprintf(arquivo, "%d\n", currentPlayer);
    fprintf(arquivo, "%d %d\n", castarCoinsPlayer1, castarCoinsPlayer2);

    // Salvar o estado do tabuleiro
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(arquivo, "%c %d %c ", tabuleiro[i][j], tabuleiroOwners[i][j], tabuleiroUnits[i][j].type[0]);
        }
        fprintf(arquivo, "\n");
    }

    // Salvar informações sobre as bases e construções
    fprintf(arquivo, "%d %d %d %d %d %d %d %d\n",
        bases[0].build.cost, bases[0].build.health,
        bases[1].build.cost, bases[1].build.health,
        mina1.cost, mina1.health, mina2.cost, mina2.health);

    fclose(arquivo);
}

//void carregarJogo() {
//    FILE* arquivo = fopen("savegame.txt", "r");
//
//    if (arquivo == NULL) {
//        printf("Nenhum jogo salvo encontrado.\n");
//        return;
//    }
//
//    // Carregar informações do jogo do arquivo
//    fscanf(arquivo, "%d", &currentPlayer);
//    fscanf(arquivo, "%d %d", &castarCoinsPlayer1, &castarCoinsPlayer2);
//
//    // Carregar o estado do tabuleiro
//    for (int i = 0; i < ROWS; i++) {
//        for (int j = 0; j < COLS; j++) {
//            fscanf(arquivo, " %c %d %c ", &tabuleiro[i][j], &tabuleiroOwners[i][j], &tabuleiroUnits[i][j].type[0]);
//        }
//        fscanf(arquivo, "\n");
//    }
//
//    // Carregar informações sobre as bases e construções
//    fscanf(arquivo, "%d %d %d %d %d %d %d %d",
//        &bases[0].build.cost, &bases[0].build.health,
//        &bases[1].build.cost, &bases[1].build.health,
//        &mina1.cost, &mina1.health, &mina2.cost, &mina2.health);
//
//    fclose(arquivo);
//
//    printf("Jogo carregado com sucesso!\n");
//}

int main() {
    menu();
    
    int option;
    scanf_s("%d", &option);
    switch (option) {
    case 1:
        system("cls");
        initializeBoard();
        initializeBase(&bases[0], 'G');
        initializeBase(&bases[1], 'M');
        printBoard();

        placeBase();
        system("cls");
        printBoard();

        switchPlayer();
        placeBase();
        system("cls");
        printBoard();
        switchPlayer();

        while (bases[0].build.health > 0 && bases[1].build.health > 0) {
            playerTurn();
            switchPlayer();
            system("cls");
        }
        break;
    case 2:
        carregarJogo();
        break;
    case 3:

        break;
    case 4:

        break;
    };
}
