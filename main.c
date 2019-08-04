//copyright © 2019 all rights reserved - Vitor Siqueira Lobao UNIFEI-2018004809


#include "pdfgen.h"
#include "print.h"
#include "calendario.h"

int main(void) {
   
   	FILE *f;
   	int opcao;
   	int ano;
   	int mes;
   	char arquivo[100];
   	int lingua;

   	while(1){
   		printf("Selecione a opcao de seu desejo\n");
   		printf("1 - inserir dados\n");
   		printf("2 - imprime calendario no terminal\n");
   		printf("3 - imprime no pdf\n");
   		printf("4 - exit\n");
   		scanf("%d",&opcao);
	   	switch(opcao){
	   		case 1:
	   			printf("Insira o mes\n");
	   			scanf("%d",&mes);
	   			printf("Insira o ano\n");
	   			scanf("%d",&ano);
	   			printf("Digite 0 para portugues e 1 para ingles\n");
	   			scanf("%d",&lingua);
	   			printf("Escreva o nome do arquivo que deseja inserir\n");
	   			scanf("%s",arquivo);
	   			break;
	   		case 2:
	   			imprimeTerminal(f,lingua,mes,ano,arquivo);
	   			break;
	   		case 3:
	   			iniciaPdf(f,mes,ano,lingua,arquivo);
	   			exit(1);
	   			break;
	   		case 4:
	   			exit(1);
	   	}	
    }



    
   	
   	


    
    return 0;
}
