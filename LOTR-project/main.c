#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int tabuleiro()
{
	printf("   A B C D E F G H I J K L M N O P Q R J T U V W X Y Z\n");
	//NOMES DAS COLUNAS
	printf("  %c", 218);
	for (int i = 0; i < 25; i++)
	{
		printf("%c%c", 196, 194);
	}
	printf("%c%c\n", 196, 191);
	//PARTE SUPERIOR DA TABELA
	for (int ii = 0; ii < 10; ii++)
	{
		printf("%d ", ii);
		for (int i = 0; i < 27; i++)
		{
			printf("%c ", 179);
		}
		printf("\n  %c", 195);
		for (int i = 0; i < 25; i++)
		{
			printf("%c%c", 196, 197);
		}
		printf("%c%c\n", 196, 180);
	}
	//TABELA ATÉ A LINHA 9
	for (int ii = 10; ii < 16; ii++)
	{
		printf("%d", ii);
		for (int i = 0; i < 27; i++)
		{
			printf("%c ", 179);
		}
		printf("\n  %c", 195);
		for (int i = 0; i < 25; i++)
		{
			printf("%c%c", 196, 197);
		}
		printf("%c%c\n", 196, 180);
	}
	//TABELA DA LINHA 10 A 16 - DOIS DIGITOS = MENOS UM ESPAÇO (PARA A TABELA FICAR ALINHADA;CONFIA)
	printf("16");
	for (int i = 0; i < 27; i++)
	{
		printf("%c ", 179);
	}
	//FAZ A ULTIMA LINHA DA TABELA
	printf("\n  %c", 192);
	for (int i = 0; i < 25; i++)
	{
		printf("%c%c", 196, 193);
	}
	printf("%c%c", 196, 217);
	//PARTE INFERIOR DA TABELA
}

int main()
{
	int opcao = 0;
	while (opcao != 4)
	{
		printf("bem-vindo blablabla\nSelecione uma opcao:\n\n");
		printf("1. Novo jogo\n2. Carregar jogo\n3. Configuracoes\n4. Sair\n");
		scanf("%d", &opcao);
		if (opcao == 1)
		{
			tabuleiro();
		}
		else if (opcao == 2)
		{

		}
		else if (opcao == 3)
		{
			printf("1. Idioma\n2. Creditos\n3. ");
		}
	}
}