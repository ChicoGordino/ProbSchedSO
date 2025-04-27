#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config carregarConfig(const char* nome_ficheiro) {
    Config cfg;
    cfg.valido = 0;

    FILE* f = fopen(nome_ficheiro, "r");
    if (!f) {
        perror("Erro ao abrir ficheiro de configuração");
        return cfg;
    }

    char linha[64];
    while (fgets(linha, sizeof(linha), f)) {
        if (strncmp(linha, "processos=", 10) == 0) {
            cfg.numProcessos = atoi(&linha[10]);
        } else if (strncmp(linha, "seed=", 5) == 0) {
            cfg.seed = atoi(&linha[5]);
        } else if (strncmp(linha, "algoritmo=", 10) == 0) {
            sscanf(&linha[10], "%15s", cfg.algoritmo);
        } else if (strncmp(linha, "quantum=", 8) == 0) {
            cfg.quantum = atoi(&linha[8]);
        }
    }

    fclose(f);
    cfg.valido = 1;
    return cfg;
}
