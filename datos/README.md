# Bases de partidos

Extractos usados por ERA. Cada fila corresponde a un partido. Los campos son competición y temporada, fecha, equipo local, visitante y goles de cada equipo. Las columnas de localía identifican el partido histórico. El simulador enfrenta equipos en campo neutral.
https://football-data.co.uk/downloadm.php
- [Clubes](clubes.csv) contiene 2,099 partidos de Football-Data. La temporada 2026/27 tiene corte al 2 de noviembre de 2026.
- [Selecciones](selecciones.csv) contiene 124 partidos de StatsBomb Open Data. Los marcadores pueden incluir prórroga y excluyen tandas. Los registros de 1970 y 1986 son muestras parciales.

El programa en C usa datos ilustrativos definidos en `main`. Los CSV documentan los datos de la aplicación web y permiten calcular las entradas de un equipo, que se ingresan manualmente en C. Los datos conservan los términos de sus fuentes.

| Competición y temporada | Partidos | Fuente |
|---|---:|---|
| Premier League 2003/04 | 380 | [Original](https://football-data.co.uk/mmz4281/0304/E0.csv) |
| Premier League 2007/08 | 380 | [Original](https://football-data.co.uk/mmz4281/0708/E0.csv) |
| Premier League 2026/27 | 90 | [Original](https://football-data.co.uk/mmz4281/2627/E0.csv) |
| La Liga 2008/09 | 380 | [Original](https://football-data.co.uk/mmz4281/0809/SP1.csv) |
| La Liga 2010/11 | 380 | [Original](https://football-data.co.uk/mmz4281/1011/SP1.csv) |
| La Liga 2016/17 | 380 | [Original](https://football-data.co.uk/mmz4281/1617/SP1.csv) |
| La Liga 2026/27 | 109 | [Original](https://football-data.co.uk/mmz4281/2627/SP1.csv) |
| Mundial 1970 | 6 | [Original](https://github.com/hudl/open-data/blob/master/data/matches/43/272.json) |
| Mundial 1986 | 3 | [Original](https://github.com/hudl/open-data/blob/master/data/matches/43/54.json) |
| Mundial 2022 | 64 | [Original](https://github.com/hudl/open-data/blob/master/data/matches/43/106.json) |
| Eurocopa 2024 | 51 | [Original](https://github.com/hudl/open-data/blob/master/data/matches/55/282.json) |
