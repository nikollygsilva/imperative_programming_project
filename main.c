#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //Na teoria, isso será desativado nos outros sistemas operacionais

#define MAX_LINES 101 //
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


typedef enum { //
    CEREAIS_DERIVADOS,
    FRUTAS,
    VERDURAS_HORTALICAS,
    CARNES,
    LATICINIOS,
    LEGUMINOSAS,
    OUTROS,
} Categoria;


typedef struct {
    int numero;
    char descricao[256];
    float umidade;
    int energia;
    float proteina;
    float carboidrato;
    Categoria categoria;
} Alimento;

Alimento alimentos[MAX_LINES];
//------------------------------------------------------------------------------
Categoria categoria_from_string(const char *str) {
    if (strcmp(str, "Cereais e derivados") == 0)
        return CEREAIS_DERIVADOS;
    if (strcmp(str, "Frutas e derivados") == 0)
        return FRUTAS;
    if (strcmp(str, "Verduras e hortaliças") == 0)
        return VERDURAS_HORTALICAS;
    if (strcmp(str, "Carnes e derivados") == 0)
        return CARNES;
    if (strcmp(str, "Leite e derivados") == 0)
        return LATICINIOS;
    if (strcmp(str, "Leguminosas e derivados") == 0)
        return LEGUMINOSAS;
    return OUTROS;
}

const char* categoria_to_string(Categoria c) {
    switch(c) {
        case CEREAIS_DERIVADOS: return "Cereais e derivados";
        case FRUTAS: return "Frutas e derivados";
        case VERDURAS_HORTALICAS: return "Verduras e hortaliças";
        case CARNES: return "Carnes e derivados";
        case LATICINIOS: return "Leite e derivados";
        case LEGUMINOSAS: return "Leguminosas e derivados";
        default: return "Outros";
    }
}
//---------------------------------------------------------------------------------------

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
            a.numero = atoi(token);
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
            strncpy(a.descricao, token, sizeof(a.descricao) - 1);
            a.descricao[sizeof(a.descricao) - 1] = '\0';
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
            a.categoria = categoria_from_string(token);
            break;
        }
        field++;
        token = strtok(NULL, ";");
    }
    return a;
}
//-----------------------------------------------------------------------------------------
void all_categorias(int n) {
    printf("As categorias existentes na ficha são:\n");

    for (int i = 0; i < n; i++) {
        printf("%i - %s\n", alimentos[i].numero, categoria_to_string(alimentos[i].categoria));}}

//Função com o intuito de colocar os iitens em ordem alfabetica.
//-------------------------------------------------------------------------------------------------------
int comparafuncao2(const void *a, const void *b) {
    return strcmp(((Alimento *)a)->descricao, ((Alimento *)b)->descricao);
}

//-----------------------------------------------------------------------------------------------------
void categoriavalidacao(Alimento alimentos[], int line_count, Categoria cat) {
    Alimento selecionados[line_count];
    int count = 0;

    for (int i = 0; i < line_count; i++) {
        if (alimentos[i].categoria == cat) {
            selecionados[count++] = alimentos[i]; // "guarda" o elemento no novo array
            }}

    qsort(selecionados, count, sizeof(Alimento), comparafuncao2);


    printf("Numero do alimento;Descricao do alimento;Umidade (%%);Energia (Kcal);Proteina (g);Carboidrato (g)\n");

    for (int i = 0; i < count; i++) {
        printf("%i,%s,%.2f,%i,%.2f,%.2f\n",
               selecionados[i].numero,
               selecionados[i].descricao,
               selecionados[i].umidade,
               selecionados[i].energia,
               selecionados[i].proteina,
               selecionados[i].carboidrato);
    }
}
//-------------------------------------------------------------------------------------------------------------------------
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

            switch (category[0] ) {

                case '1': categoriavalidacao(alimentos,line_count,CEREAIS_DERIVADOS);break;
                case '2': categoriavalidacao(alimentos,line_count,FRUTAS);break;
                case '3': categoriavalidacao(alimentos,line_count,VERDURAS_HORTALICAS);break;
                case '4': categoriavalidacao(alimentos,line_count,CARNES);break;
                case '5':categoriavalidacao(alimentos,line_count,LATICINIOS);break;
                case '6': categoriavalidacao(alimentos,line_count,LEGUMINOSAS);break;
                case '7':categoriavalidacao(alimentos,line_count,OUTROS);break;

            }
        }

    };

//-----------------------------------------------------------------------------------------


    // Função auxiliar que realiza o print do nosso vetor de structs (alimentos)
    //void print_tabela(int line_count) {
    // for (int i = 0; i < line_count; i++) {
    // printf("%d | %s | %.1f | %d | %.1f | %.1f | %s\n", alimentos[i].numero,
    //  alimentos[i].descricao, alimentos[i].umidade,
    // alimentos[i].energia, alimentos[i].proteina,
    //alimentos[i].carboidrato, alimentos[i].categoria);
    // }
    //}

    // Retorna a quantidade de elementos que o vetor, depois de filtrado com base em
    // uma categoria, terá
    //int tamanho_vetor_filtrado(Alimento vet[], int tamanho_vet,
    // const char *categoria_escolhida) {
    //int count = 0;
    //for (int i = 0; i < tamanho_vet; i++) {
    //if (strcmp(vet[i].categoria, categoria_escolhida) == 0) {
    //count++;
    //}
    // }

    //   return count;
    // }
//----------------------------------------------------------------------------------------------------------------------
    int menu(int line_count) {
        printf("                                        \n");
        printf(
            "===================MENU==========================================\n");
        printf("                                        \n");
        printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
        printf("2. LISTAR TODOS ALIMENTOS DE CATEGORIA ESPECÍFICA\n");
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
                case '1': all_categorias(line_count);
                    break;
                case '2': categoria_usuario(line_count);
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

//-----------------------------------------------------------------------------------------------------------
    int main() {
        SetConsoleOutputCP(CP_UTF8);
        FILE *arquivo = fopen("alimentos.csv", "r");//
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
        } fclose(arquivo);
        plataforma();
    while (control){
        //print_tabela(line_count);
        menu(line_count);}}





