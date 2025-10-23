#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char pista[50]; // pista da sala, se houver
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma sala
Sala* criarSala(char nome[], char pista[], Sala* esquerda, Sala* direita) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = esquerda;
    novaSala->direita = direita;
    return novaSala;
}

typedef struct NoBST {
    char pista[50];
    struct NoBST *esquerda;
    struct NoBST *direita;
} NoBST;


NoBST* criarNoBST(char pista[]) {
    NoBST* novoNo = (NoBST*) malloc(sizeof(NoBST));
    strcpy(novoNo->pista, pista);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

NoBST* inserirBST(NoBST* raiz, char pista[]) {
    if (raiz == NULL) {
        return criarNoBST(pista);
    }
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirBST(raiz->direita, pista);
    }
    return raiz; // ignorar duplicatas
}

// Exibir pistas em ordem alfabética
void emOrdem(NoBST* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->direita);
    }
}

void explorarSalas(Sala* salaAtual, NoBST** pistas) {
    if (salaAtual == NULL) return;

    printf("\nVocê entrou na sala: %s\n", salaAtual->nome);

    if (strlen(salaAtual->pista) > 0) {
        printf("Você encontrou uma pista: %s\n", salaAtual->pista);
        *pistas = inserirBST(*pistas, salaAtual->pista);
    }

    printf("Escolha o próximo caminho: (e = esquerda, d = direita, s = sair): ");
    char escolha;
    scanf(" %c", &escolha);

    if (escolha == 'e') {
        explorarSalas(salaAtual->esquerda, pistas);
    } else if (escolha == 'd') {
        explorarSalas(salaAtual->direita, pistas);
    } else if (escolha == 's') {
        printf("Saindo da exploração...\n");
    } else {
        printf("Opção inválida. Tente novamente.\n");
        explorarSalas(salaAtual, pistas); // repetir
    }
}

int main() {

    Sala* sala3 = criarSala("Biblioteca", "Livro suspeito", NULL, NULL);
    Sala* sala4 = criarSala("Cozinha", "", NULL, NULL);
    Sala* sala2 = criarSala("Sala de Estar", "Chave misteriosa", sala3, sala4);
    Sala* sala5 = criarSala("Quarto", "Bilhete enigmático", NULL, NULL);
    Sala* hallEntrada = criarSala("Hall de Entrada", "", sala2, sala5);

    NoBST* pistas = NULL; // BST vazia

    printf("=== Bem-vindo ao Detective Quest (Nível Aventureiro) ===\n");
    explorarSalas(hallEntrada, &pistas);

    printf("\n=== Pistas encontradas em ordem alfabética ===\n");
    emOrdem(pistas);

    return 0;
}
