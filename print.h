#ifndef PRINT_H
#define PRINT_H

#include "pdfgen.h"
#include "calendario.h"

/*
* cria o pdf, chama a funcao de desenhar o calendario,
* salva o pdf e desaloca o ponteiro usado para cria-lo
*/
void iniciaPdf(FILE *f,int mes,int ano,int lingua,char *arquivo);

/*
* chama todas as funcoes necessarias para desenhar o calendario
*/
void desenhaCalendario(struct pdf_doc *pdf,FILE *f,int mes,int ano,int lingua);

/*
* usa a funcao defineTipo() para desenhar a grade adequada para o mes
*/
void desenhaGrade(struct pdf_doc *pdf,double tipo);

/*
* imprime os dias da semana baseado na escolha da lingua
*/
void imprimeSemana(struct pdf_doc *pdf,int lingua);

/*
* imprime os dias do mes nas posicoes adequdas, 
* colocando o dia 1 em seu dia da semana correspondente para determinado mes
*/
void imprimeDias(struct pdf_doc *pdf,double tipo,int mes,int ano,int distanciaX,int distanciaY,int fonte,int x1,int x2);

/*
* faz calculos baseados no mes,e ano para definir em que dia da semana o 
* mes comeca
* retorno 0 = sabado, 1 = domingo , 2 = segunda, 3 = terca, 4 = quarta
* 5 = quinta, 6 = sexta; 
*/
int defineInicio(int mes, int ano);

/*
* usa a funcao defineInicio(); para descobrir qual tipo de grade deve ser impressa
* retorna float para facilitar os calculos
* retorno = 0, 4 colunas (quando o ano nao e bissexto, o mes e fevereiro e comeca no domingo)
* retorno = 1, 5 colunas (quando o mes tem 30 ou 31 dias e nao comeca sexta ou sabado)
* retorno = 1.68 colunas (quando o mes tem 31 dias e o mes comeca sexta ou sabado, ou o mes tem 30 dias e comeca sabado)
*/
double defineTipo(int dia, int mes, int ano);

/*
* usa o ano para fazer os calculos adequados para descobrir se o ano e bissexto ou nao
* para 
*/

void imprimeMesAno(struct pdf_doc *pdf,int mes,int ano,int lingua,int fonte,int x1,int y1);
int descobreMes(int mes,int ano);
void desenhaProximoMes(struct pdf_doc *pdf, int tipo,int lingua, int mes, int ano);
void imporimeEventos(struct pdf_doc* pdf,FILE *f,int mes, int ano);


#endif