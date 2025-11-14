#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CEREAIS_DERIVADOS,
    VERDURAS_HORTALICAS_DERIVADOS,
    FRUTAS_DERIVADOS,
    PESCADOS_FRUTOS_DO_MAR,
    CARNES_DERIVADOS,
    LEITE_DERIVADOS,
    BEBIDAS,
    OVOS_DERIVADOS,
    ALIMENTOS_PREPARADOS,
    LEGUMINOSAS_DERIVADOS,
} Categoria;

typedef struct Alimento Alimento;

struct Alimento {
    int id;
    char descricao[256];
    int energia;
    float proteina;
    Categoria categoria;
    Alimento *proximo;
};

// função que conta quantas linhas tem no arquivo .bin para facilitar alocação
// de memória.
int count_records(FILE *file) {
    int count = 0;
    Alimento temp;

    while (fread(&temp, sizeof(Alimento), 1, file) == 1) {
        count++;
    }

    // volta ao começo do arquivo.
    rewind(file);
    return count;
}

int main() {
    FILE *file = fopen("dados.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir arquivo.");
        return 1;
    }

    int total = count_records(file);

    Alimento *alimentos = (Alimento *)malloc(total * sizeof(Alimento));
    if (alimentos == NULL) {
        printf("Falha no alocamento de memória para a lista encadeada de "
               "alimentos.*");
        exit(1);
    }

    size_t read = fread(alimentos, sizeof(Alimento), total, file);
    printf("Read %zu records\n", read);
    fclose(file);

    for (int i = 0; i < total; i++) {
        printf("ID: %d, Descrição: %s, Energia: %d, Proteína: %.2f, Categoria: "
               "%u\n",
               alimentos[i].id, alimentos[i].descricao, alimentos[i].energia,
               alimentos[i].proteina, alimentos[i].categoria);
    }

    free(alimentos);
    return 0;
}
