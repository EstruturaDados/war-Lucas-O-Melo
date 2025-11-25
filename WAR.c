#include <stdio.h>
#include <string.h>

struct Territorio{ char nome[30]; char cor[10]; int tropas; };

//Criando o vetor de Territorio e usando o for pata preencher os dados
int main() {
    struct Territorio t[5];
    int i;

    for (i = 0; i< 5; i++){
        printf("Digite o nome do territorio: ");
        scanf("%s", t[1].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", t[i].cor);

        printf("Digite o número de tropas: ");
        scanf("%d", &t[i].tropas);

        printf("\n");
    }


    
     
    
}