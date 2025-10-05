#include "funcoes.h"
#include <stdio.h>

int main() {
#ifdef _WIN32
#include <windows.h>
    SetConsoleOutputCP(CP_UTF8);
#endif

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

    while (control) {
        menu(line_count);
    }
}
