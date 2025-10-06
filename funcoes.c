#include "funcoes.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Alimento alimentos[MAX_LINES];
bool control = true;

Categoria obter_categoria_alimento_selecionada() {
    print_categorias(true);
    char categoria_escolhida;

    do {
        puts("");
        printf("Digite o número da categoria que deseja listar: ");

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

    Categoria categoria_alimento_selecionada;
    switch (categoria_escolhida) {
    case '1':
        categoria_alimento_selecionada = CEREAIS_DERIVADOS;
        break;
    case '2':
        categoria_alimento_selecionada = FRUTAS;
        break;
    case '3':
        categoria_alimento_selecionada = VERDURAS_HORTALICAS;
        break;
    case '4':
        categoria_alimento_selecionada = CARNES;
        break;
    case '5':
        categoria_alimento_selecionada = LATICINIOS;
        break;
    case '6':
        categoria_alimento_selecionada = LEGUMINOSAS;
        break;
    case '7':
        categoria_alimento_selecionada = OUTROS;
        break;
    }
    return categoria_alimento_selecionada;
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

int deseja_voltar_menu() {
    if (!control) {
        return 0;
    }

    puts("");
    printf("-------------------------------------\n");

    char selection[2];

    puts("1. VOLTAR AO MENU");
    puts("2. ENCERRAR O PROGRAMA\n");
    printf("Digite a opção desejada: ");
    scanf("%1s", selection);
    printf("-------------------------------------\n");

    if (strlen(selection) > 1) {
        printf("Você digitou mais de um caractere! Digite apenas um.\n");
        return 0;
    } else if (!isdigit(selection[0])) {
        printf("= Entrada Inválida! Tente novamente!\n");
        return 0;
    } else {
        Categoria categoria_alimento_selecionada;
        int tamanho_exibicao;
        switch (selection[0]) {
        case '1':
            return 0;
        case '2':
            puts("Você selecionou a opção 2: ENCERRAR O PROGRAMA.");
            puts("ENCERRANDO O PROGRAMA.");
            control = false;
            return 0;
        default:
            printf("Opção inválida! Digite uma opção válida");
        }
    }
    return 0;
}

int menu() {
    puts("");
    printf("==========================================================="
           "=MENU"
           "==========================================================="
           "=\n");
    puts("");
    printf("1. LISTAR TODAS AS CATEGORIAS DE ALIMENTO.\n");
    printf("2. LISTAR TODOS ALIMENTOS DE CATEGORIA ESPECÍFICA E EM ORDEM "
           "ALFABETICA.\n");
    printf("3. LISTAR TODOS ALIMENTOS DE CATEGORIA E EM ORDEM "
           "DECRESCENTE COM "
           "RESPEITO À CAPACIDADE ENERGETICA DOS ALIMENTOS.\n");
    printf("4. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR "
           "PERCENTUAL DE "
           "UMIDADE.\n");
    printf("5. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR CAPACIDADE "
           "ENERGÉTICA.\n");
    printf("6. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR "
           "QUANTIDADE DE "
           "PROTEÍNA.\n");
    printf("7. LISTAR ALIMENTOS DE CERTA CATEGORIA COM MAIOR "
           "QUANTIDADE DE "
           "CARBOIDRATO.\n");
    printf("8. LISTAR ALIMENTOS DE CERTA CATEGORIA QUE POSSUAM A "
           "RELAÇÃO MAIS "
           "ALTA ENTRE ENERGIA E PROTEÍNA.\n");
    printf("9. LISTAR ALIMENTOS DE CERTA CATEGORIA QUE POSSUAM A "
           "RELAÇÃO MAIS "
           "ALTA ENTRE ENERGIA E CARBOIDRATO.\n");
    printf("0. ENCERRAR O PROGRAMA.\n");
    puts("");
    printf("==========================================================="
           "====="
           "==========================================================="
           "=\n");

    char selection[2];
    printf("Digite o número da opção desejada: ");
    scanf(" %1s", selection);
    printf("-------------------------------------\n");

    if (strlen(selection) > 1) {
        printf("Você digitou mais de um caractere! Digite apenas um.\n");
        return 0;
    } else if (!isdigit(selection[0])) {
        printf("Entrada Inválida! Tente novamente!\n");
        return 0;
    } else {
        Categoria categoria_alimento_selecionada;
        int tamanho_exibicao;
        switch (selection[0]) {
        case '1':
            puts("Você selecionou a opção 1: LISTAR TODAS AS "
                 "CATEGORIAS DE "
                 "ALIMENTO.");
            print_categorias(false);
            break;

        case '2':
            puts("Você selecionou a opção 2: LISTAR TODOS ALIMENTOS DE "
                 "CATEGORIA ESPECÍFICA E EM ORDEM.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 DESCRICAO, 1, -1);
            break;

        case '3':
            puts("Você selecionou a opção 3: LISTAR TODOS ALIMENTOS DE "
                 "CATEGORIA E EM ORDEM DECRESCENTE COM "
                 "RESPEITO À CAPACIDADE ENERGETICA DOS ALIMENTOS.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 ENERGIA, -1, -1);
            break;

        case '4':
            puts("Você selecionou a opção 4: LISTAR ALIMENTOS DE CERTA "
                 "CATEGORIA COM MAIOR PERCENTUAL DE "
                 "UMIDADE.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 UMIDADE, -1, tamanho_exibicao);
            break;

        case '5':
            puts("Você selecionou a opção 5: LISTAR ALIMENTOS DE CERTA "
                 "CATEGORIA COM MAIOR CAPACIDADE "
                 "ENERGÉTICA.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 ENERGIA, -1, tamanho_exibicao);
            break;

        case '6':
            puts("Você selecionou a opção 6: LISTAR ALIMENTOS DE CERTA "
                 "CATEGORIA COM MAIOR QUANTIDADE DE "
                 "PROTEÍNA.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 PROTEINA, -1, tamanho_exibicao);
            break;

        case '7':
            puts("Você selecionou a opção 7: LISTAR ALIMENTOS DE CERTA "
                 "CATEGORIA COM MAIOR QUANTIDADE DE "
                 "CARBOIDRATO.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 CARBOIDRATO, -1, tamanho_exibicao);
            break;

        case '8':
            puts("Você selecionou a opção 8: LISTAR ALIMENTOS DE CERTA "
                 "CATEGORIA QUE POSSUAM A RELAÇÃO MAIS "
                 "ALTA ENTRE ENERGIA E PROTEÍNA.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 REL_ENERGIA_PROTEINA, -1, tamanho_exibicao);
            break;

        case '9':
            puts("Você selecionou a opção 9: LISTAR ALIMENTOS DE CERTA "
                 "CATEGORIA QUE POSSUAM A RELAÇÃO MAIS "
                 "ALTA ENTRE ENERGIA E CARBOIDRATO.");
            categoria_alimento_selecionada =
                obter_categoria_alimento_selecionada();
            tamanho_exibicao = obter_tamanho_vetor_do_usuario();
            print_vetor_filtrado(alimentos, categoria_alimento_selecionada,
                                 REL_ENERGIA_CARBOIDRATO, -1, tamanho_exibicao);
            break;

        case '0':
            puts("Você selecionou a opção 0: ENCERRAR O PROGRAMA.");
            puts("ENCERRANDO O PROGRAMA.");
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
            // Verifica se começa com aspas. Se sim, pula o primeiro
            // caractere
            // ("), e transforma o último (") em um terminator
            // character.
            if (token[0] == '"') {
                token++;
                token[strlen(token) - 1] = '\0';
            }
            // Se o token for igual o tamanho do buffer aqui, strncpy
            // não iria adicionar o terminator character. Por isso,
            // passamos sizeof - 1 e depois fazemos append manual do
            // '\0'.
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

void print_categorias(bool categorias_como_opcao) {
    if (categorias_como_opcao) {
        puts("");
        puts("Verifique abaixo as categorias disponíveis e seus "
             "respectivos "
             "números:\n");
        puts("1. Cereais e derivados");
        puts("2. Frutas e derivados");
        puts("3. Verduras, hortaliças e derivados");
        puts("4. Carnes e derivados");
        puts("5. Leite e derivados");
        puts("6. Leguminosas e derivados");
        puts("7. Outros");
    } else {
        puts("As categorias de alimentos são:\n");
        bool impressos[10] = {false};
        for (int i = 0; i < tamanho_vetor_alimentos; i++) {
            if (!impressos[alimentos[i].categoria]) {
                printf("%s\n", categoria_to_string(alimentos[i].categoria));
                impressos[alimentos[i].categoria] = true;
            }
        }
    }
}

// Retorna a quantidade de elementos que o vetor, depois de filtrado com
// base em uma categoria, terá
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

// Com base no filtro, cria um vetor auxiliar contendo todos os
// alimentos que pertençam àquela categoria.
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
void trocar_elementos(void *a, void *b, int tamanhoElemento) {
    char temp[tamanhoElemento];
    memcpy(temp, a, tamanhoElemento);
    memcpy(a, b, tamanhoElemento);
    memcpy(b, temp, tamanhoElemento);
}

// Algoritmo de ordenação genérica.
// Independente do tipo de dado passado, a função ordena
void bubble_sort_generico(void *inicio, int tamanhoElemento, int qtdElementos,
                          int (*cmp)(const void *, const void *, void *),
                          void *ctx, int ordem) {
    char *arr = (char *)inicio;

    for (int i = 0; i < qtdElementos - 1; i++) {
        int troca = 0;

        for (int j = 0; j < qtdElementos - i - 1; j++) {
            void *elem1 = arr + j * tamanhoElemento;
            void *elem2 = arr + (j + 1) * tamanhoElemento;
            if (ordem * cmp(elem1, elem2, ctx) > 0) {
                trocar_elementos(elem1, elem2, tamanhoElemento);
                troca = 1;
            }
        }
        if (!troca)
            break;
    }
}

// Função que recebe um vetor de Alimento, o tamanho do vetor, uma
// categoria e um campo, e imprime um vetor daquela categoria ordenando
// com base no campo.
void print_vetor_filtrado(Alimento vet[], Categoria cat, Campo campo_ordenacao,
                          int ordem, int tamanho_resultado) {
    int tamanho_filtrado;
    Alimento *aux_alimentos = criar_vetor_filtrado(vet, tamanho_vetor_alimentos,
                                                   cat, &tamanho_filtrado);
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
    bubble_sort_generico(aux_alimentos, sizeof(Alimento), tamanho_resultado,
                         cmp_alimento, &campo, ordem);

    printf("\nLista de alimentos da categoria:\n");
    for (int i = 0; i < tamanho_resultado; i++) {
        printf("Descrição: %s | Umidade: "
               "%.1f | Energia (kcal): %d | Proteína (g): %.1f | Carboidrato "
               "(g): %.1f | "
               "Categoria: %u\n",
               aux_alimentos[i].descricao, aux_alimentos[i].umidade,
               aux_alimentos[i].energia, aux_alimentos[i].proteina,
               aux_alimentos[i].carboidrato, aux_alimentos[i].categoria);
    }

    free(aux_alimentos);
}
