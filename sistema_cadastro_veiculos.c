#include <stdio.h>
#include <string.h>
#define MAXTAM 100
#define MAXSTR 100

typedef struct {
    char modelo[MAXSTR], placa[MAXSTR];
    int ano;
} dados;

int quant = 0;
dados carros[MAXTAM];

void salvarCarros() {
    FILE *arqCarros = fopen("C:/Faculdade/C/PROJETOS/GITHUB/arquivos/carros.txt", "w"); // pode ser alterado o caminho da forma que precisar!
    int i;

    if (arqCarros) {
        for (i = 0; i < quant; i++) {
            fprintf(arqCarros, "Modelo: %s\n", carros[i].modelo);
            fprintf(arqCarros, "Placa: %s\n", carros[i].placa);
            fprintf(arqCarros, "Ano: %d\n\n", carros[i].ano);
        }

        fclose(arqCarros);
    } else {
        printf("ERRO: ERRO: nao foi possivel abrir o arquivo carros.txt");
    }
}

void carregarCarros() {
    FILE *arqCarros = fopen("C:/Faculdade/C/PROJETOS/GITHUB/arquivos/carros.txt", "r");

    if (arqCarros) {
        while (fscanf(arqCarros, "Modelo: %[^\n]\nPlaca: %[^\n]\nAno: %d\n",
                      carros[quant].modelo,
                      carros[quant].placa,
                      &carros[quant].ano) == 3) {
            quant++;
        }
        fclose(arqCarros);
    }
}

int cadastrarCarros() {
    if (quant < MAXTAM) {
        printf("\n--- CADASTRO DE CARROS ---\n");
        printf("\nDigite o modelo: ");
        fgets(carros[quant].modelo, MAXSTR, stdin);
        carros[quant].modelo[strcspn(carros[quant].modelo, "\n")] = '\0';

        printf("\nDigite a placa: ");
        fgets(carros[quant].placa, MAXSTR, stdin);
        carros[quant].placa[strcspn(carros[quant].placa, "\n")] = '\0';

        printf("\nDigite o ano: ");
        scanf("%d", &carros[quant].ano);
        getchar();

        quant++;
        salvarCarros();
        return 1;
    } else {
        printf("\nERRO: vetor esta cheio!");
        return 0;
    }
}

void exibirCarros() {
    int i;

    for (i = 0; i < quant; i++) {
        printf("\nModelo: %s ", carros[i].modelo);
        printf("\nPlaca: %s ", carros[i].placa);
        printf("\nAno: %d \n", carros[i].ano);
    }
}

void buscarPorPlaca() {
    int i;
    char buscPlaca[MAXSTR];

    printf("\nDigite a placa para buscar: ");
    fgets(buscPlaca, MAXSTR, stdin);
    buscPlaca[strcspn(buscPlaca, "\n")] = '\0';

    for (i = 0; i < quant; i++) {
        if (strcmp(carros[i].placa, buscPlaca)== 0) {
            printf("\nModelo: %s ", carros[i].modelo);
            printf("\nPlaca: %s ", carros[i].placa);
            printf("\nAno: %d \n", carros[i].ano);
        }       
    }
}

void removerPorPlaca() {
    int i, j, posicaoRemob = 0;
    char buscPlaca2[MAXSTR];

    printf("\nDigite a placa para apagar: ");
    fgets(buscPlaca2, MAXSTR, stdin);
    buscPlaca2[strcspn(buscPlaca2, "\n")] = '\0';

    for (i = 0; i < quant; i++) {
        if (strcmp(carros[i].placa, buscPlaca2) == 0) {
            posicaoRemob = i;

            for (j = posicaoRemob; j < quant - 1; j++) {
                carros[j] = carros[j + 1];
            }
            quant--;

            printf("\nVeiculo Apagado!\n");
            salvarCarros();
            break;
        }
    }
}

int main() {
    carregarCarros();
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("\n1 - Cadastro carros");
        printf("\n2 - Exibir carros");
        printf("\n3 - Buscar por placa");
        printf("\n4 - Remover por placa");
        printf("\n0 - Sair: ");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                cadastrarCarros();
            break;
        case 2:
                exibirCarros();
            break;
        case 3:
                buscarPorPlaca();
            break;
        case 4:
                removerPorPlaca();
            break;
        case 0:
                printf("\nSaindo...");
            break;
        default:
                printf("\nERRO: opcao invalida!");
            break;
        }

    } while (op != 0);
    



    return 0;
}