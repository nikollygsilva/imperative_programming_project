#include "funcoes.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Alimento alimentos[MAX_LINES];
bool control = true;

Categoria obter_categoria_do_usuario() {
    char categoria_escolhida;

    do {
        puts("Digite o número da categoria desejada: ");
        puts("Para mais informações, digite a opção 1 do menu (digite 0 para "
             "sair)");

        scanf(" %c", &categoria_escolhida);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Limpa o buffer

        if (!isdigit(categoria_escolhida) || categoria_escolhida > '7') {
            printf("\nOpção inválida! Por favor, tente novamente.\n");
        }

    } while (!isdigit(categoria_escolhida) || categoria_escolhida > '7');

    if (categoria_escolhida == '0') {
        return -1;
    }

    Categoria cat_enum;
    switch (categoria_escolhida) {
    case '1':
        cat_enum = CEREAIS_DERIVADOS;
        break;
    case '2':
        cat_enum = FRUTAS;
        break;
    case '3':
        cat_enum = VERDURAS_HORTALICAS;
        break;
    case '4':
        cat_enum = CARNES;
        break;
    case '5':
        cat_enum = LATICINIOS;
        break;
    case '6':
        cat_enum = LEGUMINOSAS;
        break;
    case '7':
        cat_enum = OUTROS;
        break;
    }
    return cat_enum;
}

int obter_tamanho_vetor_do_usuario() {
    puts("Digite o filtro de quantidade de alimentos que deseja que apareça na "
         "exibição:");
    puts("Obs: Em caso de valores negativos ou maiores que a quantidade de "
         "alimentos serão considerados todos os alimentos.");
    int numero_alimentos;
    scanf(" %d", &numero_alimentos);

    return numero_alimentos;
}

int menu(int line_count) {
    printf("                                                                   "
           "                                                             \n");
    printf("===================MENU============================================"
           "===========================================================\n");
    printf("                                        \n");
    printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
    printf("2. LISTAR TODOS ALIMENTOS DE CATEGORIA ESPECÍFICA E EM ORDEM "
           "ALFABETICA.\n");
    printf("3. LISTAR TODOS ALIMENTOS DE CATEGORIA E EM ORDEM DECRESCENTE COM "
           "RESPEITO À CAPACIDADE ENERGETICA DOS ALIMENTOS.\n");
    printf("4. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR PERCENTUAL DE "
           "UMIDADE.\n");
    printf("5. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR CAPACIDADE "
           "ENERGÉTICA.\n");
    printf("6. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR QUANTIDADE DE "
           "PROTEÍNA.\n");
    printf("7. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR QUANTIDADE DE "
           "CARBOIDRATO.\n");
    printf("8. LISTAR ALIMENTOS DE CERTA CATEGORIA QUE POSSUAM A RELAÇÃO MAIS "
           "ALTA ENTRE ENERGIA E PROTEÍNA.\n");
    printf("9. LISTAR ALIMENTOS DE CERTA CATEGORIA QUE POSSUAM A RELAÇÃO MAIS "
           "ALTA ENTRE ENERGIA E CARBOIDRATO.\n");
    printf("0. ENCERRAR O PROGRAMA.\n");
    printf("-------------------------------------------------------------------"
           "-----------------------------------\n");

    char selection[2];
    printf("Digite o número da opção desejada: ");
    scanf(" %1s", selection);
    printf("-------------------------------------\n");

    if (strlen(selection) > 1) {
        printf("= Você digitou mais de um caractere! Digite apenas um.\n");
        return 0;
    } else if (!isdigit(selection[0])) {
        printf("= Entrada Inválida! Tente novamente!\n");
        return 0;
    } else {
        Categoria cat_enum;
        int tamanho_exibicao;
        switch (selection[0]) {
        case '1':
            all_categorias(line_count);
            break;

        case '2':
            cat_enum = obter_categoria_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum, DESCRICAO, 1,
                              -1);
            break;

        case '3':
            cat_enum = obter_categoria_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum, ENERGIA, -1, -1);
            break;

        case '4':
            cat_enum = obter_categoria_do_usuario();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum, UMIDADE, -1,
                              tamanho_exibicao);
            break;

        case '5':
            cat_enum = obter_categoria_do_usuario();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum, ENERGIA, -1,
                              tamanho_exibicao);
            break;

        case '6':
            cat_enum = obter_categoria_do_usuario();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum, PROTEINA, -1,
                              tamanho_exibicao);
            break;

        case '7':
            cat_enum = obter_categoria_do_usuario();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum, CARBOIDRATO, -1,
                              tamanho_exibicao);
            break;

        case '8':
            cat_enum = obter_categoria_do_usuario();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum,
                              REL_ENERGIA_PROTEINA, -1, tamanho_exibicao);
            break;

        case '9':
            cat_enum = obter_categoria_do_usuario();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            imprimirFiltrados(alimentos, line_count, cat_enum,
                              REL_ENERGIA_CARBOIDRATO, -1, tamanho_exibicao);
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

