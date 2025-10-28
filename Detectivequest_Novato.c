#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// cria dinamicamente uma sala com o nome informado
Sala* criarSala(const char *nome) {
    Sala *novo = (Sala*) malloc(sizeof(Sala));
    if (!novo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->nome, nome, sizeof(novo->nome)-1);
    novo->nome[sizeof(novo->nome)-1] = '\0';
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// libera memoria da arvore (pos-ordem)
void liberarSalas(Sala *raiz) {
    if (!raiz) return;
    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

// explora salas interativamente a partir da raiz
// registra e imprime o caminho visitado
void explorarSalas(Sala *raiz) {
    if (!raiz) return;
    Sala *atual = raiz;
    char opcao;
    printf("Exploracao iniciada - voce esta em: %s\n", atual->nome);

    // buffer para registrar caminho (lista simples)
    char caminho[1000] = "";
    strncat(caminho, atual->nome, sizeof(caminho)-strlen(caminho)-1);

    while (1) {
        printf("\nSala atual: %s\n", atual->nome);
        printf("Escolhas: (e) esquerda");
        if (atual->direita) printf("  (d) direita");
        printf("  (s) sair\n");
        printf("Digite sua escolha: ");
        if (scanf(" %c", &opcao) != 1) break;

        if (opcao == 's') {
            printf("Encerrando exploracao...\n");
            break;
        } else if (opcao == 'e') {
            if (atual->esquerda) {
                atual = atual->esquerda;
                strncat(caminho, " -> ", sizeof(caminho)-strlen(caminho)-1);
                strncat(caminho, atual->nome, sizeof(caminho)-strlen(caminho)-1);
            } else {
                printf("Nao ha caminho para a esquerda.\n");
            }
        } else if (opcao == 'd') {
            if (atual->direita) {
                atual = atual->direita;
                strncat(caminho, " -> ", sizeof(caminho)-strlen(caminho)-1);
                strncat(caminho, atual->nome, sizeof(caminho)-strlen(caminho)-1);
            } else {
                printf("Nao ha caminho para a direita.\n");
            }
        } else {
            printf("Opcao invalida. Use 'e', 'd' ou 's'.\n");
        }

        // se chegou em folha (sem filhos) informa e encerra automaticamente
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVoce chegou a uma sala sem caminhos (no-folha): %s\n", atual->nome);
            break;
        }
    }

    printf("\nCaminho visitado: %s\n", caminho);
}

int main() {
    // Montagem manual do mapa da mansao (fixo)
    Sala *hall = criarSala("Hall de Entrada");

    hall->esquerda = criarSala("Sala de Estar");
    hall->direita  = criarSala("Biblioteca");

    hall->esquerda->esquerda = criarSala("Quarto");
    hall->esquerda->direita  = criarSala("Cozinha");
    hall->direita->esquerda  = criarSala("Estudo");
    hall->direita->direita   = criarSala("Jardim Interno");

    printf("=== Detective Quest (Nivel Novato) ===\n");
    printf("Mapa criado. Voce pode explorar a mansao a partir do Hall de Entrada.\n\n");

    explorarSalas(hall);

    liberarSalas(hall);
    return 0;
}