#define _USE_MATH_DEFINES
#include "utils.h"
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double gerar_exponencial(double lambda) {
    double u = rand() / (RAND_MAX + 1.0);
    return -log(1.0 - u) / lambda;
}

double gerar_normal(double media, double desvio) {
    double u1 = rand() / (RAND_MAX + 1.0);
    double u2 = rand() / (RAND_MAX + 1.0);
    double z = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
    return media + desvio * fabs(z);
}

