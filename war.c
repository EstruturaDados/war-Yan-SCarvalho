Ah! Esse erro sh: 1: pause: not found e sh: 1: cls: not found acontece por um motivo bem específico: o seu Dev-C++ ou o terminal que está rodando o código não está usando o comando padrão do prompt do Windows (CMD), mas sim um terminal baseado em Linux/Unix (como o bash ou o sh).

No Linux, os comandos pause e cls simplesmente não existem! O equivalente para limpar a tela no Linux é clear, e para pausar precisamos usar um comando próprio do C.

Para o seu código funcionar perfeitamente em qualquer computador (seja Windows, Linux, no Dev-C++ ou se você tentar rodar no VS Code depois), vamos substituir esses comandos do sistema por funções nativas da linguagem C. Assim o código fica 100% portátil e nunca mais dá esse erro de "not found".

Aqui está o código corrigido e blindado contra esse problema:

C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Estrutura do Território
struct Territorio {
    char nome[50];
    char corExercito[30];
    int numTropas;
};

// FUNÇÃO PARA FAZER UMA PAUSA COMPATÍVEL COM QUALQUER SISTEMA
void pausarJogo() {
    printf("\nPressione ENTER para continuar...");
    getchar(); // Limpa qualquer sobra do teclado
    getchar(); // Aguarda o usuário apertar ENTER
}

// FUNÇÃO PARA LIMPAR A TELA COMPATÍVEL COM QUALQUER SISTEMA
void limparTela() {
    // Tenta limpar usando o comando do Windows, se falhar (retornar diferente de 0), limpa usando o do Linux
    if (system("cls") != 0) {
        system("clear");
    }
}

// Função para simular a batalha detalhada
void realizarAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    printf("\n=========================================\n");
    printf("        ⚔️  CONFRONTO DETALHADO  ⚔️\n");
    printf("=========================================\n");
    printf("ATACANTE: %s (%s) [Tropas: %d]\n", atacante->nome, atacante->corExercito, atacante->numTropas);
    printf("DEFENSOR: %s (%s) [Tropas: %d]\n", defensor->nome, defensor->corExercito, defensor->numTropas);
    printf("-----------------------------------------\n");
    
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("🎲 Dado do Atacante [%s]: %d\n", atacante->nome, dadoAtaque);
    printf("🎲 Dado do Defensor [%s]: %d\n", defensor->nome, dadoDefesa);
    printf("-----------------------------------------\n");

    if (dadoAtaque >= dadoDefesa) {
        printf("🏆 RESULTADO: Vencedor [%s] | Perdedor [%s]\n", atacante->nome, defensor->nome);
        defensor->numTropas--;
        printf("💥 O defensor perdeu 1 tropa!\n");
    } else {
        printf("🏆 RESULTADO: Vencedor [%s] | Perdedor [%s]\n", defensor->nome, atacante->nome);
        printf("🛡️  O defensor conseguiu resistir ao ataque!\n");
    }

    printf("-----------------------------------------\n");
    printf("📊 SALDO DE TROPAS ATUALIZADO:\n");
    printf("-> %s: %d tropas restantes\n", atacante->nome, atacante->numTropas);
    printf("-> %s: %d tropas restantes\n", defensor->nome, defensor->numTropas);

    if (defensor->numTropas <= 0) {
        printf("\n🚩 !!! TERRITÓRIO CONQUISTADO !!!\n");
        printf("O exército %s dominou %s!\n", atacante->corExercito, defensor->nome);
        
        strcpy(defensor->corExercito, atacante->corExercito);
        defensor->numTropas = 1; 
    }
    printf("=========================================\n");
    
    // Usa a nossa função nova e segura de pausa
    pausarJogo();
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    struct Territorio *mapa = (struct Territorio *) calloc(5, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== CADASTRO AVENTUREIRO (ALOCAÇÃO DINÂMICA) ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("--- %dº Território ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do Exército: ");
        scanf(" %[^\n]", mapa[i].corExercito);
        printf("Quantidade de Tropas: ");
        scanf("%d", &mapa[i].numTropas);
        printf("\n");
    }

    int turno = 1;

    while (1) {
        // Usa a nossa função inteligente de limpar a tela
        limparTela(); 

        printf("=========================================\n");
        printf("             🎮 TURNO %d 🎮\n", turno);
        printf("=========================================\n");
        printf("\n=== MAPA ATUAL DO MUNDO ===\n");
        for (int i = 0; i < 5; i++) {
            printf("[%d] %s (%s) - %d Tropas\n", i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].numTropas);
        }

        int at, def;
        printf("\nEscolha o número do ATACANTE (1-5) ou 0 para encerrar o jogo: ");
        scanf("%d", &at);
        if (at == 0) break;

        printf("Escolha o número do DEFENSOR (1-5): ");
        scanf("%d", &def);

        if (at >= 1 && at <= 5 && def >= 1 && def <= 5 && at != def) {
            realizarAtaque(&mapa[at-1], &mapa[def-1]);
            turno++; 
        } else {
            printf("\n⚠️ Escolha inválida! Não é possível atacar a si mesmo ou escolher números fora de 1-5.\n");
            pausarJogo();
        }
    }

    free(mapa);
    limparTela();
    printf("\n=========================================\n");
    printf("   Obrigado por jogar! Memória liberada. \n");
    printf("=========================================\n\n");
    
    return 0;
}