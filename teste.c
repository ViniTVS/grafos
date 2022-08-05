#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void)
{

  grafo g = le_grafo();

  // escreve_grafo(g);
  int n = n_vertices(g);
  printf("Vértices de G: %d \n", n);
  n = n_arestas(g);
  printf("Arestas de G: %d \n", n);
  destroi_grafo(g);
  vertice v;
  // para cada nodo, obter seu grau
  for (v = agfstnode(g); v; v = agnxtnode(g, v)){
    n = grau(v, g);
    printf("Grau do vértice %s: %d \n", agnameof(v), n);
  }

  n = grau_maximo(g);
  printf("Maior grau de G: %d \n", n);
  n = grau_minimo(g);
  printf("Menor grau de G: %d \n", n);
  float m = grau_medio(g);
  printf("Grau médio de G: %f \n", m);
  n = regular(g);
  printf("G é regular? %d \n", n);
  n = completo(g);
  printf("G é completo? %d \n", n);

  return 0;
}
