#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int menu() {
    printf("                                        \n");
    printf(
        "===================MENU==========================================\n");
    printf("                                        \n");
    printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
    printf("2. *******\n");
    printf("3. ********\n");
    printf("4. *********\n");
    printf("5. *********\n");
    printf("6. *********\n");
    printf("7. *********\n");
    printf("8. *********\n");
    printf("9. *********\n");
    printf(
        "------------------------------------------------------------------\n");

    char selection[100];
    printf("Digite o número da opção desejada:");
    scanf(" %99s", selection);
    printf("-------------------------------------\n");

    if (strlen(selection) > 1) {
        printf("= Você digitou mais de um caractere! Digite apenas um.\n");
        return 0;
    }

    else if (!isdigit(selection[0])) {
        printf("= Entrada Inválida! Tente novamente!\n");
        return 0;
    } else {
        switch (selection[0]) {
        case '1':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '2':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '3':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '4':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '5':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '6':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '7':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '8':
            printf("Apague esse printf e coloque sua função\n");
            break;
        case '9':
            printf("Apague esse printf e coloque sua função\n");
            break;
        default:
            printf("Opção inválida! Digite uma opção válida");
        }
    }
    return 0;
}


int main() {
    FILE *arquivo = fopen("alimentos.csv", "r");
    if (!arquivo) {
        perror("Erro ao tentar abrir arquivo csv.");
        return 1;
    }

    char line[MAX_LINE_SIZE];
    int line_count = 0;

    // lê e descarta a primeira linha do arquivo (header)
    fgets(line, sizeof(line), arquivo);

    while (fgets(line, sizeof(line), arquivo) && line_count < MAX_LINES) {
        alimentos[line_count] = parse_csv_line(line);
        line_count++;
    }

    fclose(arquivo);
    print_tabela(line_count);

    return 0;
}
