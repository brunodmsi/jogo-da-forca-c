#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.h"

char* palavra;
char* palavra_traduzida;
char* erros;
int chances;
int letras;

int isJogoSalvo() {
	startaVariaveis();
	
	FILE *forca;
	forca = fopen("forca.prova", "r");
	if(forca == NULL) {
		forca = fopen("forca.prova", "ab+");
		return 0;
	}
	
	fseek(forca, 0, SEEK_END);
	int tamanho = ftell(forca);
	fclose(forca);
	
	if(tamanho == 0) return 0;
	else return 1;
}

int isLetra(char c) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
      return 1;
   return 0;
}

int contarLetras(char *s) {
	int i;
	for(i = 0; s[i] != 0; i++) {
		if(isLetra(s[i])) letras++;
	}
	return letras;
}

char maiuscula(char c) {
	return (c >= 'a' && c <= 'z') ? (c - 32) : c;
}

char* comecaNovo() {
	int linha_pais = rand() % 20 + 1;
	chances = 6;
	
	startaVariaveis();
	
	FILE *f = fopen("Paises.txt", "r");
	if(f == NULL) {
		criaArquivoPaises();
		f = fopen("Paises.txt", "r");
	}
	int contador = 1;
	if(f != NULL) {
		char linha[20];
		while(fgets(linha, sizeof linha, f) != NULL) {
			if(contador == linha_pais) {
				strcpy(palavra, linha);
		//		printf("%s", palavra);
				letras = contarLetras(palavra);
				char *a_traduzir = (char *) malloc(25 * sizeof(char));
				strcpy(a_traduzir, palavra);
				palavra_traduzida = traduzir_nome(a_traduzir);
				return palavra_traduzida;
			} else contador++;
		}
		fclose(f);
	}
}

char* traduzir_nome(char *traduzido) {
	int i;
	for(i = 0; i < strlen(traduzido) - 1; i++) {
		if(traduzido[i] != ' ') {
			traduzido[i] = '_';
		}
	}
	return traduzido;
}

char* desenhaStickman() {
	char *stickman = (char *) malloc(50 * sizeof(char));
	limpaBuffer(stickman, 50);
	
	if(chances >= 1)
		strcat(stickman, "   O\n");
	if(chances >= 2)
		strcat(stickman, "  /");
	if(chances >= 3)
		strcat(stickman, " \\ \n");
	if(chances >= 4)
		strcat(stickman, "   |\n");
	if(chances >= 5)
		strcat(stickman, "  /");
	if(chances == 6)
		strcat(stickman, " \\");
		
	return stickman;
}

void salvarProgresso() {
	char *save = (char *) malloc(250 * sizeof(char));
	
	limpaBuffer(save, 250 * sizeof(char));
	
	char *str_letras, *str_chances;
	str_chances = (char *) malloc(10 * sizeof(char));
	str_letras = (char *) malloc(10 * sizeof(char));
	sprintf(str_letras, "%d", letras);
	sprintf(str_chances, "%d", chances);
//	printf("\n%s", palavra);
	strcat(save, palavra);
	strcat(save, palavra_traduzida);
	strcat(save, erros);
	strcat(save, "\n");
	strcat(save, str_letras);	
//	printf("\n%s", str_letras);
	strcat(save, "\n");
//	printf("\n%s", str_chances);
	strcat(save, str_chances);
//	printf("\n%s", save);
//	system("pause>null");
	FILE *f;
	f = fopen("forca.prova", "w");
	fprintf(f, save);
	fclose(f);
	
	free(save);
}

void carregaSalvo() {
	FILE *f;
	f = fopen("forca.prova", "r");
	int i = 0, contador = 0, isGanho;
	const size_t tamanho_linha = 100;
	char *linha = malloc(tamanho_linha);
	while(fgets(linha, tamanho_linha, f) != NULL) {
		if(i == 0) {
//			printf("%s", linha);			
			strcpy(palavra, linha);
		}
		
		if(i == 1) {
//			printf("%s", linha);
			for(contador = 0; contador < strlen(linha) - 1; contador++) {
				printf("%c", linha[contador]);
				if(linha[contador] == '_') {
					isGanho = 0;
					break;
				} else
					isGanho = 1;
			}
			
			if(isGanho == 1) {
				comecaNovo();
				break;
			}
			
			strcpy(palavra_traduzida, linha);
		}
			
		if(i == 2) {
			if(strlen(linha) > 0) {
				linha[strlen(linha) - 1] = 0;
				strcpy(erros, linha);
//				printf("%s", erros);
			}
		}
				
		if(i == 3) {
			char *str_letras = linha;
//			printf("%s", linha);
			int qtde_letras = sscanf(str_letras, "%d", &letras);
		}
		
		if(i == 4) {
			char *str_chances = linha;
//			printf("%s", linha);
			int qtde_chances = sscanf(str_chances, "%d", &chances);
			
			if(chances == 0) {
				limpaBuffer(palavra, 25);
				limpaBuffer(palavra_traduzida, 25);
				limpaBuffer(erros, 20);
				comecaNovo();
				break;
			}
//			system("pause>null");
		}
		i++;
	}
	free(linha);
	fclose(f);
}

void criaArquivoPaises() {
	char *paises = (char *) malloc(250 * sizeof(char));
	limpaBuffer(paises, 250);
	
	strcat(paises, "Estados Unidos\n");
	strcat(paises, "Africa do Sul\n");
	strcat(paises, "Brasil\n");
	strcat(paises, "Alemanha\n");
	strcat(paises, "Argentina\n");
	strcat(paises, "Canada\n");
	strcat(paises, "Espanha\n");
	strcat(paises, "Franca\n");
	strcat(paises, "Arabia Saudita\n");
	strcat(paises, "Egito\n");
	strcat(paises, "Coreia do Sul\n");
	strcat(paises, "Costa do Marfim\n");
	strcat(paises, "Nova Zelandia\n");
	strcat(paises, "Australia\n");
	strcat(paises, "Costa Rica\n");
	strcat(paises, "Croacia\n");
	strcat(paises, "Coreia do Norte\n");
	strcat(paises, "Bangladesh\n");
	strcat(paises, "Afeganistao\n");
	strcat(paises, "Maldivas");
	
	FILE *arquivo_paises;
	arquivo_paises = fopen("Paises.txt", "w");
	fprintf(arquivo_paises, paises);
	fclose(arquivo_paises);
	
	free(paises);
}

void limpaBuffer(char *buf, int tamanho) {
	int i = 0;
	for(i = 0; i < tamanho; i++) {
		buf[i] = 0;
	}
}

void startaVariaveis() {
	palavra = (char *) malloc(25 * sizeof(char));
	palavra_traduzida = (char *) malloc(25 * sizeof(char));
	erros = (char *) malloc(20 * sizeof(char));
	
	limpaBuffer(palavra, 25 * sizeof(char));
	limpaBuffer(palavra_traduzida, 25 * sizeof(char));
	limpaBuffer(erros, 20 * sizeof(char));
	letras = 0;
}

char* getForca() {
	return palavra_traduzida;
}

char* getPalavra() {
	return palavra;
}

char* getErros() {
	return erros;
}

int getChances() {
	return chances;
}

int getQtdeLetras() {
	return letras;
}

void diminuiChances() {
	chances = chances - 1;
}
