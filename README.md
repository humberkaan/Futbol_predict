# Futbol_predict

Simulador de fútbol. Estima las probabilidades de victoria, empate y derrota al repetir un partido 10,000 veces.



## Cómo funciona

1. Cada equipo tiene partidos jugados (PJ), goles a favor (GF), goles en contra (GC) y promedio de goles por equipo y partido de su competición (μ).
2. El programa calcula los goles esperados (λ) de cada equipo a partir de su ataque y de los goles que suele recibir el rival.
3. Poisson genera un número entero de goles para cada equipo de forma independiente. Monte Carlo repite el partido y cuenta los resultados.

## Ecuaciones

### 1. Ataque y defensa de cada equipo

```text
Ataque  = (GF + 5 × μ) / [(PJ + 5) × μ]
Defensa = (GC + 5 × μ) / [(PJ + 5) × μ]
```

| Variable | Qué significa |
|---|---|
| PJ | Partidos que jugó el equipo en el período analizado. |
| GF y GC | Goles que el equipo anotó (GF) y recibió (GC) en esos partidos. |
| μ | Promedio de goles por equipo y partido en esa competición. Se dividen los goles totales de la competición entre el doble del número de partidos, porque en cada partido participan dos equipos. |
| 5 | Peso del ajuste. El modelo añade el equivalente a cinco partidos con rendimiento promedio para reducir el peso de muestras pequeñas. |
| Ataque y Defensa | Índices respecto al promedio de la competición. Un ataque de 1.20 significa que el equipo anota un 20 % más que el promedio tras el ajuste. Una defensa de 0.80 significa que recibe un 20 % menos. |

### 2. Goles esperados en el enfrentamiento

```text
λA = 1.35 × ataque A × defensa B
λB = 1.35 × ataque B × defensa A
```

- **A y B** son los equipos que se enfrentan. Para estimar los goles de A se combinan el ataque de A y la defensa de B. Para B se invierten los papeles.
- **1.35** es el promedio de goles por equipo que el prototipo toma como referencia para un partido en campo neutral.
- **λA y λB** son los goles que el modelo espera que anote cada equipo en ese cruce. En el código se llaman `lambda_a` y `lambda_b`.

### 3. Probabilidad de anotar una cantidad exacta de goles

$$
P(G=k)=\frac{e^{-\lambda}\lambda^k}{k!}
$$

- **G** representa cuántos goles anota el equipo. **k** es la cantidad que queremos evaluar. Por ejemplo, **P(G = 2)** es la probabilidad de que anote exactamente dos goles.
- **λ** es el valor del paso anterior para el equipo elegido, **λA** o **λB**.
- **e** es la base del logaritmo natural, aproximadamente 2.71828. **k!** es el factorial de k. Por ejemplo, 3! = 3 × 2 × 1 = 6 y 0! = 1.

### 4. Probabilidad de victoria o empate con Monte Carlo

```text
Porcentaje estimado del resultado = 100 × n / N
```

- **n** es el número de simulaciones en las que ocurrió el resultado elegido (victoria de A, empate o victoria de B).
- **N** es el total de partidos simulados. El programa usa 10,000.

## Ejemplo

Con los datos ilustrativos del código, el equipo A tiene λ = 1.326 y el B tiene λ = 0.990. Con semilla 42, A gana 4,501 de los 10,000 partidos simulados. Su probabilidad estimada es **45.01%**. El empate queda en **27.50%** y la victoria de B en **27.49%**.

## Ejecutar

```sh
cc -std=c11 -Wall -Wextra -Wpedantic simulador.c -lm -o /tmp/futbol-simulador
/tmp/futbol-simulador
```

## Datos de la aplicación

Consulta los CSV de clubes y selecciones, sus campos y fuentes en [datos/](datos/README.md). El ejemplo de C carga sus entradas desde el código.
