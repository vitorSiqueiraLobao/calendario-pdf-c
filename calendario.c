#include "calendario.h"



void imprimeTerminal(FILE *f,int lingua,int mes,int ano,char *arquivo){
	f = fopen(arquivo,"r");
	char tipo;
	int diaArq;
	int mesArq;
	int anoArq;
	char descricao[26];
	int quantidadeEventos = 0;
	int semanaInicio = defineInicio(mes,ano);
	char tiposEntram[100];
	int diasEntram[100];
	int mesesEntram[100];
	int anosEntram[100];
	char descricoesEntram[100][26];

	char diasDaSemana[14][14] = {{"SABADO"},{"DOMINGO"},{"SEGUNDA-FEIRA"},{"TERCA-FEIRA"},{"QUARTA-FEIRA"},{"QUINTA-FEIRA"},{"SEXTA-FEIRA"},
                                {"SATURDAY"},{"SUNDAY"},{"MONDAY"},{"TUESDAY"},{"WEDNESDAY"},{"THURSDAY"},{"FRIDAY"}};

	while(fscanf(f," %c %d %d %d %[^\n]s",&tipo,&diaArq,&mesArq,&anoArq,descricao) != EOF){
		if((mesArq == mes || mesArq == 0)&&(anoArq == ano || anoArq == 0)){
			tiposEntram[quantidadeEventos] = tipo;
			diasEntram[quantidadeEventos] = diaArq;
			mesesEntram[quantidadeEventos] = mesArq;
			anosEntram[quantidadeEventos] = anoArq;
			sprintf(descricoesEntram[quantidadeEventos], "%s", descricao);
			quantidadeEventos++;
		}
	
	}
	
	
	for(int i = 0; i < descobreDias(mes,ano) ;i++){
		printf("%d %s\n",i+1,diasDaSemana[semanaInicio+(7*lingua)]);
		for(int j = 0; j<quantidadeEventos;j++){
			if(diasEntram[j]== (i+1) || diasEntram[j] == 0){
				printf("   %c %s \n",tiposEntram[j],descricoesEntram[j]);
			}
		}
		if(semanaInicio==6){
			semanaInicio = 0;
		}else{
			semanaInicio++;
		}
		
	}
	fclose(f);
	

}

int descobreDias(int mes, int ano){
	if(mes == 2){
        if(checaAno(mes)){
            return 29;
        }else{
            return 28;
        }
    }else if(mes%2==0 && mes<=7){
		return 30;
	}else if(mes%2!=0 && mes<=7){
		return 31;
	}else if(mes%2==0 && mes>7){
		return 31;
	}else if(mes%2!=0 && mes>7){
		return 30;
	}
}

int checaAno(int ano){
    if((ano % 4 == 0) && (ano % 100 != 0)){
        return 1;
    }else if((ano % 4 == 0) && (ano % 100 == 0)&&(ano % 400 == 0)){
        return 1.0;
    }else{
        return 0.0;
    }
}
