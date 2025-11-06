#include <stdio.h>
#include <string.h> 

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

int main(){
    struct Territorio territorios[Max_Territorio];
    int totalTerritorios = 0;
    
    printf("=================================\n ");
    printf("Vamos cadastrar os 5 terrritorios inicias do nosso mundo\n ");

  for (totalTerritorios = 0; totalTerritorios < Max_Territorio; totalTerritorios++) 
  {
    printf("\n--- Cadastrando o território %d ---\n", totalTerritorios + 1);
    printf("Nome do território: ");
    fgets(territorios[totalTerritorios].nome, TAM_STRING, stdin);
    printf("Cor do exército (ex: Azul, Verde): ");
    fgets(territorios[totalTerritorios].cor, TAM_STRING, stdin);

    territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';
    territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

    printf("Número de tropas: ");
    scanf("%d", &territorios[totalTerritorios].tropas);
    limparBufferEntrada();
}


    printf("Cadastro incial concluido com sucesso\n");
    printf("==============================================\n");
    printf("       MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("==============================================\n");

 for (int i = 0; i < Max_Territorio; i++) {
    printf("\n-------------------------------------\n");
    printf("Território %d\n", i + 1);
    printf("- Nome: %s\n", territorios[i].nome);
    printf("- Dominado por: Exército %s\n", territorios[i].cor);
    printf("- Tropas: %d\n", territorios[i].tropas);
}

    return 0;
}

