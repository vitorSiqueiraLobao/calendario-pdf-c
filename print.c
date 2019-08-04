#include "print.h"

void iniciaPdf(FILE *f,int mes,int ano,int lingua,char *arquivo){
    f = fopen(arquivo,"r");
    struct pdf_info info = {//cria os ,metadados do arquivo
        .creator = "My software",
        .producer = "My software",
        .title = "My document",
        .author = "My name",
        .subject = "My subject",
        .date = "Today"
    };
     struct pdf_doc *pdf = pdf_create(PDF_A4_HEIGHT, PDF_A4_WIDTH, &info);//cria o objeto pdf com as dimensoes
     pdf_set_font(pdf, "Helvetica");//define fonte
     pdf_append_page(pdf);//adiciona uma pagina no objeto criado
     desenhaCalendario(pdf,f,mes,ano,lingua);//desenha o calendario

     pdf_save(pdf, "teste.pdf");//exporta o objeto em forma de pdf
     pdf_destroy(pdf);//limpa a memoria alocada
     fclose(f);
}


void desenhaCalendario(struct pdf_doc *pdf,FILE *f,int mes,int ano,int lingua){ 
        

       double tipo = defineTipo(1,mes,ano);

                     //variavel utilizada para os casos nos quais os dias n 
                     //cabem em mais de 4 colunas, se a variavel for 1,
                     //ela age multiplicando os parametros das funcoes 
                     //da biblioteca responsavel por imprimir,diminuindo
                     // o espaco entre as linhas,se a variavel
                     //for 0, nao havera mudanca, e ha tbm o caso em que ela sera
                     // 1.68, que sera o caso em que o mes tera 31 dias, e o dia 1
                     // for na sexta ou no domingo.
        desenhaGrade(pdf,tipo);
        imprimeSemana(pdf,0);
        desenhaProximoMes(pdf,lingua,tipo,mes,ano);
        imprimeDias(pdf,tipo,mes,ano,117,110,15,18,465);
        imprimeMesAno(pdf,mes,ano,lingua,72,10,510);
        imporimeEventos(pdf,f,mes,ano);
        
        
}

void imprimeSemana(struct pdf_doc *pdf,int lingua){

    int fonte = 12;
    int x1 = 25;
    int y1 = 486;

    char diasDaSemana[14][14] = {{"DOMINGO"},{"SEGUNDA-FEIRA"},{"TERCA-FEIRA"},{"QUARTA-FEIRA"},{"QUINTA-FEIRA"},{"SEXTA-FEIRA"},{"SABADO"},
                                {"SUNDAY"},{"MONDAY"},{"TUESDAY"},{"WEDNESDAY"},{"THURSDAY"},{"FRIDAY"},{"SATURDAY"}};

    for(int i = 0+(7*lingua); i<7+(7*lingua) ; i++){//printa os dias
        if((i == 0+(7*lingua)|| i == 6+(7*lingua))){//printa os dias  vermelhos
           pdf_add_text(pdf,NULL,diasDaSemana[i],fonte,x1+(i*117),y1,PDF_RED);
        }else{//printa os dias pretos
           pdf_add_text(pdf,NULL,diasDaSemana[i],fonte,x1+(i*117),y1,PDF_BLACK);
        }
    }
}

void desenhaGrade(struct pdf_doc *pdf, double tipo){
        for(int j = 0; j < 5+((tipo*2)); j++){//laco responsavel por todas as repitcoes, 
            if(j==0){//garante que somente duas linhas serao printadas proximamente
                for(int i = 0; i < 7 ; i++){//printa as linhas "gemeas"

                    if(i == 0 || i== 6){//printa as partes vermelhas das linhas "gemeas"
                     pdf_add_line(pdf,NULL,10+(i*117),500,127+(i*117),500,2,PDF_RED);
                     pdf_add_line(pdf,NULL,10+(i*117),480,127+(i*117),480,2,PDF_RED);
                    }else{//printa as partes pretas das linhas "gemeas"
                     pdf_add_line(pdf,NULL,10+(i*117),500,127+(i*117),500,2,PDF_BLACK);
                     pdf_add_line(pdf,NULL,10+(i*117),480,127+(i*117),480,2,PDF_BLACK);   
                    }
                }

            }else{
                 for(int i = 0; i < 7 ; i++){//printa o resto das linhas
                    if(i == 0 || i== 6){//printa a parte vermelha das linhas
                     pdf_add_line(pdf,NULL,10+(i*117),480-(110*j)+(22*tipo*j),127+(i*117),480-(110*j)+(22*tipo*j),2,PDF_RED);
                    }else{//printa as partes pretas das linhas 
                     pdf_add_line(pdf,NULL,10+(i*117),480-(110*j)+(22*tipo*j),127+(i*117),480-(110*j)+(22*tipo*j),2,PDF_BLACK);   
                    }
            }
        }
        for(int i = 0; i < 8; i++){//printa as linhas verticais
            if(i == 0 || i ==7){//printa as linhas vermelhas
                pdf_add_line(pdf,NULL,10+(117*i),500,10+(117*i),40,2,PDF_RED);
            }else{//printa as linhas pretas
                pdf_add_line(pdf,NULL,10+(117*i),500,10+(117*i),40,2,PDF_BLACK);
            }
        }
    }        
}

