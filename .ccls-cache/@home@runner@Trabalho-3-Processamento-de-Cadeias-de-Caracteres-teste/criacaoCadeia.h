#include "stdafx.h"
#include "structsBase.h"
#define CONTEXTO 2

int verificaCaracter(char caracter)
{
	if(caracter == ' ')
		return 0;
	else if (caracter == ',')
		return 0;
	else if (caracter == '!')
		return 0;
	else if (caracter == '?')
		return 0;
	else if (caracter == '.')
		return 0;
	else if (caracter == ';')
		return 0;
	else if (caracter == '\'')
		return 0;
	else if (caracter == '\"')
		return 0;
	else if (caracter == ':')
		return 0;
	else if (caracter == '-')
		return 0;
	else if (caracter == '\n')
		return 0;
	else
		return 1;
}

void lerArquivo(Texto *texto, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	FILE *arquivo;
	int linha=0, palavra = 0, espaco = 1;
	char token;
	arquivo = fopen(config.nomeArquivo, "r");
	comp->m++;
	
	if(!arquivo)
	{
		perror("Não foi possível achar o arquivo");
		exit(1);
	}
	comp->c++;

	comp->m++;
	texto->caracter = (char*) malloc ((config.qntd_crct+1)*sizeof(char));
	if(!texto->caracter)
	{
		printf("Não há espaço na memória!\n");
		exit(1);
	}
	comp->c++;

	comp->m++;
	texto->inicio = (int*) malloc ((config.qntd_plv)*sizeof(int));
	if(!texto->inicio)
	{
		printf("Não há espaço na memória!\n");
		exit(1);
	}
	comp->c++;
	
	for (token=fgetc(arquivo); token!=EOF; token=fgetc(arquivo))
	{
		texto->caracter[linha] = token;
		if(!verificaCaracter(token))
		{
			espaco = 1;
			comp->m++;
		}
		else if(verificaCaracter(token) && espaco == 1)
		{
			texto->inicio[palavra] = linha;
			palavra++;
			espaco = 0;
			comp->m+=3;
		}
		linha++;
		comp->m+=2;
		comp->c+=3;
	}
	comp->m++;
	comp->c++;
	fclose(arquivo);

	comp->m++;
	texto->caracter[config.qntd_crct] = '\0';
	printf("%d caracteres lidos!\n", linha);
	printf("%d palavras lidas!\n", palavra);
	
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void criarIndice(Indice **indice, Texto texto, Comparacoes *comp, Config *config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	int crc = 0;
	char palavra[20];
	
	comp->m++;
	*indice = (Indice*) malloc ((config->qntd_plv)*sizeof(Indice));
	if(!*indice)
	{
		printf("Não há espaço na memória!\n");
		exit(1);
	}
	comp->c++;
	
	for (int i=0; i<config->qntd_plv; i++) 
	{
		crc = 0;
		comp->m++;
		for(int j = texto.inicio[i]; verificaCaracter(texto.caracter[j]); j++)
		{
			palavra[crc] = tolower(texto.caracter[j]);
			crc++;
			comp->m+=2;
			comp->c++;
		}
		palavra[crc] = '\0';
		comp->m++;
		comp->c++;
		
		for(int k=0; k<=config->qntd_indice; k++)
		{
			if(strcmp((*indice)[k].cadeia, palavra) == 0)
			{
				(*indice)[k].ocorrencias+=1;
				(*indice)[k].locais = (int*) realloc ((*indice)[k].locais, (*indice)[k].ocorrencias*sizeof(int));
				(*indice)[k].locais[(*indice)[k].ocorrencias-1] = texto.inicio[i];
				comp->m+=3;
				break;
			}
			else if(k == config->qntd_indice)
			{
				strcpy((*indice)[k].cadeia, palavra);
				(*indice)[k].ocorrencias = 1;
				(*indice)[k].locais = (int*) malloc (sizeof(int));
				(*indice)[k].locais[0] = texto.inicio[i];
				config->qntd_indice++;
				comp->m+=5;
				break;
			}
			comp->c+=3;
		}
		comp->c++;
	}
	
	comp->m++;
	*indice = (Indice*) realloc (*indice, config->qntd_indice*sizeof(Indice));
	if(!(*indice))
	{
		printf("Não há espaço na memória!\n");
		exit(1);
	}
	comp->c++;
	
	for(int i=0; i<config->qntd_indice; i++)
	{
		printf("%d| %s, %d | ", i+1, (*indice)[i].cadeia, (*indice)[i].ocorrencias);
		for(int j=0; j<(*indice)[i].ocorrencias; j++)
		{
			printf("%d ", (*indice)[i].locais[j]);
			comp->c++;
		}
		printf("\n");
		comp->c++;
	}
	printf("%d palavras registradas!\n", config->qntd_indice);
	comp->c++;
	
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void criarArvoreTrie(Trie **arvore, Indice *indice, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	
	for (int i=0; i<config.qntd_plv; i++) 
	{
		for(int j = 0; indice[i].cadeia[j] != '\0'; j++)
		{
			if ((*arvore)->caracter[indice[i].cadeia[j] - 'a'] == NULL) 
			{
        		(*arvore)->caracter[indice[i].cadeia[j] - 'a'] = (Trie*) malloc (sizeof(Trie));
       		}
			
		    (*arvore) = (*arvore)->caracter[texto.caracter[j] - 'a'];
		}
	    (*arvore)->folha = 1;
	}
	
	printf("Árvore Trie criado!\n");
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}


void ordenarIndiceOrdemAlfabetica(Indice **indice, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	
	int ordenou=0;
	Indice aux;
	
	comp->m++;
	while(ordenou!=1)
	{
		ordenou=1;
		comp->m++;
		for(int e=0; e<config.qntd_indice-1; e++)
		{
			if(strcmp((*indice)[e].cadeia, (*indice)[e+1].cadeia) > 0)
			{	
				strcpy(aux.cadeia, (*indice)[e].cadeia);
				aux.ocorrencias = (*indice)[e].ocorrencias;
				aux.locais = (*indice)[e].locais;
				strcpy((*indice)[e].cadeia, (*indice)[e+1].cadeia);
				(*indice)[e].ocorrencias = (*indice)[e+1].ocorrencias;
				(*indice)[e].locais = (*indice)[e+1].locais;
				strcpy((*indice)[e+1].cadeia, aux.cadeia);
				(*indice)[e+1].ocorrencias = aux.ocorrencias;
				(*indice)[e+1].locais = aux.locais;
				
				ordenou=0;
				comp->m+=9;
			}
			comp->c+=2;
			comp->m++;
		}
		comp->m+=2;
		comp->c+=2;
	}
	comp->c++;
	
	for(int i=0; i<config.qntd_indice; i++)
	{
		printf("%d| %s,%d\n", i+1, (*indice)[i].cadeia, (*indice)[i].ocorrencias);
		comp->c++;
	}
	comp->c++;
	
	printf("Índice ordenado em ordem alfabética!\n");
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void ordenarIndicePorOcorrencias(Indice **indice, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	
	int ordenou=0;
	Indice aux;
	
	comp->m++;
	while(ordenou!=1)
	{
		ordenou=1;
		for(int e=0; e<config.qntd_indice-1; e++)
		{
			if((*indice)[e].ocorrencias < (*indice)[e+1].ocorrencias)
			{
				strcpy(aux.cadeia, (*indice)[e].cadeia);
				aux.ocorrencias = (*indice)[e].ocorrencias;
				aux.locais = (*indice)[e].locais;
				strcpy((*indice)[e].cadeia, (*indice)[e+1].cadeia);
				(*indice)[e].ocorrencias = (*indice)[e+1].ocorrencias;
				(*indice)[e].locais = (*indice)[e+1].locais;
				strcpy((*indice)[e+1].cadeia, aux.cadeia);
				(*indice)[e+1].ocorrencias = aux.ocorrencias;
				(*indice)[e+1].locais = aux.locais;
				
				ordenou=0;
				comp->m+=9;
			}
			comp->c+=2;
			comp->m++;
		}
		comp->m+=2;
		comp->c+=2;
	}
	comp->c++;
	
	for(int i=0; i<config.qntd_indice; i++)
	{
		printf("%d| %s,%d\n", i+1, (*indice)[i].cadeia, (*indice)[i].ocorrencias);
		comp->c++;
	}
	comp->c++;
	
	printf("Índice ordenado elo número de ocorrencias!\n");
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}



void procuraContexto(Indice *indice, Texto texto, Comparacoes *comp, Config config, int local)
{
	int antes, depois;
	printf("Posição: %d\n", local);
	for(int i = 0; i < config.qntd_plv; i++)
	{
		if(local == texto.inicio[i])
		{
			if(i == 0)
				antes = 0;
			else
			{
				antes = texto.inicio[i-CONTEXTO];
				printf("...");
			}

			if(i >= config.qntd_plv-CONTEXTO)
				depois = config.qntd_crct;
			else
				depois = texto.inicio[i+CONTEXTO+1];

			break;
		}
	}
	
	for(int a = antes; a < depois; a++)
	{
		printf("%c", texto.caracter[a]);
	}
	
	if(local != texto.inicio[config.qntd_plv-CONTEXTO])
	{
		printf("...\n\n\n");
	}
}

void procuraContextoFrase(Indice *indice, Texto texto, Comparacoes *comp, Config config, int local)
{
	int fim_frase;
	int antes, depois;
	int achou = 0;
	
	fim_frase = local + config.tam_padrao;
	
	for(int i = 0; i < config.qntd_plv; i++)
	{
		if(local == texto.inicio[i] && achou==0)
		{
			if(i == 0)
				antes = 0;
			else
			{
				antes = texto.inicio[i-CONTEXTO];
				printf("...");
			}
			achou = 1;
		}
		
		if(fim_frase <= texto.inicio[i] && achou==1)
		{
			if(i >= config.qntd_plv-CONTEXTO-1)
				depois = config.qntd_crct;
			else
				depois = texto.inicio[i+CONTEXTO+1];

			achou = 2;
		}
	}
	
	for(int a = antes; a < depois; a++)
	{
		printf("%c", texto.caracter[a]);
	}
	
	if(local != texto.inicio[config.qntd_plv-2])
	{
		printf("...\n\n\n");
	}
}

int pesquisaFrase(Indice *indice, Texto texto, Comparacoes *comp, Config config)
{
	int encontrou=0, k, j;
	for (int i = 0; i < config.qntd_crct-config.tam_padrao; i++)
	{ 
		k=i;
		j=0;
		while(tolower(texto.caracter[k]) == config.padrao[j] && j<=config.tam_padrao)
		{
			j++;
			k++;
		}
		
		if (j >= config.tam_padrao)
		{
			procuraContextoFrase(indice, texto, comp, config, i);
			encontrou=1;
		}
	}
	if(encontrou==1)
		return 1;
	else 
		return 0;
}

void pesquisaSequencial(Indice *indice, Texto texto, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	int encontrou=0;
	comp->m++;
	comp->c++;
	
	for(int e=0; e<config.qntd_indice && encontrou==0; e++)
	{
		if(strcmp(indice[e].cadeia, config.padrao) == 0)
		{
			printf("Palavra encontrada!!\n");
			printf("%d| %s, %d ocorrência(s)\n\n", e+1, indice[e].cadeia, indice[e].ocorrencias);
			for(int f = 0; f < indice[e].ocorrencias; f++)
			{
				procuraContexto(indice, texto, comp, config, indice[e].locais[f]);
			}
			encontrou=1;
			comp->m++;
		}
		comp->c+=2;
	}
	
	/*if(encontrou!=1)
	{
		encontrou = pesquisaFrase(indice, texto, comp, config);
	}*/
	comp->c++;
	if(encontrou!=1)
		printf("Palavra não encontrada");
	
    clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void pesquisaBinaria(Indice *indice, Texto texto, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	int minimo=0, meio=(config.qntd_indice-1)/2, maximo=config.qntd_indice-1;
	int encontrou=0, crc = 0;
	comp->m+=4;
	comp->c++;
	
	while(maximo>minimo && encontrou!=1)
	{
		if(strcmp(indice[meio].cadeia, config.padrao) > 0)
		{
			if(meio == minimo)
			{
				maximo = 0;
				meio = 0;
				comp->m+=2;
			}
			maximo = meio;
			comp->c++;
			comp->m++;
		}
		else if(strcmp(indice[meio].cadeia, config.padrao) < 0)
		{
			if(meio == minimo)
			{
				minimo = maximo;
				meio = maximo;
				comp->m+=2;
			}
			minimo = meio;
			comp->c++;
			comp->m++;
		}
		if(strcmp(indice[meio].cadeia, config.padrao) == 0)
		{
			printf("Palavra encontrada!!\n");
			printf("%d| %s, %d ocorrência(s)\n\n", meio+1, indice[meio].cadeia, indice[meio].ocorrencias);
			printf("Contexto(s):\n\n");
			for(int f = 0; f < indice[meio].ocorrencias; f++)
			{
				procuraContexto(indice, texto, comp, config, indice[meio].locais[f]);
			}
			encontrou=1;
			comp->m++;
		}
		meio=(maximo-minimo)/2 + minimo;
		comp->c+=5;
		comp->m++;
	}
	
	if(encontrou==0)
		printf("Palavra não encontrada");
	
	comp->c++;
    clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void pesquisaArvoreTrie(Trie *arvore, Texto texto, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	int encontrou=0;

	for(int j = 0; config.padrao[j] != '\0' ; j++)
	{
	    arvore = arvore->caracter[config.padrao[j] - 'a'];

		if(!arvore)
		{
			break;
		}
	}

	encontrou = arvore->folha;
	
	if(encontrou!=1)
		printf("Palavra não encontrada");
	
    clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void mostrarArquivoInvertido(Indice *indice, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	
	for(int i=0; i<config.qntd_indice; i++)
	{
		printf("%d| %s, %d | ", i+1, indice[i].cadeia, indice[i].ocorrencias);
		for(int j=0; j < indice[i].ocorrencias; j++)
		{
			printf("%d ", indice[i].locais[j]);
		}
		printf("\n");
	}
	printf("%d palavras registradas!\n", config.qntd_indice);
	
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

void salvarArquivoInvertido(Indice *indice, Texto texto, Comparacoes *comp, Config config)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	FILE *arquivo;
	arquivo = fopen(config.arqSalvo, "w");
	comp->m++;
	for(int g=0; g<config.qntd_indice; g++)
	{
		fprintf(arquivo, "%s, %d | ", indice[g].cadeia, indice[g].ocorrencias);
		for(int h = 0; h < indice[g].ocorrencias; h++)
		{
			fprintf(arquivo, "%d ", indice[g].locais[h]);
		}
		fprintf(arquivo, "\n");
		comp->c++;
	}
	comp->c++;
	fclose(arquivo);
	printf("\nArquivo salvo!");
    clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
	comparacoes(comp->c, comp->m, comp->tempo);
}

int temRamifimifacoes(Trie *arvore, Config config, Comparacoes *comp)
{
	for (int i = 0; i < 26; i++)
    {
        if (arvore->caracter[i])
		{
        	return 1;
        }
    }
	
    return 0;
}

int deletarRamificacoes(Trie **arvore, char* string, Config config, Comparacoes *comp)
{
    if (string == NULL) 
	{
        return 0;
    }
 
    if (*string)
    {
        if (*arvore != NULL && (*arvore)->caracter[*string - 'a'] != NULL && 
		deletarRamificacoes(&((*arvore)->caracter[*string - 'a']), string + 1, config, comp) &&
        (*arvore)->folha == 0)
        {
            if (!temRamifimifacoes(*arvore, config, comp))
            {
                free(*arvore);
                (*arvore) = NULL;
                return 1;
            }
            else
            	return 0;
        }
    }
 
    if (*string == '\0' && (*arvore)->folha)
    {
        if (!temRamifimifacoes(*arvore, config, comp))
        {
            free(*arvore);
            (*arvore) = NULL;
            return 1;
        }
 
        else 
		{
            (*arvore)->folha = 0;
            return 0;
        }
    }
 
    return 0;
}

void apagarArvoreTrie(Trie **arvore, Indice *indice, Config config, Comparacoes *comp)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);

	for(int i = 0; i < config.qntd_plv; i++)
	{
	    deletarRamificacoes(arvore, indice[i].cadeia, config, comp);
	}
		
	
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
}

void apagarIndice(Indice **indice, Config config, Comparacoes *comp)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);

	for(int i=0; i<config.qntd_indice; i++)
	{
		free((*indice)[i].locais);
	}
	free(*indice);
	comp->m++;
	
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
}

void apagarTexto(Texto *texto, Comparacoes *comp)
{
	comp->m=0;
	comp->c=0;
	clock_gettime(CLOCK_REALTIME, &comp->comeco);
	
	free(texto->caracter);
	free(texto->inicio);
	comp->m++;
	
	clock_gettime(CLOCK_REALTIME, &comp->fim);
    comp->tempo = (comp->fim.tv_sec-comp->comeco.tv_sec) + (comp->fim.tv_nsec-comp->comeco.tv_nsec)/1000000000.0;
}