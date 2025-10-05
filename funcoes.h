#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h>
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

typedef enum {
    DESCRICAO,
    UMIDADE,
    ENERGIA,
    PROTEINA,
    CARBOIDRATO,
    CATEGORIA,
    REL_ENERGIA_PROTEINA,
    REL_ENERGIA_CARBOIDRATO
} Campo;

extern Alimento alimentos[MAX_LINES];
extern bool control; // Variável de controle para manter em loop
extern int tamanho_vetor_alimentos;

// Essa função recebe um ponteiro para uma string que contém uma linha inteira
// do arquivo csv. Ela quebra essa string em tokens (um ponteiro para cada
// pedaço da string após divisão), e preenche e retorna um struct Alimento com
// os dados preenchidos vindo do csv.
Alimento parse_csv_line(char *line);
Categoria categoria_from_string(const char *str);

const char *categoria_to_string(Categoria cat);

// Função que imprime todas as categorias.
void print_categorias(bool categorias_como_opcao);

int tamanho_vetor_filtrado(Alimento vet[], int tamanho_vet,
                           Categoria categoria_escolhida);

Alimento *criar_vetor_filtrado(Alimento vet[], int tamanho_vet,
                               Categoria categoria_escolhida,
                               int *tamanho_filtrado);

int cmp_alimento(const void *pa, const void *pb, void *ctx);

void trocar_elementos(void *a, void *b, int tamanhoElemento);

void bubble_sort_generico(void *inicio, int tamanhoElemento, int qtdElementos,
                          int (*cmp)(const void *, const void *, void *),
                          void *ctx, int ordem);

void print_vetor_filtrado(Alimento vet[], Categoria cat, Campo campo_ordenacao,
                          int ordem, int tamanho_resultado);

Categoria obter_categoria_alimento_selecionada();
int obter_tamanho_vetor_do_usuario();
int deseja_voltar_menu();
int menu();

#endif