Categoria categoria_from_string(const char *str) {
    if (strcmp(str, "Cereais e derivados") == 0 || strcmp(str, "1") == 0)
        return CEREAIS_DERIVADOS;
    else if (strcmp(str, "Frutas e derivados") == 0 || strcmp(str, "2") == 0)
        return FRUTAS;
    else if (strcmp(str, "Verduras, hortaliças e derivados") == 0 ||
             strcmp(str, "3") == 0)
        return VERDURAS_HORTALICAS;
    else if (strcmp(str, "Carnes e derivados") == 0 || strcmp(str, "4") == 0)
        return CARNES;
    else if (strcmp(str, "Leite e derivados") == 0 || strcmp(str, "5") == 0)
        return LATICINIOS;
    else if (strcmp(str, "Leguminosas e derivados") == 0 ||
             strcmp(str, "6") == 0)
        return LEGUMINOSAS;
    return OUTROS;
}

// Converte cada categoria em string.
const char *categoria_to_string(Categoria cat) {
    switch (cat) {
    case CEREAIS_DERIVADOS:
        return "Cerais e derivados";
    case FRUTAS:
        return "Frutas";
    case VERDURAS_HORTALICAS:
        return "Verduras, hortaliças e derivados";
    case CARNES:
        return "Carnes e derivados";
    case LATICINIOS:
        return "Leite e derivados";
    case LEGUMINOSAS:
        return "Leguminosas e derivados";
    default:
        return "Outros";
    }
}

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

// Função que imprime as strings de diferentes categorias e por meio de uma
// variavel de controle controla se ja foi imprimida para não haver impressão
// duplicada.
void all_categorias(int n) {
    printf("As categorias existentes na ficha são:\n");
    bool impressos[10] = {false};
    for (int i = 0; i < n; i++) {
        if (!impressos[alimentos[i].categoria]) {
            printf("%s\n", categoria_to_string(alimentos[i].categoria));
            impressos[alimentos[i].categoria] = true;
        }
    }
}

// Retorna a quantidade de elementos que o vetor, depois de filtrado com base em
// uma categoria, terá
int tamanho_vetor_filtrado(Alimento vet[], int tamanho_vet,
                           Categoria categoria_escolhida) {
    int count = 0;
    for (int i = 0; i < tamanho_vet; i++) {
        if (vet[i].categoria == categoria_escolhida) {
            count++;
        }
    }

    return count;
}

// Com base no filtro, cria um vetor auxiliar contendo todos os alimentos que
// pertençam àquela categoria.
Alimento *criar_vetor_filtrado(Alimento vet[], int tamanho_vet,
                               Categoria categoria_escolhida,
                               int *tamanho_filtrado) {
    *tamanho_filtrado =
        tamanho_vetor_filtrado(vet, tamanho_vet, categoria_escolhida);

    if (*tamanho_filtrado == 0) {
        return NULL;
    }

    Alimento *aux = (Alimento *)malloc((*tamanho_filtrado) * sizeof(Alimento));
    if (aux == NULL) {
        perror("Falha ao alocar memoria para vetor filtrado");
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < tamanho_vet; i++) {
        if (vet[i].categoria == categoria_escolhida) {
            aux[j] = vet[i];
            j++;
        }
    }

    return aux;
}

