#include "funcoes.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //Na teoria, isso será desativado nos outros sistemas operacionais

#define MAX_LINES 101
#define MAX_LINE_SIZE 1024

const bool control= true; //variavel de controle para manter em loop


void plataforma() { //funçao apenas para colocar os comandinhos
#ifdef _WIN32
    // This covers both 32-bit and 64-bit Windows
    printf("Running on Windows!\n");

#elif _linux_
    printf("Running on Linux!\n");
#elif _APPLE_
    printf("Running on macOS!\n");
#else
    printf("Unknown platform!\n");
#endif

}

Alimento alimentos[MAX_LINES];
//------------------------------------------------------------------------------

void all_categorias(int n) {
    printf("As categorias existentes na ficha são:\n");
        bool impressos[10] = {false}; // array para marcar categorias já impressas
    for (int i = 0; i < n; i++) {
            if (!impressos[alimentos[i].categoria]) {
                printf("%s\n", categoria_to_string(alimentos[i].categoria));
                impressos[alimentos[i].categoria] = true;
            }
    }
}

//Função com o intuito de colocar os itens em ordem alfabetica.
int comparafuncao2(const void *a, const void *b) {
    return strcmp(((Alimento *)a)->descricao, ((Alimento *)b)->descricao);
}


void categoriavalidacao(Alimento alimentos[], int line_count, Categoria cat) {
    Alimento selecionados[line_count];
    int count = 0;

    for (int i = 0; i < line_count; i++) {
        if (alimentos[i].categoria == cat) {
            selecionados[count++] = alimentos[i]; // "guarda" o elemento no novo array
            }}

    qsort(selecionados, count, sizeof(Alimento), comparafuncao2);


        printf("Numero do alimento | Descricao do alimento | Umidade (%%) | Energia (Kcal) | Proteina (g) | Carboidrato (g)\n");
    for (int i = 0; i < count; i++) {
        printf("%10i/  %20s | %.2f | %i | %.2f | %.2f\n",
               selecionados[i].numero,
               selecionados[i].descricao,
               selecionados[i].umidade,
               selecionados[i].energia,
               selecionados[i].proteina,
               selecionados[i].carboidrato);
    }
}
int categoria_usuario(int line_count) {
        printf("Categorias\n");
        printf("1- Cereais e derivados\n");
        printf("2- Frutas e derivados\n");
        printf("3- Verduras e hortaliases\n");
        printf("4- Carnes e derivados\n");
        printf("5- Leite e derivados\n");
        printf("6- Leguminosas e derivados\n");
        printf("7- Outros\n");

        char category[100];
        printf("Digite o número da categoria desejada:");
        scanf(" %99s", category);
        printf("-------------------------------------\n");

        if (strlen(category) > 1) {
            printf("= Você digitou mais de um caractere! Digite apenas um.\n");
            return 0;
        }

        else if (!isdigit(category[0])) {
            printf("= Entrada Inválida! Tente novamente!\n");
            return 0;
        }
        else {
            switch (category[0]) {

                case '1': categoriavalidacao(alimentos,line_count,CEREAIS_DERIVADOS);break;
                case '2': categoriavalidacao(alimentos,line_count,FRUTAS);break;
                case '3': categoriavalidacao(alimentos,line_count,VERDURAS_HORTALICAS);break;
                case '4': categoriavalidacao(alimentos,line_count,CARNES);break;
                case '5':categoriavalidacao(alimentos,line_count,LATICINIOS);break;
                case '6': categoriavalidacao(alimentos,line_count,LEGUMINOSAS);break;
                case '7':categoriavalidacao(alimentos,line_count,OUTROS);break;}
        }};


int menu(int line_count) {
    printf("                                        \n");
    printf(
        "===================MENU==========================================\n");
    printf("                                        \n");
    printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
    printf("2. LISTAR TODOS ALIMENTOS DE CATEGORIA ESPECÍFICA E EM ORDEM ALFABETICA\n");
    printf("3. LISTAR TODOS ALIMENTOS DE CATEGORIA E EM ORDEM DECRESCENTE COM RESPEITO À CAPACIDADE ENERGETICAS  DOS ALIMENTOS\n");
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
            case '1': all_categorias(line_count);
                break;
            case '2': categoria_usuario(line_count);
                break;
            case '3': printf("Apague esse printf e coloque sua função\n");
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
    SetConsoleOutputCP(CP_UTF8);
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
    plataforma();
    print_tabela(line_count);
    while (control) {
        menu(line_count);}
}