void imprimeDias(struct pdf_doc *pdf,double tipo,int mes,int ano,int distanciaX,int distanciaY,int fonte,int x1,int y1){
    int mesTipo = descobreMes(mes,ano);


    int inicio = defineInicio(mes,ano);
    if(inicio == 0){inicio = 7;}//troca o sabado de 0 para 7, para facilitar as contas
    inicio--;

    int aux = 0;
 
    for(int i = 1; i <= 31-mesTipo; i++){
        char *dia = malloc(2*sizeof(char));
        int n = i/10;
        int a,b;

        int diaSemana = x1+(distanciaX*inicio)-(distanciaX*aux*6)+(distanciaX*(i-aux-1));
        int semanaMes = y1-(aux * distanciaY)+(aux*tipo * 22);
        
        a = (i/10) + 48;
        b = (i%10) + 48;
      
        dia[0] = a;
        dia[1] = b;

        
        if( diaSemana == x1 || diaSemana == x1+(distanciaX*6)){
            pdf_add_text(pdf,NULL,dia,fonte,diaSemana,semanaMes,PDF_RED);
            
        }else{
            pdf_add_text(pdf,NULL,dia,fonte,diaSemana,semanaMes,PDF_BLACK);
        }

         if(((i+inicio)%7)==0){
            aux++;
        }
    }
     
}

void imprimeMesAno(struct pdf_doc *pdf,int mes,int ano,int lingua,int fonte,int x1,int y1){
    mes--;
    char meses[24][10] = {{"JANEIRO"},{"FEVEREIRO"},{"MARCO"},{"ABRIL"},{"MAIO"},{"JUNHO"},{"JULHO"},{"AGOSTO"},{"SETEMBRO"},{"OUTUBRO"},{"NOVEMBRO"},{"DEZEMBRO"},
                            {"JANUARY"},{"FEBRUARY"},{"MARCH"},{"APRIL"},{"MAY"},{"JUNE"},{"JULY"},{"AUGUST"},{"SEPTEMBER"},{"OCTOBER"},{"NOVEMBER"},{"DECEMBER"}};
    char *anoC = malloc(4 * sizeof(char));
    anoC[0] = (ano/1000) + 48;
    anoC[1] = ((ano%1000)/100) + 48;
    anoC[2] = (((ano%1000)%100)/10) + 48;
    anoC[3] = (((ano%1000)%100)%10) + 48;

    char mesAno[16];

    sprintf(mesAno,"%s %s",meses[mes+(12*lingua)],anoC);

    pdf_add_text(pdf,NULL,mesAno,fonte,x1,y1,PDF_BLACK);
}

int defineInicio(int mes, int ano){//usa um formula para definir em que dia da semana o mes comeca
    if(mes == 1){
        mes = 13;
        ano--;
    }
    if(mes == 2){
        mes = 14;
        ano--;
    }
    int k = 1 + 2*mes + ((3*(mes+1))/5)+ano+(ano/4)-(ano/100)+(ano/400)+2;

    int diaSemana = k % 7;
    
    return diaSemana;
}

