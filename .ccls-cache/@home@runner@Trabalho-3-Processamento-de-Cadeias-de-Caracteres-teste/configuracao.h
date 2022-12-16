#include "stdafx.h"
#include "structsBase.h"


void aparenciaMenu(void)
{
	system(LIMPA);
	printf("*****************************************************\n");
	printf("        PROCESSAMENTO DE CADEIAS DE CARACTERES\n");
	printf("*****************************************************\n\n\n\n");
}



void aparenciaLista(void)
{
	system(LIMPA);
	printf("-------------------------------\n");
	printf("    PALAVRA    |  OCORRÊNCIAS  \n");
	printf("-------------------------------\n");
}



void aparenciaMenuDescricao(int descricao)
{
	switch(descricao)
	{
		case 1:
		{
			printf("Ações: \n");
			break;
		}
		case 2:
		{
			printf("Leitura do arquivo:\n");
			break;
		}
		case 3:
		{
			printf("Ordenação:\n");
			break;
		}
		case 4:
		{
			printf("Procurar:\n");
			break;
		}
		case 5:
		{
			printf("Mostrar arquivo invertido:\n");
			break;
		}
		case 6:
		{
			printf("Salvar arquivo como:\n");
			break;
		}
		case 7:
		{
			printf("Como funciona o programa:\n");
			break;
		}
	}
	printf("-----------------------------------------------------\n\n");
}



void ler_string(char *resposta)
{
	int tamanho;
    char letra, *string;
	string = (char*) malloc (2*sizeof(char));
    
	scanf(" %c", &letra);

    for (tamanho = 0; letra != '\n'; tamanho++)
    {
        string[tamanho] = letra;
        string = (char*) realloc(string, (tamanho+3)*sizeof(char));

        scanf("%c", &letra);
    }
    string[tamanho+1] = '\0';
	*resposta = string[0];
	free(string);
}


void digiteAlgo()
{
	char continuar;
	printf("\n\nDigite qualquer tecla para continuar:\n");
	ler_string(&continuar);
}
	

void tipoDeErro(int erro)
{
	system(LIMPA);
	aparenciaMenu();
	switch(erro)
	{
		case 2:
		{
			aparenciaMenuDescricao(2);
			printf("Digite o número da ação novamente!!!\n"
			       "O número da ação precisa estar presente no menu de\n"
				   "seleção!\n");
			break;
		}
		case 3:
		{
			aparenciaMenuDescricao(2);
			printf("Digite o número da ação novamente!!!\n"
			       "É preciso ler uma lista pelo menu de seleção antes\n"
				   "de escolher outras ações!\n");
			break;
		}
		case 4:
		{
			aparenciaMenuDescricao(6);
			printf("Digite o arquivo novamente!!!\n"
			       "O arquivo precisa existir no sistema!\n");
			break;
		}
		case 5:
		{
			aparenciaMenuDescricao(7);
			printf("Digite a posição novamente!!!\n"
			       "A posição precisa estar entre os limites\n"
			       "de tamanho!\n");
			break;
		}
		case 7:
		{
			aparenciaMenuDescricao(2);
			printf("Digite o número da ação novamente!!!\n"
			       "Esta opção só está habilitada para as listas\n"
				   "sequenciais!\n");
			break;
		}
		case 8:
		{
			aparenciaMenuDescricao(2);
			printf("Digite o número da ação novamente!!!\n"
			       "É necessário ordenar a lista antes de procurá-la\n"
				   "por binário!\n");
			break;
		}
		case 9:
		{
			aparenciaMenuDescricao(11);
			printf("Digite o número da ordenação novamente!!!\n"
			       "O número da ordenação precisa estar presente no\n"
				   "menu de seleção!\n");
			break;
		}
	}
	sleep(3);
	system(LIMPA);
}



void menuDeSelecao(Config *config)
{
	do
	{
		system(LIMPA);
		aparenciaMenu();
		aparenciaMenuDescricao(1);
		printf("1) Ler arquivo.\n");
		printf("2) Ordenar por ordem alfabética.\n");
		printf("3) Ordenar pelo número de ocorrências.\n");
		printf("4) Pesquisa Sequencial.\n");
		printf("5) Pesquisa Binária.\n");
		printf("6) Mostrar arquivo invertido.\n");
		printf("7) Salvar arquivo invertido.\n");
		printf("8) Comparar resultados.\n");
		printf("9) Como funciona?\n");
		printf("10) Sair do sistema.\n\n");
		printf("Escolha uma ação: ");
		scanf("%d", &config->opcao);
		if (config->opcao<1 || config->opcao>10)
			tipoDeErro(2);
	}
	while(config->opcao<1 || config->opcao>10);
}

void menudeSelecaoLer()
{
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(2);
}

void menuOrdenacao()
{
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(3);
}

void menudeSelecaoProcurar()
{
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(4);
}

void menuMostrar()
{
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(5);
}

