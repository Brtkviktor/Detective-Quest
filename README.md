# 🕵️ Detective Quest

**Descrição:**
Detective Quest é um projeto em linguagem C que combina estruturas de dados avançadas com uma narrativa investigativa.
O jogador explora uma mansão misteriosa, coleta pistas e tenta descobrir o culpado, enquanto o programa utiliza **árvores binárias**, **árvores de busca (BST)**, **Tries** e **tabelas hash** para gerenciar o progresso do jogo.

---

## 📁 Estrutura do Projeto

```
Detective_Quest/
│
├── src/
│   ├── main.c           # Função principal e controle do fluxo do jogo
│   ├── sala.c / sala.h  # Implementação da árvore binária (mapa da mansão)
│   ├── bst.c / bst.h    # Implementação da árvore binária de busca (pistas)
│   ├── trie.c / trie.h  # Implementação da Trie (normalização de palavras)
│   ├── hash.c / hash.h  # Implementação da tabela hash (pistas x suspeitos)
│   └── utils.c / utils.h# Funções auxiliares e manipulação de strings
│
├── Makefile             # Compilação automatizada
├── README.md            # Documentação principal do projeto
└── LICENSE              # Licença de uso (opcional)
```

---

## ⚙️ Requisitos

- Compilador compatível com **C99** ou superior (ex.: GCC ou Clang)
- Sistema operacional: Linux, macOS ou Windows (com MinGW/Cygwin)
- Make (opcional, para compilação automatizada)

---

## 🧩 Compilação e Execução

### Compilação manual:
```bash
gcc -std=c99 -Wall -Wextra src/*.c -o detective_quest
```

### Execução:
```bash
./detective_quest
```

### Usando Makefile:
```bash
make
./detective_quest
```

---

## 🎮 Níveis do Projeto

### 🥉 Nível Novato — Árvores Binárias

**Objetivo:**
Implementar o mapa da mansão usando uma **árvore binária**. Cada nó representa uma sala com uma pista.

**Funcionalidades:**
- Criar e exibir as salas da mansão.
- Permitir que o jogador explore à esquerda (E) ou à direita (D).
- Exibir o caminho percorrido.

**Estrutura básica:**
```c
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;
```

---

### 🥈 Nível Aventureiro — Árvores de Busca (BST)

**Objetivo:**
Utilizar uma **árvore binária de busca** para armazenar as pistas coletadas pelo jogador.

**Funcionalidades:**
- Inserir automaticamente as pistas encontradas em ordem alfabética.
- Exibir todas as pistas em **ordem crescente** no final da exploração.

**Funções principais:**
```c
BSTNode* inserirPista(BSTNode* raiz, char* pista);
void exibirEmOrdem(BSTNode* raiz);
```

---

### 🥇 Nível Mestre — Hash Table + Trie

**Objetivo:**
Integrar uma **tabela hash** que associa cada pista a um suspeito e uma **Trie** para normalizar e comparar palavras.

**Funcionalidades:**
- Normalizar palavras (sem acento, minúsculas, sem espaços).
- Associar pistas a suspeitos via hash.
- Permitir que o jogador acuse um suspeito.
- Validar se há pelo menos **duas pistas** ligando o suspeito ao crime.

**Funções principais:**
```c
void inserirNaHash(HashTable* h, char* pista, char* suspeito);
char* buscarSuspeito(HashTable* h, char* pista);
int verificarAcusacao(HashTable* h, BSTNode* pistas, char* acusado);
```

---

## 🧠 Conceitos Aplicados

- **Árvore Binária:** estrutura hierárquica usada para representar caminhos (salas).
- **BST:** garante armazenamento ordenado e rápido acesso às pistas.
- **Trie:** estrutura ideal para indexar e comparar palavras de forma eficiente.
- **Tabela Hash:** associa pistas a suspeitos com busca de tempo constante.

---

## 🧪 Boas Práticas

- Utilize `free()` para liberar toda a memória alocada dinamicamente.
- Evite variáveis globais; prefira passar ponteiros entre funções.
- Comente cada função explicando seu propósito e parâmetros.
- Valide entradas de usuário (ex.: opções inválidas durante a exploração).

---

## 🧾 Exemplo de Execução

```
=== Detective Quest ===
Você está na Sala Principal.
Deseja ir para (E) esquerda, (D) direita ou (S) sair? E

Você entrou na Biblioteca!
Pista encontrada: “Luvas sujas de tinta”.

Deseja continuar explorando? D
Você entrou no Jardim!
Pista encontrada: “Pegadas próximas à janela”.

Pistas coletadas:
- Luvas sujas de tinta
- Pegadas próximas à janela

Digite o nome do suspeito: Pintor
O suspeito Pintor foi acusado!
Verificando evidências...
Resultado: Culpado! As pistas confirmam sua culpa.
```

---

## 📘 Contribuição

1. Faça um fork do repositório.
2. Crie uma branch com o nome da feature:
   ```bash
   git checkout -b feature/nova-funcionalidade
   ```
3. Commit suas alterações com mensagens claras:
   ```bash
   git commit -m "Adiciona função de verificação de suspeito"
   ```
4. Envie sua branch:
   ```bash
   git push origin feature/nova-funcionalidade
   ```
5. Abra um Pull Request.

---
