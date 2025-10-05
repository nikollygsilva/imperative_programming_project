#include "funcoes.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


Categoria categoria_from_string(const char *str) {
    if (strcmp(str, "Cereais e derivados") == 0 || strcmp(str, "1") == 0)
        return CEREAIS_DERIVADOS;
    else if (strcmp(str, "Frutas e derivados") == 0 || strcmp(str, "2") == 0)
        return FRUTAS;
    else if (strcmp(str, "Verduras, hortaliças e derivados") == 0 || strcmp(str, "3") == 0)
        return VERDURAS_HORTALICAS;
    else if (strcmp(str, "Carnes e derivados") == 0 || strcmp(str, "4") == 0)
        return CARNES;
    else if (strcmp(str, "Leite e derivados") == 0 || strcmp(str, "5") == 0)
        return LATICINIOS;
    else if (strcmp(str, "Leguminosas e derivados") == 0 || strcmp(str, "6") == 0)
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


// Função que imprime as strings de diferentes categorias e por meio de uma variavel de controle controla se ja foi imprimida para não haver impressão duplicada.
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
    *tamanho_filtrado = tamanho_vetor_filtrado(vet, tamanho_vet, categoria_escolhida);

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
    }
    return -2; // se chegar aqui, algo está errado
}


// Troca dois elementos de lugar entre si
void trocarElementos(void *a, void *b, size_t tamanhoElemento) {
    char temp[tamanhoElemento];
    memcpy(temp, a, tamanhoElemento);
    memcpy(a, b, tamanhoElemento);
    memcpy(b, temp, tamanhoElemento);
}


// Algoritmo de ordenação genérica.
// Independente do tipo de dado passado, a função ordena
void sortAlg(void *inicio, int tamanhoElemento, int qtdElementos,
             int (*cmp)(const void *, const void *, void *), void *ctx, int ordem) {
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


// Função que recebe um vetor de Alimento, o tamanho do vetor, uma categoria e um campo,
// e imprime um vetor daquela categoria ordenando com base no campo.
void imprimirFiltrados(Alimento vet[], int tamanho_vet, Categoria cat, Campo campo_ordenacao, int ordem, int tamanho_resultado){
    int tamanho_filtrado;
    Alimento *aux_alimentos = criar_vetor_filtrado(vet, tamanho_vet, cat, &tamanho_filtrado);
    if (aux_alimentos == NULL) {
        printf("Nenhum alimento encontrado na categoria.\n");
        if (aux_alimentos) free(aux_alimentos);
        return;
    }

    if(tamanho_resultado == -1){
        tamanho_resultado = tamanho_filtrado;
    }
    if(tamanho_resultado > tamanho_filtrado){
        tamanho_resultado = tamanho_filtrado;
    }

    Campo campo = campo_ordenacao;
    sortAlg(aux_alimentos, sizeof(Alimento), tamanho_resultado, cmp_alimento, &campo, ordem);

    printf("\nLista de alimentos da categoria:\n");
    for(int i = 0; i < tamanho_resultado; i++){
        printf("%d | %s | %.1f | %d | %.1f | %.1f | %u\n", aux_alimentos[i].numero,
        aux_alimentos[i].descricao, aux_alimentos[i].umidade,
        aux_alimentos[i].energia, aux_alimentos[i].proteina,
        aux_alimentos[i].carboidrato, aux_alimentos[i].categoria);
    }

    free(aux_alimentos);
}
