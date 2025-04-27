#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int numProcessos;
    int seed;
    char algoritmo[16];
    int quantum;
    int valido; 
} Config;

Config carregarConfig(const char* nome_ficheiro);

#endif
