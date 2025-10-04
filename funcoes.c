#include "funcoes.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

Categoria categoria_from_string(const char *str) {
    if (strcmp(str, "Cereais e derivados") == 0)
        return CEREAIS_DERIVADOS;
    if (strcmp(str, "Frutas") == 0)
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

// Converte cada categoria em string.
const char *categoria_to_string(Categoria cat) {
    switch (cat) {
    case CEREAIS_DERIVADOS:
        return "Cereais e derivados";
    case FRUTAS:
        return "Frutas";
    case VERDURAS_HORTALICAS:
        return "Verduras e hortaliças";
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

// Função auxiliar que realiza o print do nosso vetor de structs (alimentos)
// MARCOS: Não mexi pq n sei se já tá funcionando, mas escrito dessa forma
// funciona? acho que a função devia receber um Alimentos vet[] como parâmetro
// tbm e usar no lugar de alimentos[i] pra referenciar o vetor de Alimentos, n
// é?
// void print_tabela(int line_count) {
    // for (int i = 0; i < line_count; i++) {
        // printf("%d | %s | %.1f | %d | %.1f | %.1f | %u\n", alimentos[i].numero,
               // alimentos[i].descricao, alimentos[i].umidade,
               // alimentos[i].energia, alimentos[i].proteina,
               // alimentos[i].carboidrato, alimentos[i].categoria);
    // }
// }

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

// Com base no filtro, cria um vetor auxiliar contendo todos os alimentos que pertençam
// àquela categoria.
Alimento* criar_vetor_filtrado(Alimento vet[], int tamanho_vet, Categoria categoria_escolhida,
                               int *tamanho_filtrado){
    *tamanho_filtrado = tamanho_vetor_filtrado(vet, tamanho_vet, categoria_escolhida);
    
    if(*tamanho_filtrado == 0){
        return NULL;
    }

    Alimento *aux = (Alimento*) malloc((*tamanho_filtrado) * sizeof(Alimento));
    if(aux == NULL){
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
            if(a->umidade < b->umidade) return -1;
            if(a->umidade > b->umidade) return 1;
            return 0;
        case ENERGIA:
            if(a->energia < b->energia) return -1;
            if(a->energia > b->energia) return 1;
            return 0;
        case PROTEINA:
            if(a->proteina < b->proteina) return -1;
            if(a->proteina > b->proteina) return 1;
            return 0;
        case CARBOIDRATO:
            if(a->carboidrato < b->carboidrato) return -1;
            if(a->carboidrato > b->carboidrato) return 1;
            return 0;
        case CATEGORIA:
            if(a->categoria < b->categoria) return -1;
            if(a->categoria > b->categoria) return 1;
            return 0;
    }
    return -2; // se chegar aqui, algo está errado
}


// Troca dois elementos de lugar entre si
void trocarElementos(void *a, void *b, size_t tamanhoElemento){
    char temp[tamanhoElemento];
    memcpy(temp, a, tamanhoElemento);
    memcpy(a, b, tamanhoElemento);
    memcpy(b, temp, tamanhoElemento);
}

// Algoritmo de ordenação genérica.
// Independente do tipo de dado passado, a função ordena
void sortAlg(void *inicio, int tamanhoElemento, int qtdElementos,
             int (*cmp)(const void *, const void *, void *), void *ctx) {
    char *arr = (char *)inicio;

    for (int i = 0; i < qtdElementos - 1; i++) {
        // variável para checar se algum elemento foi trocado de lugar
        int troca = 0;

        for (int j = 0; j < qtdElementos - i - 1; j++) {
            void *elem1 = arr + j * tamanhoElemento;
            void *elem2 = arr + (j + 1) * tamanhoElemento;
            if (cmp(elem1, elem2, ctx) > 0) {
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





