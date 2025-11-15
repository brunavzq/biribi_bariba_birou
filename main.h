#define MAX_LINE_LENGTH 1024

typedef struct {
    int numero;
    char descricao[100];
    char categoria[50];
    float energia;
    float proteina;
} Alimento;

typedef struct NodeAlimento {
    Alimento dados;
    struct NodeAlimento *next;
} NodeAlimento;

typedef struct NodeCategoria {
    char nome[50];
    NodeAlimento *alimentos;
    struct NodeCategoria *next;
} NodeCategoria;
