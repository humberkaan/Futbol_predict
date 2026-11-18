# Futbol_predict

Simulador de fútbol. Estima las probabilidades de victoria, empate y derrota al repetir un partido 10,000 veces.



## Cómo funciona

1. En `main`, cada equipo tiene partidos jugados (PJ), goles a favor (GF), goles en contra (GC) y promedio de goles por equipo y partido de su competición (μ).
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

## Ejemplo

Con los datos ilustrativos del código, el equipo A tiene λ = 1.326 y el B tiene λ = 0.990. Con semilla 42, A gana 4,501 de los 10,000 partidos simulados. Su probabilidad estimada es **45.01%**. El empate queda en **27.50%** y la victoria de B en **27.49%**.

## Ejecutar

```sh
cc -std=c11 -Wall -Wextra -Wpedantic simulador.c -lm -o /tmp/futbol-simulador
/tmp/futbol-simulador
```

## Datos de la aplicación

Consulta los CSV de clubes y selecciones, sus campos y fuentes en [datos/](datos/README.md). El ejemplo de C carga sus entradas desde el código.
