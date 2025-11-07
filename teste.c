#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 100
#define TAM_DESC 100
#define ARQ "tarefas.db"

typedef struct {
    int id;
    char descricao[TAM_DESC];
    int concluida;
} Tarefa;

Tarefa tarefas[MAX_TAREFAS];
int total = 0;

// ----------------------------
// Funções auxiliares
// ----------------------------

void salvarEmArquivo() {
    FILE *fp = fopen(ARQ, "wb");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }
    fwrite(&total, sizeof(int), 1, fp);
    fwrite(tarefas, sizeof(Tarefa), total, fp);
    fclose(fp);
}

void carregarDoArquivo() {
    FILE *fp = fopen(ARQ, "rb");
    if (!fp) return;

    fread(&total, sizeof(int), 1, fp);
    fread(tarefas, sizeof(Tarefa), total, fp);
    fclose(fp);
}

// ----------------------------
// Operações CRUD
// ----------------------------

void adicionarTarefa() {
    if (total >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }

    getchar();
    printf("Descrição da tarefa: ");
    fgets(tarefas[total].descricao, TAM_DESC, stdin);

    // Remover \n
    tarefas[total].descricao[strcspn(tarefas[total].descricao, "\n")] = 0;

    tarefas[total].id = total + 1;
    tarefas[total].concluida = 0;

    total++;
    salvarEmArquivo();
    printf("Tarefa adicionada!\n");
}

void listarTarefas() {
    printf("\n----- LISTA DE TAREFAS -----\n");
    if (total == 0) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("[%d] %s - %s\n",
               tarefas[i].id,
               tarefas[i].descricao,
               tarefas[i].concluida ? "Concluída" : "Pendente");
    }
}

void concluirTarefa() {
    int id;
    printf("ID da tarefa a concluir: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (tarefas[i].id == id) {
            tarefas[i].concluida = 1;
            salvarEmArquivo();
            printf("Tarefa marcada como concluída!\n");
            return;
        }
    }
    printf("Tarefa não encontrada.\n");
}

void removerTarefa() {
    int id;
    printf("ID da tarefa para remover: ");
    scanf("%d", &id);

    int pos = -1;
    for (int i = 0; i < total; i++) {
        if (tarefas[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    for (int i = pos; i < total - 1; i++) {
        tarefas[i] = tarefas[i + 1];
        tarefas[i].id = i + 1; // atualizar IDs
    }

    total--;
    salvarEmArquivo();
    printf("Tarefa removida com sucesso!\n");
}

// ----------------------------
// Menu
// ----------------------------

void exibirMenu() {
    printf("\n===== GERENCIADOR DE TAREFAS =====\n");
    printf("1 - Adicionar tarefa\n");
    printf("2 - Listar tarefas\n");
    printf("3 - Concluir tarefa\n");
    printf("4 - Remover tarefa\n");
    printf("5 - Sair\n");
    printf("Escolha: ");
}

int main() {
    carregarDoArquivo();

    int opcao;

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarTarefa();
                break;
            case 2:
                listarTarefas();
                break;
            case 3:
                concluirTarefa();
                break;
            case 4:
                removerTarefa();
                break;
            case 5:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}
