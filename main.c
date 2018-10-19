#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.h"

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	
	int chances, qtdeLetras, i, ganhou;
	char tentativa, *palavra, *palavra_forca, *erros;
	
	if(!isJogoSalvo())
		comecaNovo();
	else
		carregaSalvo();
		
	palavra = (char *) malloc(25 * sizeof(char));
	palavra_forca = (char *) malloc(25 * sizeof(char));
	
	limpaBuffer(palavra, 25);
	limpaBuffer(palavra_forca, 25);
	
	qtdeLetras = getQtdeLetras();
	palavra = (char *) getPalavra();
	palavra_forca = (char *) getForca();	
	chances = getChances();
	erros = (char *) getErros();
	
	while(chances > 0) {
		system("cls");
		printf("\n  |-> Chances: %d\n  |-> Palavra tem %d letras\n\n", chances, qtdeLetras);
		
		char *stickman = desenhaStickman();
		printf("%s\n\n", stickman);
	//	printf("%s", palavra);
		printf("%s", palavra_forca);
		if(strlen(erros) > 0) {
			printf("\nErros: %s", erros);
		}
		
		printf("\n\nDigite uma letra: ");
		scanf("%c", &tentativa);
		fflush(stdin);
		
		if(!isLetra(tentativa)) continue;
		
		int jaTentou = 0;
		for(i = 0; erros[i] != 0; i++) {
			if(erros[i] == maiuscula(tentativa)) {
				jaTentou = 1;
				break;
			}
		}
		
		if(jaTentou) continue;
		for(i = 0; palavra_forca[i] != 0; i++) {
			if(maiuscula(palavra_forca[i]) == maiuscula(tentativa)) {
				jaTentou = 1;
				break;
			}
		}
		
		if(jaTentou) continue;
		
		ganhou = 1;
		int achou = 0;
		for(i = 0; palavra[i] != 0; i++) {
			if(!isLetra(palavra[i])) continue;
			if(palavra_forca[i] == '_') {
				if(maiuscula(palavra[i]) == maiuscula(tentativa)) {
					palavra_forca[i] = palavra[i];
					achou = 1;
				} else {
					ganhou = 0;
				}
			}
		}
		
		if(!achou) {
			diminuiChances();
			erros[strlen(erros)] = maiuscula(tentativa);
		}
		
		chances = getChances();
		
		salvarProgresso();
		
		if(ganhou) break;
	}
	
	if(ganhou) {
		system("cls");
		printf("\n ==============================================\n");
		printf(" ============ PARABENS VOCE GANHOU ============\n");
		printf(" ==============================================\n");
		printf("\n\n\t Descobriu a palavra %s", palavra);
	}
	
	if(chances == 0) {
		system("cls");
		printf("\n ==============================================\n");
		printf(" ================ VOCE  PERDEU ================\n");
		printf(" ==============================================\n");
		printf("\n\n\t Os seus erros foram: %s", erros);
		printf("\n\t A palavra era %s", palavra);
		printf("\t E voce conseguiu chegar ate %s", palavra_forca);
	}
	
	return 0;
}
