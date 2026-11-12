/* Simulacion Monte Carlo de goles con distribucion de Poisson.
   Ejemplo ilustrativo: las entradas no son estadisticas de un equipo real. */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SIMULACIONES 10000
#define AJUSTE 5.0
#define PROMEDIO_NEUTRAL 1.35

typedef struct {
    const char *nombre;
    int partidos, goles_favor, goles_contra;
    double promedio_competicion; /* goles por equipo y partido */
} Equipo;

/* Generador reproducible xorshift32; estado inicial distinto de cero. */
static uint32_t estado = 42;
static double uniforme(void) {
    estado ^= estado << 13;
    estado ^= estado >> 17;
    estado ^= estado << 5;
    return ((double)estado + 0.5) / 4294967296.0;
}

/* Algoritmo de Knuth para Poisson. Adecuado para tasas bajas de goles. */
static int poisson(double lambda) {
    double limite = exp(-lambda), producto = 1.0;
    int k = 0;
    do {
        ++k;
        producto *= uniforme();
    } while (producto > limite);
    return k - 1;
}

static double ataque(Equipo e) {
    return (e.goles_favor + AJUSTE * e.promedio_competicion)
         / (e.partidos + AJUSTE) / e.promedio_competicion;
}

/* Un indice defensivo alto significa que el equipo recibe mas goles. */
static double defensa(Equipo e) {
    return (e.goles_contra + AJUSTE * e.promedio_competicion)
         / (e.partidos + AJUSTE) / e.promedio_competicion;
}

static int valido(Equipo e) {
    return e.partidos > 0 && e.goles_favor >= 0 && e.goles_contra >= 0
        && isfinite(e.promedio_competicion) && e.promedio_competicion > 0;
}

int main(void) {
    /* Cambia estas entradas por datos del mismo periodo de cada equipo. */
    Equipo a = {"Equipo A", 10, 18, 9, 1.5};
    Equipo b = {"Equipo B", 10, 15, 12, 1.5};
    if (!valido(a) || !valido(b)) {
        fprintf(stderr, "Datos de equipos invalidos.\n");
        return 1;
    }

    double lambda_a = PROMEDIO_NEUTRAL * ataque(a) * defensa(b);
    double lambda_b = PROMEDIO_NEUTRAL * ataque(b) * defensa(a);
    if (!isfinite(lambda_a) || !isfinite(lambda_b)
        || lambda_a < 0 || lambda_b < 0 || lambda_a > 100 || lambda_b > 100) {
        fprintf(stderr, "Tasas fuera del rango del simulador.\n");
        return 1;
    }
    int victorias_a = 0, empates = 0, victorias_b = 0;
    long goles_a = 0, goles_b = 0;
    for (int i = 0; i < SIMULACIONES; ++i) {
        int ga = poisson(lambda_a);
        int gb = poisson(lambda_b);
        goles_a += ga;
        goles_b += gb;
        if (ga > gb) ++victorias_a;
        else if (ga < gb) ++victorias_b;
        else ++empates;
    }

    printf("%s vs %s\n", a.nombre, b.nombre);
    printf("Goles esperados: A = %.4f; B = %.4f\n", lambda_a, lambda_b);
    printf("Simulaciones: %d; semilla: 42\n", SIMULACIONES);
    printf("Victoria A: %d (%.2f%%)\n", victorias_a, 100.0 * victorias_a / SIMULACIONES);
    printf("Empate:     %d (%.2f%%)\n", empates, 100.0 * empates / SIMULACIONES);
    printf("Victoria B: %d (%.2f%%)\n", victorias_b, 100.0 * victorias_b / SIMULACIONES);
    printf("Media de goles simulada: A = %.4f; B = %.4f\n",
           (double)goles_a / SIMULACIONES, (double)goles_b / SIMULACIONES);
    return 0;
}
