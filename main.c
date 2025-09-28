#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>

#define MAX_ITENS 101
#define MAX_LINE_LEN 255

const bool control= true; //variavel de controle para manter em loop

typedef struct {
    int numero_alimento;
    char descricao_alimento[50];
    float umidade;
    float energia;
    float proteina;
    float carboidrato;
    char categoria_alimento[30];
} Alimento;

// essa funcao ira lidar com o parsing de cada linha e preencher o struct
void parse_csv_line(const char *line, Alimento *p) {}


    int menu() {
        printf("                                        \n");
        printf("===================MENU==========================================\n");
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
        printf("------------------------------------------------------------------\n");

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
        }
        else {
            switch (selection[0]) {
                case '1': printf("Apague esse printf e coloque sua função\n"); break;
                case '2': printf("Apague esse printf e coloque sua função\n"); break;
                case '3': printf("Apague esse printf e coloque sua função\n"); break;
                case '4': printf("Apague esse printf e coloque sua função\n"); break;
                case '5': printf("Apague esse printf e coloque sua função\n"); break;
                case '6': printf("Apague esse printf e coloque sua função\n"); break;
                case '7': printf("Apague esse printf e coloque sua função\n"); break;
                case '8': printf("Apague esse printf e coloque sua função\n"); break;
                case '9': printf("Apague esse printf e coloque sua função\n"); break;
                    default: printf("Opção inválida! Digite uma opção válida");
            }

        }
    }


int main() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *arquivo = fopen("alimentos.csv", "r");
    if (arquivo == NULL) {
        perror("Erro ao tentar abrir arquivo csv.");
        exit(1);
    }

    Alimento alimentos[MAX_ITENS];
    int line_count = 0;
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), arquivo) && line_count < MAX_ITENS) {
        // para cada linha do arquivo csv, chama nossa funcao de parsing
        parse_csv_line(line, &alimentos[line_count]);
        line_count++;
    }
    fclose(arquivo);

     //

    while (control){
        int choice = menu();
    }
}