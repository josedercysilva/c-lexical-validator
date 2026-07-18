# Validador Analítico de Cadeias e Sintaxe

> **Nota de Build:** A documentação original foi redigida em Markdown (`README.md`). A conversão estrutural para código-fonte LaTeX foi automatizada via `pandoc`, e a compilação final do PDF foi executada com o motor `tectonic`.

Este projeto implementa um motor de validação sintática. Ele recebe uma sequência de caracteres e verifica se todos os pares de abertura e fechamento estão perfeitamente balanceados, simulando a análise léxica de um compilador. 

A arquitetura foi dividida em três módulos independentes, focando em segurança de memória e responsabilidades isoladas.

## Arquitetura do Projeto

### 1. O Motor Principal (`valida_strings_simbolo.c`)
Este é o núcleo orquestrador do validador. Ele recebe um ponteiro para a `string` de teste (ou `NULL`) e varre a cadeia caractere por caractere.
* **Validação Estrita:** Se a cadeia contiver qualquer caractere que não pertença ao alfabeto previamente cadastrado, a execução é abortada e o sistema retorna o código de erro `-13`.
* **Sucesso:** Uma cadeia perfeitamente correspondente  é aprovada como válida, por exemplo`()(())`.

### 2. A Tabela de Regras (`alfabeto.c`)
Este módulo simula as regras de sintaxe da linguagem. Ele é alimentado por duas strings definidas na função `montar_tabelas`.
* **Mapeamento de Pares:** O sistema vincula as aberturas aos seus fechamentos correspondentes. Por exemplo, se a string de aberturas for `[ABC]` e a de fechamentos for `[CDE]`, o sistema mapeia os pares: `(A,C)`, `(B,D)` e `(C,E)`.
* **Motor de Decisão:** O código monta uma `struct` que atua como um Hash Map de tempo constante, respondendo a três perguntas essenciais para a lógica da Pilha:
  1. Este símbolo é uma abertura?
  2. Este símbolo é um fechamento?
  3. Sendo um fechamento, qual é a sua abertura exata?
* **Segurança:** O módulo possui funções utilitárias que impedem a execução caso as strings de abertura e fechamento tenham tamanhos assimétricos.

### 3. O Gerenciador de Estado (`pilha.c`)
Este módulo controla o histórico de aberturas lidas, implementando os métodos clássicos `empilhar`, `desempilhar` e `is_empty`.
* **Otimização de Memória:** Por simplicidade e segurança, a estrutura da pilha utiliza um Array contíguo. 
* **Alocação Inteligente:** A capacidade total da pilha é definida de forma dinâmica logo na inicialização. Ela recebe exatamente o tamanho da cadeia analisada na `main`, evitando tanto o desperdício de memória quanto o risco de estouro (*Buffer Overflow*).

---

##  Limitações e Comportamentos
A construção do alfabeto baseia-se na premissa de que as entradas farão sentido lógico. Algumas flexibilidades e ressalvas incluem:

* **Símbolos ASCII:** Todos os símbolos utilizados na montagem do alfabeto devem pertencer à tabela ASCII, limite de 1 byte. O uso de caracteres multibyte causará comportamento indefinido, pois o mapeamento é restrito a arrays de 256 posições.
* **Símbolos Customizados:** O motor é totalmente agnóstico. Você pode definir mapeamentos exóticos sem quebrar o algoritmo (ex: utilizar `@` como abertura e `%` como fechamento).
* **Interseção de Regras:** O algoritmo não verifica se um caractere foi inserido na lista de aberturas e de fechamentos simultaneamente. Definir o mesmo símbolo para ambas as funções (ex: abertura `[ABC]` e fechamento `[ABC]`) causará comportamento indefinido.


## Pares Usados por Padrão

Os pares previamente definidos no código são `(` e `)`, `[` e `]`, `{` e `}` além de `$` e `?`

Esse último par demonstra que os mapeamentos aceitam símbolos variados.

## Como Modificar os Pares

 1. Observe as regras da seção de Limitações e Comportamentos.

 2.Acesse a função `montar_tabelas` no arquivo `valida_strings_simbolo.c`.

 3. Altere o conteúdo das variáveis de aberturas e fechamentos.
