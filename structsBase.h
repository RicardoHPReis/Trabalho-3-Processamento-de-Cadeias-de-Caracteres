#pragma once
#include "stdafx.h"


typedef struct
{
	char nomeArquivo[100], arqSalvo[100];
	char padrao[20];
	int opcao, posicao;
	int leuArquivo, ordenouIndiceAlfabeto, ordenouIndiceOcorrencia;
	int qntd_plv, qntd_crct, qntd_indice, tam_padrao;
} Config;
Config config;


typedef struct
{
	char cadeia[20];
	int *locais;
	int ocorrencias;
} Indice;
Indice *indice;


typedef struct
{
	char *caracter;
	int *inicio;
} Texto;
Texto texto;

struct Node
{
	int folha;
	struct Node *caracter[26];
};
typedef struct Node Trie;
Trie *arvore;

typedef struct
{
	unsigned long int m, c; //movimentacoes, comparacoes
	struct timespec comeco, fim;
	double tempo;
}Comparacoes;
Comparacoes comp[20];


void comparacoes(unsigned long int comp, unsigned long int mov, double tempo)
{
	printf("\nComparações: %lu\n", comp);
	printf("Movimentações: %lu\n", mov);
	printf("Tempo: %fs\n", tempo);
}