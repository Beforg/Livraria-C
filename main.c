#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LIVROS 100
#define NOME_ARQUIVO_LIVROS "LivrosLocadora.csv"
#define NOME_ARQUIVO_LOCACOES "Locacoes.txt"
#define MAX_LOCACOES 150
#define MAX_LIVROS_POR_LOCACAO 10

typedef struct {
    int codigo;
    char titulo[100];
    char autor[50];
    int ano;
    char editora[50];
    int paginas;
    char genero[50];
    float valorAluguel;
} Livro;

typedef struct {
    char nomeCliente[100];
    char dataLocacao[11];
    Livro *livro;
} Locacao;

int carregarLivros(Livro livros[]) {
    FILE *file;
    char linha[256];
    int count = 0;

    file = fopen(NOME_ARQUIVO_LIVROS, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de livros");
        return -1;
    }


    fgets(linha, sizeof(linha), file);

    while (count < MAX_LIVROS && fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "%d;%99[^;];%49[^;];%d;%49[^;];%d;%49[^;];%f",
               &livros[count].codigo,
               livros[count].titulo,
               livros[count].autor,
               &livros[count].ano,
               livros[count].editora,
               &livros[count].paginas,
               livros[count].genero,
               &livros[count].valorAluguel);
        count++;
    }

    fclose(file);
    return count;
}

Livro *buscarLivroPorCodigo(int codigo, Livro livros[], int totalLivros) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].codigo == codigo) {
            return &livros[i];
        }
    }
    return NULL;
}

// int adicionarDataRelatorio() {
// 	FILE *file;
// 	file = fopen(NOME_ARQUIVO_LOCACOES,"a");
// 	if (file == NULL) {
// 		perror("Erro ao abrir o arquivo de locacoes");
// 		return -1;
// 	}
// 	char dataFormatada[50];
// 	time_t leituraAtual = time(NULL);
// 	struct tm *infoTempo = localtime(&leituraAtual);
// 	strftime(dataFormatada, 50, "%c", infoTempo);
// 	fprintf(file, "Data de Leitura: %s\n", dataFormatada);
// 	fclose(file);
// 	return 0;
// }

void pesquisarLivros(Livro livros[], int totalLivros) {
    char termoBusca[100];
    int encontrados = 0;

    printf("\n--- Pesquisar Livro ---\n");
    printf("Digite parte do titulo: ");
    scanf(" %[^\n]", termoBusca);
    printf("\nResultados da busca para '%s':\n", termoBusca);
    for (int i = 0; i < totalLivros; i++) {
        if (strstr(livros[i].titulo, termoBusca) != NULL) {
            printf("--------------------------------\n");
            printf("Codigo: %d\nTitulo: %s\nAutor: %s\nValor: R$%.2f\n",
                   livros[i].codigo, livros[i].titulo, livros[i].autor, livros[i].valorAluguel);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum livro encontrado com este titulo.\n");
    }
    printf("--------------------------------\n");
}


int validarCodigoLivro(int codigo, Livro livros[], int totalLivros) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].codigo == codigo) {
            printf("Livro com codigo %d ja existe!\n", codigo);
            return 1;
        }
    }
    return 0;
}

void adicionarLivro(Livro livros[], int *totalLivros) {
    FILE *file;
    Livro novoLivro;

    if (*totalLivros >= MAX_LIVROS) {
        printf("Limite de livros atingido. Nao e possivel adicionar mais livros.\n");
        return;
    }



    printf("=== ADICIONAR LIVRO ===\n");
    printf("Digite o codigo do livro: ");
    scanf("%d", &novoLivro.codigo);

    if (validarCodigoLivro(novoLivro.codigo, livros, *totalLivros)) {
        fclose(file);
        return;
    }
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]", novoLivro.titulo);
    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", novoLivro.autor);
    printf("Digite o ano de publicacao: ");
    scanf("%d", &novoLivro.ano);
    printf("Digite a editora do livro: ");
    scanf(" %[^\n]", novoLivro.editora);
    printf("Digite o numero de paginas: ");
    scanf("%d", &novoLivro.paginas);
    printf("Digite o genero do livro: ");
    scanf(" %[^\n]", novoLivro.genero);
    printf("Digite o valor do aluguel: ");
    scanf("%f", &novoLivro.valorAluguel);

    livros[*totalLivros] = novoLivro;
    (*totalLivros)++;
    // file = fopen(NOME_ARQUIVO_LIVROS, "a");
    //
    // if (file == NULL) {
    //     perror("Erro ao abrir o arquivo de livros");
    //     return;
    // }
    // fprintf(file, "\n%d;%s;%s;%d;%s;%d;%s;%.2f\n",
    //         novoLivro.codigo,
    //         novoLivro.titulo,
    //         novoLivro.autor,
    //         novoLivro.ano,
    //         novoLivro.editora,
    //         novoLivro.paginas,
    //         novoLivro.genero,
    //         novoLivro.valorAluguel);
    // fclose(file);
    printf("Livro '%s' adicionado com sucesso!\n", novoLivro.titulo);

}

