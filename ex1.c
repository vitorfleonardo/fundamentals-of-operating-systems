#include <stdio.h>
#include <stdlib.h>

typedef struct { int pid; int tempo_total_s; int tempo_restante_ms; } Processo;
typedef struct { int inicio; int fim; int tamanho; int capacidade; Processo* processos; } Fila;

Fila* criar_fila(int N) {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    if (!fila) return NULL;

    fila->capacidade = N;
    fila->processos = (Processo*) malloc(fila->capacidade * sizeof(Processo));
    if (!fila->processos) {
        free(fila);
        return NULL;
    }

    fila->tamanho = 0;
    fila->inicio = 0;
    fila->fim = -1; 

    return fila;
}

int eh_vazia(Fila* fila) {
    if (fila->tamanho == 0) return 1;
    return 0;
}

Processo* enfileirar(Fila* fila, Processo processo) {
    if (fila->tamanho == fila->capacidade) return NULL;

    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->processos[fila->fim] = processo;
    fila->tamanho++;

    return &fila->processos[fila->fim];
}

Processo* desenfileirar(Fila* fila) {
    if (eh_vazia(fila)) return NULL;

    Processo* processo = &fila->processos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;

    return processo;
}

int main() {
    // **************************************
    // 1. Entradas: armazenamento dos processos
    // **************************************

    int N, T;
    scanf("%d", &N);
    scanf("%d", &T);
    
    Processo processos[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &processos[i].pid, &processos[i].tempo_total_s);
        processos[i].tempo_restante_ms = processos[i].tempo_total_s * 1000;
    }

    // **************************************
    // 2. Processamento: escalonador round robin
    // **************************************

    Fila* fila_de_processos = criar_fila(N);
    int tempo_inicial = 0;

    for (int i = 0; i < N; i++) {
        enfileirar(fila_de_processos, processos[i]);
    }

    while(!eh_vazia(fila_de_processos)) {
        Processo* processo_atual = desenfileirar(fila_de_processos);
        if (processo_atual->tempo_restante_ms > T) {
            processo_atual->tempo_restante_ms -= T;
            tempo_inicial += T;
            enfileirar(fila_de_processos, *processo_atual);
        } else {
            tempo_inicial += processo_atual->tempo_restante_ms;
            processo_atual->tempo_restante_ms = 0;
            printf("%d (%d)\n", processo_atual->pid, tempo_inicial);
        }
    }

    free(fila_de_processos->processos); // liberar primeiro a memória do array interno de processos
    free(fila_de_processos); // depois liberar a memória da fila em si
    
    return 0;
}


    


