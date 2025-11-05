#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ---------------- STRUCT ----------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ---------------- FUNÇÕES ----------------
void cadastrarComponentes(Componente c[], int *qtd);
void mostrarComponentes(Componente c[], int qtd);

// Ordenações
int bubbleSortNome(Componente c[], int qtd);
int insertionSortTipo(Componente c[], int qtd);
int selectionSortPrioridade(Componente c[], int qtd);

// Busca binária
int buscaBinariaPorNome(Componente c[], int qtd, char nome[]);

int main() {
    Componente componentes[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    char nomeBusca[30];

  

    do {
        printf("\n========================================\n");
        printf("             PLANO DE FUGA");
        printf("\n========================================\n");
        printf("\n");
        printf("Componentes cadastrados: %d/%d\n", qtd, MAX_COMPONENTES);
        printf("----------------------------------------\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Ordenar por NOME \n");
        printf("3 - Ordenar por TIPO \n");
        printf("4 - Ordenar por PRIORIDADE \n");
        printf("5 - Buscar componente-chave por NOME\n");
        printf("6 - Mostrar componentes cadastrados\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                cadastrarComponentes(componentes, &qtd);
                break;
            case 2:
                if (qtd == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                {
                    clock_t inicio = clock();
                    int comparacoes = bubbleSortNome(componentes, qtd);
                    clock_t fim = clock();
                    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                    printf("\nComponentes ordenados por NOME (Bubble Sort).\n");
                    printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                    mostrarComponentes(componentes, qtd);
                }
                break;
            case 3:
                if (qtd == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                {
                    clock_t inicio = clock();
                    int comparacoes = insertionSortTipo(componentes, qtd);
                    clock_t fim = clock();
                    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                    printf("\nComponentes ordenados por TIPO (Insertion Sort).\n");
                    printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                    mostrarComponentes(componentes, qtd);
                }
                break;
            case 4:
                if (qtd == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                {
                    clock_t inicio = clock();
                    int comparacoes = selectionSortPrioridade(componentes, qtd);
                    clock_t fim = clock();
                    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                    printf("\nComponentes ordenados por PRIORIDADE (Selection Sort).\n");
                    printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                    mostrarComponentes(componentes, qtd);
                }
                break;
            case 5:
                if (qtd == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                printf("\nDigite o nome do componente a buscar: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                bubbleSortNome(componentes, qtd); // garante ordenação por nome
                {
                    int pos = buscaBinariaPorNome(componentes, qtd, nomeBusca);
                    if (pos != -1)
                        printf("Componente encontrado: %s (%s) - Prioridade %d\n",
                               componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
                    else
                        printf("Componente nao encontrado.\n");
                }
                break;
            case 6:
                if (qtd == 0) printf("Nenhum componente cadastrado!\n");
                else mostrarComponentes(componentes, qtd);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ---------------- FUNÇÕES AUXILIARES ----------------

void cadastrarComponentes(Componente c[], int *qtd) {
    if (*qtd >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido!\n");
        return;
    }
    int continuar = 1;
    while (continuar && *qtd < MAX_COMPONENTES) {
        printf("\n--- Cadastro de Componente %d ---\n", *qtd + 1);
        printf("Nome: ");
        fgets(c[*qtd].nome, 30, stdin);
        c[*qtd].nome[strcspn(c[*qtd].nome, "\n")] = 0;
        printf("Tipo: ");
        fgets(c[*qtd].tipo, 20, stdin);
        c[*qtd].tipo[strcspn(c[*qtd].tipo, "\n")] = 0;
        printf("Prioridade (1-10): ");
        scanf("%d", &c[*qtd].prioridade);
        getchar();
        (*qtd)++;
        printf("Componente cadastrado com sucesso!\n");

        if (*qtd < MAX_COMPONENTES) {
            printf("Deseja cadastrar outro componente? (1=Sim / 0=Nao): ");
            scanf("%d", &continuar);
            getchar();
        } else {
            printf("Limite maximo atingido!\n");
            break;
        }
    }
}

void mostrarComponentes(Componente c[], int qtd) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%2d) Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, c[i].nome, c[i].tipo, c[i].prioridade);
    }
}

// ---------------- ALGORITMOS DE ORDENAÇÃO ----------------

int bubbleSortNome(Componente c[], int qtd) {
    int comparacoes = 0;
    Componente temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            comparacoes++;
            if (strcmp(c[j].nome, c[j + 1].nome) > 0) {
                temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

int insertionSortTipo(Componente c[], int qtd) {
    int comparacoes = 0;
    for (int i = 1; i < qtd; i++) {
        Componente atual = c[i];
        int j = i - 1;
        while (j >= 0 && strcmp(c[j].tipo, atual.tipo) > 0) {
            c[j + 1] = c[j];
            j--;
            comparacoes++;
        }
        c[j + 1] = atual;
    }
    return comparacoes;
}

int selectionSortPrioridade(Componente c[], int qtd) {
    int comparacoes = 0;
    for (int i = 0; i < qtd - 1; i++) {
        int min = i;
        for (int j = i + 1; j < qtd; j++) {
            comparacoes++;
            if (c[j].prioridade < c[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        }
    }
    return comparacoes;
}

// ---------------- BUSCA BINÁRIA ----------------

int buscaBinariaPorNome(Componente c[], int qtd, char nome[]) {
    int ini = 0, fim = qtd - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nome, c[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}