#include "funcoes.h"
#include <stdio.h>

int tamanho_vetor_alimentos = 0;

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

    // Lê e descarta a primeira linha do arquivo (header)
    fgets(line, sizeof(line), arquivo);

    while (fgets(line, sizeof(line), arquivo) &&
           tamanho_vetor_alimentos < MAX_LINES) {
        alimentos[tamanho_vetor_alimentos] = parse_csv_line(line);
        tamanho_vetor_alimentos++;
    }

    fclose(arquivo);

    while (control) {
        menu();
        deseja_voltar_menu();
    }
}
