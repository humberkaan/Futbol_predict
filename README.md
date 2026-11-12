# Futbol_predict

Primera entrega: código en C para simular un partido de fútbol con Monte Carlo y una distribución de Poisson. No incluye página web ni requiere conexión a una API.

## Compilar y ejecutar

Con GCC o Clang:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic simulador.c -lm -o simulador
./simulador
```

## Datos de entrada

Modifica los equipos `a` y `b` dentro de `main`: nombre, partidos jugados, goles a favor, goles en contra y promedio de goles **por equipo y partido** de su competición. Los datos incluidos son **ilustrativos**, no corresponden a equipos reales. El promedio de competición se obtiene dividiendo sus goles totales entre dos veces el número de partidos.

## Cálculo

1. Se suavizan las medias con 5 partidos equivalentes al promedio de la competición.
2. Ataque = `(goles_favor + 5 * promedio) / (partidos + 5) / promedio`.
3. Defensa = `(goles_contra + 5 * promedio) / (partidos + 5) / promedio`.
4. Goles esperados A = `1.35 * ataque_A * defensa_B`; para B se intercambian los equipos.
5. Poisson genera los goles de cada equipo de forma independiente. Monte Carlo repite el partido 10,000 veces.
6. Probabilidad estimada = número de resultados del tipo buscado / número de simulaciones.

El ajuste de 5 partidos y la referencia neutral de 1.35 son supuestos del prototipo, no parámetros calibrados. La semilla fija permite reproducir el experimento; este código usa xorshift32. Los resultados concretos pueden diferir de implementaciones con otro generador aleatorio.

## Alcance

Es un modelo académico exploratorio. No corrige diferencias de nivel entre ligas o épocas, lesiones, plantillas ni calidad de rivales. Más simulaciones reducen el error de Monte Carlo, pero no garantizan mejores predicciones. Para incorporar datos reales se pueden consultar los CSV de [Football-Data](https://football-data.co.uk/downloadm.php); esta primera entrega no los descarga.
