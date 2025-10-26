#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
//  Desafio Detective Quest
//  Tema 4 - Árvores e Tabela Hash
//  Nível Novato: Mapa da Mansão com Árvore Binária
// ============================================================================
//
//  Este programa simula o mapa de uma mansão misteriosa usando uma árvore binária.
//  Cada nó representa uma sala, e o jogador pode explorar escolhendo caminhos
//  à esquerda ou à direita. A exploração termina quando se chega a um nó folha.
//
//  Funções principais:
//  - criarSala(): cria dinamicamente uma sala.
//  - conectarSalas(): conecta as salas (filhos esquerdo e direito).
//  - explorarSalas(): permite a exploração interativa.
// ============================================================================

// ---------------------------------------------------------------------------
// Estrutura da sala (nó da árvore binária)
// ---------------------------------------------------------------------------
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ---------------------------------------------------------------------------
// Função: criarSala
// Cria uma nova sala dinamicamente e retorna seu ponteiro.
// ---------------------------------------------------------------------------
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ---------------------------------------------------------------------------
// Função: conectarSalas
// Conecta duas salas (à esquerda e à direita) à sala principal.
// ---------------------------------------------------------------------------
void conectarSalas(Sala *principal, Sala *esquerda, Sala *direita) {
    if (principal != NULL) {
        principal->esquerda = esquerda;
        principal->direita = direita;
    }
}

// ---------------------------------------------------------------------------
// Função: explorarSalas
// Permite a navegação interativa do jogador pela mansão.
// ---------------------------------------------------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na sala: 🏠 %s\n", atual->nome);

        // Caso a sala seja um nó folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("👉 Não há mais caminhos a seguir. Fim da exploração!\n");
            break;
        }

        printf("\nEscolha o caminho:\n");
        if (atual->esquerda != NULL) printf("  (e) Ir para a esquerda → %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("  (d) Ir para a direita → %s\n", atual->direita->nome);
        printf("  (s) Sair da exploração\n");
        printf("Opção: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("⚠️ Caminho à esquerda inexistente!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("⚠️ Caminho à direita inexistente!\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("🚪 Você decidiu sair da mansão. Até a próxima investigação!\n");
            break;
        } 
        else {
            printf("⚠️ Opção inválida! Tente novamente.\n");
        }
    }
}

// ---------------------------------------------------------------------------
// Função: liberarArvore
// Libera a memória alocada para todas as salas da mansão.
// ---------------------------------------------------------------------------
void liberarArvore(Sala *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// ---------------------------------------------------------------------------
// Função principal: main()
// Monta o mapa da mansão e inicia a exploração.
// ---------------------------------------------------------------------------
int main() {
    // Criação das salas principais
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *cozinha = criarSala("Cozinha");
    Sala *salaJantar = criarSala("Sala de Jantar");
    Sala *jardim = criarSala("Jardim");
    Sala *sotao = criarSala("Sótão");
    Sala *porao = criarSala("Porão");

    // Estrutura da mansão (árvore binária fixa)
    //
    //                    [Hall de Entrada]
    //                      /            \
    //            [Biblioteca]          [Cozinha]
    //              /      \             /      \
    //       [Sótão]   [Sala de Jantar] [Jardim] [Porão]

    conectarSalas(hall, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, salaJantar);
    conectarSalas(cozinha, jardim, porao);

    // Início da exploração
    printf("=============================================\n");
    printf("🕵️‍♀️  Bem-vindo(a) ao Detective Quest!\n");
    printf("Explore a mansão e descubra o mistério oculto.\n");
    printf("=============================================\n");

    explorarSalas(hall);

    // Libera a memória usada pela árvore
    liberarArvore(hall);

    printf("\n👋 Exploração encerrada. Obrigado por jogar!\n");
    return 0;
}
