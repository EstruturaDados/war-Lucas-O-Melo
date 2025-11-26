#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estrutura que representa e delimita os territóios do mapa
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//Declaração das Funções
void cadastrar(struct Territorio *t);
void exibirMapa(struct Territorio *t);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void pausar();
int contarTerritorios(struct Territorio *t, const char *cor);

int main() {
    srand(time(NULL));

    int tamanho = 5; //Usando malloc para a alocação dinâmica dos territórios
    struct Territorio *t = malloc(tamanho * sizeof(struct Territorio));
    
    //Verificação da alocação
    if (t == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    
    //Cadastro dos territórios
    cadastrar(t);

    // Loop principal, contendo toda dinâmica do jogo
    while (1) {
        int a, d;
        
        // Exibição do mapa atualizado
        printf("\n================================");
        printf("\n   MAPA MUNDI - ESTADO ATUAL\n");
        printf("================================\n\n");
        exibirMapa(t);

        printf("\n--- FASE DE ATAQUE ---");
        
        //Escolha do atacante
        printf("\nEscolha o número do território ATACANTE (ou 0 para sair): ");
        scanf("%d", &a);
        if (a == 0) break;// Se caso digitado 0, o jogo se encerra

        //Escolha do defensor
        printf("Escolha o número do território DEFENSOR (1 a 5): ");
        scanf("%d", &d);

        // Ajuste dos índixes para o vetor (usuário usa 1-5, vetor usa 0-4)
        a -= 1;
        d -= 1;
 
        //Verificação de índices válidos
        if (a < 0 || a >= tamanho || d < 0 || d >= tamanho) {
            printf("Indice invalido.\n");
            continue;
        }
        
        //Impede que o ataque seja feito no próprio território
        if (a == d) {
            printf("Nao pode atacar o mesmo territorio.\n");
            continue;
        }
        
        //Realiza o ataque sendo [a] o atacante e [d] o defensor
        atacar(&t[a], &t[d]);

        // Conta quantos territórios cada exército ainda possui
        int terrA = contarTerritorios(t, t[a].cor);
        int terrD = contarTerritorios(t, t[d].cor);
        
        //Derrota completa de um exercito Defensor
        if (terrD == 0) {
            printf("\n==============================\n");
            printf("O EXERCITO %s PERDEU TODOS SEUS TERRITÓRIOS!\n", t[d].cor);
            printf("VITORIA DO EXERCITO %s!!!\n", t[a].cor);
            printf("==============================\n");
            break;
        }
 
        //Derrota completa de um exercito Atacante
        if (terrA == 0) {
            printf("\n==============================\n");
            printf("O EXERCITO %s PERDEU TODOS OS TERRITORIOS!\n", t[a].cor);
            printf("VITORIA DO EXERCITO %s!!!\n", t[d].cor);
            printf("==============================\n");
            break;
        }
        
        //Aguarda o jogador continuar
        pausar();
    }
    
    //libera a memória alocada
    free(t);
    printf("\nMemoria liberada. Programa encerrado.\n");
    return 0;
}

//Função que cadatra os 5 territórios antes do jogo começar
void cadastrar(struct Territorio *t) {
    int i;
    for (i = 0; i < 5; i++) {
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
    int i;
    for (i = 0; i < 5; i++) {
        printf("[%d] %s (Exercito %s, Tropas: %d)\n",
                i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

//Função do ataque
void atacar(struct Territorio *atac, struct Territorio *def) {

    printf("\n====== RESULTADO DA BATALHA ======\n");

     // Rolagem dos dados
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("O Atacante %s rolou o dado e tirou: %d\n", atac->nome, dadoA);
    printf("O Defensor %s rolou o dado e tirou: %d\n", def->nome, dadoD);

    // Cálculo de poder total
    int poderA = atac->tropas + dadoA;
    int poderD = def->tropas + dadoD;

    //Se o atacante vencer
    if (poderA > poderD) {
        printf("\nVitória do Atacante!\n");
        printf("%s perdeu 1 tropa.\n", def->nome);

        def->tropas -= 1;
        if (def->tropas < 0) def->tropas = 0;

        if (def->tropas == 0) {
            printf("%s conquistou o território de %s!\n", atac->cor, def->nome);
            strcpy(def->cor, atac->cor);
            def->tropas = 1;
            atac->tropas -= 1;
        }

    //Se o defensor vencer    
    } else if (poderA < poderD) {
        printf("\nO Defensor resistiu ao ataque!\n");
        printf("%s perdeu 1 tropa.\n", atac->nome);

        atac->tropas -= 1;
        if (atac->tropas < 1) atac->tropas = 1;

    //Caso empate    
    } else {
        printf("\nEmpate!\n");
        printf("Ambos os territórios perderam 1 tropa.\n");

        atac->tropas -= 1;
        def->tropas -= 1;

        if (atac->tropas < 1) atac->tropas = 1;
        if (def->tropas < 1) def->tropas = 1;
    }
}

//Pausa o jogo e aguarda o ENTER 
void pausar() {
    printf("\nPressione ENTER para continuar para o próximo turno...");
    getchar();
    getchar();
}

// Conta quantos territórios pertencem a um exército
int contarTerritorios(struct Territorio *t, const char *cor) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(t[i].cor, cor) == 0) {
            count++;
        }
    }
    return count;
}