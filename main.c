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

    printf("1. listar todas as categorias de alimentos.\n");
    printf("2. *******\n");
    printf("3. ********\n");
    printf("4. *********\n");
    printf("5. *********\n");
    printf("6. *********\n");
    printf("7. *********\n");
    printf("8. *********\n");
    printf("9. *********\n");
    printf("---------------------------------------------\n");



    int selection;
    printf("Digite sua escolha:");
    scanf(" %c", &selection);

    if (!isdigit(selection)) {
        printf("Essa entrada não é um número! Tente novamente!\n");
    }


    if (selection == 1) {

    }
    if (selection == 2) {

    }
    if (selection == 3) {

    }
    if (selection == 4) {

    }
    if (selection == 5) {

    }
    if (selection == 6) {

    }
    if (selection == 7) {

    }
    if (selection == 8) {

    }
    if (selection == 9) {

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
        int choice = menu();}
    return 0;

}


