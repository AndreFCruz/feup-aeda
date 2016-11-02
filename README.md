# StockMarket-AEDA
Stock Market (Part 1) - AEDA.

--Requisitos:

_Notas relativas à implementação (itens sujeitos a avaliação)
Deve utilizar classes adequadas para representação das entidades envolvidas. Os atributos devem ser escolhidos de forma a caracterizar os conceitos mais importantes das entidades a representar).
Deve utilizar o conceito de herança e polimorfismo onde considerar conveniente.
Os dados usados pela aplicação devem ser guardados em ficheiro, para utilização em futuras execuções.
Deve tratar convenientemente possíveis excepções.
Deve usar algoritmos de pesquisa e ordenação (por exemplo, nas múltiplas listagens solicitadas) 
As classes implementadas devem ser devidamente documentadas (usando Doxygen).

_Notas relativas à demonstração (itens sujeitos a avaliação)
Preparação adequada para demonstrar as funcionalidades do trabalho
Deve usar um número significativo de itens (dados).
Todos os elementos do grupo devem estar presentes

_Relatório (itens sujeitos a avaliação)
O relatório, a ser entregue em formato pdf, deve incluir:
Página de rosto com título do trabalho, identificação dos elementos do grupo (nome, código, email) e data
Descrição sucinta do tema do trabalho
Descrição da solução implementada
Diagramas UML do modelo de dados concebido (diagrama de classes, indicando para cada classe as suas relações, atributos e métodos)
Lista de Casos de Utilização identificados para a aplicação (não é necessário desenhar os diagramas de casos de utilização)
Relato das principais dificuldades encontradas no desenvolvimento do trabalho
Indicação do esforço dedicado por cada elemento do grupo

_Entrega
Disponibilizar em um ficheiro <NOME>.zip:
pasta codigo (contém código fonte do programa)
pasta documentacao (contém documentação html, criada pelo Doxygen)
ficheiro relatorio (documento em formato pdf)
O <NOME> do ficheiro deverá obedecer ao formato AEDA1617_<TURMA>_<GRUPO>, onde turma é o código da turma teórico/prática e <GRUPO> é uma letra que identifica o grupo, conforme indicado na atribuição de trabalhos. Por exemplo: AEDA1617_2MIEIC5_C.zip corresponde ao trabalho realizado pelo grupo C da turma 2MIEIC5

_Datas
Data de entrega: dia 18/novembro, até às 23h59m. Submeter pelo Moodle:
Relatório em pdf + Código do programa + documentação
Apresentação do trabalho:  de 21 a 24 de novembro, em horário a combinar com o docente das aulas práticas


--Descrição:

Num mercado de ações, os clientes podem colocar ordens de compra ou de venda. Uma ordem de compra inclui
a designação das ações (título) que quer comprar, o preço máximo por unidade e o valor máximo a gastar. Uma
ordem de venda inclui a designação das ações que quer vender, a quantidade que possui para venda (pode não
vender tudo numa transação) e o preço mínimo por unidade. A data em que uma ordem de compra ou venda é
colocada no mercado deve ficar registada.
A cada ordem de compra ou de venda está associado um cliente, identificado pelo seu nome e NIF.
O sistema a implementar efetua a gestão deste mercado de ações. Sempre que uma ação é colocada no
mercado, são verificadas as possíveis transações, isto é:
­ Se é colocada uma ordem de venda de valor mínimo por unidade = V, são verificadas as ordens de
compra existentes (de preço máximo por unidade = C) que a possam satisfazer (isto é, C > V), por
ordem de entrada no mercado. Considere que o preço efetivo da transação é a média de V e C. Pode
otimizar este processo, escolhendo as ordens de compra de maior valor C, tal que C > V.
­ Se é colocada uma ordem de compra de valor máximo por unidade = V, são verificadas as ordens de
venda existentes (de preço mínimo por unidade = V) que a possam satisfazer (isto é, V > C), por ordem
de entrada no mercado. Considere que o preço efetivo da transação é a média de V e C e são
compradas tantas ações quanto o valor máximo que o comprador está disposto a gastar.
O sistema deve registar todas as transações efetuadas pelo mercado.
Deve ser possível a consulta da atividade do mercado, transações efetuadas por clientes, transações efetuadas
por título e outras que considere relevantes.