int compararLivrosPorCodigo(const void *a, const void *b) {
    Livro *livroA = (Livro *) a;
    Livro *livroB = (Livro *) b;

    return livroA->codigo - livroB->codigo;
}

void salvarAlteracoesNoArquivo(Livro livros[], int totalLivros) {
    FILE *file;

    file = fopen(NOME_ARQUIVO_LIVROS, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de livros!");
        return;
    }

    fprintf(file, "ID;Título;Autor(a);Ano;Editora;Páginas;Gênero;Valor de Aluguel (R$)");
    qsort(livros, totalLivros, sizeof(Livro), compararLivrosPorCodigo);
    for (int i = 0; i < totalLivros; i++) {
        fprintf(file, "\n%d;%s;%s;%d;%s;%d;%s;%.2f",
                livros[i].codigo,
                livros[i].titulo,
                livros[i].autor,
                livros[i].ano,
                livros[i].editora,
                livros[i].paginas,
                livros[i].genero,
                livros[i].valorAluguel);
    }

    fclose(file);
    printf("Alteracoes salvas com sucesso no arquivo '%s'.\n", NOME_ARQUIVO_LIVROS);
}

void editarLivro(Livro livros[], int totalLivros) {
    int codigo;
    Livro *livroParaEditar;

    printf("\n--- Editar Livro ---\n");
    printf("Digite o codigo do livro a ser editado: ");
    scanf("%d", &codigo);

    livroParaEditar = buscarLivroPorCodigo(codigo, livros, totalLivros);

    if (livroParaEditar == NULL) {
        printf("Livro com codigo %d nao encontrado!\n", codigo);
        return;
    }

    printf("Digite o novo titulo do livro: ");
    scanf(" %[^\n]", livroParaEditar->titulo);
    printf("Digite o novo autor do livro: ");
    scanf(" %[^\n]", livroParaEditar->autor);
    printf("Digite o novo ano de publicacao: ");
    scanf("%d", &livroParaEditar->ano);
    printf("Digite a nova editora do livro: ");
    scanf(" %[^\n]", livroParaEditar->editora);
    printf("Digite o novo numero de paginas: ");
    scanf("%d", &livroParaEditar->paginas);
    printf("Digite o novo genero do livro: ");
    scanf(" %[^\n]", livroParaEditar->genero);
    printf("Digite o novo valor do aluguel: ");
    scanf("%f", &livroParaEditar->valorAluguel);

    // FILE *file = fopen(NOME_ARQUIVO_LIVROS, "w");
    // if (file == NULL) {
    //     perror("Erro ao abrir o arquivo de livros para edicao");
    //     return;
    // }
    //
    // for (int i = 0; i < totalLivros; i++) {
    //     fprintf(file, "%d;%s;%s;%d;%s;%d;%s;%.2f\n",
    //             livros[i].codigo,
    //             livros[i].titulo,
    //             livros[i].autor,
    //             livros[i].ano,
    //             livros[i].editora,
    //             livros[i].paginas,
    //             livros[i].genero,
    //             livros[i].valorAluguel);
    // }
    //
    // fclose(file);

    printf("Livro '%s' editado com sucesso!\n", livroParaEditar->titulo);
}