int cmp_alimento(const void *pa, const void *pb, void *ctx) {
    const Alimento *a = pa;
    const Alimento *b = pb;
    Campo campo = *(Campo *)ctx;

    switch (campo) {
    case DESCRICAO:
        return strcmp(a->descricao, b->descricao);
    case UMIDADE:
        if (a->umidade < b->umidade)
            return -1;
        if (a->umidade > b->umidade)
            return 1;
        return 0;
    case ENERGIA:
        if (a->energia < b->energia)
            return -1;
        if (a->energia > b->energia)
            return 1;
        return 0;
    case PROTEINA:
        if (a->proteina < b->proteina)
            return -1;
        if (a->proteina > b->proteina)
            return 1;
        return 0;
    case CARBOIDRATO:
        if (a->carboidrato < b->carboidrato)
            return -1;
        if (a->carboidrato > b->carboidrato)
            return 1;
        return 0;
    case CATEGORIA:
        if (a->categoria < b->categoria)
            return -1;
        if (a->categoria > b->categoria)
            return 1;
        return 0;
    case REL_ENERGIA_PROTEINA:
        if (a->energia * a->proteina < b->energia * b->proteina)
            return -1;
        if (a->energia * a->proteina > b->energia * b->proteina)
            return 1;
        return 0;
    case REL_ENERGIA_CARBOIDRATO:
        if (a->energia * a->carboidrato < b->energia * b->carboidrato)
            return -1;
        if (a->energia * a->carboidrato > b->energia * b->carboidrato)
            return 1;
        return 0;
    }
    return -2; // se chegar aqui, algo está errado
}

// Troca dois elementos de lugar entre si
void trocarElementos(void *a, void *b, int tamanhoElemento) {
    char temp[tamanhoElemento];
    memcpy(temp, a, tamanhoElemento);
    memcpy(a, b, tamanhoElemento);
    memcpy(b, temp, tamanhoElemento);
}

// Algoritmo de ordenação genérica.
// Independente do tipo de dado passado, a função ordena
void sortAlg(void *inicio, int tamanhoElemento, int qtdElementos,
             int (*cmp)(const void *, const void *, void *), void *ctx,
             int ordem) {
    char *arr = (char *)inicio;

    for (int i = 0; i < qtdElementos - 1; i++) {
        // variável para checar se algum elemento foi trocado de lugar
        int troca = 0;

        for (int j = 0; j < qtdElementos - i - 1; j++) {
            void *elem1 = arr + j * tamanhoElemento;
            void *elem2 = arr + (j + 1) * tamanhoElemento;
            if (ordem * cmp(elem1, elem2, ctx) > 0) {
                trocarElementos(elem1, elem2, tamanhoElemento);
                troca = 1;
            }
        }
        // se em uma passagem nenhum elemento foi trocado de ordem, então já
        // estava ordenado.
        if (!troca)
            break;
    }
}

// Função que recebe um vetor de Alimento, o tamanho do vetor, uma categoria e
// um campo, e imprime um vetor daquela categoria ordenando com base no campo.
void imprimirFiltrados(Alimento vet[], int tamanho_vet, Categoria cat,
                       Campo campo_ordenacao, int ordem,
                       int tamanho_resultado) {
    int tamanho_filtrado;
    Alimento *aux_alimentos =
        criar_vetor_filtrado(vet, tamanho_vet, cat, &tamanho_filtrado);
    if (aux_alimentos == NULL) {
        printf("Nenhum alimento encontrado na categoria.\n");
        if (aux_alimentos)
            free(aux_alimentos);
        return;
    }

    if (tamanho_resultado < 1) {
        tamanho_resultado = tamanho_filtrado;
    }
    if (tamanho_resultado > tamanho_filtrado) {
        tamanho_resultado = tamanho_filtrado;
    }

    Campo campo = campo_ordenacao;
    sortAlg(aux_alimentos, sizeof(Alimento), tamanho_resultado, cmp_alimento,
            &campo, ordem);

    printf("\nLista de alimentos da categoria:\n");
    for (int i = 0; i < tamanho_resultado; i++) {
        printf("%d | %s | %.1f | %d | %.1f | %.1f | %u\n",
               aux_alimentos[i].numero, aux_alimentos[i].descricao,
               aux_alimentos[i].umidade, aux_alimentos[i].energia,
               aux_alimentos[i].proteina, aux_alimentos[i].carboidrato,
               aux_alimentos[i].categoria);
    }

    free(aux_alimentos);
}
