#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>

#define MAX_LINES 101
#define MAX_LINE_SIZE 1024

typedef enum {
    CEREAIS_DERIVADOS,
    FRUTAS,
    VERDURAS_HORTALICAS,
    CARNES,
    LATICINIOS,
    LEGUMINOSAS,
    OUTROS,
} Categoria;

typedef enum {
    DESCRICAO,
    UMIDADE,
    ENERGIA,
    PROTEINA,
    CARBOIDRATO,
    CATEGORIA
} Campo;

typedef struct {
    int numero;
    char descricao[256];
    float umidade;
    int energia;
    float proteina;
    float carboidrato;
    Categoria categoria;
} Alimento;

extern Alimento alimentos[MAX_LINES];

Categoria categoria_from_string(const char *str);
const char *categoria_to_string(Categoria cat);
Alimento parse_csv_line(char *line);

void all_categorias(int n);

int tamanho_vetor_filtrado(Alimento vet[], int tamanho_vet, Categoria categoria_escolhida);
Alimento *criar_vetor_filtrado(Alimento vet[], int tamanho_vet, Categoria categoria_escolhida, int *tamanho_filtrado);

int cmp_alimento(const void *pa, const void *pb, void *ctx);
void trocarElementos(void *a, void *b, size_t tamanhoElemento);
void sortAlg(void *inicio, int tamanhoElemento, int qtdElementos, int (*cmp)(const void *, const void *, void *), void *ctx, int ordem);

void imprimirFiltrados(Alimento vet[], int tamanho_vet, Categoria cat, Campo campo_ordenacao, int ordem, int tamanho_resultado);

#endif