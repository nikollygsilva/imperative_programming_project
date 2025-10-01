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

typedef struct {
    int numero;
    char descricao[256];
    float umidade;
    int energia;
    float proteina;
    float carboidrato;
    Categoria categoria;
} Alimento;

Categoria categoria_from_string(const char *str);
const char* categoria_to_string(Categoria cat);
Alimento parse_csv_line(char *line);
void print_tabela(int line_count);
int tamanho_vetor_filtrado(Alimento vet[], int tamanho_vet, Categoria categoria_escolhida);
Alimento* criar_vetor_filtrado(Alimento vet[], int tamanho_vet, Categoria categoria_escolhida, int *tamanho_filtrado);
int cmp_int(const void *a, const void *b);
int cmp_double(const void *a, const void *b);
int cmp_str(const void *a, const void *b);
void trocarElementos(void *a, void *b, size_t tamanhoElemento);
void sortAlg(void *inicio, int tamanhoElemento, int qtdElementos, int (*cmp)(const void *, const void *));

#endif