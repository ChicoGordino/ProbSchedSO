#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int num_processos;
    int seed;
    char algoritmo[16];
    int quantum;
    int valido; // 1 = ok, 0 = erro
} Config;

Config carregar_config(const char* nome_ficheiro);

#endif
