#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  // escreve_grafo(g);
  int n = n_vertices(g);
  printf("Vértices de g: %d \n", n);
  n = n_arestas(g);
  printf("Arestas de g: %d \n", n);
  destroi_grafo(g);

  return 0;
}
