#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 101
#define MAX_LINE_LEN 255

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

int main() {
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

    return 0;
}
