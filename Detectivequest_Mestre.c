#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 31
#define MAX_STR 128

// Estruturas principais

typedef struct Room {
    char name[MAX_STR];
    char clue[MAX_STR];
    struct Room *left;
    struct Room *right;
} Room;

typedef struct ClueNode {
    char clue[MAX_STR];
    struct ClueNode *left;
    struct ClueNode *right;
} ClueNode;

typedef struct HashNode {
    char clue[MAX_STR];
    char suspect[MAX_STR];
    struct HashNode *next;
} HashNode;

HashNode *hash_table[HASH_SIZE];

/* ================================================================
   TABELA HASH (pista -> suspeito)
   ================================================================ */

int hash_simple(const char *s) {
    long sum = 0;
    for (int i = 0; s[i]; i++) sum = (sum * 31 + (unsigned char)s[i]) % HASH_SIZE;
    return (int)sum;
}

void hash_insert(const char *clue, const char *suspect) {
    int idx = hash_simple(clue);
    HashNode *n = (HashNode*) malloc(sizeof(HashNode));
    strncpy(n->clue, clue, MAX_STR);
    strncpy(n->suspect, suspect, MAX_STR);
    n->next = hash_table[idx];
    hash_table[idx] = n;
}

const char* hash_find(const char *clue) {
    int idx = hash_simple(clue);
    HashNode *cur = hash_table[idx];
    while (cur) {
        if (strcmp(cur->clue, clue) == 0) return cur->suspect;
        cur = cur->next;
    }
    return NULL;
}

/* ================================================================
   BST DE PISTAS
   ================================================================ */

ClueNode* create_clue_node(const char *clue) {
    ClueNode *n = (ClueNode*) malloc(sizeof(ClueNode));
    strncpy(n->clue, clue, MAX_STR);
    n->left = n->right = NULL;
    return n;
}

ClueNode* insert_clue(ClueNode *root, const char *clue) {
    if (!root) return create_clue_node(clue);
    int cmp = strcmp(clue, root->clue);
    if (cmp < 0) root->left = insert_clue(root->left, clue);
    else if (cmp > 0) root->right = insert_clue(root->right, clue);
    return root;
}

void inorder_clues(ClueNode *root) {
    if (!root) return;
    inorder_clues(root->left);
    printf(" - %s\n", root->clue);
    inorder_clues(root->right);
}

int clue_collected(ClueNode *root, const char *clue) {
    if (!root) return 0;
    int cmp = strcmp(clue, root->clue);
    if (cmp == 0) return 1;
    if (cmp < 0) return clue_collected(root->left, clue);
    return clue_collected(root->right, clue);
}

/* ================================================================
   ARVORE DE SALAS (MANSÃO)
   ================================================================ */

Room* create_room(const char *name, const char *clue) {
    Room *r = (Room*) malloc(sizeof(Room));
    strncpy(r->name, name, MAX_STR);
    if (clue) strncpy(r->clue, clue, MAX_STR);
    else r->clue[0] = '\0';
    r->left = r->right = NULL;
    return r;
}

Room* build_mansion() {
    Room *hall = create_room("Hall de Entrada", "");
    Room *living = create_room("Sala de Estar", "Pegadas de lama");
    Room *kitchen = create_room("Cozinha", "Lencol manchado");
    Room *library = create_room("Biblioteca", "Livro com pagina faltando");
    Room *study = create_room("Escritorio", "");
    Room *bedroom = create_room("Quarto Principal", "Chave perdida");
    Room *garden = create_room("Jardim", "Gaveta perdida");

    // conexoes
    hall->left = living;
    hall->right = library;
    living->left = kitchen;
    living->right = study;
    kitchen->left = bedroom;
    library->right = garden;

    return hall;
}

/* ================================================================
   NOVOS COMANDOS
   ================================================================ */

// Mostra o mapa da mansao (estrutura fixa)
void show_map() {
    printf("\n=== MAPA DA MANSAO ===\n");
    printf("          [Hall de Entrada]\n");
    printf("             /         \\\n");
    printf("   [Sala de Estar]   [Biblioteca]\n");
    printf("       /     \\              \\\n");
    printf(" [Cozinha] [Escritorio]   [Jardim]\n");
    printf("     |\n");
    printf(" [Quarto Principal]\n");
    printf("=========================\n");
}

// Mostra o inventario atual do jogador
void show_inventory(ClueNode *collected) {
    printf("\n=== INVENTARIO DE PISTAS ===\n");
    if (!collected) {
        printf("Nenhuma pista coletada ainda.\n");
        return;
    }
    inorder_clues(collected);
    printf("=============================\n");
}