// Função necessaria que diz ao qsort como comparar os livros
// Recebe dois ponteiros genẽ́ricos, e devemos dizer o que cada um representa
// Segue a lógica de comparação, retornando um valor negativo, zero ou positivo
int compararLivros(const void *a, const void *b) {
    Livro *livroA = (Livro *) a;
    Livro *livroB = (Livro *) b;

    return strcmp(livroA->titulo, livroB->titulo);
}

void exibirTodosLivros(Livro livros[], int totalLivros) {
    qsort(livros, totalLivros, sizeof(Livro), compararLivros);
    printf("=== LIVROS DISPONIVEIS ===\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("--------------------------------\n");
        printf("Codigo: %d\nTitulo: %s\nAutor: %s\nAno: %d\nEditora: %s\nPaginas: %d\nGenero: %s\nValor Aluguel: R$%.2f\n",
               livros[i].codigo, livros[i].titulo, livros[i].autor, livros[i].ano,
               livros[i].editora, livros[i].paginas, livros[i].genero, livros[i].valorAluguel);
    }
}

void alugarLivro(Livro livros[], int totalLivros) {
    char nomeCliente[100];
    int codigoDesejado;
    Livro *livroParaAlugar;
    FILE *arquivoLocacoes;

    printf("\n--- Alugar Livro ---\n");
    printf("Digite o seu nome: ");
    scanf(" %[^\n]", nomeCliente);

    printf("Digite o codigo do livro desejado: ");
    scanf("%d", &codigoDesejado);

    livroParaAlugar = buscarLivroPorCodigo(codigoDesejado, livros, totalLivros);

    if (livroParaAlugar == NULL) {
        printf("\nERRO: Livro com codigo %d nao encontrado!\n", codigoDesejado);
        return;
    }

    arquivoLocacoes = fopen(NOME_ARQUIVO_LOCACOES, "a");
    if (arquivoLocacoes == NULL) {
        perror("Nao foi possivel registrar a locacao");
        return;
    }


    char dataFormatada[11];
    time_t tempoAtual = time(NULL);
    struct tm *infoTempo = localtime(&tempoAtual);
    strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", infoTempo);


    fprintf(arquivoLocacoes, "%s;%s;%d;%s;%.2f\n",
            nomeCliente,
            dataFormatada,
            livroParaAlugar->codigo,
            livroParaAlugar->titulo,
            livroParaAlugar->valorAluguel);

    fclose(arquivoLocacoes);

    printf("\n--------------------------------\n");
    printf("Livro '%s' alugado com sucesso para %s!\n", livroParaAlugar->titulo, nomeCliente);
    printf("Registro salvo em %s.\n", NOME_ARQUIVO_LOCACOES);
    printf("--------------------------------\n");

}

int carregarLocacoes(Locacao locacoes[], Livro livros[], int totalLivros) {
    FILE *file;
    char linha[256];
    int count = 0, tmpCodigo;
    file = fopen(NOME_ARQUIVO_LOCACOES, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de locacoes");
        return -1;
    }

    while (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "%99[^;];%10[^;];%d;%*[^;];%*f",
               locacoes[count].nomeCliente,
               locacoes[count].dataLocacao,
               &tmpCodigo);
        locacoes[count].livro = buscarLivroPorCodigo(tmpCodigo, livros, totalLivros);
        count++;
    }
    fclose(file);
    printf("%d locacoes carregadas com sucesso!\n", count);
    return count;
}

void pesquisarLocacao(Locacao locacoes[], int totalLocacoes) {
    printf("--- Pesquisar ---\n");
    printf("Informe o nome do cliente: ");
    char nomeCliente[100];
    scanf(" %[^\n]", nomeCliente);
    int encontrado = 0;
    float valorTotal = 0.0;
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(nomeCliente, locacoes[i].nomeCliente) == 0) {
            if (encontrado == 0) {
                printf("\n--- Locacoes para o cliente: %s ---\n", nomeCliente);
            }
            encontrado++;
            valorTotal += locacoes[i].livro->valorAluguel;
            printf("Livro: %s (Data: %s, Valor: R$%.2f)\n",
            locacoes[i].livro->titulo,
            locacoes[i].dataLocacao,
            locacoes[i].livro->valorAluguel);
        }
    }
    if (encontrado == 0) {
        printf("Nenhuma locacao encontrada para o cliente '%s'.\n", nomeCliente);
    } else {
        printf("\n--- Resultados da pesquisa ---\n");
        printf("Cliente: %s - Total de locacoes: %d\n", nomeCliente, encontrado);
        printf("Valor total das locacoes: R$%.2f\n", valorTotal);
    }
}

