#ifndef CALENDARIO_H
#define CALENDARIO_H value

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimeTerminal(FILE *f,int lingua,int mes,int ano,char *arquivo);
int descobreDias(int mes, int ano);
int checaAno(int ano);
int defineInicio(int mes, int ano);

//void liberaAno(dia *a);

#endif