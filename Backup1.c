#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Territorio{ char nome[30]; char cor[10]; int tropas; };

//Criando o vetor de Territorio e usando o for pata preencher os dados
int main() {
    struct Territorio t[5];
    int i;

    for (i = 0; i< 5; i++){

        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        printf("Digite o nome do Território: ");
        scanf("%s", t[i].nome);

        printf("Digite a cor do Exercito: ");
        scanf("%s", t[i].cor);

        printf("Digite o número de Tropas: ");
        scanf("%d", &t[i].tropas);

        printf("\n");
    }

    //Criando a exibição dos dados solicitados
    printf("\n=-=-=-= Territorios Cadastrados =-=-=-=\n\n");

    for (i= 0; i < 5; i++) {
        printf("Nome: %s\n", t[i].nome);
        printf("Cor: %s\n", t[i].cor);
        printf("Tropas: %d\n\n", t[i].tropas);
    }

    return 0;  
}