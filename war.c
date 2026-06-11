#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MISSAO_CONQUISTAR_3 1
#define MISSAO_DESTRUIR_VERDE 2

struct Territorio {
    char nome[50];
    char corExercito[30];
    int numTropas;
};

struct Jogador {
    char cor[30];
    int tipoMissao;
};

void pausarJogo() {
    printf("\nPressione ENTER para continuar...");
    getchar(); 
    getchar(); 
}

void limparTela() {
    if (system("cls") != 0) {
        system("clear");
    }
}

void inicializarMapa(struct Territorio * const mapa) {
    struct Territorio mapaInicial[5] = {
        {"Brasil", "Vermelho", 4},
        {"Argentina", "Verde", 3},
        {"Egito", "Vermelho", 2},
        {"Moscou", "Verde", 3},
        {"China", "Amarelo", 5}
    };
    for (int i = 0; i < 5; i++) {
        mapa[i] = mapaInicial[i];
    }
}

void sortearMissao(struct Jogador *j) {
    struct Jogador temp = {"Vermelho", (rand() % 2) + 1};
    *j = temp;
}

void exibirMissao(const struct Jogador *j) {
    printf("\n=========================================\n");
    printf("🎯 SUA MISSÃO ATUAL:\n");
    printf("=========================================\n");
    if (j->tipoMissao == MISSAO_CONQUISTAR_3) {
        printf("-> Conquistar pelo menos 3 territórios para o exército %s.\n", j->cor);
    } else if (j->tipoMissao == MISSAO_DESTRUIR_VERDE) {
        printf("-> Destruir totalmente o exército Verde do mapa!\n");
    }
    printf("=========================================\n");
}

void exibirMapa(const struct Territorio * const mapa, int tam) {
    printf("\n=== MAPA ATUAL DO MUNDO ===\n");
    for (int i = 0; i < tam; i++) {
        printf("[%d] %s (%s) - %d Tropas\n", i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].numTropas);
    }
    printf("===========================\n");
}

int verificarVitoria(const struct Territorio * const mapa, int tam, const struct Jogador *j) {
    if (j->tipoMissao == MISSAO_CONQUISTAR_3) {
        int contagem = 0;
        for (int i = 0; i < tam; i++) {
            if (strcmp(mapa[i].corExercito, j->cor) == 0) {
                contagem++;
            }
        }
        return (contagem >= 3); 
    } 
    if (j->tipoMissao == MISSAO_DESTRUIR_VERDE) {
        for (int i = 0; i < tam; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0) {
                return 0; 
            }
        }
        return 1; 
    }
    return 0;
}

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
    printf("📊 SALDO DE TROPAS:\n");
    printf("-> %s: %d tropas restantes\n", atacante->nome, atacante->numTropas);
    printf("-> %s: %d tropas restantes\n", defensor->nome, defensor->numTropas);

    if (defensor->numTropas <= 0) {
        printf("\n🚩 !!! TERRITÓRIO CONQUISTADO !!!\n");
        printf("O exército %s dominou %s!\n", atacante->corExercito, defensor->nome);
        
        for (int i = 0; i < 30; i++) {
            defensor->corExercito[i] = atacante->corExercito[i];
            if (atacante->corExercito[i] == '\0') {
                break; 
            }
        }
        defensor->numTropas = 1; 
    }
    printf("=========================================\n");
    pausarJogo();
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    struct Territorio *mapa = (struct Territorio *) calloc(5, sizeof(struct Territorio));
    struct Jogador jogadorHumano;

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarMapa(mapa);
    sortearMissao(&jogadorHumano);

    int opcao = -1;

    while (opcao != 0) {
        limparTela();
        printf("=========================================\n");
        printf("         ⚔️  WAR: NÍVEL MESTRE  ⚔️\n");
        printf("=========================================\n");
        exibirMapa(mapa, 5);
        
        printf("\nMENU PRINCIPAL:\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair do Jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                int at, def;
                printf("\nEscolha o número do ATACANTE (1-5): ");
                scanf("%d", &at);
                printf("Escolha o número do DEFENSOR (1-5): ");
                scanf("%d", &def);

                if (at >= 1 && at <= 5 && def >= 1 && def <= 5 && at != def) {
                    realizarAtaque(&mapa[at-1], &mapa[def-1]);
                } else {
                    printf("\n⚠️ Escolha inválida! Verifique os números digitados.\n");
                    pausarJogo();
                }
                break;
            }
            case 2:
                limparTela();
                exibirMissao(&jogadorHumano);
                
                if (verificarVitoria(mapa, 5, &jogadorHumano)) {
                    printf("\n🎉 PARABÉNS! VOCÊ CUMPRIU A SUA MISSÃO E GANHOU O JOGO! 🎉\n\n");
                    opcao = 0; 
                } else {
                    printf("\nA missão ainda não foi cumprida. Continue lutando!\n");
                }
                pausarJogo();
                break;
                
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
                
            default:
                printf("\n⚠️ Opção inválida!\n");
                pausarJogo();
                break;
        }
    }

    free(mapa);
    limparTela();
    printf("\n=========================================\n");
    printf("   Jogo finalizado. Memória liberada!   \n");
    printf("=========================================\n\n");
    
    return 0;
}