/* ================================================================
   EXPLORACAO
   ================================================================ */

void explore_rooms(Room *hall, ClueNode **collected) {
    Room *node = hall;
    char choice[8];

    while (1) {
        printf("\nVoce esta em: %s\n", node->name);

        // Coleta de pista
        if (node->clue[0] != '\0') {
            printf("Pista encontrada: %s\n", node->clue);
            if (!clue_collected(*collected, node->clue)) {
                *collected = insert_clue(*collected, node->clue);
                printf("-> Pista adicionada ao inventario.\n");
            } else {
                printf("-> Voce ja possui esta pista.\n");
            }
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        // Menu de opcoes
        printf("\nEscolha o proximo comando:\n");
        printf("(e) esquerda  (d) direita  (v) voltar ao hall\n");
        printf("(i) inventario  (m) mapa  (s) sair\n> ");
        if (!fgets(choice, sizeof(choice), stdin)) return;
        choice[strcspn(choice, "\n")] = '\0';

        // Processamento dos comandos
        if (strcmp(choice, "e") == 0) {
            if (node->left) node = node->left;
            else {
                printf("Caminho a esquerda nao existe.\n");
                printf("Deseja voltar para o Hall? (s/n): ");
                char opt[4];
                fgets(opt, sizeof(opt), stdin);
                if (opt[0] == 's' || opt[0] == 'S') node = hall;
            }
        } else if (strcmp(choice, "d") == 0) {
            if (node->right) node = node->right;
            else {
                printf("Caminho a direita nao existe.\n");
                printf("Deseja voltar para o Hall? (s/n): ");
                char opt[4];
                fgets(opt, sizeof(opt), stdin);
                if (opt[0] == 's' || opt[0] == 'S') node = hall;
            }
        } else if (strcmp(choice, "v") == 0) {
            printf("Voltando para o Hall de Entrada...\n");
            node = hall;
        } else if (strcmp(choice, "i") == 0) {
            show_inventory(*collected);
        } else if (strcmp(choice, "m") == 0) {
            show_map();
        } else if (strcmp(choice, "s") == 0) {
            printf("Encerrando exploracao...\n");
            break;
        } else {
            printf("Comando invalido.\n");
        }
    }
}

/* ================================================================
   VERIFICACAO FINAL
   ================================================================ */

int count_clues_pointing_to(ClueNode *root, const char *accused) {
    if (!root) return 0;
    int cnt = 0;
    const char *sus = hash_find(root->clue);
    if (sus && strcmp(sus, accused) == 0) cnt = 1;
    cnt += count_clues_pointing_to(root->left, accused);
    cnt += count_clues_pointing_to(root->right, accused);
    return cnt;
}

/* ================================================================
   PROGRAMA PRINCIPAL
   ================================================================ */

int main() {
    // inicializa tabela hash
    for (int i = 0; i < HASH_SIZE; i++) hash_table[i] = NULL;

    // constroi a mansao
    Room *hall = build_mansion();

    // associa pistas a suspeitos
    hash_insert("Pegadas de lama", "Suspeito A");
    hash_insert("Lencol manchado", "Suspeito B");
    hash_insert("Livro com pagina faltando", "Suspeito C");
    hash_insert("Chave perdida", "Suspeito A");
    hash_insert("Gaveta perdida", "Suspeito B");

    // BST das pistas coletadas
    ClueNode *collected = NULL;

    printf("=== DETECTIVE QUEST - NIVEL MESTRE ===\n");
    printf("Explore a mansao, colete pistas e acuse o culpado.\n");

    // exploracao principal
    explore_rooms(hall, &collected);

    // exibicao final
    printf("\nPistas coletadas:\n");
    if (collected) inorder_clues(collected);
    else printf("Nenhuma pista coletada.\n");

    // julgamento
    char accused[MAX_STR];
    printf("\nDigite o nome do suspeito que deseja acusar (ex: Suspeito A, B ou C):\n> ");
    if (!fgets(accused, sizeof(accused), stdin)) return 0;
    accused[strcspn(accused, "\n")] = '\0';

    int matches = count_clues_pointing_to(collected, accused);
    printf("\nPistas que apontam para %s: %d\n", accused, matches);

    if (matches >= 2)
        printf("Acusacao sustentada! %s e considerado(a) culpado(a).\n", accused);
    else
        printf("Acusacao nao sustentada. Evidencias insuficientes.\n");

    printf("\nFim da investigacao. Obrigado por jogar!\n");
    return 0;
}