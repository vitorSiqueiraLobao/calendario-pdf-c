# calendario-pdf-c
#############################################################################################################################################
                                copyright © 2019 all rights reserved - Vitor Siqueira Lobao UNIFEI-2018004809
#############################################################################################################################################

Programa implementado em c que cria um calendário em PDF
Para compilar basta usar o metodo de TAD.



O programa possui uma funcionalidade de adicionar eventos, para tal, precisa-se criar um documento .txt (o nome sera escolhido durante a execucao).Existem 3 tipos de eventos 
reconhecidos dentro do programa, Aniversarios, Viagens e Outro, para escoher o tipo, data e descricao deve-se seguir o seguinte padrao:

#############################################################################################################################################

TIPO (A-Aniversarios, V-Viagens, O-Outros) DATA (D/M/A - *) DESCRICAO (ate 25 caracteres)

Exemplo:

O 22 0 2019 Reunião de câmara
V 4 0 2019 São Paulo, SP
A 4 2 0 Zeca Pagodinho


*- se um evento vier a se repetir mais de uma vez, basta colar um 0 no lugar do dia/mes/ano entao o evento se repetira, no caso do exemplo acima, no aniversario coloca-se um 0 
no lugar do ano, assim todo ano no mes e dia da data o evento ira aparecer no calendario, isso tambem vale para mes e dia, se repetindo com intensidade dependente do escolhido

#############################################################################################################################################

O programa possui alguns erros decorrentes da biblioteca usadas, como no caso de apos imprimir o pdf do mes do calendario o buffer se enche e fica instavel, entao o calendario 
so pode ser impresso uma pagina por execucao, para facilitar o debug foi acrecentado uma funcionalidade de imprimir todos os eventos no terminal.

Por motivos desconhecidos e a serem pesquisados o programa se mostra instavel em IDEs, as funcionalidades funcionam bem , menos na hora de exportar o pdf, o problema requer mais 
porem no terminal o programa funciona bem.
