
-----

# 📚 Locadora Digital

Um sistema de gerenciamento para uma locadora de livros, desenvolvido em linguagem C. O projeto permite cadastrar, editar, pesquisar e alugar livros, além de gerar relatórios de locações. Todos os dados são persistidos em arquivos de texto (`.csv` / `.txt`).

-----

## Tabela de Conteúdos

- [Sobre o Projeto](https://www.google.com/search?q=%23sobre-o-projeto)
- [Funcionalidades](https://www.google.com/search?q=%23funcionalidades)
- [Estrutura dos Arquivos de Dados](https://www.google.com/search?q=%23estrutura-dos-arquivos-de-dados)
    - [LivrosLocadora.csv](https://www.google.com/search?q=%23livroslocadoracsv)
    - [Locacoes.txt](https://www.google.com/search?q=%23locacoestxt)
- [Como Compilar e Executar](https://www.google.com/search?q=%23como-compilar-e-executar)
- [Estrutura do Código](https://www.google.com/search?q=%23estrutura-do-c%C3%B3digo)
- [Autor](https://www.google.com/search?q=%23autor)

-----

## Sobre o Projeto

A **Locadora Digital** é um software de console (terminal) que simula as operações básicas de uma locadora de livros. Ele gerencia um catálogo de livros e um registro de todas as locações realizadas. O programa carrega os dados dos arquivos ao iniciar, permite que o usuário interaja com os dados em memória e, opcionalmente, pode salvar as alterações de volta no arquivo de catálogo.

As principais entidades do sistema são:

- **Livro**: Representa um livro no catálogo, com atributos como código, título, autor, ano, valor do aluguel, etc.
- **Locação**: Representa o aluguel de um livro por um cliente em uma determinada data.

-----

## Funcionalidades

O sistema oferece um menu interativo com as seguintes opções:

- **1. Pesquisar Livro por Título**:

    - Permite ao usuário digitar parte de um título e lista todos os livros que correspondem à busca.

- **2. Alugar Livro**:

    - Solicita o nome do cliente e o código do livro desejado.
    - Se o livro for encontrado, registra a locação no arquivo `Locacoes.txt` com a data atual.

- **3. Relatórios**:

    - **Exibir todas as locações**: Mostra um relatório detalhado de todas as locações registradas, incluindo cliente, data e informações do livro.
    - **Pesquisar locação por cliente**: Busca e agrupa todas as locações feitas por um cliente específico, calculando o valor total.

- **4. Gerenciar Livros**:

    - **Adicionar Livro**: Permite adicionar um novo livro ao catálogo (em memória), validando se o código já existe.
    - **Editar Livro**: Busca um livro pelo código e permite ao usuário alterar todas as suas informações.
    - **Exibir Livros**: Lista todos os livros do catálogo, ordenados alfabeticamente por título.
    - **Salvar Alterações**: Sobrescreve o arquivo `LivrosLocadora.csv` com os dados atuais do catálogo em memória (incluindo livros adicionados/editados), ordenando-os por código.

- **5. Sobre**:

    - Exibe informações sobre o projeto.

- **0. Sair**:

    - Encerra o programa.

-----

## Estrutura dos Arquivos de Dados

O programa utiliza dois arquivos para persistir os dados:

### `LivrosLocadora.csv`

Arquivo no formato CSV (Comma-Separated Values) utilizando ponto e vírgula (`;`) como delimitador. A primeira linha é um cabeçalho e é ignorada pelo programa ao carregar os dados.

**Formato:**
`ID;Título;Autor(a);Ano;Editora;Páginas;Gênero;Valor de Aluguel (R$)`

**Exemplo:**

```csv
ID;Título;Autor(a);Ano;Editora;Páginas;Gênero;Valor de Aluguel (R$)
20;O Pequeno Príncipe;Antoine de Saint-Exupéry;1943;Gallimard;96;Fábula;8.00
52;Cabra Cega;Raphael Montes;2019;Companhia das Letras;320;Suspense;19.00
```

### `Locacoes.txt`

Arquivo de texto simples onde cada linha representa o aluguel de um único livro, com campos separados por ponto e vírgula (`;`). Novas locações são adicionadas ao final do arquivo.

**Formato:**
`Nome do Cliente;Data do Aluguel;Código do Livro;Título do Livro;Valor do Aluguel`

**Exemplo:**

```txt
Maria;11/06/2025;34;Lolita;17.00
Maria;11/06/2025;33;O Sol é para Todos;14.00
Bruno Forgiarini;12/06/2025;20;O Pequeno Príncipe;8.00
```

-----

## Como Compilar e Executar

### Pré-requisitos

Para compilar e executar este projeto, você precisa de um compilador C, como o **GCC (GNU Compiler Collection)**.

### Passos

1.  **Clone o repositório ou baixe os arquivos** para um diretório em seu computador. Certifique-se de que os arquivos `LivrosLocadora.csv` e `Locacoes.txt` (mesmo que vazios) estejam no mesmo diretório que o código-fonte (`.c`).

2.  **Abra um terminal** ou prompt de comando no diretório do projeto.

3.  **Compile o código** usando o seguinte comando:

    ```bash
    gcc -o locadora_digital seu_arquivo_fonte.c -Wextra -Wall
    ```

    *Substitua `seu_arquivo_fonte.c` pelo nome do seu arquivo C.*

    * `-o locadora_digital` define o nome do programa executável.
    * `-Wextra -Wall` são flags recomendadas que ativam avisos extras do compilador, ajudando a encontrar possíveis erros.

4.  **Execute o programa:**

    ```bash
    ./locadora_digital
    ```

O menu interativo da locadora será exibido no terminal.

-----

## Estrutura do Código

O código é estruturado em várias funções modulares, cada uma com uma responsabilidade específica:

- `main()`: Ponto de entrada do programa. Carrega os dados, controla o loop do menu principal e gerencia as chamadas para outras funções.
- `carregarLivros()`: Responsável por ler o arquivo `LivrosLocadora.csv` e popular o array de `structs Livro`.
- `carregarLocacoes()`: Lê o arquivo `Locacoes.txt` e preenche o array de `structs Locacao`, vinculando cada locação a um livro do catálogo.
- `salvarAlteracoesNoArquivo()`: Sobrescreve o arquivo `LivrosLocadora.csv` com os dados do array de livros em memória.
- `adicionarLivro()`, `editarLivro()`: Funções para manipulação do catálogo de livros.
- `alugarLivro()`: Gerencia o processo de aluguel e salva o registro em `Locacoes.txt`.
- `buscarLivroPorCodigo()`: Uma função utilitária crucial que procura um livro em memória a partir de seu código.
- `comparar...()`: Funções de comparação passadas para a função `qsort` para ordenar os dados por diferentes critérios.
- `exibir...()`, `menu...()`: Funções responsáveis pela interface com o usuário (menus e exibição de dados).

-----

## Autor

**Bruno Forgiarini**

*Trabalho de Algoritmos EC11 2025/1*