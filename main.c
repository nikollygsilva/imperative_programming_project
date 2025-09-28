#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 101
#define MAX_LINE_SIZE 1024

typedef struct {
    int numero_alimento;
    char descricao_alimento[256];
    float umidade;
    int energia;
    float proteina;
    float carboidrato;
    char categoria_alimento[128];
} Alimento;

Alimento alimentos[MAX_LINES];

// Realiza o parsing de cada linha do arquivo
Alimento parse_csv_line(char *line) {
    line[strcspn(line, "\n")] = '\0';

    char *token;
    int field = 0;
    Alimento a;

    token = strtok(line, ";");
    while (token != NULL) {
        switch (field) {
        case 0:
            a.numero_alimento = atoi(token);
            break;
        case 1: {
            // Verifica se começa com aspas. Se sim, pula o primeiro caractere
            // ("), e transforma o último (") em um terminator character.
            if (token[0] == '"') {
                token++;
                token[strlen(token) - 1] = '\0';
            }
            // Se o token for igual o tamanho do buffer aqui, strncpy não iria
            // adicionar o terminator character. Por isso, passamos sizeof - 1 e
            // depois fazemos append manual do '\0'.
            strncpy(a.descricao_alimento, token,
                    sizeof(a.descricao_alimento) - 1);
            a.descricao_alimento[sizeof(a.descricao_alimento) - 1] = '\0';
            break;
        }
        case 2:
            a.umidade = atof(token);
            break;
        case 3:
            a.energia = atoi(token);
            break;
        case 4:
            a.proteina = atof(token);
            break;
        case 5:
            a.carboidrato = atof(token);
            break;
        case 6:
            strncpy(a.categoria_alimento, token, sizeof(a.categoria_alimento));
            break;
        }
        field++;
        token = strtok(NULL, ";");
    }
    return a;
}

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

// Função auxiliar que realiza o print do nosso vetor de structs (alimentos)
void print_tabela(int line_count) {
    for (int i = 0; i < line_count; i++) {
        printf("%d | %s | %.1f | %d | %.1f | %.1f | %s\n",
               alimentos[i].numero_alimento, alimentos[i].descricao_alimento,
               alimentos[i].umidade, alimentos[i].energia,
               alimentos[i].proteina, alimentos[i].carboidrato,
               alimentos[i].categoria_alimento);
    }
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
