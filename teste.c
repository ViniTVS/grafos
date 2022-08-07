#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void)
{
  vertice v, vizinho;
  grafo g = le_grafo();


  // escreve_grafo(g);
  int n = n_vertices(g);
  printf("Vértices de G: %d \n", n);
  n = n_arestas(g);
  printf("Arestas de G: %d \n", n);

  // para cada nodo, obter seu grau
  for (v = agfstnode(g); v; v = agnxtnode(g, v)){
    n = grau(v, g);
    printf("Grau do vértice %s: %d \n", agnameof(v), n);
  }

  n = grau_maximo(g);
  printf("Maior grau de G: %d \n", n);
  n = grau_minimo(g);
  printf("Menor grau de G: %d \n", n);
  printf("Grau médio de G: %d \n", grau_medio(g));
  n = regular(g);
  printf("G é regular? %d \n", n);
  n = completo(g);
  printf("G é completo? %d \n", n);
  printf("É bipartido? %d \n", bipartido(g));
  printf("Numero de triangulos: %d\n", n_triangulos(g));

  // for (v = agfstnode(g); v; v = agnxtnode(g, v)){
  //   printf("Vizinhos de %s: \n\t", agnameof(v));
  //   for ( vizinho = obtem_vizinho(g, v, NULL); vizinho; vizinho = obtem_vizinho(g, v, vizinho)){
  //     printf("%s\n\t", agnameof(vizinho));
  //   }
  //   printf("\n");
  // }

  int **ma_g = matriz_adjacencia(g);
  grafo g_barra = complemento(g);
  int **ma_g_barra = matriz_adjacencia(g_barra);

  n = n_vertices(g);

  // Imprime matrizes de adjacencia
  printf("Matriz de adjacencia\n");
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++)
      printf("%d ", ma_g[i][j]);
    printf("\n");
  }
  printf("\n");

  // Imprime matrizes de adjacencia
  printf("Matriz de adjacencia - complemento\n");
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++)
      printf("%d ", ma_g_barra[i][j]);
    printf("\n");
  }

  escreve_grafo(g);

  // Libera alocacoes de memoria
  destroi_grafo(g);
  destroi_grafo(g_barra);

  // Libera matrizes
  for (int i = 0; i < n; i++){
    free(ma_g[i]);
    free(ma_g_barra[i]);
  }
  free(ma_g);
  free(ma_g_barra);

  return 0;
}
