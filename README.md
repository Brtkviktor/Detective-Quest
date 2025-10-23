🕵️‍♂️ Detective Quest
Bem-vindo ao Detective Quest, um jogo educativo desenvolvido em linguagem C com o objetivo de explorar estruturas de dados avancadas de forma pratica e divertida.

O projeto e dividido em tres niveis de dificuldade: Novato, Aventureiro e Mestre.
Cada nivel introduz um novo conceito de estrutura de dados e aumenta a complexidade logica do programa.

🧩 Objetivo Geral
O jogador deve explorar uma mansao misteriosa, descobrindo pistas e suspeitos.
Cada nivel aprimora o sistema de exploracao, armazenamento e busca de informacoes, usando diferentes estruturas de dados:

🌲 Nivel Novato → Arvore binaria

🌳 Nivel Aventureiro → Arvore binaria de busca (BST)

🧮 Nivel Mestre → Tabela Hash integrada com BST

⚙️ Estrutura do Projeto
Copiar código
DetectiveQuest/
├── nivel_novato
├── nivel_aventureiro
├── nivel_mestre
└── README.md
💡 Nivel Novato – Arvore Binaria
Arquivo: nivel_novato.c

Neste nivel, voce aprende a criar e percorrer uma arvore binaria que representa o mapa da mansao.
O jogador inicia no Hall de Entrada e pode se mover entre as salas usando comandos simples.

🔧 Conceitos aplicados
Estrutura struct com ponteiros para a esquerda e direita.

Funcoes recursivas de exploracao.

Alocacao dinamica com malloc e free.

🎯 Objetivo
Percorrer a mansao ate encontrar uma sala folha (sem caminhos).

🧠 Nivel Aventureiro – BST (Arvore Binaria de Busca)
Arquivo: nivel_aventureiro.c

Neste nivel, alem do mapa da mansao, algumas salas escondem pistas.
Cada pista encontrada e inserida em uma BST (Binary Search Tree) e exibida em ordem alfabetica ao final.

🔧 Conceitos aplicados
Arvore Binaria de Busca (BST).

Insercao e percorrimento em ordem (InOrder).

Uso de ponteiros e alocacao dinamica.

Pistas encontradas serao automaticamente armazenadas na BST.

🎯 Objetivo
Coletar e listar todas as pistas encontradas em ordem alfabetica.

🔐 Nivel Mestre – Tabela Hash + BST
Arquivo: nivel_mestre.c

No nivel final, o jogador coleta pistas e descobre os suspeitos relacionados a cada uma.
Cada pista e associada a um suspeito usando uma tabela hash, enquanto as pistas continuam organizadas em uma BST.

🔧 Conceitos aplicados
Tabela Hash com encadeamento (colisao).

Funcoes hash simples e ponderada.

Integracao entre BST e Tabela Hash.

Busca rapida de informacoes (pista → suspeito).

Pistas encontradas serao automaticamente associadas a suspeitos.

Ao final, voce pode digitar o nome da pista para descobrir o suspeito correspondente:

text
Copiar código
> Pegadas de Lama
Suspeito associado: Suspeito A
🎯 Objetivo
Encontrar pistas e relaciona-las aos suspeitos corretos atraves da tabela hash.

🧮 Estruturas de Dados Implementadas
Nivel	Estrutura	Funcionalidade Principal
Novato	Arvore Binaria	Mapa da mansao
Aventureiro	BST (Arvore Binaria de Busca)	Armazenar pistas em ordem
Mestre	Tabela Hash + BST	Relacionar pistas e suspeitos

🧰 Tecnologias Utilizadas
Linguagem C (puro)

Compilador GCC

Estruturas de dados dinamicas

Programacao modular e documentada
