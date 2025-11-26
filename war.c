#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// ESTRUTURA DOS TERRISTÓRIOS
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};


// DECLARAÇÃO DAS FUNÇÕES
void cadastrar(struct Territorio *t);
void exibirMapa(struct Territorio *t);
void atacar(struct Territorio *atac, struct Territorio *def);
void pausar();
int contarTerritorios(struct Territorio *t, const char *cor);
void atribuirMissao(char *destino, char *missoes[], int total);
void exibirMissao(const char *missao, const char *corEscolhida);
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho, const char *corJogador);


// MAIN PARA A VERACIDADE DO QUE SERÁ DIGITADO
int main() {
    srand(time(NULL));

    int tamanho = 5;
    struct Territorio *t = malloc(tamanho * sizeof(struct Territorio));

    if (!t) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrar(t);

    // Declaração das Missões disponíveis
    char *missoes[] = {
        "Conquistar 3 territorios.",
        "Manter ao menos 4 territorios ao final de um turno.",
        "Eliminar completamente um exercito inimigo.",
        "Controlar o territorio com mais numeros de exercitos.",
        "Vencer 3 batalhas consecutivas."
    };
    int totalMissoes = 5;

    // MISSÃO DO JOGADOR (utilizando malloc)
    char *missaoJogador = malloc(100);
    char corEscolhida[10];

    // SORTEIO DE UM EXÉRCITO ALEATÓRIO PARA RECEBER A MISSÃO
    int indiceSorteado = rand() % tamanho;
    strcpy(corEscolhida, t[indiceSorteado].cor);

    // SORTEIO DA MISSÃO
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    // EXIBIÇÃO DO MAPA
    printf("\n============ MAPA-MÚNDI =============\n");
    exibirMapa(t);
    printf("=====================================\n\n");

    // EXIBIÇÃO DA MISSÃO
    exibirMissao(missaoJogador, corEscolhida);

    // LOOP DO MENU
    int opcao;
    int a, d;

    while (1) {

        printf("\n----- MENU DE ACOES -----\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar se a missão foi concluida\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            printf("\nEncerrando jogo...\n");
            break;
        }

        // ATAQUE + MAPA ATUAL + NEGAÇÃO DE ATAQUE A SI MESMO
        if (opcao == 1) {

            printf("\n=== MAPA ATUAL ===\n");
            exibirMapa(t);

            printf("\nEscolha território ATACANTE (1 a 5): ");
            scanf("%d", &a);

            printf("Escolha território DEFENSOR (1 a 5): ");
            scanf("%d", &d);

            a--; d--;

            if (a < 0 || a >= tamanho || d < 0 || d >= tamanho) {
                printf("Índice inválido!\n");
                continue;
            }
            if (a == d) {
                printf("Não pode atacar a si mesmo!\n");
                continue;
            }

            atacar(&t[a], &t[d]);
            pausar();
        }

        // VERIFICAÇÃO DA MISSÃO
        if (opcao == 2) {
            int completa = verificarMissao(missaoJogador, t, tamanho, corEscolhida);

            if (completa) {
                printf("\n====================================\n");
                printf(" PARABENS! O EXERCITO %s CUMPRIU A MISSAO!\n", corEscolhida);
                printf(" Missao: %s\n", missaoJogador);
                printf("====================================\n");
                break;
            } else {
                printf("\nSua missão AINDA não foi concluída. Continue lutando!\n");
            }
        }
    }

    // LIBERAÇÃO DA MEMÓRIA
    free(t);
    free(missaoJogador);

    printf("\nMemória liberada. Programa encerrado.\n");
    return 0;
}

// FUNÇÕES DO CADASTRO
void cadastrar(struct Territorio *t) {
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome: ");
        scanf("%s", t[i].nome);

        printf("Cor: ");
        scanf("%s", t[i].cor);

        printf("Tropas: ");
        scanf("%d", &t[i].tropas);
    }
}

void exibirMapa(struct Territorio *t) {
    for (int i = 0; i < 5; i++) {
        printf("[%d] %s (Exército %s, Tropas: %d)\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

// MATEMÁTICA E RESULTADO DOS ATAQUES
void atacar(struct Territorio *atac, struct Territorio *def) {

    printf("\n==== RESULTADO DO ATAQUE ====\n");

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("%s tirou %d | %s tirou %d\n", atac->nome, dadoA, def->nome, dadoD);

    int poderA = atac->tropas + dadoA;
    int poderD = def->tropas + dadoD;

    if (poderA > poderD) {
        printf("Atacante venceu!\n");
        def->tropas--;

        if (def->tropas <= 0) {
            printf("Território conquistado!\n");
            strcpy(def->cor, atac->cor);
            def->tropas = 1;
            atac->tropas--;
        }

    } else if (poderA < poderD) {
        printf("Defensor venceu!\n");
        atac->tropas--;
        if (atac->tropas < 1) atac->tropas = 1;

    } else {
        printf("Empate! Ambos perdem 1 tropa.\n");
        atac->tropas--;
        def->tropas--;

        if (atac->tropas < 1) atac->tropas = 1;
        if (def->tropas < 1) def->tropas = 1;
    }
}

// PAUSA NO PROGRAMA COM ENTER P/ CONTINUAR
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

// CONTE E ATUALIZAÇÃO DOS TERRITÓRIOS
int contarTerritorios(struct Territorio *t, const char *cor) {
    int count = 0;
    for (int i = 0; i < 5; i++)
        if (strcmp(t[i].cor, cor) == 0)
            count++;
    return count;
}

// FUNCIONAMENTO DAS MISSÕES 
void atribuirMissao(char *destino, char *missoes[], int total) {
    int r = rand() % total;
    strcpy(destino, missoes[r]);
}

void exibirMissao(const char *missao, const char *corEscolhida) {
    printf("\n---- SUA MISSAO (Exercito %s) ----\n", corEscolhida);
    printf(" -> %s\n", missao);
}

int verificarMissao(char *missao, struct Territorio *m, int tamanho, const char *corJogador) {

    // 1) Conquistar 3 territórios
    if (strcmp(missao, "Conquistar 3 territorios.") == 0) {
        return contarTerritorios(m, corJogador) >= 3;
    }

    // 2) Manter ao menos 4 territórios
    if (strcmp(missao, "Manter ao menos 4 territorios ao final de um turno.") == 0) {
        return contarTerritorios(m, corJogador) >= 4;
    }

    // 3) Eliminar completamente um exército inimigo
    if (strcmp(missao, "Eliminar completamente um exercito inimigo.") == 0) {

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(m[i].cor, corJogador) != 0) {
                int qtd = contarTerritorios(m, m[i].cor);
                if (qtd == 0) return 1;
            }
        }
        return 0;
    }

    // 4) Controlar o território com mais tropas
    if (strcmp(missao, "Controlar o territorio com mais numeros de exercitos.") == 0) {

        int maior = -1;
        char donoMaior[10];

        for (int i = 0; i < tamanho; i++) {
            if (m[i].tropas > maior) {
                maior = m[i].tropas;
                strcpy(donoMaior, m[i].cor);
            }
        }
        return strcmp(donoMaior, corJogador) == 0;
    }

    // 5) Vencer 3 batalhas consecutivas (se possui 3 ou mais conquistas)
    if (strcmp(missao, "Vencer 3 batalhas consecutivas.") == 0) {
        return contarTerritorios(m, corJogador) >= 4;
    }

    return 0;
}