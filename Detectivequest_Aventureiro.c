#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura das salas
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala* criarSala(const char *nome, const char *pista) {
    Sala *s = (Sala*) malloc(sizeof(Sala));
    if (!s) { perror("malloc"); exit(EXIT_FAILURE); }
    strncpy(s->nome, nome, sizeof(s->nome)-1);
    s->nome[sizeof(s->nome)-1] = '\0';
    if (pista && pista[0] != '\0') {
        strncpy(s->pista, pista, sizeof(s->pista)-1);
        s->pista[sizeof(s->pista)-1] = '\0';
    } else {
        s->pista[0] = '\0';
    }
    s->esquerda = s->direita = NULL;
    return s;
}

void liberarSalas(Sala *r) {
    if (!r) return;
    liberarSalas(r->esquerda);
    liberarSalas(r->direita);
    free(r);
}

// BST de pistas
typedef struct PistaNode {
    char *texto;
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

char* minha_strdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
    memcpy(p, s, n);
    return p;
}

PistaNode* inserirPista(PistaNode *raiz, const char *texto) {
    if (!raiz) {
        PistaNode *n = (PistaNode*) malloc(sizeof(PistaNode));
        n->texto = minha_strdup(texto);
        n->esq = n->dir = NULL;
        return n;
    }
    int cmp = strcmp(texto, raiz->texto);
    if (cmp < 0) raiz->esq = inserirPista(raiz->esq, texto);
    else if (cmp > 0) raiz->dir = inserirPista(raiz->dir, texto);
    return raiz;
}

void emOrdemPistas(PistaNode *raiz) {
    if (!raiz) return;
    emOrdemPistas(raiz->esq);
    printf("- %s\n", raiz->texto);
    emOrdemPistas(raiz->dir);
}

void liberarPistas(PistaNode *raiz) {
    if (!raiz) return;
    liberarPistas(raiz->esq);
    liberarPistas(raiz->dir);
    free(raiz->texto);
    free(raiz);
}

// Exploracao com coleta de pistas
void explorarSalasComPistas(Sala *raizMapa, PistaNode **raizPistas) {
    Sala *atual = raizMapa;
    char opcao;
    printf("Exploracao iniciada - voce esta em: %s\n", atual->nome);

    while (1) {
        printf("\nSala atual: %s\n", atual->nome);
        if (atual->pista[0] != '\0') {
            printf("Voce encontrou uma pista: \"%s\"\n", atual->pista);
            *raizPistas = inserirPista(*raizPistas, atual->pista);
            atual->pista[0] = '\0';
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        printf("Escolhas: (e) esquerda");
        if (atual->direita) printf("  (d) direita");
        printf("  (s) sair\n");
        printf("Digite sua escolha: ");
        if (scanf(" %c", &opcao) != 1) break;

        if (opcao == 's') {
            printf("Encerrando exploracao...\n");
            break;
        } else if (opcao == 'e') {
            if (atual->esquerda) atual = atual->esquerda;
            else printf("Nao ha caminho para a esquerda.\n");
        } else if (opcao == 'd') {
            if (atual->direita) atual = atual->direita;
            else printf("Nao ha caminho para a direita.\n");
        } else {
            printf("Opcao invalida. Use 'e', 'd' ou 's'.\n");
        }

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVoce chegou a uma sala sem caminhos (no-folha): %s\n", atual->nome);
            if (atual->pista[0] != '\0') {
                printf("Voce encontrou uma pista: \"%s\"\n", atual->pista);
                *raizPistas = inserirPista(*raizPistas, atual->pista);
                atual->pista[0] = '\0';
            }
            break;
        }
    }
}

int main() {
    Sala *hall = criarSala("Hall de Entrada", "Pegadas de Lama");
    hall->esquerda = criarSala("Sala de Estar", "Lencol manchado");
    hall->direita  = criarSala("Biblioteca", "Livro com pagina faltando");
    hall->esquerda->esquerda = criarSala("Quarto", "");
    hall->esquerda->direita  = criarSala("Cozinha", "Chave perdida");
    hall->direita->esquerda  = criarSala("Estudo", "");
    hall->direita->direita   = criarSala("Jardim Interno", "Gaveta perdida");

    PistaNode *raizPistas = NULL;

    printf("=== Detective Quest (Nivel Aventureiro) ===\n");
    printf("Mapa com pistas criado. Explore e colete pistas automaticamente.\n\n");

    explorarSalasComPistas(hall, &raizPistas);

    printf("\n=== Pistas coletadas (em ordem alfabetica) ===\n");
    if (raizPistas == NULL) printf("Nenhuma pista coletada.\n");
    else emOrdemPistas(raizPistas);

    liberarPistas(raizPistas);
    liberarSalas(hall);
    return 0;
}