void relatorioLocacoes(Locacao locacoes[], int totalLocacoes) {
    float valorTotal = 0.0;
    printf("--- Locacoes ---\n");
    for (int i = 0; i < totalLocacoes; i++) {
        printf("Cliente: %s\n", locacoes[i].nomeCliente);
        printf("Data de Locacao: %s\n", locacoes[i].dataLocacao);
        if (locacoes[i].livro != NULL) {
            printf("Livro: %s (Codigo: %d)\n", locacoes[i].livro->titulo, locacoes[i].livro->codigo);
            printf("Valor do Aluguel: R$%.2f\n", locacoes[i].livro->valorAluguel);
            printf("");
            valorTotal += locacoes[i].livro->valorAluguel;
        } else {
            printf("Livro alterado ou não existente.\n");
        }
        printf("-------------------------------\n");
        printf("Valor total das locacoes: R$%.2f\n", valorTotal);
        printf("-------------------------------\n");
    }
}

int menuRelatorio() {
    int opcao;
    printf("=== RELATORIOS ===\n");
    printf("1. Exibir todas as locacoes\n");
    printf("2. Pesquisar locacao por cliente\n");
    printf("0. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;

}

void exibirRelatorio(Locacao locacoes[], int totalLocacoes) {
    int opcao;
    do {
        opcao = menuRelatorio();
        switch (opcao) {
            case 1:
                relatorioLocacoes(locacoes, totalLocacoes);
                break;
            case 2:
                pesquisarLocacao(locacoes, totalLocacoes);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

int menuGerenciarLivros() {
    int opcao;
    printf("-------------------------------\n");
    printf("=== GERENCIAR LIVROS ===\n");
    printf("1. Adicionar Livro\n");
    printf("2. Editar Livro\n");
    printf("3. Exibir Livros\n");
    printf("4. Salvar Alteracoes\n");
    printf("0. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

int exibirGerenciarLivros(Livro livros[], int *totalLivros) {
    int opcao;
    do {
        opcao = menuGerenciarLivros();
        switch (opcao) {
            case 1:
                adicionarLivro(livros, totalLivros);
                break;
            case 2:
                editarLivro(livros, *totalLivros);
                break;
            case 3:
                exibirTodosLivros(livros, *totalLivros);
                break;
            case 4:
                salvarAlteracoesNoArquivo(livros, *totalLivros);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
    return opcao;
}

int exibirMenu() {
    int opcao;
    printf("\n=== LOCADORA DIGITAL ===\n");
    printf("1. Pesquisar livro por titulo\n");
    printf("2. Alugar livro\n");
    printf("3. Relatorios\n");
    printf("4. Gerenciar Livros\n");
    printf("5. Sobre\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void sobre() {
    printf("Trabalho de Algoritmos EC11 2025/1");
}



int main() {
    Livro todosOsLivros[MAX_LIVROS];
    Locacao todasLocacoes[MAX_LOCACOES];
    int totalLivros;
    int totalLocacoes;
    int opcao;

    totalLivros = carregarLivros(todosOsLivros);
    totalLocacoes = carregarLocacoes(todasLocacoes, todosOsLivros, totalLivros);

    if (totalLivros <= 0) {
        printf("Nenhum livro carregado. Erro ao procurar '%s'. Encerrando.\n", NOME_ARQUIVO_LIVROS);
        return 1;
    }

    printf("%d livros carregados com sucesso!\n", totalLivros);

    do {
        opcao = exibirMenu();

        switch (opcao) {
            case 1:
                pesquisarLivros(todosOsLivros, totalLivros);
                break;
            case 2:
                alugarLivro(todosOsLivros, totalLivros);
                break;
            case 3:
                exibirRelatorio(todasLocacoes, totalLocacoes);
                break;
            case 4:
                exibirGerenciarLivros(todosOsLivros, &totalLivros);
                break;
            case 5:
                sobre();
                break;
            case 0:
                printf("Obrigado por utilizar o sistema!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