double defineTipo(int dia, int mes, int ano){

    int inicio = defineInicio(mes,ano);


    int tipoMes = descobreMes(mes,ano);


    double tipo = 1;


    if((inicio == 6 || inicio == 0)&&((mes != 2))){
        if(inicio==0 && mes%2==0){

            tipo = 1.68;

            return tipo;

        }else if((inicio == 6 || inicio == 0)&&(tipoMes == 0)){
            tipo = 1.68;

            return tipo;

        }
        
    }else if((inicio == 6 || inicio == 0)&&(tipoMes == 1)){
        tipo = 1;

        return tipo;

    }else if(mes == 2 && inicio == 1 && !checaAno(ano)){

        tipo = 0;

        return tipo;

    }
}



int descobreMes(int mes,int ano){
    if(mes == 2){
        if(checaAno(ano)){
            return 2;
        }else{
            return 3;
        }
    }else if(mes%2!=0 && mes <= 7){
        return 0;
    }else if(mes%2==0 && mes <= 7){
        return 1;
    }else if(mes%2==0 && mes > 7){
        return 0;
    }else if(mes%2!=0 && mes > 7){
        return 1;
    }
}

void desenhaProximoMes(struct pdf_doc *pdf,int lingua, int tipo, int mes, int ano){
    char semana[14][3] = {{"D"},{"S"},{"T"},{"Q"},{"Q"},{"S"},{"S"},
                          {"S"},{"M"},{"T"},{"W"},{"T"},{"F"},{"S"}};
    int mesAux = mes+1;
    int anoAux = ano;
    if(mes == 12){
        mesAux = 1;
        anoAux = ano+1; 
    }
    
       for(int i = 0; i < 7; i++){
            if(i==0+(7*lingua)||i==6+(7*lingua)) {pdf_add_text(pdf,NULL,semana[i],7,713+(i*18),560,PDF_RED);
            }else{pdf_add_text(pdf,NULL,semana[i],7,713+(i*18),560,PDF_BLACK);}
        }

   

    defineTipo(1,mesAux,anoAux);
    imprimeMesAno(pdf,mesAux,anoAux,lingua,10,745,570);
    imprimeDias(pdf,tipo,mesAux,ano,18,32,8,710,550);
}

void imporimeEventos(struct pdf_doc* pdf,FILE *f,int mes, int ano){  
    
    //int tipoEvento,int tipoCalendario,int inicio,int dia
    char tipo;
    int diaArq;
    int mesArq;
    int anoArq;
    char descricao[26];
    int quantidadeEventos = 0;

    int inicio = defineInicio(mes,ano);
    
    double tipoCalendario = defineTipo(1,mes,ano);
    char tiposEntram[100];
    int diasEntram[100];
    int mesesEntram[100];
    int anosEntram[100];
    char descricoesEntram[100][26];
    int copia = 0;

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

    int aux = 0; 
    int x1;
    int y1;
    


    for(int i = 0; i < descobreDias(mes,ano); i++){


        int inseriu = 0;

        for(int j = 0; j < quantidadeEventos; j++){
            x1 = 30 +((inicio) * 117) - (117 * aux * 6) + (117 * (i-aux-1));
            y1 = 450 - (aux*110) + (22*tipoCalendario*aux);
           
            if(diasEntram[j] == 1+i || diasEntram[j] == 0){
                if(tiposEntram[j]=='A'){
                    pdf_add_circle(pdf,NULL,x1,y1-(15*inseriu),5,0,PDF_RED,PDF_RED);
                    pdf_add_text(pdf,NULL,descricoesEntram[j],10, x1 + 10,y1-(1)-(15*inseriu),PDF_RED);    
                }else if(tiposEntram[j]=='V'){
                    pdf_add_circle(pdf,NULL,x1,y1-(15*inseriu),5,0,PDF_BLUE,PDF_BLUE);
                    pdf_add_text(pdf,NULL,descricoesEntram[j],10, x1 + 10,y1-(1)-(15*inseriu),PDF_BLUE);    
                }else if(tiposEntram[j]=='F'){
                    pdf_add_circle(pdf,NULL,x1,y1-(15*inseriu),5,0,PDF_BLACK,PDF_BLACK);
                    pdf_add_text(pdf,NULL,descricoesEntram[j],10, x1 + 10,y1-(1)-(15*inseriu),PDF_BLACK);    
                }else{
                    pdf_add_text(pdf,NULL,descricoesEntram[j],10, x1,y1-(1)-(15*inseriu),PDF_BLACK);
                }
                
                inseriu++;

            }

        }

        if(((i+inicio)%7)==0){
            aux++;
        }

    }
     

}

