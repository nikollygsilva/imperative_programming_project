#include "funcoes.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //Na teoria, isso será desativado nos outros sistemas operacionais

#define MAX_LINES 101
#define MAX_LINE_SIZE 1024

bool control = true; //variavel de controle para manter em loop

Alimento alimentos[MAX_LINES];

void plataforma() { // função para tudo funcionar corretamente em cada plataforma
#ifdef _WIN32
    // Cobre tanto Windows 32 bits quanto 64 bits.
    printf("Running on Windows!\n");
#elif _linux_
    printf("Running on Linux!\n");
#elif _APPLE_
    printf("Running on macOS!\n");
#else
    printf("Unknown platform!\n");
#endif
}

Categoria obter_categoria_do_usuario() {
    char categoria_escolhida;
    
    do {
        puts("Digite o número da categoria desejada.");
        puts("Para mais informações, digite a opção 1 do menu (digite 0 para sair)");

        scanf(" %c", &categoria_escolhida);
        int c;
        while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer

        if (!isdigit(categoria_escolhida) || categoria_escolhida > '7') {
            printf("\nOpção inválida! Por favor, tente novamente.\n");
        }

    } while (!isdigit(categoria_escolhida) || categoria_escolhida > '7');
    
    if (categoria_escolhida == '0') {
        return -1;
    }

    Categoria cat_enum;
    switch (categoria_escolhida) {
        case '1': cat_enum = CEREAIS_DERIVADOS; break;
        case '2': cat_enum = FRUTAS; break;
        case '3': cat_enum = VERDURAS_HORTALICAS; break;
        case '4': cat_enum = CARNES; break;
        case '5': cat_enum = LATICINIOS; break;
        case '6': cat_enum = LEGUMINOSAS; break;
        case '7': cat_enum = OUTROS; break;
    }
    return cat_enum;
}

int obter_tamanho_vetor_do_usuario(){
    puts("Digite o filtro de quantidade de alimentos que deseja que apareça na exibição:");
    puts("Obs: Em caso de valores negativos ou maiores que a quantidade de alimentos serão considerados todos os alimentos.");
    int numero_alimentos;
    scanf(" %d", &numero_alimentos);

    return numero_alimentos;
}

int menu(int line_count) {
    printf("                                                                                                                                \n");
    printf("===================MENU=======================================================================================================\n");
    printf("                                        \n");
    printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
    printf("2. LISTAR TODOS ALIMENTOS DE CATEGORIA ESPECÍFICA E EM ORDEM ALFABETICA.\n");
    printf("3. LISTAR TODOS ALIMENTOS DE CATEGORIA E EM ORDEM DECRESCENTE COM RESPEITO À CAPACIDADE ENERGETICA DOS ALIMENTOS.\n");
    printf("4. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR PERCENTUAL DE UMIDADE.\n");
    printf("5. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR CAPACIDADE ENERGÉTICA.\n");
    printf("6. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR QUANTIDADE DE PROTEÍNA.\n");
    printf("7. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR QUANTIDADE DE CARBOIDRATO.\n");
    printf("8. LISTAR ALIMENTOS DE CERTA CATEGORIA QUE POSSUAM A RELAÇÃO MAIS ALTA ENTRE ENERGIA E PROTEÍNA.\n");
    printf("9. LISTAR ALIMENTOS DE CERTA CATEGORIA QUE POSSUAM A RELAÇÃO MAIS ALTA ENTRE ENERGIA E CARBOIDRATO.\n");
    printf("0. ENCERRAR O PROGRAMA.\n");
    printf(
        "------------------------------------------------------------------------------------------------------\n");

    char selection[2];
    printf("Digite o número da opção desejada:");
    scanf(" %1s", selection);
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
        Categoria cat_enum;
        int tamanho_exibicao;
        switch (selection[0]) {
            case '1':
                all_categorias(line_count);
                break;

            case '2':
                cat_enum = obter_categoria_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, DESCRICAO, 1, -1);
                break;

            case '3':
                cat_enum = obter_categoria_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, ENERGIA, -1, -1);
                break;

            case '4':
                cat_enum = obter_categoria_do_usuario();
                tamanho_exibicao = obter_tamanho_vetor_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, UMIDADE, -1, tamanho_exibicao);
                break;

            case '5':
                cat_enum = obter_categoria_do_usuario();
                tamanho_exibicao = obter_tamanho_vetor_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, ENERGIA, -1, tamanho_exibicao);
                break;

            case '6':
                cat_enum = obter_categoria_do_usuario();
                tamanho_exibicao = obter_tamanho_vetor_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, PROTEINA, -1, tamanho_exibicao);
                break;

            case '7':
                cat_enum = obter_categoria_do_usuario();
                tamanho_exibicao = obter_tamanho_vetor_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, CARBOIDRATO, -1, tamanho_exibicao);
                break;

            case '8':
                cat_enum = obter_categoria_do_usuario();
                tamanho_exibicao = obter_tamanho_vetor_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, REL_ENERGIA_PROTEINA, -1, tamanho_exibicao);
                break;

            case '9':
                cat_enum = obter_categoria_do_usuario();
                tamanho_exibicao = obter_tamanho_vetor_do_usuario();
                imprimirFiltrados(alimentos, line_count, cat_enum, REL_ENERGIA_CARBOIDRATO, -1, tamanho_exibicao);
                break;

            case '0':
                printf("ENCERRANDO O PROGRAMA.");
                control = false;
                return 0;
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
    
    while (control) {
        menu(line_count);
    }
}
