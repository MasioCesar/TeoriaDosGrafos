# TeoriaDosGrafos
Este projeto é uma implementação de diversos algoritmos fundamentais da Teoria dos Grafos.

## Aluno

- Másio César de Carvalho Moraes

## Algoritmos

**Dijkstra:** Este algoritmo encontra o caminho mais curto entre dois vértices em um grafo ponderado.

**Prim:** O algoritmo de Prim encontra a árvore geradora mínima em um grafo ponderado.

**Kruskal:** O algoritmo de Kruskal também encontra a árvore geradora mínima em um grafo ponderado, mas através de uma abordagem diferente da de Prim.

**Kosaraju:** O algoritmo de Kosaraju é utilizado para encontrar componentes fortemente conexos em um grafo direcionado.

**Floyd-Warshall:** Este algoritmo encontra todos os caminhos mínimos entre todos os pares de vértices em um grafo ponderado.

## Compilar o código
Para compilar o código, basta executar o comando make no diretório do algoritmo. Isso criará o arquivo executável .bin.

## Sobre o Floyd-Warshall
As entradas testadas estão no diretório **Floyd–Warshall/casosTestes/**;

**O output dos casosTestes são feitos considerando que o usuário não informou nenhum vértice.**

## Formato de Entrada e saída
A saída será apresentada no formato "vértice:valor", indicando o valor da distância mínima até aquele vértice partindo do vértice inicial especificado pelo comando -i.

Se nenhum vértice for informado pelo comando -i, a saída conterá o caminho mínimo de todos os vértices para todos os outros vértices no formato "vértice:valor".

Agora, vamos executar o algoritmo de Floyd-Warshall com o vértice inicial sendo 1. O comando seria algo como:
```bash
./warshall.bin -f casosTestes/casoTeste1.mtx -i 1
```
A saída será a distância mínima de 1 para todos os outros vértices. Por exemplo:
```bash
1:0 2:29 3:36 4:28 5:14 6:26 7:29 8:34 9:37 10:18 11:30 12:27 13:39 14:12 15:24 16:30 17:28 18:36 19:29 20:31 21:30 22:22 23:25 24:27 25:30 26:29 27:34 28:25
```




