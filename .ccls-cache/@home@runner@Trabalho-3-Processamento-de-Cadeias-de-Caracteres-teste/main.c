#include "stdafx.h"
#include "configuracao.h"
#include "criacaoCadeia.h"

int main(void)
{
	config.opcao = 0;
	config.leuArquivo = 0;
	config.ordenouIndiceAlfabeto = 0;
	config.ordenouIndiceOcorrencia = 0;
	while(config.opcao!=9)
	{
		menuDeSelecao(&config);
		switch(config.opcao)
		{
			case 1:
			{
				menudeSelecaoArquivo(&config);
				contadorCaracter(&config);
				contadorPalavras(&config);
				menudeSelecaoLer();
				
				if(config.leuArquivo == 1)
				{
					//apagarArvoreTrie(&arvore, indice, config, &comp[7]);
					apagarIndice(&indice, config, &comp[8]);
					apagarTexto(&texto, &comp[9]);
				}
				
				lerArquivo(&texto, &comp[0], config);
				criarIndice(&indice, texto, &comp[1], &config);
				//criarArvoreTrie(&arvore, indice, &comp[7], config);
						
				config.leuArquivo=1;
				digiteAlgo();
				break;
			}
			case 2:
			{
				if(config.leuArquivo!=1)
				{
					tipoDeErro(3);
					break;
				}
				config.ordenouIndiceOcorrencia = 0;

				ordenarIndiceOrdemAlfabetica(&indice, &comp[2], config);
				digiteAlgo();
				config.ordenouIndiceAlfabeto = 1;
				break;
			}
			case 3:
			{
				if(config.leuArquivo!=1)
				{
					tipoDeErro(3);
					break;
				}
				config.ordenouIndiceAlfabeto = 0;

				ordenarIndicePorOcorrencias(&indice, &comp[3], config);
				digiteAlgo();
				config.ordenouIndiceOcorrencia = 1;
				break;
			}
			case 4:
			{
				if(config.leuArquivo!=1)
				{
					tipoDeErro(3);
					break;
				}
				
				menudeSelecaoPalavra(&config);
				menudeSelecaoProcurar();
				pesquisaSequencial(indice, texto, &comp[4], config);
				//pesquisaArvoreTrie(arvore, texto, &comp[7], config);
				digiteAlgo();
				break;
			}
			case 5:
			{
				if(config.leuArquivo!=1)
				{
					tipoDeErro(3);
					break;
				}

				if(config.ordenouIndiceAlfabeto!=1)
				{
					tipoDeErro(8);
					break;
				}
				
				menudeSelecaoPalavra(&config);
				menudeSelecaoProcurar();
				pesquisaBinaria(indice, texto, &comp[5], config);
				digiteAlgo();
				break;
			}
			case 6:
			{
				if(config.leuArquivo!=1)
				{
					tipoDeErro(3);
					break;
				}
				
				menudeSelecaoSalvar(&config);
				mostrarArquivoInvertido(indice, &comp[6], config);
				digiteAlgo();
				break;
			}
			case 7:
			{
				if(config.leuArquivo!=1)
				{
					tipoDeErro(3);
					break;
				}
				
				menudeSelecaoSalvar(&config);
				salvarArquivoInvertido(indice, texto, &comp[7], config);
				digiteAlgo();
				break;
			}
			case 8:
			{
				aparenciaMenu();
				comparacoesListaSequencial(comp);
				digiteAlgo();
				break;
			}
			case 9:
			{
				explicacaoPrograma();
				break;
			}
			case 10:
			{
				//apagarArvoreTrie(&arvore, indice, config, &comp[7]);
				apagarIndice(&indice, config, &comp[8]);
				apagarTexto(&texto, &comp[9]);
				fimDoPrograma();
				break;
			}
		}
	}
	system(LIMPA);
}