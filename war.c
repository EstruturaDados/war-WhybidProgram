#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>


// --- Constantes Globais ---
#define Max_Territorio 5
#define TAM_STRING 100

// --- Estrutura de Dados ---
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

//Funcao para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// --- Função para cadastrar territórios ---
void cadastrarTerritorios(struct Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastrando o território %d ---\n", i + 1);
        printf("Nome do território: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército (ex: Azul, Verde): ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// --- Função para exibir todos os territórios ---
void exibirTerritorios(struct Territorio* mapa, int n) {
    printf("\n========== ESTADO ATUAL DO MAPA ==========\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Exército: %s\n", mapa[i].cor);
        printf("- Tropas: %d\n", mapa[i].tropas);
    }
}

// --- Função de ataque entre territórios ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n%s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1; // de 1 a 6
    int dadoDefensor = (rand() % 6) + 1;

    printf(" Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(" O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);        // muda o controle
        defensor->tropas = atacante->tropas / 2;     // metade das tropas do atacante
    } else {
        printf(" O defensor resistiu! O atacante perde uma tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// --- Função para liberar a memória ---
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}


int main(){
    srand(time(NULL)); // inicializa aleatoriedade
    int totalTerritorios;
    
    printf("=================================\n ");
     printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada();

        // Alocação dinâmica
    struct Territorio* mapa = (struct Territorio*) calloc(totalTerritorios, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

 // Cadastro inicial
    cadastrarTerritorios(mapa, totalTerritorios);

    int opcao;
    do {
        printf("\n=================================\n");
        printf("              MENU               \n");
        printf("=================================\n");
        printf("1. Exibir territórios\n");
        printf("2. Realizar ataque\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, totalTerritorios);
                break;

            case 2: {
                exibirTerritorios(mapa, totalTerritorios);
                int iAtacante, iDefensor;

                printf("\nEscolha o número do território atacante: ");
                scanf("%d", &iAtacante);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &iDefensor);
                limparBufferEntrada();

                if (iAtacante < 1 || iAtacante > totalTerritorios ||
                    iDefensor < 1 || iDefensor > totalTerritorios) {
                    printf("Escolha inválida.\n");
                    break;
                }

                if (iAtacante == iDefensor) {
                    printf(" Um território não pode atacar a si mesmo!\n");
                    break;
                }

                if (strcmp(mapa[iAtacante - 1].cor, mapa[iDefensor - 1].cor) == 0) {
                    printf(" Você não pode atacar um território da mesma cor!\n");
                    break;
                }

                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
                printf("\n--- Situação após o ataque ---\n");
                exibirTerritorios(mapa, totalTerritorios);
                break;
            }

            case 3:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 3);

    liberarMemoria(mapa);
    return 0;
}