void menudeSelecaoPalavra(Config *config)
{
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(4);
	getchar();
	printf("Escolha uma palavra: ");
	fgets(config->padrao, 20, stdin);
	config->padrao[strlen(config->padrao)-1] = '\0';
	for(int i=0; config->padrao[i]!='\0'; i++)
	{
		config->padrao[i] = tolower(config->padrao[i]);
	}
	config->tam_padrao = strlen(config->padrao);
}

void menudeSelecaoArquivo(Config *config)
{
	FILE *arquivo;
	char txt[5]= ".txt";
	do
	{
		system(LIMPA);
		aparenciaMenu();
		aparenciaMenuDescricao(2);
		printf("Digite o nome do arquivo aqui: ");
		scanf("%s", config->nomeArquivo);
		strcat(config->nomeArquivo, txt);
		arquivo = fopen(config->nomeArquivo, "r");
		if(!arquivo)
		{
			tipoDeErro(4);
		}
	}
	while(!arquivo);
	fclose(arquivo);
}

void menudeSelecaoSalvar(Config *config)
{
	FILE *arquivo;
	char txt[5]= ".txt";
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(6);
	printf("Digite o nome do arquivo para salvar: ");
	scanf("%s", config->arqSalvo);
	strcat(config->arqSalvo, txt);
}

int verificaCaracterInicio(char caracter)
{
	if(caracter == ' ')
		return 1;
	else if (caracter == ',')
		return 1;
	else if (caracter == '!')
		return 1;
	else if (caracter == '?')
		return 1;
	else if (caracter == '.')
		return 1;
	else if (caracter == ';')
		return 1;
	else if (caracter == '\'')
		return 1;
	else if (caracter == '\"')
		return 1;
	else if (caracter == ':')
		return 1;
	else if (caracter == '-')
		return 1;
	else if (caracter == '\n')
		return 1;
	else
		return 0;
}

void contadorCaracter(Config *config)
{
	FILE *arquivo;
	config->qntd_crct=0;
	char caracter;
	arquivo = fopen(config->nomeArquivo, "r");
	while(fgetc(arquivo)!=EOF)
	{
        config->qntd_crct++;
	}
	fclose(arquivo);
}

void contadorPalavras(Config *config)
{
	FILE *arquivo;
	config->qntd_plv=0;
	config->qntd_indice = 0;
	int espaco = 1;
	char caracter;
	arquivo = fopen(config->nomeArquivo, "r");
	for (caracter=fgetc(arquivo); caracter!=EOF; caracter=fgetc(arquivo))
	{
		if(verificaCaracterInicio(caracter))
		{
			espaco = 1;
		}
		else if(!verificaCaracterInicio(caracter) && espaco == 1)
		{
			config->qntd_plv++;
			espaco = 0;
		}
	}
	fclose(arquivo);
}

void comparacoesListaSequencial(Comparacoes *comp)
{
	printf("Lista Sequencial\n");
	printf("-----------------------------------------------------\n\n");
	printf("Comparações | Movimentações | Tempo\n\n");
	printf("Ler arquivo:                    %lu | %lu | %fs\n", comp[0].c, comp[0].m, comp[0].tempo);
	printf("Criar índice:                   %lu | %lu | %fs\n", comp[1].c, comp[1].m, comp[1].tempo);
	printf("Ordenar por ordem alfabética:   %lu | %lu | %fs\n", comp[2].c, comp[2].m, comp[2].tempo);
	printf("Ordenar por ocorrências:        %lu | %lu | %fs\n", comp[3].c, comp[3].m, comp[3].tempo);
	printf("Pesquisa Sequencial:            %lu | %lu | %fs\n", comp[4].c, comp[4].m, comp[4].tempo);
	printf("Pesquisa Binária:               %lu | %lu | %fs\n", comp[5].c, comp[5].m, comp[5].tempo);
	printf("Mostrar arquivo:                %lu | %lu | %fs\n", comp[6].c, comp[6].m, comp[6].tempo);
	printf("Salvar arquivo:                 %lu | %lu | %fs\n", comp[7].c, comp[7].m, comp[7].tempo);
	printf("Apagar índice:                  %lu | %lu | %fs\n", comp[8].c, comp[8].m, comp[8].tempo);
	printf("Apagar texto:                   %lu | %lu | %fs\n", comp[9].c, comp[9].m, comp[9].tempo);
	printf("-----------------------------------------------------\n\n");
}



void explicacaoPrograma(void)
{
	char continuar;
	system(LIMPA);
	aparenciaMenu();
	aparenciaMenuDescricao(11);
	printf("Ideia: criar um programa capaz de coletar as palavras\n"
		"de um texto e pesquisar a frequência da palavra escolhida.\n\n");
	
	printf("\n\nDigite qualquer tecla para continuar:\n");
	ler_string(&continuar);
}



void fimDoPrograma(void)
{
	system(LIMPA);
	printf("*****************************************************\n");
	printf("                    FIM DO PROGRAMA\n");
	printf("*****************************************************\n");
	sleep(3);
}