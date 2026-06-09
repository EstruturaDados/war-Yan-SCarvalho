#include <stdio.h>
#include <stdlib.h>

struct Territorio {
    char nome[50];
    char corExercito[30];
    int numTropas;
};

int main() {
    struct Territorio mapa[5];

    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("--- %d o Territorio ---\n", i + 1);
        
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do Exercito: ");
        scanf(" %[^\n]", mapa[i].corExercito);

        printf("Quantidade de Tropas: ");
        scanf("%d", &mapa[i].numTropas);
        
        printf("\n");
    }

    printf("=== ESTADO DO MAPA ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio: %s | Exercito: %s | Tropas: %d\n", 
               mapa[i].nome, 
               mapa[i].corExercito, 
               mapa[i].numTropas);
    }

    printf("\n");
    system("pause"); 
    return 0;
}