# MEU DIÁRIO PARA ACOMPANHAMENTO

Comecei programando o seeker no dia de ontem, `dia 27-01-26`l... Até ontem tava tudo bem e nítido a ideia e o esquema do projeto...
Mas hoje, `dia 28-01-26` encontrei um bug que parecia pequeno, mas até em termos de imaginação se tornou um pesadelo... Vou explicar o problema:

Então eu tenho uma função que faz leitura de um arquivo e guarda todo o texto dentro de um ponteiro de ponteiros, até aqui tudo bem, certo? NÃO!!!!!!!

O erro começa no segundo loop quando tentamos reescrever o array de ponteiros char que já tem texto alocado do primeiro arquivo... Isso causa SegF

eu agora estou pensando em criar uma função que recorda ou aponta para o endereço do último espaço alocado e pula para o seguinte, assim a gente pode ao menos adicionar e não precisar reescrever toda vez o array
mas isso também não seria necessário porque estou apenas fazendo isso por questões de debug do código, a minha ideia é abrir um arquivo em cada loop para ir adicionando o conteudo em um arquivo apenas, e usar esse arquivo para gerar o relatório final de tudo!

Estou tão ansioso por esse Hackthon... é mais pela participação do que outra coisa... Enfim, terminei o relatório

Dia 28-01-27 - Diário terminado.
