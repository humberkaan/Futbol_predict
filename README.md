# Futbol_predict

Simulador de fútbol. Estima las probabilidades de victoria, empate y derrota al repetir un partido 10,000 veces.



## Cómo funciona

1. Cada equipo tiene partidos jugados (PJ), goles a favor (GF), goles en contra (GC) y promedio de goles por equipo y partido de su competición (μ).
2. El programa calcula los goles esperados (λ) de cada equipo a partir de su ataque y de los goles que suele recibir el rival.
3. Poisson genera un número entero de goles para cada equipo de forma independiente. Monte Carlo repite el partido y cuenta los resultados.

## Ecuaciones

El ajuste de cinco partidos promedio reduce el peso de muestras pequeñas. Un índice de defensa más alto indica que el equipo suele conceder más goles.

```text
Ataque  = (GF + 5 × μ) / [(PJ + 5) × μ]
Defensa = (GC + 5 × μ) / [(PJ + 5) × μ]

λA = 1.35 × ataque A × defensa B
λB = 1.35 × ataque B × defensa A
```

El valor 1.35 es la referencia de goles por equipo que usa el modelo para un campo neutral. Dado λ, la ecuación de Poisson da la probabilidad de anotar exactamente k goles.

$$
P(G=k)=\frac{e^{-\lambda}\lambda^k}{k!}
$$

La probabilidad estimada de cada resultado es su conteo dividido entre el número de simulaciones.

## Significado de las variables

| Símbolo | Significado |
|---|---|
| A, B | Los dos equipos que se enfrentan. |
| PJ | Partidos jugados por el equipo en el período analizado. |
| GF | Total de goles a favor del equipo en esos partidos. |
| GC | Total de goles en contra del equipo en esos partidos. |
| μ | Promedio de goles por equipo y partido en la competición y el período de referencia. Se calcula como goles totales / (2 × partidos). |
| Ataque | Índice de goles anotados respecto a μ. Un valor mayor que 1 indica que el equipo anota por encima del promedio tras el ajuste. |
| Defensa | Índice de goles concedidos respecto a μ. Un valor menor que 1 indica que el equipo concede por debajo del promedio tras el ajuste. |
| λA, λB | Goles esperados de A y B, respectivamente, en el partido simulado. En C son `lambda_a` y `lambda_b`. |
| λ | Goles esperados del equipo al que se aplica Poisson. |
| G | Número de goles anotados por ese equipo en un partido simulado. |
| k | Cantidad exacta de goles cuya probabilidad se calcula, como 0, 1 o 2. |
| P(G = k) | Probabilidad de que el equipo anote exactamente k goles. |
| e | Base del logaritmo natural, aproximadamente 2.71828. En C, `exp(-lambda)` calcula e elevado a −λ. |
| k! | Factorial de k. Por ejemplo, 3! = 3 × 2 × 1 = 6 y 0! = 1. |

El **5** representa el ajuste de cinco partidos promedio. El **1.35** es la referencia de goles por equipo en campo neutral. Ambos valores son supuestos del prototipo.

## Ejemplo

Con los datos ilustrativos del código, el equipo A tiene λ = 1.326 y el B tiene λ = 0.990. Con semilla 42, A gana 4,501 de los 10,000 partidos simulados. Su probabilidad estimada es **45.01%**. El empate queda en **27.50%** y la victoria de B en **27.49%**.

## Ejecutar

```sh
cc -std=c11 -Wall -Wextra -Wpedantic simulador.c -lm -o /tmp/futbol-simulador
/tmp/futbol-simulador
```

## Datos de la aplicación

Consulta los CSV de clubes y selecciones, sus campos y fuentes en [datos/](datos/README.md). El ejemplo de C carga sus entradas desde el código.
